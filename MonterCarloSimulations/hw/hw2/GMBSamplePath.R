#generate sample path for stock price using Geometric Brownian motion
#define constants
S_0<-100
T<-1
r<-0.05
sigma<-0.3
n<-3 # sample size
d<-4   #time size
delta<-T/d
grid<-seq(delta,T,length.out=d) #time grid
S<-matrix(rep(0,n*(d+1)),nrow=n)#create a matrix to store asset prices

#generate nxd pseudo-random normal numbers
set.seed(1) #for illustrative purpose only
x<-matrix(rnorm(n*d),nrow=n)

#generate n sample paths of Brownian Motion
BM<-sqrt(delta)*t(apply(x,1,cumsum))

#generate n sample paths of stock price
S<-cbind(rep(S_0,n),S_0*exp(sweep(sigma*BM,MARGIN=2,(r-sigma^2/2)*grid,'+')))

#plot the sample paths
plot(1:(d+1),S[1,],type='l',ylim=c(60,220),col=1,ylab='Stock Price',xlab='Time (days)')
for (i in 2:n){
	points(1:(d+1),S[i,],type='l',col=i)
}

