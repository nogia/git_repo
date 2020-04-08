#Vanilla European call/put option pricing

#define constants
S_0<-1 #initial stock price
K<-100 #strike price
MT<-1 #maturity time
r<-0.05 #risk-free rate
sigma<-0.26 #volatility

n<-10 #number of sample paths

#generate n pseudo-random normal numbers (n samples of Brownian motion at maturity)
x<-sqrt(MT)*rnorm(n)
#generate n sample stock prices at maturity
S_T<-S_0*exp((r-sigma^2/2)*MT+sigma*x*MT^1/2)

S_T
EuroCallPayoff<-pmax(-S_T+K,0)*exp(-r*MT)
EuroCallPayoff
EuroPutPayoff<-pmax(K-S_T,0)*exp(-r*MT)
EuroCallPayoff
EuroCallPrice<-mean(EuroCallPayoff)
#EuroPutPrice<-mean(EuroPutPayoff)
#exact option prices using Black-Scholes formula
ExactEuroCall<-S_0*pnorm((log(S_0/K)+(r+sigma^2/2)*MT)/(sigma*sqrt(MT)))-K*exp(-r*MT)*pnorm((log(S_0/K)+(r-sigma^2/2)*MT)/(sigma*sqrt(MT)))
#ExactEuroPut<-K*exp(-r*MT)*pnorm((log(K/S_0)-(r-sigma^2/2)*MT)/(sigma*sqrt(MT)))-S_0*pnorm((log(K/S_0)-(r+sigma^2/2)*MT)/(sigma*sqrt(MT)))
#error_EuroPut<-abs(EuroPutPrice-ExactEuroPut)/ExactEuroPut
error_EuroCall<-abs(EuroCallPrice-ExactEuroCall)/ExactEuroCall

cat("With S(0)=",S_0, ", r=",r,", volatility=",sigma, ", T=", MT, ", K=",K, ", and sample size n=",n, ". The estimated European call option price is" , EuroCallPrice, ", with relative error as", error_EuroCall, ". The estimated European put option price is" , EuroPutPrice, ", with relative error as", error_EuroPut, ". " )

