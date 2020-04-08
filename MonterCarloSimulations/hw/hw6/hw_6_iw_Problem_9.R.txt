library(pracma)

n<-1000
alpha<-2
betta<-2
efficiency<-2/3 #efficiency of the method
c<-gamma(alpha)*gamma(betta)*(alpha+betta-2)^(alpha+betta-2)/(gamma(alpha+betta) * ((alpha-1)^(alpha-1))*(betta-1)^(betta-1)) 
efficiency<-c #efficiency of the method
N<-ceiling(n/efficiency*1.1)
Y<-runif(N) #uniform random numbers as candidate numbers
W<-runif(N) #uniform random numbers used in criterion 
Z<-numeric(n)
f<-function(x) gamma(alpha+betta)*x^(alpha-1)*(1-x)^(betta-1)/(gamma(alpha)*gamma(betta))
g<-function(x) 1
f_y<-f(Y)
g_y<-g(Y)
tic()
Z<-Y[which(c*f_y/g_y>=W)]
Z<-Z[1:n]
toc()
hist(Z,freq=F,ylim=c(0,2.5))
xfit<-seq(min(Z),max(Z),length=1000)
lines(xfit, 6*xfit*(1-xfit),col='blue',lwd=2)



