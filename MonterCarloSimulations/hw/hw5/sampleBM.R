#generate one sample path of Brownian Motion
d<-12 #discretize T year into d subintervals
T<-1 #1 year
delta<-T/d
set.seed(1) #for illustrative purpose only
x<-rnorm(d) #generate standard normal random numbers
BM<-c(0,sqrt(delta)*cumsum(x)) #generate sample path of Brownian motion
#plot the sample path
plot(1:(d+1),BM,type='l',col=1,ylab='Brownian motion',xlab='Time')

#generate n sample paths of Brownian Motion
n<-3 #number of sample paths
d<-4 #discretize T year into d subintervals
T<-1 #1 year
delta<-T/d
set.seed(1) #for illustrative purpose only
#generate nxd pseudo-random normal numbers
x<-matrix(rnorm(n*d),nrow=n)
#generate n sample paths of Brownian Motion
BM<-cbind(numeric(n),sqrt(delta)*t(apply(x,1,cumsum)))
#plot the sample paths
plot(1:(d+1),BM[1,],type='l',ylim=c(-3,3),col=1,ylab='Brownian Motion',xlab='Time')
for (i in 2:n){
	points(1:(d+1),BM[i,],type='l',col=i)
}
