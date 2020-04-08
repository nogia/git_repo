####################################################################################################################
#       CReated By Inna Williams
#       Homework 3
####################################################################################################################
S_0<-100 #initial stock price
K<-c(75,100,130) #strike price
MT<-1.0 #maturity time
r<-0.03 #risk-free rate
sigma<-0.30 #volatility
n=100000
excact_prices=numeric(3)

#####################################################################################################################
ExactEuro <-function(S_0,K,r,sigma,MT,type)
{
  if (type=='call')
  {
      return(S_0*pnorm((log(S_0/K)+(r+sigma^2/2)*MT)/(sigma*sqrt(MT)))-K*exp(-r*MT)*pnorm((log(S_0/K)+(r-sigma^2/2)*MT)/(sigma*sqrt(MT))));
  }
  else if(type=='put')
  {
    return(K*exp(-r*MT)*pnorm((log(K/S_0)-(r-sigma^2/2)*MT)/(sigma*sqrt(MT)))-S_0*pnorm((log(K/S_0)-(r+sigma^2/2)*MT)/(sigma*sqrt(MT))));
  }
}
####################################################################################################################
AppoximateEuro <-function(n,K,r,sigma,MT,type,ExactEuro)
{
  #generate n pseudo-random normal numbers (n samples of Brownian motion at maturity)
  x<-sqrt(MT)*rnorm(n)
  #generate n sample stock prices at maturity
  S_T<-S_0*exp((r-sigma^2/2)*MT+sigma*x)
  if (type=='call')
  {
    EuroCallPayoff<-pmax(S_T-K,0)*exp(-r*MT)
    EuroPrice<-mean(EuroCallPayoff)
    error<-abs(EuroPrice-ExactEuro)/ExactEuro
  }
  else if(type=='put')
  {
    EuroPutPayoff<-pmax(K-S_T,0)*exp(-r*MT)
    EuroPrice<-mean(EuroPutPayoff)
    error<-abs(EuroPrice-ExactEuro)/ExactEuro
  }
  return(c(EuroPrice,error))
}

cat("\n#######################################################################################################\n")
cat("\n(a) compute the exact/true fair option price for strike prices $75, $100, and $130.\n")

for (i in 1:3)
{
  cat("\n################################  Strike price K=",K[i]   ,"#################################################")
  excact_prices[i]=ExactEuro(S_0,K[i],r,sigma,MT,"call")
  cat("\nPrice at time zero =",S_0, "\ninterest rate r=",r,"\nvolatility=",sigma, "\nMaturity Time T=", MT, " year \nExcact price European call option =", excact_prices[i])
  
}
cat("\n#######################################################################################################\n")
cat("\nb) Using simple Monte Carlo simulation with n = 105 samples, compute the approximate
value of the European call option for the parameter values above. You may use the
sample program on d2l. What is the relative error for each strike price? For which strike
price is the relative error largest?\n")
cat("\n#######################################################################################################\n")
for (i in 1:3)
{
  cat("\n################################  Strike price K=",K[i]   ," n = ", n ,"#####################################")
  approximated_prices=AppoximateEuro(n,K[i],r,sigma,MT,"call",excact_prices[i])
  approximated_prices
  cat("\ninterest rate r=",r,"\nvolatility=",sigma, "\nMaturity Time T=", MT, " year \nApproximated price European call option =", approximated_prices[1],"\nExcact price European call option =", excact_prices[i],"\nerror = ",approximated_prices[2],"\n")
  
}
cat("\n########################################################################################################\n")
