#compare 'runif', 'rnorm',inverse normal, accept-reject, Box-Muller normal random number generators
library(pracma)
n<-10^6

#runif
tic()
x1<-runif(n)
toc()

#rnorm
tic()
x2<-rnorm(n)
toc()
hist(x2,main="Empirical Distribution of rnorm in R")

#inverse normal
tic()
x3<-qnorm(x1)
toc()
dev.new()
hist(x3, main="Empirical Distribution of Inverse Distribution Transformation")

#accept-rejection method

N<-ceiling(n/0.76*1.1)
x<-runif(N)
w<-runif(N)
v<-runif(n)
y<--log(x)

#if you use for loop
tic()
z<-numeric(n)
k<-1
i=1
while (k<(n+1)){
 if (w[i]<=exp(-(y[i]-1)^2/2)) {
	z[k]<-y[i]
 	k<-k+1} 
 i<-i+1
}
z<-sign(v-0.5)*z
toc()
dev.new()
hist(z,main="Empirical Distribution of Accep-rejec. with Loop")

#without for loop
tic()
prez<-y[which(exp(-(y-1)^2/2)>=w)]
z1<-sign(v-0.5)*prez[1:n]
toc()
dev.new()
hist(z1,main="Empirical Distribution of Accep-rejec. without Loop")

