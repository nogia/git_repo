#Create Reference class WeatherDerivative 
WeatherDerivative <- setRefClass(Class = "weatherDerivative",
                           # Creates class member functions
                           fields = list(
                             name = "character",
                             T_Min = "numeric",
                             T_Max = "numeric",
                             T_1 = 'matrix',
                             Threshold = 'numeric',
                             MAX_Price = 'numeric',
                             Temperature = 'numeric',
                             Error = 'numeric',
                             d = 'numeric',  #Number Of Days
                             n ='numeric',
                             const_1='numeric', #  14
                             const_2='numeric' ,#   3
                             const_3='numeric',
                             X ='matrix',
                             T_t = 'matrix',
                             hat_sigma = 'numeric',
                             Vector_Price = 'numeric',
                             Price= 'numeric',
                             estimated_error='numeric'
                            
                           ),
                           # Creates Methods Of the Class 
                           methods = list(
                             # Calculate Matrix T
                             t = function() {
                               # sets the first column of the Matrix T to T1
                               .self$T_t[,1] =  .self$T_1[,1]
                               # Calculates each column starting from 2 of the Matrix T
                               # Calculations made by columns
                               for(i in 2:.self$d)
                               {
                                 .self$T_t[,i] = .self$T_t[,i] + .self$const_3*.self$T_t[,i-1] + .self$X[,i]
                               }
                             },
                             #
                             CalculatePrices = function() {
                               # Calculate Matrix of prices
                                .self$Vector_Price = apply(.self$T_t, 1, function(x)    ((sum(x < .self$Threshold, na.rm=TRUE))>=2 )*100)
                                #Calculate the price
                                .self$Price = mean(.self$Vector_Price)
                                #calculate the sample standard deviation
                                .self$hat_sigma = sd( .self$Vector_Price)
                             },
                             #
                             FindSampleSize = function() {
                               #  1% from $ 1  = 0.01
                               #  hat_sigma is in dollars
                               N<-ceiling((2.58*1.1*(.self$hat_sigma/100)/(.self$Error))^2)
                               #resets the initial size of n to new calculated N
                               .self$n=N
                               # run the program again to relculate Price and the sample standard deviation
                               .self$Run()
                               # calcalates estimation error
                               .self$estimated_error = error<-2.58*(.self$hat_sigma/100)/sqrt(N)
                             },
                             # Init function initializes object variables that will be used in calculations
                             # Initializes X, T_1,T_t, Price
                             Init = function() {
            
                               .self$Price = 0
                               # Craetes Matrix X and Multiply it 0m const_2 =3
                               .self$X = .self$const_2*matrix(rnorm(.self$n*.self$d), ncol=.self$d,nrow=.self$n, byrow = TRUE)
                               # creates Matrix T and set each element of the T = cont_1 = 14
                               .self$T_t = matrix(.self$const_1, ncol=.self$d, nrow=.self$n)
                               # create one column Matrix T1 of uniform (70,80)
                               .self$T_1 = .self$T_Min + (.self$T_Max-.self$T_Min)* matrix(runif(.self$n*.self$d),ncol=1,nrow=.self$n)
                             },
                             # This is a mai method that call other methods to execute the code
                             Run = function()
                             {
                               .self$Init()
                               .self$t()
                               .self$CalculatePrices()
                               #.self$Price = .self$MAX_Price * .self$Probabylity_of_success
                              
                             },
                             WriteOutput = function()
                             {
                               cat("##############################   Start First Output ############################################\n")
                               if(.self$n<=50)
                               {
                                 cat("************************************************************************************************\n")
                                 print("Initial T1=")
                                 print(.self$T_1)
                               }
                              
                               if(s$n<=50)
                               {
                                 cat("************************************************************************************************\n")
                                 print("Matrix 3 * x =")
                                 print(.self$X)
                               }
                               
                               if(s$n<=50)
                               {
                                 cat("************************************************************************************************\n")
                                 print("Matrix T = ")
                                 print(.self$T_t)
                               }
                              
                               if(s$n<=50)
                               {
                                 cat("************************************************************************************************\n")
                                 print("Vector Of Prices = ")
                                 print(.self$Vector_Price)
                               }
                               cat("************************************************************************************************\n")
                               cat("Calculated  Price = ", .self$Price," for n = ", .self$n," \n")
                               
                               cat("Standard Deviation Of the sammple =  ",.self$hat_sigma,"\n")
                              
                               cat("##############################   End First Output ##############################################\n")
                               
                             },
                             WrireOutAfterRecalculation = function()
                             {
                               cat("##############################   Start Recalculated Output #####################################\n")
                               cat("Standard Deviation Of the sammple =  ",.self$hat_sigma,"\n")
                               cat(" New Calculated Sample Size = ", .self$n, "\n")
                               cat("Price recalculated for new calculated sample size  = ", s$Price,"\n")
                               cat("Estimated Error = ", .self$estimated_error,"\n")
                               cat("##############################   End Recalculated Output #######################################\n")
                             },
                             # Create Constructor Of the class
                             initialize=function(...) {
                               callSuper(...)
                               
                               .self
                               .self$const_1 <- 14
                               .self$const_2 <- 3
                               .self$const_3 <- 0.8
                               
                               
                             }
                           )
)
cat("##############################   Start New Run ############# n = 10 ###########################\n")
#start runing with n=10 , Initialize Object Of the reference class WeatherDerivative
s <- WeatherDerivative$new(name = "another test", T_Min=70, T_Max=80,Threshold = 70, MAX_Price=100, Error= 0.01, d=7,n=10)
s$Run()
s$WriteOutput()

cat("##############################    Recalculate ##################################################\n")
s$FindSampleSize()
s$WrireOutAfterRecalculation()

cat("##############################    Recalculate ##################################################\n")
s$FindSampleSize()
s$WrireOutAfterRecalculation()
cat("##############################   End Run #######################################################\n")

cat("##############################   Start New Run ############# n = 10000 #########################\n")
#start runing with n=10 , Initialize Object Of the reference class WeatherDerivative
s <- WeatherDerivative$new(name = "another test", T_Min=70, T_Max=80,Threshold = 70, MAX_Price=100, Error= 0.01, d=7,n=10000)
s$Run()
s$WriteOutput()

cat("##############################    Recalculate ##################################################\n")
s$FindSampleSize()
s$WrireOutAfterRecalculation()

cat("##############################    Recalculate ##################################################\n")
s$FindSampleSize()
s$WrireOutAfterRecalculation()
cat("##############################   End Run #######################################################\n")



