function [bler, ber] = simulationBPSK(N, K, design_epsilon, max_runs, max_err, resolution, ebno_vec, list_size_vec, crc_length)
%effective rate of concatenated codes
R = (K - crc_length)/N;

%codes parameters to avoid redundant calcularions
lambda_offset = 2.^(0 : log2(N));
llr_layer_vec = get_llr_layer(N);
bit_layer_vec = get_bit_layer(N);


%Self-made CRC check
% [G_crc, H_crc] = crc_generator_matrix(g, K - crc_length);
% crc_parity_check = G_crc(:, K - crc_length + 1 : end)';

%Bhattacharyya Code (BEC) Construction
% channels = get_BEC_IWi(N, 1 - design_epsilon);
% [~, channel_ordered] = sort(channels, 'descend');
% info_bits = sort(channel_ordered(1 : K), 'ascend');
% frozen_bits = ones(N , 1);
% frozen_bits(info_bits) = 0;
% info_bits_logical = logical(mod(frozen_bits + 1, 2));
% search_index = get_search_index(info_bits, K, log2(N))

%Gaussian approximation Code Construction
design_snr = 2.5;
sigma_cc = 1/sqrt(2 * R) * 10^(-design_snr/20);
[channels, ~] = GA(sigma_cc, N);
[~, channel_ordered] = sort(channels, 'descend');
info_bits = sort(channel_ordered(1 : K), 'ascend');
frozen_number=sort(channel_ordered(K+1 : N), 'ascend');
frozen_bits = ones(N , 1);
frozen_bits(info_bits) = 0;
info_bits_logical = logical(mod(frozen_bits + 1, 2));

%beta expansion
% beta = sqrt(sqrt(2));
% channels = beta_expansion_polar_code_construction(N, beta);
% [~, channel_ordered] = sort(channels, 'descend');
% info_bits = sort(channel_ordered(1 : K));
% frozen_bits = ones(N , 1);
% frozen_bits(info_bits) = 0;

%Special nodes
node_type_matrix = get_node_structure(frozen_bits);

%indices for BP decoding
[M_up, M_down] = index_Matrix(N);

%Results Stored
bler = zeros(length(ebno_vec), length(list_size_vec));
ber = zeros(length(ebno_vec), length(list_size_vec));
num_runs = zeros(length(ebno_vec), length(list_size_vec));
% ber = 0;
%Loop starts
tic
% profile on

for i_run = 1 : max_runs
    if  mod(i_run, max_runs/resolution) == 1
        disp(' ');
        disp(['Sim iteration running = ' num2str(i_run)]);
        disp(['N = ' num2str(N) ' K = ' num2str(K)]);
        disp(['List size = ' num2str(list_size_vec)]);
        disp('The first column is the Eb/N0');
        disp('The second column is the BLER of SCL.');
        disp('The remaining columns are the BLERs of SCAN you desired');
        disp(num2str([ebno_vec'  bler./num_runs ber./(num_runs*K)]));
        disp(' ')
    end
    %To avoid redundancy
    info  = rand(K - crc_length, 1) > 0.5;
    u1 = zeros(N, 1);
    u2 = zeros(N, 1);
    %SPC
    u1(info_bits_logical) = info;
    x1 = polar_encoder(u1, lambda_offset, llr_layer_vec);
    x1(frozen_number)=0;
    x1=polar_encoder(x1, lambda_offset, llr_layer_vec);
    x1_Ac=x1(frozen_number);
    interleaver=randperm(K);
    u2(info_bits_logical) = info(interleaver);
    x2 = polar_encoder(u2, lambda_offset, llr_layer_vec);
    x2(frozen_number)=0;
    x2=polar_encoder(x2', lambda_offset, llr_layer_vec);
    x2_Ac=x2(frozen_number);
    x=[info;x1_Ac;x2_Ac];
    bpsk = 1 - 2 * x;
    noise = (randn(2*N-K,1));
%     noise=zeros(2*N-K,1);
    prev_decoded = zeros(length(ebno_vec), length(list_size_vec));
    %%
    for i_ebno = 1 : length(ebno_vec)
        sigma = 1/sqrt(2 * R) * 10^(-ebno_vec(i_ebno)/20);
        y_noise = bpsk + noise*sigma;
        for i_list = 2 : length(list_size_vec)
            if i_list ~= 1
                if bler(i_ebno, i_list) == max_err
                    continue;
                end
            else
                if all(bler(i_ebno, 2 : end) == max_err)
                    continue
                end
            end
            num_runs(i_ebno, i_list) = num_runs(i_ebno, i_list) + 1;
            run_sim = 1;
            for i_ebno2 = 1 : i_ebno
                for i_list2 = 1 : i_list
                    if prev_decoded(i_ebno2, i_list2)
                        run_sim = 0;
                    end
                end
            end
            if run_sim == 0
                continue;
            end
%             if list_size_vec(i_list) == 1
                L_path=8;
                I=6; %iteration numbers
                Imax=8; %I_SCAN
                ys=y_noise(1:K);
                y1=y_noise(K+1:N);
                y2=y_noise(N+1:2*N-K);
                a1=zeros(K,1);
                a2=zeros(K,1);
                z1=zeros(N,1);
                for i_iter=1:I
                    z1(info_bits)=2/sigma^2*ys;
                    z1(frozen_number)=2/sigma^2*y1;
                    llr_z1=z1;
                    llr_z1(info_bits)=llr_z1(info_bits)+a1;
                    %Soft list decoder=SCLBP
                    [x1_esti, l1]=SCLBP_decoder(llr_z1, L_path, K, frozen_bits, lambda_offset, llr_layer_vec, bit_layer_vec,M_up,M_down);
%                     [x1_esti, l1]= SoSCL_decoder(llr_z1, L_path, K, frozen_bits, lambda_offset, llr_layer_vec, bit_layer_vec);
                    x1_esti=polar_encoder(x1_esti, lambda_offset, llr_layer_vec);
                    polar_info_esti=x1_esti(info_bits);
                    for i_code=1:K
                        llr_bf=polar_info_esti(i_code)-sign(l1(i_code));
                        if llr_bf==1||llr_bf==0
                            l1(i_code)=-l1(i_code);
                        end
                    end
                    e1=l1;%产生外部信息
                    a2=e1(interleaver);%交织
                    z2=zeros(N,1);
                    z2(info_bits)=2/sigma^2*ys(interleaver);
                    z2(frozen_number)=2/sigma^2*y2;
                    llr_z2=z2;
                    llr_z2(info_bits)=llr_z2(info_bits)+a2;
                    %Soft list decoder=SCLBP
                    [x2_esti, l2]=SCLBP_decoder(llr_z2, L_path, K, frozen_bits, lambda_offset, llr_layer_vec, bit_layer_vec,M_up,M_down);
%                     [x2_esti, l2]= SoSCL_decoder(llr_z2, L_path, K, frozen_bits, lambda_offset, llr_layer_vec, bit_layer_vec);
                    x2_esti=polar_encoder(x2_esti, lambda_offset, llr_layer_vec);
                    polar_info_esti_inter=x2_esti(info_bits);
                    for i_code=1:K
                        llr_bf=polar_info_esti_inter(i_code)-sign(l2(i_code));
                        if llr_bf==1||llr_bf==0
                            l2(i_code)=-l2(i_code);
                        end
                    end
                    e2=l2;
                    polar_info_esti(interleaver)=polar_info_esti_inter;
                    a1(interleaver)=e2;
                end
            
            ber(i_ebno,i_list) = ber(i_ebno,i_list) + sum( mod((info + polar_info_esti) , 2));
            
            if any(polar_info_esti ~= info)
                bler(i_ebno, i_list) = bler(i_ebno, i_list) + 1;
            else
                prev_decoded(i_ebno, i_list) = 1;
            end
            
        end
    end
end
% profile viewer
toc
end

