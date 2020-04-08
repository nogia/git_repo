#estimate int 1/sqrt(2*pi)e^(-x^2/2) from 0 to 1 with for estimators 

library(pracma) #call the package so that I can use function tic() toc() to monitor execution time

n <- 10^6 #simulation size
mu<-pnorm(1)-pnorm(0) #true value of the integral

#Estimator 1, simple Monte Carlo estimator with uniform random sample
tic()
x_1<-runif(n) #uniform random numbers
y_1<-1/sqrt(2*pi)*exp(-x_1^2/2) #random samples of Y
mu_1<-mean(y_1) #sample mean of Y, estimate of integral
error_1<-abs(mu_1-mu)/mu #true relative error
toc()

#Estimator 2, simple Monte Carlo estimator with standard normal random sample
tic()
x_2<-rnorm(n) #standard normal random numbers
y_2<-ifelse((x_2<=1 & x_2>=0),1,0) #samples of Y which is the indicator function whether the sample x_2 is inside [0,1] or not

#an alternative way to generate y_2 that saves time 
#y_2<-(sign(-x_2*(1-x_2))+1)/2

mu_2<-mean(y_2) #sample mean of Y, estimate of integral
error_2<-abs(mu_2-mu)/mu #true relative error
toc()

#Estimator 3, left rectangle rule estimator, deterministic
tic()
x_3<-seq(0,1-1/n,by=1/n) #left endpoints of the subintervals
y_3<-1/sqrt(2*pi)*exp(-x_3^2/2) #height of the left rectangles
mu_3<-mean(y_3) #sum of areas of left rectangles, estimate of integral
error_3<-abs(mu_3-mu)/mu #true relative error
toc()

#Estimator 4, stratified sampling Monte Carlo estimator
tic()
u<-runif(n) #generate random movements on each subinterval
x_4<-seq(0,1-1/n,by=1/n)+u #the stratified samples on subintervals with one in each subinterval
y_4<-1/sqrt(2*pi)*exp(-x_4^2/2) #height of the rectangle
mu_4<-mean(y_4) #sum of areas of rectangles, estimate of integral
error_4<-abs(mu_4-mu)/mu #true relative error
toc()

