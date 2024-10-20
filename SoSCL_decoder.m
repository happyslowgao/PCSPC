function [x_esti, llr_R]= SoSCL_decoder(llr, L_path, K, frozen_bits, lambda_offset, llr_layer_vec, bit_layer_vec)
N = length(llr);
n = log2(N);
L=zeros(N,(n+1)*L_path);
R=zeros(N,(n+1)*L_path);
for i=1:L_path
    L(:,1+(n+1)*(i-1))=llr';
    R(:,(n+1)*i)=frozen_bits'.*realmax;
end
C = zeros(N - 1, 2 * L_path);%每条路径P是7个
u = zeros(K, L_path);%存放译码，就是非冻结比特 unfrozen bits that polar codes carry, including crc bits.
PM = zeros(L_path, 1);%Path metrics
activepath = zeros(L_path, 1);%Indicate if the path is active. '1'→active; '0' otherwise.
cnt_u = 1;%information bit counter 
%initialize
activepath(1) = 1;
complexity=0;
for phi = 0 : N - 1
    layer = llr_layer_vec(phi + 1);
    phi_mod_2 = mod(phi, 2);
    for l_index = 1 : L_path
        if activepath(l_index) == 0
            continue;
        end
        switch phi%Decoding bits u_0 and u_N/2 needs channel LLR, so the decoding of them is separated from other bits. 
            case 0
                for i_layer = n-1 : -1 : 0
                    index_1 = lambda_offset(i_layer + 1);
                    for beta = 1: index_1  
%                         L(beta,n-i_layer+1+(n+1)*(l_index-1)) = f(L(beta,n-i_layer+(n+1)*(l_index-1)),L(beta+index_1,n-i_layer+(n+1)*(l_index-1))+R(beta+index_1,n-i_layer+1+(n+1)*(l_index-1)));
                        L(beta,n-i_layer+1+(n+1)*(l_index-1)) = f(L(beta,n-i_layer+(n+1)*(l_index-1)),L(beta+index_1,n-i_layer+(n+1)*(l_index-1)));
                        complexity=complexity+5;
                    end
                end
            otherwise
                %向左运算
                %在奇数位group的L更新
                llr_layer = llr_layer_vec(phi + 1);
                index_1 = lambda_offset(llr_layer + 1);%一个节点包含的节点数
                index_2 = lambda_offset(llr_layer + 2);
                group=fix(phi/2^(llr_layer));
                group_right=fix(group/2);
                i_layer=llr_layer; 
                for beta = 0 : index_1 - 1
                     L(beta+1+group*index_1,n-i_layer+1+(n+1)*(l_index-1))=(1 - 2 * C(beta+index_1, 2 * l_index - 1))*L( beta+1+group_right*index_2,n-i_layer+(n+1)*(l_index-1))+L(beta+1+group*index_1,n-i_layer+(n+1)*(l_index-1));
                     complexity=complexity+3;
%                     L(beta+1+group*index_1,n-i_layer+1)=f(L( beta+1+group_right*index_2,n-i_layer),R(beta+1+group*index_1-index_1,n-i_layer+1))+L(beta+1+group*index_1,n-i_layer);
                end
                %在偶数位group的更新
                group=fix(phi/2^(llr_layer-1));
                group_right=fix(group/2);
                for i_layer = llr_layer - 1 : -1 : 0
                     index_1 = lambda_offset(i_layer + 1);
                     index_2 = lambda_offset(i_layer + 2);
                     group=fix(phi/2^(i_layer));
                     group_right=fix(group/2);
                     for beta = 0 : index_1 - 1
%                          L(beta+1+group*index_1,n-i_layer+1+(n+1)*(l_index-1))=f(L(beta+1+group_right*index_2,n-i_layer+(n+1)*(l_index-1)),L(beta+1+group_right*index_2+index_1,n-i_layer+(n+1)*(l_index-1))+R(beta+1+group_right*index_2+index_1,n-i_layer+1+(n+1)*(l_index-1)));
                         L(beta+1+group*index_1,n-i_layer+1+(n+1)*(l_index-1))=f(L(beta+1+group_right*index_2,n-i_layer+(n+1)*(l_index-1)),L(beta+1+group_right*index_2+index_1,n-i_layer+(n+1)*(l_index-1)));
                         complexity=complexity+5;
                     end
                end
                %向右运算
                phi_mod_2 = mod(phi, 2);
                if phi_mod_2  == 1 %&& phi ~= N - 1
                    bit_layer = bit_layer_vec(phi + 1);
                    group=phi;
                    group_right=fix((group-1)/2);
                    for i_layer = 0 : bit_layer 
                        index_1 = lambda_offset(i_layer + 1);
                        index_2 = lambda_offset(i_layer + 2);
                        for beta = 0 : index_1 - 1
                            R(beta+1+group_right*index_2,n-i_layer+(n+1)*(l_index-1))=f(R(beta+1+group_right*index_2,n-i_layer+1+(n+1)*(l_index-1)),R(beta+1+group_right*index_2+index_1,n-i_layer+1+(n+1)*(l_index-1))+L(beta+1+group_right*index_2+index_1,n-i_layer+(n+1)*(l_index-1)));
                            R(beta+1+group_right*index_2+index_1,n-i_layer+(n+1)*(l_index-1))=f(L(beta+1+group_right*index_2,n-i_layer+(n+1)*(l_index-1)),R(beta+1+group_right*index_2,n-i_layer+1+(n+1)*(l_index-1)))+R(beta+1+group_right*index_2+index_1,n-i_layer+1+(n+1)*(l_index-1));
                            complexity=complexity+10;
                        end
                        group=group_right;
                        group_right=fix((group-1)/2);
                    end
                end
        end
    end
    if frozen_bits(phi + 1) == 0%if now we decode an unfrozen bit
        PM_pair = realmax * ones(2, L_path);
        for l_index = 1 : L_path
            if activepath(l_index) == 0
                continue;
            end
            if L(phi+1,(n+1)*l_index) >= 0
                PM_pair(1, l_index) = PM(l_index);
                PM_pair(2, l_index) = PM(l_index) + L(phi+1,(n+1)*l_index);%P(1, l_index)
            else
                PM_pair(1, l_index) = PM(l_index) - L(phi+1,(n+1)*l_index);
                PM_pair(2, l_index) = PM(l_index);
            end
        end
        middle = min(2 * sum(activepath), L_path);
        PM_sort = sort(PM_pair(:));
        PM_cv = PM_sort(middle);
%         number=find(PM_pair==PM_cv);
%         number=number(2:length(number));
%         PM_pair(number)=PM_cv+1;
        compare = PM_pair <= PM_cv; 
        kill_index = zeros(L_path, 1);%to record the index of the path that is killed
        kill_cnt = 0;%the total number of killed path
        %the above two variables consist of a stack
        for i = 1 : L_path
            if (compare(1, i) == 0)&&(compare(2, i) == 0)%which indicates that this path should be killed
                activepath(i) = 0;
                kill_cnt = kill_cnt + 1;%push stack
                kill_index(kill_cnt) = i;
            end
        end
        for l_index = 1 : L_path
            if activepath(l_index) == 0
                continue;
            end
            path_state = compare(1, l_index) * 2 + compare(2, l_index);
            switch path_state%path_state can equal to 0, but in this case we do no operation.
                case 1
                    u(cnt_u, l_index) = 1;
                    x(phi+1,l_index)=1;
                    C(1, 2 * l_index - 1 + phi_mod_2) = 1;
                    PM(l_index) = PM_pair(2, l_index);
                case 2
                    u(cnt_u, l_index) = 0;
                    x(phi+1,l_index)=0;
                    C(1, 2 * l_index - 1 + phi_mod_2) = 0;
                    PM(l_index) = PM_pair(1, l_index);
                case 3
                    index = kill_index(kill_cnt);
                    kill_cnt = kill_cnt - 1;%pop stack
                    activepath(index) = 1;
                    L(:,1+(n+1)*(index-1):(n+1)*index)=L(:,1+(n+1)*(l_index-1):(n+1)*l_index);
                    R(:,1+(n+1)*(index-1):(n+1)*index)=R(:,1+(n+1)*(l_index-1):(n+1)*l_index);
%                     P(:, index) = P(:, l_index);
                    C(:, 2*index-1) = C(:, 2*l_index-1);
                    C(:, 2*index) = C(:, 2*l_index);
                    u(:, index) = u(:, l_index);
                    x(:,index)=x(:,l_index);
                    u(cnt_u, l_index) = 0;
                    u(cnt_u, index) = 1;
                    x(phi+1,l_index)=0;
                    x(phi+1,index)=1;
                    C(1, 2 * l_index - 1 + phi_mod_2) = 0;
                    C(1, 2 * index - 1 + phi_mod_2) = 1;
                    PM(l_index) = PM_pair(1, l_index);
                    PM(index) = PM_pair(2, l_index);
            end
        end
        cnt_u = cnt_u + 1;
    else%frozen bit operation
        for l_index = 1 : L_path
            if activepath(l_index) == 0
                continue;
            end
            x(phi+1,l_index)=0;
            if L(phi+1,(n+1)*l_index) < 0
                PM(l_index) = PM(l_index) - L(phi+1,(n+1)*l_index);
            end
            if phi_mod_2 == 0
                C(1, 2 * l_index - 1) = 0;
                complexity=complexity+1;
            else
                C(1, 2 * l_index) = 0;
                complexity=complexity+1;
            end 
        end
    end 
    
    for l_index = 1 : L_path%partial-sum return
        if activepath(l_index) == 0
            continue
        end
        if (phi_mod_2  == 1) && (phi ~= N - 1)
            layer = bit_layer_vec(phi + 1);
            for i_layer = 0 : layer - 1
                index_1 = lambda_offset(i_layer + 1);
                index_2 = lambda_offset(i_layer + 2);
                for beta = index_1 : 2 * index_1 - 1
                    C(beta + index_1, 2 * l_index) = mod(C(beta, 2 * l_index-1) + C(beta, 2 * l_index), 2);
                    C(beta + index_2, 2 * l_index) = C(beta, 2 * l_index);   
                    complexity=complexity+2;
                end
            end
            index_1 = lambda_offset(layer + 1);
            index_2 = lambda_offset(layer + 2);
            for beta = index_1 : 2 * index_1 - 1
                C(beta + index_1, 2 * l_index - 1) = mod(C(beta, 2 * l_index-1) + C(beta, 2 * l_index), 2);
                C(beta + index_2, 2 * l_index - 1) = C(beta, 2 * l_index);
                complexity=complexity+2;
            end 
        end
    end
end
%path selection.
[~, path_ordered] = sort(PM);%对PM进行排序
path_num = path_ordered(1);%取排序最小的那个在原来PM数组中占第几列
% decoder = u(:, path_num);
x_esti=x(:,path_num);
% PM_normal=PM./sum(PM);
% PM_normal=1./PM_normal;
% PM_normal=PM_normal/sum(PM_normal);
w=1./exp(PM);
PM_normal=w./sum(w);
llr_R=zeros(N,1);
% for i=1:L_path
%     if PM(path_num)==0
%         llr_R=R(:,1+(n+1)*(path_num-1));
%     else
%         llr_R=llr_R+PM_normal(i)*R(:,1+(n+1)*(i-1));
%     end
% end
for i=1:N
    fenzi=0;
    fenmu=0;
    for l=1:L_path
        if R(i,1+(n+1)*(l-1))>35.9 
            R(i,1+(n+1)*(l-1))=35.9;
        elseif R(i,1+(n+1)*(l-1))<-35.9
                R(i,1+(n+1)*(l-1))=-35.9;
        end
%             fenzi1=fenzi1+PM_normal(l)*exp(R(i,1+(n+1)*(l-1)))/(1+exp(R(i,1+(n+1)*(l-1))));
%             fenmu1=fenmu1+PM_normal(l)/(1+exp(R(i,1+(n+1)*(l-1))));
            fenzi=fenzi+PM_normal(l)*real(1+tanh(R(i,1+(n+1)*(l-1))/2));
            fenmu=fenmu+PM_normal(l)*real(1-tanh(R(i,1+(n+1)*(l-1))/2));
    end
    llr_R(i)=log(fenzi/fenmu);
end
info_bits=find(frozen_bits==0);
llr_R=llr_R(info_bits);
end