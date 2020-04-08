%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Step 0: Initialize data
%%% Make data for matrix A and vector b
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
clear;
H2mat = [1 -1; 1 1];
H3mat = [H2mat -1*H2mat; H2mat H2mat];
H4mat = [H3mat -1*H3mat; H3mat H3mat];
H5mat = [H4mat -1*H4mat; H4mat H4mat];
H6mat = [H5mat -1*H5mat; H5mat H5mat];
H7mat = [H6mat -1*H6mat; H6mat H6mat];
H8mat = [H7mat -1*H7mat; H7mat H7mat];
rows = [3, 4, 5, 6 ,7,  8, 11, 12, 13, 19, 20 , 26,  30,  33, 34,  36,    37,  40,    41, 43];
rows = [rows,47, 49,53, 54,  55,    56,    57,  58,  60,  61,  62,  64,  65,  69, 72, 75, 80, 81, 82, 84];
rows = [rows,87, 88, 91, 92, 93, 94, 96, 97, 100, 106, 107,109];
A0mat = H8mat(rows,:)       %%% A0mat has 52 rows and 128 columns
tic
x_true = zeros(128,1);       
locations = [109,   107,    55,    30,    43];
x_true(locations) = [3.2 -4.3 3.2 -4.3 3.2];
bvect = A0mat*x_true;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%
%%%  initial estimate of the vector x
%%%  Note: we use an estimator of xvect by computing right inverse of A0mat
%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
x_initial = A0mat'*inv(A0mat*A0mat')*bvect;
%%% verify that Amat*x_initial is equal to bvect
if (norm(A0mat*x_initial - bvect) > 0.01)
    disp('WARNING: Amat times initial vect is not equal to bvect');
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Step 1
%%% enlarge the matrix to have twice as many columns
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Amat = [A0mat -1*A0mat];
A_size = size(Amat);
mcol = A_size(1);
nrow = A_size(2);
cvect = ones(nrow,1);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%
%%%   any vector x can be written as the diference of two vectors,
%%%   x_initial =x_plus subtract x_minus
%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
x_plus = zeros(nrow/2,1);
x_minus = zeros(nrow/2,1);
for j = 1:(nrow/2)
    if x_initial(j) > 0
        x_plus(j) = x_initial(j);
    end
    if x_initial(j) < 0
        x_minus(j) = abs( x_initial(j) );
    end
end
x0_vect = [x_plus ; x_minus];
%%% verify that Amat*x0_vect is equal to bvect
if (norm(Amat*x0_vect - bvect) > 0.01)
    disp('WARNING: Amat times x0_vect is not equal to bvect');
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Main Steps
%%% Given cvect, Amat, and bvect, 
%%% use the initial estimate x0_vect to solve for x_vect
%%%
ro=0.1;
mu=5;
k=0;
[m,n]=size(Amat);
nrow = m;
xvect=x0_vect;
Qmat = Amat'*Amat;
dvect = Amat'*bvect - Qmat*xvect;
for k = 1:nrow

    gk_vect = Qmat*xvect - Amat'*bvect;
    alpha = -1*dot(gk_vect,dvect)/dot(dvect,Qmat*dvect);
    xvect = xvect + alpha*dvect;
    
    g_k_plus_one = Qmat*xvect - Amat'*bvect;
    beta = dot(g_k_plus_one,g_k_plus_one)/dot(gk_vect,gk_vect);
    dvect = -1*g_k_plus_one + beta*dvect;
end
xvect


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%   Students implement the Interior Point Method in the following.
%%%%%%%%%%%%      End of Main Steps
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%
%%% Rememer that the second half of the vector xvect are
%%% the negative entries of the optimal vector that we seek
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% trim anything in the solution that is less than threshold number
threshold = 0.01;
for j = 1:nrow
    if abs(xvect(j)) < threshold
        xvect(j) = 0;
    end
end
optxvect = xvect(1:floor(nrow/2)) -xvect(floor(nrow/2)+1:nrow);
%%% compare the true solution and the optimal solution
%[x_true optxvect]


