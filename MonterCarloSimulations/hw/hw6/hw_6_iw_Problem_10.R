#Pricing lookback call/put option
source('Sample_GBM.R')

S_0<-100 #initial stock price
MT<-12/52 #maturity time
r<-0 #risk-free rate
sigma<-0.40 #volatility
d<-12   #monitoring frequency
delta<-MT/d

n<-10^4 #number of initial sample paths

#generate n sample paths of stock price
S<-Sample_GBM(S_0,MT,r,sigma,d,n)

LBCallPayoff<-(S[,d]-apply(S,1,min))*exp(-r*MT)
LBPutPayoff<-(apply(S,1,max)-S[,d])*exp(-r*MT)
LBCallPrice<-mean(LBCallPayoff)
LBPutPrice<-mean(LBPutPayoff)

#use approximate 99% confidence interval to estimate the error
error_LBCall<-2.58*sd(LBCallPayoff)/sqrt(n)
error_LBPut<-2.58*sd(LBPutPayoff)/sqrt(n)

cat("With S(0)=",S_0, ", \nr=",r,",\nvolatility=",sigma, ",\nT=", MT, 
   ",", "\nmonitoring frequency=",d, ",\nsample size n=",n, 
   ".\nThe estimated lookback call option price is", LBCallPrice, 
   ", \nwith approximate error as", error_LBCall, 
   ". \nThe estimated look back put option price is", LBPutPrice, 
   ", \nwith approximate error as", error_LBPut, ". " )
