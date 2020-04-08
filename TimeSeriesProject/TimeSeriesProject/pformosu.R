library(astsa)
examine.mod <- function(mod.fit.obj, p, d, q, P=0, D=0, Q=0, S=-1, lag.max=24) {
  dev.new(width=6, height=6)
  par(mfrow=c(2,1))
  pacf(mod.fit.obj$fit$residuals, main="PACF of Residuals", lag.max)
  if ((P==0)&(D==0)&(Q==0)) {
    title(paste("Model: (", p, ",", d, ",", q, ")", sep=""), adj=0, cex.main=0.75)
  }
  else {
    title(paste("Model: (", p, ",", d, ",", q, ") (", P, ",", D, ",", Q, ") [", S, "]", sep=""), adj=0, cex.main=0.75)
  }
  
  std.resid <- mod.fit.obj$fit$residuals/sqrt(mod.fit.obj$fit$sigma2)
  hist(std.resid, main="Histogram of Standardized Residuals", xlab="Standardized Residuals", freq=FALSE)
  curve(expr=dnorm(x, mean=mean(std.resid), sd=sd(std.resid)), col="red", add=TRUE)
}


pformosu<-read.table(file = "C:/Users/inna/Desktop/Time_Series/course/Project/pformosu.txt")

row =3726
col= 16
pformosu_dat = numeric(col*row)
count = 1
for(i in 1:row)
{
  for(j in 1:col)
  {
    pformosu_dat[count]=pformosu[i,j]
    count = count + 1
  }
}
ts_p<-ts(pformosu_dat)
dev.new()
par(mfrow=c(2,1))
tsplot(ts_p)
boxplot(ts_p)$out
##############################################################
frequency <- 30
one_day<- 30*24
two_days_of_data<- one_day*2
three_days_of_data<-one_day*3
three_days_of_data<-one_day*7
ts_p_3_days <- ts_p[(length(ts_p)-(three_days_of_data) + 1 ):(length(ts_p))]
ts_p<-ts_p[(length(ts_p)-(two_days_of_data) + 1 ):(length(ts_p))]
dev.new()
par(mfrow=c(2,1))
tsplot(ts_p,xlab="Number Of Observations")
boxplot(ts_p)$out
#############################################################

ts_pp  <- ts(ts_p,frequency = frequency,start=0)
dev.new()
par(mfrow=c(2,1))
tsplot(ts_pp,xlab="Number Of Observations -> 2 Days")
boxplot(ts_pp)$out

dev.new()
tsplot(ts_pp,xlab="Number Of Observations -> 2 Days -> 1440 observations",
       main="Circadian rhythms in the  last  2 days/48 hours Frequency =30")
x<-as.numeric(ts_pp)
tsplot(x)
############################################################
dev.new()
tsplot(ts_pp,  ylab=expression(x[t]), 
       xlab="hours", main="Circadian rhythms in the  last  week Of data")

dev.new()
acf2(x, max.lag = length(ts_pp) - 1,main = "ACF & PACF Of Original ts")
dev.new()
acf2(x, max.lag = frequency*3,main = "ACF & PACF Of Original ts")


############################################################
# Plot of (1-B^30)*x_t
dev.new()
tsplot(diff(ts_pp, lag=frequency, differences=2), ylab=expression((1-B^30)^2*x[t]), 
       xlab="hours", main=expression(paste("Plot of ", (1-B^30)^2*x[t])))

# ACF indicated cut of after 720 lag that sugests that ARIMA Q=1,
# PACF exponencially decay that sugests ARIMA P=0
# Diff =1 S=30 (1-B^30)*x_t
dev.new()
acf2(diff(x, lag=frequency, differences=), max.lag=frequency-1, 
     main=expression(paste("Est. ACF & PACF for ", (1-B^30)*x[t])))


##########################################################
# Plot of (1-B)(1-B^720)*x_t
dev.new()
tsplot(diff(diff(ts_pp, lag=frequency, differences=1)), 
       ylab=expression((1-B)(1-B^720)*x[t]), 
       xlab="Days Frequency = 720", main=expression(paste("Plot of ", 
       (1-B)(1-B^720)*x[t])))

# ACF and PACF of (1-B)(1-B^30)*x_t
dev.new()
acf2(diff(  diff(x, lag=frequency, differences=1)), 
     max.lag=717,
     main=expression(paste("Est. ACF & PACF for ", (1-B)(1-B^30)*x[t])))
#######################################################################
#Estimate 
# First Estimate ARIMA(p=0-2,d=1,q=0-10,P=0,D=1,Q=1,S=30) #######

dev.new()
mod.fit1<- sarima(ts_pp,p=0,d=1,q=0,P=0,D=1,Q=1,S=300)
mod.fit1

dev.new()
par(mfrow=c(2,1))
pacf(mod.fit1$fit$residuals,main = " PACF Of residuals")
title(paste("Model: (",
            p = 0, ",",
            d = 1, ",",
            q = 0, ")(",
            P = 0, ",",
            D = 1, ",",
            Q = 1, ")[30]",
            sep=""),adj=0,cex.main=0.75)
std.resid1 <- mod.fit1$fit$residuals / sqrt(mod.fit1$fit$sigma2)
hist(std.resid1,main = " Histogram Of Standirdized Residuals",
     xlab='Standardized Residuals',
     freq = FALSE
)
### # First Estimate ARIMA(p=0,d=1,q=1,P=0,D=1,Q=1,S=30) #######

dev.new()
mod.fit1<- sarima(ts_pp,p=0,d=1,q=1,P=0,D=1,Q=1,S=300)
mod.fit1

dev.new()
par(mfrow=c(2,1))
pacf(mod.fit1$fit$residuals,main = " PACF Of residuals")
title(paste("Model: (",
            p = 0, ",",
            d = 1, ",",
            q = 1, ")(",
            P = 0, ",",
            D = 1, ",",
            Q = 1, ")[30]",
            sep=""),adj=0,cex.main=0.75)
std.resid1 <- mod.fit1$fit$residuals / sqrt(mod.fit1$fit$sigma2)
hist(std.resid1,main = " Histogram Of Standirdized Residuals",
     xlab='Standardized Residuals',
     freq = FALSE
)
### ARIMA(p=1,d=1,q=1,P=0,D=1,Q=1,S=30)
dev.new()
mod.fit1<- sarima(ts_pp,p=1,d=1,q=1,P=0,D=1,Q=1,S=720)
mod.fit1

dev.new()
par(mfrow=c(2,1))
pacf(mod.fit1$fit$residuals,main = " PACF Of residuals")
title(paste("Model: (",
            p = 1, ",",
            d = 1, ",",
            q = 1, ")(",
            P = 0, ",",
            D = 1, ",",
            Q = 1, ")[720]",
            sep=""),adj=0,cex.main=0.75)
std.resid1 <- mod.fit1$fit$residuals / sqrt(mod.fit1$fit$sigma2)
hist(std.resid1,main = " Histogram Of Standirdized Residuals",
     xlab='Standardized Residuals',
     freq = FALSE
)
#### ARIMA(p=0,d=1,q=2,P=0,D=1,Q=1,S=30)
dev.new()
mod.fit1<- sarima(ts_pp,p=0,d=1,q=2,P=0,D=1,Q=1,S=720)
mod.fit1

dev.new()
par(mfrow=c(2,1))
pacf(mod.fit1$fit$residuals,main = " PACF Of residuals")
title(paste("Model: (",
            p = 0, ",",
            d = 1, ",",
            q = 2, ")(",
            P = 0, ",",
            D = 1, ",",
            Q = 1, ")[30]",
            sep=""),adj=0,cex.main=0.75)
std.resid1 <- mod.fit1$fit$residuals / sqrt(mod.fit1$fit$sigma2)
hist(std.resid1,main = " Histogram Of Standirdized Residuals",
     xlab='Standardized Residuals',
     freq = FALSE
)
#### ARIMA(p=0,d=1,q=3,P=0,D=1,Q=1,S=30)
dev.new()
mod.fit1<- sarima(ts_pp,p=0,d=1,q=3,P=0,D=1,Q=1,S=720)
mod.fit1

dev.new()
par(mfrow=c(2,1))
pacf(mod.fit1$fit$residuals,main = " PACF Of residuals")
title(paste("Model: (",
            p = 0, ",",
            d = 1, ",",
            q = 3, ")(",
            P = 0, ",",
            D = 1, ",",
            Q = 1, ")[30]",
            sep=""),adj=0,cex.main=0.75)
std.resid1 <- mod.fit1$fit$residuals / sqrt(mod.fit1$fit$sigma2)
hist(std.resid1,main = " Histogram Of Standirdized Residuals",
     xlab='Standardized Residuals',
     freq = FALSE
)
#### ARIMA(p=1,d=1,q=0,P=0,D=1,Q=1,S=30)
dev.new()
mod.fit1<- sarima(ts_pp,p=1,d=1,q=0,P=0,D=1,Q=1,S=30)
mod.fit1

dev.new()
par(mfrow=c(2,1))
pacf(mod.fit1$fit$residuals,main = " PACF Of residuals")
title(paste("Model: (",
            p = 1, ",",
            d = 1, ",",
            q = 0, ")(",
            P = 0, ",",
            D = 1, ",",
            Q = 1, ")[30]",
            sep=""),adj=0,cex.main=0.75)
std.resid1 <- mod.fit1$fit$residuals / sqrt(mod.fit1$fit$sigma2)
hist(std.resid1,main = " Histogram Of Standirdized Residuals",
     xlab='Standardized Residuals',
     freq = FALSE
)
#### ARIMA(p=2,d=1,q=0,P=0,D=1,Q=1,S=30)
dev.new()
mod.fit1<- sarima(ts_pp,p=2,d=1,q=0,P=0,D=1,Q=1,S=30)
mod.fit1

dev.new()
par(mfrow=c(2,1))
pacf(mod.fit1$fit$residuals,main = " PACF Of residuals")
title(paste("Model: (",
            p = 2, ",",
            d = 1, ",",
            q = 0, ")(",
            P = 0, ",",
            D = 1, ",",
            Q = 1, ")[30]",
            sep=""),adj=0,cex.main=0.75)
std.resid1 <- mod.fit1$fit$residuals / sqrt(mod.fit1$fit$sigma2)
hist(std.resid1,main = " Histogram Of Standirdized Residuals",
     xlab='Standardized Residuals',
     freq = FALSE
)


#### ARIMA(p=2,d=1,q=2,P=0,D=1,Q=1,S=30)
dev.new()
mod.fit1<- sarima(ts_pp,p=2,d=1,q=2,P=0,D=1,Q=1,S=30)
mod.fit1

dev.new()
par(mfrow=c(2,1))
pacf(mod.fit1$fit$residuals,main = " PACF Of residuals")
title(paste("Model: (",
            p = 2, ",",
            d = 1, ",",
            q = 2, ")(",
            P = 0, ",",
            D = 1, ",",
            Q = 1, ")[30]",
            sep=""),adj=0,cex.main=0.75)
std.resid1 <- mod.fit1$fit$residuals / sqrt(mod.fit1$fit$sigma2)
hist(std.resid1,main = " Histogram Of Standirdized Residuals",
     xlab='Standardized Residuals',
     freq = FALSE
)

####  ARIMA(p=2,d=1,q=3,P=0,D=1,Q=1,S=30)
dev.new()
mod.fit1<- sarima(ts_pp,p=3,d=1,q=3,P=0,D=1,Q=1,S=30)
mod.fit1

dev.new()
par(mfrow=c(2,1))
pacf(mod.fit1$fit$residuals,main = " PACF Of residuals")
title(paste("Model: (",
            p = 3, ",",
            d = 1, ",",
            q = 2, ")(",
            P = 0, ",",
            D = 1, ",",
            Q = 1, ")[30]",
            sep=""),adj=0,cex.main=0.75)
std.resid1 <- mod.fit1$fit$residuals / sqrt(mod.fit1$fit$sigma2)
hist(std.resid1,main = " Histogram Of Standirdized Residuals",
     xlab='Standardized Residuals',
     freq = FALSE
)
########################  Forecasting   ####################

dev.new()
mod.fit.110.011 <- sarima(x, p=1,d=1,q=1,P=0,D=1,Q=1,S=30)
mod.fit.110.011
examine.mod(mod.fit.110.011, 2,1,2, 0,1,1, 30)

#####  1 hour ahead  #######################################
ahead_1_hours <-30
dev.new()
fore.mod <- sarima.for(ts_pp, n.ahead=ahead_1_hours, 
        p=1, d=1, q=1, P=0, D=1, Q=1, S=30, plot.all=TRUE)

dev.new()
tsplot(fore.mod$pred)

#####  4 hours ahead  ######################################
ahead_4_hours <- 4*30
dev.new()
fore.mod <- sarima.for(ts_pp, n.ahead=ahead_4_hours, 
                       p=1, d=1, q=1, P=0, D=1, Q=1, S=30, plot.all=TRUE)

dev.new()
tsplot(fore.mod$pred)

##########################################################
#### 24 hours ahead  #####################################
ahead_24_hours <- 24*30
dev.new()
fore.mod <- sarima.for(ts_pp, n.ahead=ahead_24_hours, 
                       p=1, d=1, q=1, P=0, D=1, Q=1, S=30, plot.all=TRUE)

#########################################################

pred.mod <- ts(x - mod.fit.110.011$fit$residuals)

dev.new()
tsplot(ts_pp[1:length(ts_pp)], ylab="pred", xlab="min", 
       type="o", main="Predicted Model vs Real Data")
lines(pred.mod, col="red", type="o", pch=17)
legend("topleft", legend=c("Observed", "Forecast"), 
       lty=c("solid", "solid"), col=c("black", "red"), 
       pch=c(1, 17), bty="n")

############   Discussion  code #########################
library(astsa)
library("forecast")
library("lubridate")
library("ggplot2")
library(magrittr) 
# needs to be run every time you start R and want to use %>%
library(dplyr)
#########################################################
On_hour <- 30
one_day <- 30*24
tree_days <- 30*24*3
frequency <- c(On_hour,one_day)
msts_pp <- msts(ts_p_3_days,seasonal.periods = frequency,start = 0)
dev.new()
tsplot(msts_pp,xlab="days",
main="Circadian rhythms in the  last  3d/72h/2736obs  Freq = 30")

########################################################
#install.packages("forecast")
#install.packages("lubridate")
dev.new()
msts_pp %>% mstl() %>%autoplot() + xlab("Days")

###  Forecast made by stlf  ############################
dev.new()
msts_pp %>%  stlf() %>%autoplot() + xlab("Days")


####  Fit Multiple seasonalities using fourier  ########

fit <- auto.arima(msts_pp, seasonal=FALSE, lambda=0,xreg=fourier(msts_pp, K=c(14,65)))
fit

####  Forecast  10 minutes = 5 observations ahead #####
dev.new()
minutes_10<- 5
fit %>%
  forecast(xreg=fourier(msts_pp, K=c(14,65), minutes_10)) %>%
  autoplot(tree_days) + ylab("Circadian Rhythms in the Long-Tail Pocket Mouse 10 minutes ahead") + xlab("Days")

# Forecast  
# 1hour ahead = 30 observations observations ahead #####
dev.new()
hour_1<- 30
fit %>%
  forecast(xreg=fourier(msts_pp, K=c(14,65), h=hour_1)) %>%
  autoplot(include=tree_days) + 
  ylab("Circadian Rhythms in the Long-Tail Pocket Mouse 1 hour ahead") + 
  xlab("Days")

# Forecast  
# 4 hours ahead = 120 observations observations ahead #####
dev.new()
hours_4<- 30 * 4
fit %>%
  forecast(xreg=fourier(msts_pp, K=c(14,65), h=hours_4)) %>%
  autoplot(include=tree_days) + ylab("Circadian Rhythms in the Long-Tail Pocket Mouse 4 
                                    hours ahead") + xlab("Days")

# Forecast  
# 12 hours ahead = 360 observations observations ahead #####
dev.new()
hours_12<- 30 * 12
fit %>%
  forecast(xreg=fourier(msts_pp, K=c(14,65), h=hours_12)) %>%
  autoplot(include=tree_days) + 
  ylab("Circadian Rhythms in the Long-Tail Pocket Mouse 12 hours ahead") + 
  xlab("Days")
# Forecast  
# 24 hours ahead = 720 observations observations ahead #####
dev.new()
day_1<- 30 * 24
fit %>%
  forecast(xreg=fourier(msts_pp, K=c(14,65), h=day_1)) %>%
  autoplot(include=tree_days) + 
  ylab("Circadian Rhythms in the Long-Tail Pocket Mouse 1 day ahead") + 
  xlab("Days")
# Forecast  
# 2 days ahead = 1440 observations observations ahead #####
dev.new()
day_2<- 30 * 24 * 2
fit %>%
  forecast(xreg=fourier(msts_pp, K=c(14,65), h=day_2)) %>%
  autoplot(include=tree_days) + 
  ylab("Circadian Rhythms in the Long-Tail Pocket Mouse 2 days ahead") + 
  xlab("Days")
# Forecast  
# 1 week ahead = 5040 observations observations ahead #####
dev.new()
week_1<- 30 * 24 * 7
fit %>%
  forecast(xreg=fourier(msts_pp, K=c(14,65), h=week_1)) %>%
  autoplot(include=tree_days) + 
  ylab("Circadian Rhythms in the Long-Tail Pocket Mouse 7 days ahead") + 
  xlab("days")




















