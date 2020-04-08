#generate sample path for stock price using Geometric Brownian motion
#define constants
S_0<-120
T<-1
r<-0.05
sigma<-0.26
n<-10 # sample size
d<-365   #time size
delta<-T/d
grid<-matrix(rep(seq(delta,T,length.out=d),n),nrow=n,byrow=TRUE) #time grid as matrix
S<-matrix(rep(0,n*(d+1)),nrow=n)#create a matrix to store asset prices

#generate nxd pseudo-random normal numbers
#set.seed(1)
x<-matrix(rnorm(n*d),nrow=n)

#generate n sample paths of Brownian Motion
BM<-sqrt(delta)*t(apply(x,1,cumsum))

#generate n sample paths of stock price
S<-cbind(rep(S_0,n),S_0*exp((r-sigma^2/2)*grid+sigma*BM))

#plot the sample paths
plot(1:(d+1),S[1,],type='l',ylim=c(60,220),col=1,ylab='Stock Price',xlab='Time (days)')
for (i in 2:n){
	points(1:(d+1),S[i,],type='l',col=i)
}

