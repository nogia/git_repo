#Y~exp(30), then F(Y)~U[0,1]

n<-10^5
Y<-rexp(n,rate=1/30) #samples of Y
X<-1-exp(-Y/30) #samples of X
hist(X,freq=F) #empirical distribution of X

#X~U[0,1], then F^(-1)(X)~exp(30)
n<-1000
X<-runif(n)
Y<- -30*log(X)
hist(Y,freq=F,nclass=100)
x<-seq(0,500,by=0.1)
lines(x,1/30*exp(-x/30),type='l',lwd=2)