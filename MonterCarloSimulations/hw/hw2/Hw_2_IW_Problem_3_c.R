n=10
cat("Enter number_of simulatios ")
n <- readLines(file("stdin"),1)
n <- as.integer(n)
expected_lifitime=30
start_years=0
end_years=5
max_pay=100
std_dev=0
#calculate k for 95% confidence using Chebushev inequality
k=sqrt(1/(1-0.95))
out_k=paste("k for 95% confidence = sqrt(1/(1-0.95)) = ",k)
print(out_k)
#calculate theoretical value
theoretical_value=max_pay*pexp(end_years-start_years, 1/expected_lifitime) 

calc <-function(x,rate)
{
  return((1/rate)*exp(-x/rate));
}

create <-function(i,j)
{
  xvalues=runif(n,i,j)
  yvalues=sapply(xvalues,calc,expected_lifitime)
  return(list(xvalues,yvalues))
}

#################################   Montercarlo 1 #########################################
#create xvalues and yvalues
mt_1_values=create(start_years,end_years)
# Multiply by the pay and by the interval value
mt_1_values[[2]]=max_pay*(end_years-start_years)*mt_1_values[[2]]
# calculated the average of the (yvalues*pay)
# this is expected pay hat values
expected_prob_mtc_1=mean(mt_1_values[[2]])
#calcuate absolute error
error=abs(theoretical_value-expected_prob_mtc_1)
#calculate standard deviation hat
std_dev=sd(mt_1_values[[2]])
#calculate standard error hat
standard_error=std_dev/sqrt(n)
#calculate 95% confidence interval using chebushev inequality
conf_interval_95=c(expected_prob_mtc_1-k*std_dev/sqrt(n), expected_prob_mtc_1+k*std_dev/sqrt(n))
out=paste("number_of simulatios  =", n,"Theoretical value = ",theoretical_value,"Calculated Expected Pay Value = ",expected_prob_mtc_1, "\n Abs Error = ",error,"Std=",std_dev,"StdError=",standard_error,"\n95% conf_interval = [ ",conf_interval_95[1]," ",conf_interval_95[2]," ]")
writeLines(out)
