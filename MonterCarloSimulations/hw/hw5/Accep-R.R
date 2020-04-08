library(pracma)

n<-10^5
efficiency<-64/135 #efficiency of the method
N<-ceiling(n/efficiency*1.1)
Y<-runif(N) #uniform random numbers as candidate numbers
W<-runif(N) #uniform random numbers used in criterion 
Z<-numeric(n)

tic()
flag<-1 #check whether we get enough sample for Z
i<-1
while (flag<=n){
	if (W[i]<=c*20*Y[i]*(1-Y[i])^3) {
		Z[flag]<-Y[i]
		flag<-flag+1
	}
	i<-i+1
}
toc()
hist(Z,freq=F,ylim=c(0,2.5))
xfit<-seq(min(Z),max(Z),length=1000)
lines(xfit, 20*xfit*(1-xfit)^3,col='blue',lwd=2)

#no loop
tic()
Z<-Y[which(efficiency*20*Y*(1-Y)^3>=W)]
Z<-Z[1:n]
toc()
hist(Z,freq=F,ylim=c(0,2.5))
xfit<-seq(min(Z),max(Z),length=1000)
lines(xfit, 20*xfit*(1-xfit)^3,col='blue',lwd=2)

