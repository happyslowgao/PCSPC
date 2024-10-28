function [x_esti, llr_R]= SCLBP_decoder(llr, L, K, frozen_bits, lambda_offset, llr_layer_vec, bit_layer_vec,M_right_up,M_right_down)
N = length(llr);
m = log2(N);
P = zeros(N, m*L); %每条路径P是N*n个
C = zeros(N - 1, 2 * L);%每条路径P是7个
u = zeros(K, L);%存放译码，就是非冻结比特 unfrozen bits that polar codes carry, including crc bits.
PM = zeros(L, 1);%Path metrics
activepath = zeros(L, 1);%Indicate if the path is active. '1'→active; '0' otherwise.
cnt_u = 1;%information bit counter 
%initialize
activepath(1) = 1;
complexity=0;
for phi = 0 : N - 1
    layer = llr_layer_vec(phi + 1);
    phi_mod_2 = mod(phi, 2);
    for l_index = 1 : L
        if activepath(l_index) == 0
            continue;
        end
        switch phi%Decoding bits u_0 and u_N/2 needs channel LLR, so the decoding of them is separated from other bits. 
            case 0
                index_1 = lambda_offset(m);
                for beta = 0 : index_1 - 1
                    P(beta + 1 , 1+(l_index-1)*m) = 0.9375*sign(llr(beta + 1)) * sign(llr(beta + index_1 + 1)) * min(abs(llr(beta + 1)), abs(llr(beta + index_1 + 1)));
                    complexity=complexity+5;
                end
                for i_layer = m - 2 : -1 : 0
                    index_1 = lambda_offset(i_layer + 1);
                    index_2 = lambda_offset(i_layer + 2);
                    for beta = 0 : index_1 - 1
                        P(beta + 1, m-i_layer+(l_index-1)*m) = 0.9375*sign(P(beta + 1, m-i_layer+(l_index-1)*m - 1)) *...
                            sign(P(beta + 1 + index_1, m-i_layer+(l_index-1)*m - 1)) * min(abs(P(beta + 1, m-i_layer+(l_index-1)*m - 1)), abs(P(beta + 1 + index_1, m-i_layer+(l_index-1)*m - 1)));
                        complexity=complexity+5;
                    end
                end
            case N/2
                index_1 = lambda_offset(m);
                i_layer=m-1;
                for beta = 0 : index_1 - 1
                    x_tmp = C(beta + index_1, 2 * l_index - 1);
                    P(beta+1+index_1, m-i_layer+(l_index-1)*m) = (1 - 2 * x_tmp) * llr(beta + 1) + llr(beta + 1 + index_1);
                    complexity=complexity+3;
                end
                for i_layer = m - 2 : -1 : 0
                    index_1 = lambda_offset(i_layer + 1);
                    index_2 = lambda_offset(i_layer + 2);
                    group=fix(phi/2^(i_layer));
                    group_right=fix(group/2);
                    for beta = 0 : index_1 - 1
                        P(beta+1+group*index_1, m-i_layer+(l_index-1)*m) = 0.9375*sign(P(beta+1+group*index_1, m-i_layer+(l_index-1)*m-1)) *...
                            sign(P(beta+1+group*index_1+index_1, m-i_layer+(l_index-1)*m-1)) * min(abs(P(beta+1+group*index_1, m-i_layer+(l_index-1)*m-1)), abs(P(beta+1+group*index_1+index_1, m-i_layer+(l_index-1)*m-1)));
                        complexity=complexity+5;
                    end
                end
            otherwise
                llr_layer = llr_layer_vec(phi + 1);
                index_1 = lambda_offset(layer + 1);
                index_2 = lambda_offset(layer + 2);
                group=fix(phi/2^(llr_layer));
                i_layer=llr_layer;
                for beta = 0 : index_1 - 1
                    P(beta+1+group*index_1, m-i_layer+(l_index-1)*m) = (1 - 2 * C(beta + index_1, 2 * l_index - 1)) * P(beta+1+group*index_1-index_1, m-i_layer+(l_index-1)*m-1) +...
                        P(beta+1+group*index_1, m-i_layer+(l_index-1)*m-1);
                    complexity=complexity+3;
                end
                for i_layer = llr_layer - 1 : -1 : 0
                    index_1 = lambda_offset(i_layer + 1);
                    index_2 = lambda_offset(i_layer + 2);
                    group=fix(phi/2^(i_layer));
                    group_right=fix(group/2);
                    for beta = 0 : index_1 - 1
                        P(beta+1+group*index_1, m-i_layer+(l_index-1)*m) = 0.9375*sign(P(beta+1+group*index_1, m-i_layer+(l_index-1)*m-1)) *...
                            sign(P(beta+1+group*index_1+index_1, m-i_layer+(l_index-1)*m-1)) * min(abs(P(beta+1+group*index_1, m-i_layer+(l_index-1)*m-1)),...
                            abs(P(beta+1+group*index_1+index_1, m-i_layer+(l_index-1)*m-1)));
                        complexity=complexity+5;
                    end
                end
        end
    end
    if frozen_bits(phi + 1) == 0%if now we decode an unfrozen bit
        PM_pair = realmax * ones(2, L);
        for l_index = 1 : L
            if activepath(l_index) == 0
                continue;
            end
            if P(phi+1, m*l_index) >= 0
                PM_pair(1, l_index) = PM(l_index);
                PM_pair(2, l_index) = PM(l_index) + P(phi+1, m*l_index);
            else
                PM_pair(1, l_index) = PM(l_index) - P(phi+1, m*l_index);
                PM_pair(2, l_index) = PM(l_index);
            end
        end
        middle = min(2 * sum(activepath), L);
        PM_sort = sort(PM_pair(:));
        PM_cv = PM_sort(middle);
        compare = PM_pair <= PM_cv; 
        kill_index = zeros(L, 1);%to record the index of the path that is killed
        kill_cnt = 0;%the total number of killed path
        %the above two variables consist of a stack
        for i = 1 : L
            if (compare(1, i) == 0)&&(compare(2, i) == 0)%which indicates that this path should be killed
                activepath(i) = 0;
                kill_cnt = kill_cnt + 1;%push stack
                kill_index(kill_cnt) = i;
            end
        end
        for l_index = 1 : L
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
                    P(:, 1+(index-1)*m:m*index) = P(:, 1+(l_index-1)*m:m*l_index);
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
        for l_index = 1 : L
            if activepath(l_index) == 0
                continue;
            end
            x(phi+1,l_index)=0;
            if P(phi+1, m*l_index) < 0
                PM(l_index) = PM(l_index) - P(phi+1, m*l_index);
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
    
    for l_index = 1 : L%partial-sum return
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
%BP-right prop
R = zeros(N, m + 1);
R(:,1)=frozen_bits'.*realmax;
L=P(:,1+(path_num-1)*m:path_num*m);
L=fliplr(L);
L(:, m + 1) = llr;
    for j = 1 : m
        for i = 1 : N/2
            up_index = M_right_up(i, j);
            down_index = M_right_down(i, j);
            R_up_j = R(up_index, j);
            R_down_j = R(down_index, j);
            L_up_j_plus_1 = L(up_index, j + 1);
            L_down_j_plus_1 = L(down_index, j + 1);
            R(up_index, j + 1) = 0.9375 * sign(R_down_j + L_down_j_plus_1) * sign(R_up_j) * min(abs(R_down_j + L_down_j_plus_1), abs(R_up_j));
            R(down_index, j + 1) = 0.9375 * sign(R_up_j) * sign(L_up_j_plus_1) * min(abs(R_up_j), abs(L_up_j_plus_1)) + R_down_j;
            complexity=complexity+10;
        end
    end
info_bits=find(frozen_bits==0);
llr_R=R(info_bits,m+1);
x2_esti=polar_encoder(x_esti, lambda_offset, llr_layer_vec);
polar_info_esti_inter=x2_esti(info_bits);
for i_code=1:K
    llr_bf=polar_info_esti_inter(i_code)-sign(llr_R(i_code));
    if llr_bf==1||llr_bf==0
       llr_R(i_code)=-llr_R(i_code);
    end
end
end