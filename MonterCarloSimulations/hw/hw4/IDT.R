#generate N(0,1) random numbers using inverse distribution transformation
n <-10^4
u <- runif(n)
x <- qnorm(u)

#generate exp(\lambda) random numbers using inverse distribution transformation
n <- 10^4
lambda<-30
u <- runif(n)
y <- -lambda*log(u)