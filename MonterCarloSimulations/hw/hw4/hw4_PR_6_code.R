cat("\n###############################################################################################\n
6. (Computer Problem) The Poisson random variable is a discrete random variable that models\n
how many taxis come by in a fixed time, or how many charged particles are detected in a\n
fixed time, or how hard drive crashes in a fixed time. The probability mass function of the\n
Poisson random variable with mean (and variance) \n
Write an R program to generate i.i.d. Poisson random variables with mean one, X1..  Xn \n
from uniform random variables, Z1.. Zn using the inverse distribution transformation method.\n
Use your program to print out Z1.. Zn and X1..Xn for n = 10. \n
################################################################################################\n")
lambda =1
pois <-function(x)
{
  return( 1/(exp(lambda)*factorial(x)))
}
calculateFunctionValue <-function(i,x,subintervals)
{
  result=0;

  if( x < subintervals[i])
  {
    result=1
  }
  
  return(result)
}


calculatesubintervals <-function(f,subintervals,n)
{
  for(i in 1:n)
  {
    subintervals[i]=f(i-1 )
    if(i>1)
    {
      subintervals[i]= subintervals[i]+ subintervals[i-1]
    }
  }
  return(subintervals)
}

calculateXValues <-function(z,subintervals,n)
{
  x=numeric(n)
  for(i in 1:n)
  {
    success=0
    j=1
    while(!success)
    {
      success=calculateFunctionValue(j,z[i],subintervals)
      j=j+1
     
    }
    x[i] = j-2
  }
  return(x)
}
cat("\n##################  START  PROBLEM  6   ########################################################\n")
problem_6 <-function()
{
  n=10
  lambda=1
  z<-runif(n)
  poisonvalues=numeric(n)
  poisonvalues=calculatesubintervals(pois,poisonvalues,n)
  x=calculateXValues(z,poisonvalues,n)
  result <- matrix(c(poisonvalues,z,x),ncol=n,byrow=TRUE)
  colnames(result) <- c('0','1','2','3','4','5','6','7','8','9')
  rownames(result) <- c("F(y)","Zi","Xi")
  result <- as.table(result)
  return(result)
}

result = problem_6();
print( result)



