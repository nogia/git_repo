Number_Of_Simulations=100
player_number=1
number_of_players=3
cat("Enter number_of_players ")
number_of_players <- readLines(file("stdin"),1)
cat("Enter player_number to win ")
player_number <- readLines(file("stdin"),1)
cat("Enter Number_Of_Simulations ")
Number_Of_Simulations <- readLines(file("stdin"),1)

Number_Of_Simulations <- as.integer(Number_Of_Simulations)
player_number <- as.integer(player_number)
number_of_players <- as.integer(number_of_players)
out_start=paste("number_of_players =", number_of_players, "player_number to get winning ticket = ", player_number, "Number_Of_Simulations = ",Number_Of_Simulations)
print(out_start)

theoretiical_value <-function(player_number,number_of_players)
{
  
  probability_Of_n_player_win = 1;
  # number of tickects = number of playes
  
  p_cur=1/number_of_players;
  q_cur=1-p_cur;
  for(p_cur_num_of_players in number_of_players:player_number-1)
  {
    probability_Of_n_player_win=probability_Of_n_player_win*q_cur
    p_cur=1/p_cur_num_of_players;
    q_cur=1-p_cur;
   
  }
  probability_Of_n_player_win=probability_Of_n_player_win*p_cur
  return ( probability_Of_n_player_win)
}

# Using Replicate

# functionsuccess retuns 1 if 
# player_number  draw winning ticket
success <-function(player_number,number_of_players)
{
  success=0
  #create winner number one out of {1,2,3,4,5  k}
  winning_number=sample(1:number_of_players, 1)
  # draws winner_number of elemets of the array out of random  numbers=number_of_payers  
  # without replacement
  # each element of the array  reppesent a guess for a winning number 
  xk <- sample(1:number_of_players, player_number, replace=F)
  # match the position of the correct guess
  # zero if no correct guess
  pos=match( winning_number,xk,nomatch = 0)
  # if the position of correct guess correspond to the 
  # player_number then set success and return 
  if(pos==player_number)
  {
    success=1
  }
  return (success)
}

# Count number of sussesfull guess for player_number
# and devide on Number_Of_Simulations
#This function calculate probability that player_number
# gets the winning ticket
print('###################################################################')
print('Start using_replications')
# replicate success function Number_Of_Simulations times


using_replications<-replicate(Number_Of_Simulations,
                              {
                                success(player_number,number_of_players)
                              }
)
calculated_probability2 = length(grep(1, using_replications))/Number_Of_Simulations

print('End using_replications')

theoretiical_value_OfProbability=theoretiical_value(player_number,number_of_players)
relative_error2=abs((theoretiical_value_OfProbability-calculated_probability2)*100/theoretiical_value_OfProbability);
out2=paste('player number =' , player_number , "  probability to get winning ticket = " , calculated_probability2, "theoretical value = ",theoretiical_value_OfProbability," relative error = ",relative_error2, "%") 
print(out2)
print("End Of File")
