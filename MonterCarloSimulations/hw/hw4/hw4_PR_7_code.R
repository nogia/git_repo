n=2000
u<-runif(n)
x<-log(u/(1-u))
x1=x[x<0]
hist(x1,prob=T,main=expression(f(x1)==1/(1+exp(-x1))))
y<-seq(-100,100,1)
lines(y,1/(1+exp(-y)))
print(x1)
