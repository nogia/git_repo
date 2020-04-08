#this code generates n sample paths of a Geometric Brownian motion with monitoring frequency d

#input:
#S_0: initial asset price
#MT: maturity time
#r: risk-free rate
#sigma: volatility
#d: monitoring frequency 
#n: simulation size

#output:
#S: nxd matrix with n sample paths of GBM

Sample_GBM <- function(S_0,MT,r,sigma,d,n){
	#generate nxd pseudo-random normal numbers (n sample paths with d time nodes for each path)
	x<-matrix(rnorm(n*d),nrow=n)
	
	#generate n sample paths of Brownian Motion
	BM<-sqrt(delta)*t(apply(x,1,cumsum))
	
	#generate n sample paths of stock price
	grid<-seq(delta,MT,length.out=d) #time grid
	S<-S_0*exp(sweep(sigma*BM,MARGIN=2,(r-sigma^2/2)*grid,'+'))
	
	return (S)
}





