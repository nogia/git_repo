#determine the required size given the error tolerance
#  $100 ->100%  0.5->0.005%
#
n<-1000 #initial samp0le size
x<-runif(n) #generate 1000 random samples from U[0,1]
hat_sigma<-sd(x) #calculate the sample standard deviation
N<-ceiling((2.58*1.1*hat_sigma/0.005)^2)

#do the estimation using another independent sample with N points
y<-runif(N)

est<-mean(y)
error<-2.58*sd(y)/sqrt(N)

out=paste("Sample size   =", N, " Error = ",error)
writeLines(out)