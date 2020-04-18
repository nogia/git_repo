/*
  performed by Inna Williams
/*
/*(a) #2.4*/

data CLINIC;
	input ID 1-3 GENDER $ 4 RACE $ 5 HR 6-8 SBP 9-11 DBP 12-14 N_PROC 15-16;
	AVE_BP=DBP-(1/3)*(SBP-DBP);
	cards;
001MW08013008010
002FW08811007205
003MB05010010002
004FB   10806801
005MW06812208204
006FB101   07404
007FW07810406603
008MW04811207006
009FB07719011009
010FB06616410610
;

proc freq data=CLINIC;
 title "Clinic DATA Chapter 2 Problem 4 Freq  for Gender";
 tables GENDER / nocum;
 
proc sgplot data=CLINIC;
title "Clinic DATA Chapter 2 Problem 4 Bar charts for Gender";
vbar Gender;
run; 
                                                      
/*#####################################################################################*/
/*(b) #2.8*/

proc sgpanel data=CLINIC;
title "Clinic DATA Chapter 2 Problem 8 Bar charts of each Gender for each Race";
panelby RACE;
vbar GENDER;
run;

proc sgpanel data=CLINIC;
title "Clinic DATA Chapter 2 Problem 8 Distribution Of HR for each Gender";
panelby GENDER;
histogram HR;

/*(c) #2.10*/
/*  (a) */
proc sgplot data=CLINIC;
title "Chapter 2 Problem 10 a sgplot x=HR y=SBP";
scatter x=HR y=SBP / markerattrs=(symbol=diamond 
size=2.5mm color=blue) dataskin=sheen;
xaxis label="Heart Rate";
yaxis label="Systolic Blood Pressure";
run;
/*Interpretation for the graph*/
/*
From the graph I do not see any relation between Heart Rate and 
the systolic pressure
*/

/*  (b) */
proc sgplot data=CLINIC;
title "Chapter 2 Problem 10 b sgplot x=DBP y=SBP";
scatter x=DBP y=SBP / markerattrs=(symbol=diamond size=2.5mm color=blue) dataskin=sheen;
xaxis label="Diastolic blood presure";
yaxis label="Systolic Blood Pressure";
run;
/*Interpretation for the graph*/
/*
Interpretation for the graph
From the graph I can say that Systolic blood pressure increases
With increasing Diastolic blood pressure.

*/

/*  (c) */
/* Todsplay on  two separate graphs */
data RACEW;
set CLINIC;
if RACE EQ "W";

data RACEB;
set CLINIC;
if RACE EQ "B";

run;

proc sgplot data=RACEW;
title "Chapter 2 Problem 10 c sgplot x=DBP y=SBP";
by RACE;
scatter x=DBP y=SBP / markerattrs=(symbol=diamond 
size=2.5mm colors=cxFF6666) dataskin=sheen;
xaxis label="Diastolic blood presure";
yaxis label="Systolic Blood Pressure";

proc sgplot data=RACEB;
title "Chapter 2 Problem 10 c sgplot x=DBP y=SBP";
by RACE;
scatter x=DBP y=SBP / markerattrs=(symbol=diamond 
size=2.5mm colors=cxFF6666) dataskin=sheen;
xaxis label="Diastolic blood presure";
yaxis label="Systolic Blood Pressure";
run;

/*
or we can see both graphs in separate panels
*/
proc sgpanel data=CLINIC;
title "Chapter 2 Problem 10 c sgpanel x=DBP y=SBP";
panelby RACE;
scatter x=DBP y=SBP / markerattrs=(symbol=diamond size=2.5mm colors=cxFF6666) dataskin=sheen;

run;

/*2. The data set fueleconomy2016.csv, found in the Week One course
content in D2L, summarizes the fuel economy and other information
of 1211 different model cars in 2016. (Note that these data are from
the website fueleconomy.gov and DASL, the Data and Story Library
housed by Carnegie Mellon University.)*/
/*(a) Create boxplots for the Combined MPG variable for each Class of car.*/

proc import datafile='/folders/myfolders/data/week1/fueleconomy2016.csv' 
	out=fueleconomy2016 dbms=csv replace;
	delimiter=',';
	getnames=yes;
run;

options nodate ps=60 ls=80;

proc sgplot data=fueleconomy2016;
	TITLE "Fuel Economy 2016  (a) Combined MPG";
	vbox CombinedMPG /group=Class;
	
/********     Interpretetion for FuelEconomy2016   ******/
/*
Variable Of interest CombinedMPG
11 classes found
Vbox plot shows that on each class of car the mean ~ median
therefore the center is a mean and spread is standard deviation
Plot also shows outliers for each class of car;
Compact Car has 3 outliers between 40 and 50
Large car has 2 outliers  between 30 and 40
Midsize car has 3 outliers > 45
Minicompact car has 1 outlier between 30 and 40
Station Wag has 1 outlier between 40 and 50
Two seaters has 4 outliers between 40 and 50
/*


(b) Is there a relationship between fuel economy, measured by the
Combined MPG variable and the engine displacement in liters,
measured by the Displacement variable. Create a scatterplot
of these two variables and explain what you see.*/


proc sgplot data=fueleconomy2016;
title "Fuel Economy 2016 (b) Combined MPG";
scatter x=Displacement y=CombinedMPG / markerattrs=(symbol=plus size=1.5mm colors=maroon) dataskin=sheen;
xaxis label="Engine Displacement In Liters";
yaxis label="Fuel Economy";

run;
/********     Interpretetion for the graph   ******/
/*
From the graph we can see that with increasing the displacement in liters
the fuel economy decreases. The relationship is  seems like ~ Hyperbolic decay
of fuel economy with increasing the displacement in liters.
*/