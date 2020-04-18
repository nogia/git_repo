/* Statistical Methods Using SAS
   Case Study 1
  performed by Inna Williams, January 11, 2019
/*
/****************************START CHAPTER 1*************************************/
/**************************START Problem 1****************************************/
/*2. In the Cody and Smith textbook, do the following problems.*/
/*(a) #1.1*/
data PROBLEM_1;
	input ID AGE GENGER $ GPA CSCORE;
	INDEX=GPA+3*CSCORE/500;
	cards;
1 18 M 3.7 650
2 18 F 2.0 490
3 19 F 3.3 580
4 23 M 2.8 530
5 21 M 3.5 640
;

	/*(b)#1.1*/
proc means data=PROBLEM_1 n mean median min max std q1 q3 maxdec=2;
	title "Cody Smith Problem 1 (b)";
	var GPA CSCORE;
run;
	/*(c)#1.1*/
proc sort data=PROBLEM_1;
	by INDEX;
run;
proc print data=problem_1 NOOBS;
	title "Cody Smith Problem 1 (c)";
	ID ID;
	var GPA CSCORE INDEX;
run;
/*******     Interpretetion for Chapre 1 Problem 1  ******/
/*
################################################################################
A sample of 5 has been created
Variables of interest : GPA, CSCORE
    GPA
    Mean = 3.06, Median = 3.3
    Mean approximatly equal Median => 
    Because Mean < Median the distribution is left skewed.
    The center is Median and spread is IQR=3.5-2.8=0.7
    The Range Of GPA Rate Min = 2.0 and Max = 3.7
    There are some outliers.
    
    CSCORE
    Mean = 578, Median = 580
    Mean approximatly equal Median => 
    Because Mean ~ Median the distribution is approximatly symmetric. 
    The center is Mean and spread is standard deviation 578 +- (N * 69.06)
    The Range Of GPA Rate Min = 490 and Max = 650
    There are no potential outliers.
*/
/**************************END Problem 1****************************************/
/**************************START Problem 3**************************************/
/*(b) #1.3*/
/*(a)#1.3*/
data PROBLEM_3;
	input SS SALARY AGE RACE $;
	TAX=0.3*SALARY;
	cards;
123874414 28000 35 W
646239182 29500 37 B
012437652 35100 40 W
018451357 26500 31 W
;

proc means data=PROBLEM_3 n mean median min max std q1 q3 maxdec=0;
	title "Cody Smith Problem 3 (a)";
	var SALARY AGE;
run;

	/*(b)#1.3*/
proc sort data=PROBLEM_3;
	by SS;

proc print data=PROBLEM_3;
	title "Cody Smith Problem 3 (b)";
	ID SS;
	var SALARY TAX;
run;

/*******     Interpretetion for Chapre 1 Problem 3  ******/
/*
################################################################################
A sample of 4 has been created
Variables of interest for means procedure: SALARY, AGE
    SALARY
    Mean = 29775, Median = 28750
    Mean approximatly equal Median => 
    Because Mean > Median the distribution is right skewed.
    The center is Median and spread is IQR=3.5-2.8=0.7
    The Range Of GPA Rate Min = 26500 and Max = 35100
    There are some outliers.
    
    AGE
    Mean = 36, Median = 36
    Mean approximatly equal Median => 
    Because Mean ~ Median the distribution is approximatly symmetric. 
    The center is Mean and spread is standard deviation : 36 +- (N*4)
    The Range Of Age Min = 31 and Max = 40
    There are no potential outliers.
*/
/**************************END Problem 3**************************************/
/**************************START Problem 4************************************/
/*and #1.4*/
/*(a)#1.4*/
data IQ_AND_TEST_SCORES;
	input ID 1-3 IQ 4-6 MATH 7-9 SCIENCE 10-12 OVERALL 13-15;
	OVERALL=Mean(of IQ MATH SCIENCE)/500;

	if IQ ge 0 and IQ le 100 then
		GROUP=1;
	else if IQ ge 101 and IQ le 140 then
		GROUP=2;
	else if IQ gt 140 then
		GROUP=3;
	cards;
001128550590
002102490501
003140670690
004115510510
;

	/*(b)#1.4*/
proc sort data=IQ_AND_TEST_SCORES;
	title "Cody Smith Problem 4 (a-b)";
	by IQ;

proc print data=IQ_AND_TEST_SCORES;
	ID ID;
	var IQ MATH SCIENCE OVERALL GROUP;

	/*(c)#1.4*/
proc FREQ DATA=IQ_AND_TEST_SCORES;
	title "Cody Smith Problem 4 (c) GROUP FREQ REPORT";
	TABLES GROUP;
run;
/*******     Interpretetion for Chapre 1 Problem 4  ******/
/*
################################################################################
A sample of 4 has been created
Variables of interest IQ  MATH  SCIENCE 10  OVERALL
3 Groups has been defined 
    1 : [0   - 100]
    2 : [101 - 140]
    3 : > 140
Listing has been created in IQ order
Frequancies for each of group has been computed.
There is only one group found : group 2, frequency = 4 = number in the sample
*/
/**************************END Problem 4************************************/
/**************************** START Problem 9 ************************************/
/*#1.9*/
data Problem_9;
	input ID RACE $ SBP DBP HR;
	cards;
001 W 130 80 60
002 B 140 90 70
003 W 120 70 64
004 W 150 90 76
005 B 124 86 72
;

proc sort data=Problem_9;
	BY SBP;

proc print data=Problem_9 NOOBS;
	TITLE "Race and Hemodynamic Variable";
	var ID RACE SBP DBP;
run;
/*******     Interpretetion for Chapre 1 Problem 9  ******/
/*
################################################################################
A sample of 5 has been created
Variables of interest RACE SBP DBP
Data sorted in increacing order of SBP
The Variable HR is not included
The report has a title = "Race and Hemodynamic Variable"
*/
/**************************** END  Problem 9 ************************************/
/**************************** START CHAPTER 2 ************************************/
/**************************** START Problem 2 ************************************/
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

proc print data=CLINIC NOOBS;
	title "Clinic DATA";
run;

proc means data=CLINIC n mean std clm median min max q1 q3 maxdec=0;
	title "Clinic DATA Descriptive Stat";
	var SBP DBP AVE_BP;
run;

/*******     Interpretetion Capter 2 Problem 2  ******/
/*
################################################################################
A sample of 10 days CLINIC data set has beet created.
The Variables of interest are : SBP DBP AVE_BP
    SBP
    	Mean = 127, Median = 112.
    	Because Mean > Median the distribution is rigth skewed.
    	The center is Median and spread is IQR= q3-q1 = 130-108 = 22
    	The Range Of SBP Min = 100 and Max = 190
    	108-3*22   -   130 + 3*22  = 42 - 196
    	It has the missing value that is zero and therefore the only major outlier
    	108-1.5*22  - 130 + 1.5*22 = 75 - 163 => it has no minor outliers
    DBP
    	Mean = 83, Median = 77.
    	Because Mean > Median the distribution is rigth skewed.
    	The center is Median and spread is IQR= q3-q1 = 100-70 = 30
    	The Range Of DBP Min = 66 and Max = 110
        70 - 3*30   -  100 + 3*30 =  -20 - 190 => there no major outliers
        70 - 1.5*30   -  100 + 1.5*30 =  25 - 145 => there no minor outliers
        
    AVE_BP
    	Mean = 69, Median = 63.
    	Because Mean > Median the distribution is right skewed.
    	The center is Median and spread is IQR= q3-q1 = 83-56 = 27
    	The Range Of AVE_BP Min = 53 and Max = 100
    	56 - 3*27   -  83 + 3*27 =  -25 - 164 =>   no major outliers
        56 - 1.5*27   -  83 + 1.5*27 =  15.5 - 123.5 => It has the missing value that is 
    	zero and this value is a minor outlier

##################################################################################
*/
/**************************** END Problem 2 **************************************/
/**************************** START Problem 7 ************************************/
data Problem_7;
	input SUBJECT DOSE REACT LIVER_WT SPLEEN;
	cards;
 1 1  5.4 10.2 8.9
 2 1  5.9  9.8 7.3
 3 1  4.8 12.2 9.1
 4 1  6.9 11.8 8.8
 5 1 15.8 10.9 9.0
 6 2  4.9 13.8 6.6
 7 2  5.0 12.0 7.9
 8 2  6.7 10.5 8.0
 9 2 18.2 11.9 6.9
10 2  5.5  9.9 9.1
;

proc univariate data=Problem_7 normal plots;
	TITLE "Chapter 2 Problem 7";
	var REACT LIVER_WT SPLEEN;
	Histogram REACT LIVER_WT SPLEEN;	
run;
proc sort data=Problem_7;
	BY DOSE;
proc univariate data=Problem_7 normal plots;
	TITLE "Chapter 2 Problem 7 for each of Doses";
	BY DOSE;
	var REACT LIVER_WT SPLEEN;
	Histogram REACT LIVER_WT SPLEEN;
run;
/*******     Interpretetion Capter 2 Problem 7  ******/
/*
################################################################################
A sample of 10 data set has beet created.
The Variables of interest are : REACT LIVER_WT SPLEEN
    REACT
    	Mean = 7.91, Median = 5.7
    	Because Mean > Median the distribution is rigth skewed.
    	The center is Median and spread is IQR= q3-q1 = 6.9 - 5.0 = 1.9
    	The Range Of REACT = 13.4 Min = 4.8 Max = 18.2 
    	5.0-3*1.9   -   6.9 + 3*1.9  = -0.7 - 12 => 
    	  major outliers are:
    	    5  -  15.8
    	    9  -  18.8
    	5.0-1.5*1.9   -   6.9 + 1.5*1.9  = 2.15 - 9.75
    	  minor outliers are:
    	     5  -  15.8
    	     9  -  18.8 
    LIVER_WT
         Mean = 11.30, Median = 11.35
    	 Because Mean ~ Median the distribution is approximatly symmetric.
    	 The center is Mean and spread is Staandard Deviation: 11.3 +- (N * 1.26)
    	 The Range Of LIVER_WT = 4.0 Min = 9.8 Max = 13.8
    	 Q1=10.2  Q3 = 12.2  Q3-Q1 = 2.0
    	 10.2-3*2.0   -   12.2 + 3*2.0  = 4.2 - 18.2 => 
    	 There are no major outliers
    	 10.2-1.5*2.0   -   12.2 + 1.5*2.0  = 7.2 - 15.2 => 
    	 There are no minor outliers
    SPLEEN
         Mean = 8.16, Median = 8.40
    	 Because Mean < Median the distribution is left skewed.
    	 The center is Median and spread is IRQ =q3-q1 = 9.0-7.3 = 1.7
    	 The Range Of SPLEEN = 2.5 Min = 6.6 Max = 9.1
    	 Q1=7.3  Q3 = 9.0  Q3-Q1 = 1.7
    	 7.3-3*1.7   -   9.0 + 3*1.7  = 2.2 - 14.1 => 
    	 There are no major outliers
    	 7.3-1.5*1.7   -   9.0 + 1.5*1.7  = 4.75 - 11.55 => 
    	 There are no minor outliers
    	 
    REACT for Dose 1
    	Mean = 7.76, Median = 5.9
    	Because Mean > Median the distribution is rigth skewed.
    	The center is Median and spread is IQR= q3-q1 = 6.9 - 5.4 = 1.5
    	The Range Of REACT = 11 Min = 4.8 Max = 15.8 
    	5.4-3*1.5   -   6.9 + 3*1.5  = 0.9 - 12 => 
    	     Major outliers are:
    	        5  15.8
    	5.4-1.5*1.5   -   6.9 + 1.5*1.5  = 3.15 - 11.4
    	  minor outliers are:
    	    5  15.8
    REACT for Dose 2
    	Mean = 8.05, Median = 5.5
    	Because Mean > Median the distribution is rigth skewed.
    	The center is Median and spread is IQR= q3-q1 = 6.7 - 5.0 = 1.7
    	The Range Of REACT = 13.3 Min = 4.9 Max = 18.2 
    	5.0-3*1.7   -   6.7 + 3*1.7  = -0.1 - 11.8 => 
    	     major outliers are:
    	       9  -  18.8
    	5.0-1.5*1.7   -   6.7 + 1.5*1.7  = 2.45 - 9.25
    	  minor outliers are:
    	     9  -  18.8 
    LIVER_WT fo Dose 1
         Mean = 10.98, Median = 10.9
    	 Because Mean ~ Median the distribution is approximatly symmetric.
    	 The center is Mean and spread is Standard Deviation: 10.98 +- (N * 1.02)
    	 The Range Of LIVER_WT = 2.4 Min = 9.8 Max = 12.2
    	 Q1=10.2  Q3 = 11.8  Q3-Q1 = 1.6
    	 10.2-3*1.6   -   11.8 + 3*1.6  = 7.8 - 16.6 => 
    	 There are no major outliers
    	 10.2-1.5*1.6   -   11.8 + 1.5*1.6  = 8.4 - 14.2 => 
    	 There are no minor outliers
    LIVER_WT fo Dose 2
         Mean = 11.62, Median = 11.90
    	 Because Mean < Median the distribution is left skewed.
    	 The center is Median and spread is Spread is IRQ=q3-q1= 12.0 -10.5=1.5
    	 The Range Of LIVER_WT = 3.9 Min = 9.9 Max = 13.8
    	 Q1=10.5  Q3 = 12.0  Q3-Q1 = 1.5
    	 10.5-3*1.5   -   12.0 + 3*1.5  = 6.0 - 16.5 => 
    	 There are no major outliers
    	 10.5-1.5*1.5   -   12.0 + 1.5*1.5  = 8.25 - 14.25 => 
    	 There are no minor outliers
     SPLEEN for Dose 1
         Mean = 8.62, Median = 8.90
    	 Because Mean < Median the distribution is left skewed.
    	 The center is Median and spread is IRQ =q3-q1 = 9.0-8.8 = 0.2
    	 The Range Of SPLEEN = 1.8 Min = 7.3 Max = 9.1
    	 Q1=8.8  Q3 = 9.0  Q3-Q1 = 0.2
    	 8.8-3*0.2   -   9.0 + 3*0.2  = 8.2 - 9.6 => 
    	   major outliers are:
    	       2  -  7.3
    	 8.8-1.5*0.2   -   9.0 + 1.5*0.2  = 8.5 - 9.3 => 
    	    minor outliers are:
    	       2  -  7.3
         Mean = 7.7, Median = 7.9
    	 Because Mean < Median the distribution is left skewed.
    	 The center is Median and spread is IRQ =q3-q1 = 8.0-6.9 = 1.1
    	 The Range Of SPLEEN = 2.5 Min = 6.6 Max = 9.1
    	 Q1=6.9  Q3 = 8.0  Q3-Q1 = 1.1
    	 6.9-3*1.1   -   8.0 + 3*1.1  = 3.6 - 11.1 => 
    	 There are no major outliers
    	 6.9-1.5*1.1   -   8.0 + 1.5*1.1  = 5.25 - 9.65 => 
    	 There are no minor outliers
    
/**************************** END Problem 7 ************************************/
/**************************** END CHAPTER 2 **************************************/
/*###############################################################################*/
/*1. Nurses in the cardiac ICU
oor of Cook County Hospital believe they
need extra stang at night. To estimate the night workload, a sample
of the number of calls received in the evening shift in November 2018
was used. For each night, the total number of room calls was recorded
as follows:
68 70 86 48 90 75 58 67
95 80 70 73 82 56 67 78
37 46 58 62 63 45 71
70 69 75 69 65 54 65
Using proc means in SAS, compute the mean, standard deviation,
and median. Characterize the results in paragraph form, similar to
the cigarette tar example we did in class.*/
data NOVEMBER_NIGTH_CALLS;
	input DayOfMonth NumCalls;
	cards;
1 68
2 70
3 86
4 48
5 90
6 75
7 58
8 67
9 95
10 80
11 70
12 73
13 82
14 56
15 67
16 78
17 37
18 46
19 58
20 62
21 63
22 45
23 71
24 70
25 69
26 75
27 69
28 65
29 54
30 65
;

proc means data=NOVEMBER_NIGTH_CALLS n mean stddev median min max q1 q3 maxdec=0;
	title "Night Workload November 2018 Mean Standard Deviation Median";
	var NumCalls;
run;

proc univariate data=NOVEMBER_NIGTH_CALLS normal plots;
	title "Night More Descriptive Stat Workload November 2018";
	var NumCalls;
run;

/*******     Interpretetion for November 2018  Night Calls  ******/
/*
################################################################################
A sample of 30 days of number of calls was recorded.
Mean = 67, Median = 69.
Because Mean < Median the distribution is left skewed.
The center is Median and spread is IQR= q3-q1 = 75-58 = 17
The Range Of Calls Min = 37 and Max = 95
58 - 1.5 * 17  - 75 + 1.5*17 = 32.5 - 100.5
There appear to be no potential outliers.
##################################################################################
*/
/*###################################################################################*/
/*3. Under the Week One course content in D2L, download the data set
unemployment.csv and read it into SAS. These data represent the
estimated unemployment rates in November 2018 for the 50 states
and the District of Columbia as reported by the Bureau of Labor
Statistics. Which states have above average unemployment rates and
which states have below average unemployment rates? Characterize
sample results in a manner similar to the cigarette tar example we did
in class.*/
proc import datafile='/folders/myfolders/data/week1/unemployment.csv' 
		out=unemp_data dbms=csv replace;
	delimiter=',';
	getnames=yes;
run;

options nodate ps=60 ls=80;

proc means data=unemp_data mean median stddev min max  maxdec=2;
  TITLE "Problem 3. Unemployment";
  var Nov2018;
run;

proc univariate data=unemp_data normal plots;
  TITLE "Problem 3. Unemployment";
  var Nov2018;
run;

proc sql noprint;
	create table new_unemp_data as select State, Nov2018 , MEAN(Nov2018) as MEAN 
		from unemp_data;
	create table new1_unemp_data as select State, Nov2018 from new_unemp_data 
		where Nov2018 ge MEAN;
	create table new2_unemp_data as select State, Nov2018 from new_unemp_data 
		where Nov2018 lt MEAN;
quit;

proc print data=new1_unemp_data NOOBS;
	TITLE "Problem 3. Unemplyment Table Of States Above or Equal the average ";

proc print data=new2_unemp_data NOOBS;
	TITLE "Problem 3. Unemplyment Table Of States Below the average ";
run;
/*******     Interpretetion for November 2018  Unemployment rates  ******/
/*
################################################################################
A sample of 51 states has been drawn and Unemplyment Rate for each state for November 2018
has been recorded.
Mean = 3.73, Median = 3.70
Mean approximatly equal Median => 
Because Mean ~ Median the distribution is approximatly symmetric. 
The center is Mean and spread is Standard Deviation 3.73 +- (N * 0.82) , n=1,2,3
The Range Of Unemployment Rate Min = 2.4 and Max = 6.3
IQR = q3-q1=4.2-3.2=1.0
3.2-1.5*1.0  -  4.2+1.5*1.0 = 1.7 - 5.7
    outliers are:
        Alaska	6.3
Problem 3. Unemplyment Table Of States Above or Equal the average 
           output in the Results file

State	Nov2018
Delaware	3.8
Rhode Island	3.8
Michigan	3.9
New York	3.9
Oregon	3.9
Alabama	4
Maryland	4
New Jersey	4
California	4.1
Connecticut	4.1
Wyoming	4.1
Illinois	4.2
Pennsylvania	4.2
Washington	4.3
Nevada	4.4
Kentucky	4.5
New Mexico	4.6
Ohio	4.6
Arizona	4.7
Mississippi	4.7
Louisiana	5
West Virginia	5.2
District of Co	5.6
Alaska	6.3

Problem 3. Unemplyment Table Of States Below the average
 output in the Results file

State	Nov2018
Hawaii	2.4
Iowa	2.4
New Hampshire	2.5
Idaho	2.6
Vermont	2.7
Minnesota	2.8
Nebraska	2.8
North Dakota	2.8
Virginia	2.8
Missouri	3
South Dakota	3
Wisconsin	3
Kansas	3.2
Utah	3.2
Colorado	3.3
Florida	3.3
Oklahoma	3.3
South Carolina	3.3
Maine	3.4
Massachusetts	3.4
Georgia	3.5
Arkansas	3.6
Indiana	3.6
North Carolina	3.6
Tennessee	3.6
Montana	3.7
Texas	3.7
##################################################################################
*/
/*###################################################################################*/
/*4. The data set fueleconomy2016.csv, found in the Week One course
content in D2L, summarizes the fuel economy and other information
of 1211 dierent model cars in 2016. (Note that these data are from
the website fueleconomy.gov and DASL, the Data and Story Library
housed by Carnegie Mellon University.) Find the descriptive statistics
for the CombinedMPG variable for each Class of car. Summarize your
results.*/
proc import datafile='/folders/myfolders/data/week1/fueleconomy2016.csv' 
		out=fueleconomy2016 dbms=csv replace;
	delimiter=',';
	getnames=yes;
run;

options nodate ps=60 ls=80;

proc sort data=fueleconomy2016;
	BY Class CombinedMPG;

proc means data=fueleconomy2016 mean stddev min q1 median q3 max maxdec=3;
	TITLE "Fuel Economy 2016 Simple Descriptive Statistics for Combined MPG";
	BY Class;
	var CombinedMPG;

proc univariate data=fueleconomy2016 normal plot;
	TITLE 
		"Fuel Economy 2016 More Descriptive Statistics for Combined MPG normal plot";
	BY Class;
	var CombinedMPG;
	QQPLOT CombinedMPG;
	Histogram CombinedMPG;
run;

*******     Interpretetion for FuelEconomy2016   ******/
/*
################################################################################
A sample of 1211 different car models has been drawn. 
Variable Of interest CombinedMPG
Descriptive statistics were found for each class of car
11 Different Classes has been found and descriptive statistics for each class
1     Class=Compact Car
        Mean = 26.372, Median = 27.000
        Mean approximatly equal Median => 
        Because Mean ~ Median the distribution is approximatly symmetric. 
        The center is Mean and spread is Standard Deviation : 26.372 +- (N * 5.26) , n=1,2,3
        The Range Of Compact Car Min = 14 and Max = 50
        IQR=q3-q1=29-23=6
        23-1.5*6  - 29+1.5*6 = 14 -  38
            outliers are:3 outliers
                Compact Car	42
                Compact Car	44
                Compact Car	50
2     Class=Large Cars
        Mean = 21.194, Median = 21.000
        Mean approximatly equal Median => 
        Because Mean ~ Median the distribution is approximatly symmetric. 
        The center is Mean and spread is Standard Deviation : 21.194 +- (N * 4.254) , n=1,2,3
        The Range Of Unemployment Rate Min = 14 and Max = 40
        IQR=q3-q1=23-18=5
        18-1.5*5  - 23+1.5*5 = 10.5 -  30.5
            outliers are:3 outliers
                Large Cars	32
                Large Cars	32
                Large Cars	40
3     Class=Midsize Car
        Mean = 26.364, Median = 26.000
        Mean approximatly equal Median => 
        Because Mean ~ Median the distribution is approximatly symmetric. 
        The center is Mean and spread is Standard Deviation : 26.364 +- (N * 6.727	) , n=1,2,3
        The Range Of Midsize Car Min = 13 and Max = 56
        IQR=q3-q1=30-22=8
        22-1.5*8  - 30+1.5*8 = 10.0 -  42.0
            outliers are: 3 outliers
                Midsize Car	46
                Midsize Car	52
                Midsize Car	56
4     Class=Minicompact
        Mean = 22.868, Median = 22.000
        Mean approximatly equal Median => 
        Because Mean ~ Median the distribution is approximatly symmetric. 
        The center is Mean and spread is Standard Deviation : 22.868 +- (N * 4.067) , n=1,2,3
        The Range Of Minicompact Min = 15 and Max = 34
        IQR=q3-q1=25-21=4
        21-1.5*4  - 25+1.5*4 = 15.0 -  31.0
            outliers are: 1 outlier
                Minicompact	34
5     Class=Pick-up Tru
        Mean = 18.94, Median = 19.00
        Mean approximatly equal Median => 
        Because Mean ~ Median the distribution is approximatly symmetric. 
        The center is Mean and spread is Standard Deviation : 18.9422.868 +- (N * 2.476) , n=1,2,3
        The Range Of Pick-up Tru Min = 13 and Max = 25
        IQR=q3-q1=21-17=4
        17-1.5*4  - 21+1.5*4 = 11.0 -  27.0
        There is no potential outliers
6     Class=SUV
        Mean = 21.835, Median = 22.00
        Mean approximatly equal Median => 
        Because Mean ~ Median the distribution is approximatly symmetric. 
        The center is Mean and spread is Standard Deviation : 21.83522.868 +- (N * 4.067) , n=1,2,3
        The Range Of SUV Min = 12 and Max = 33
        IQR=q3-q1=25-18=7
        21-1.5*7  - 25+1.5*7 = 10.5 -  35.5
        There is no potential outliers
7     Class=Special Pur
        Mean = 20.686, Median = 21.0
        Mean approximatly equal Median => 
        Because Mean ~ Median the distribution is approximatly symmetric. 
        The center is Mean and spread is Standard Deviation : 20.686 +- (N * 2.795) , n=1,2,3
        The Range Of Special Pur Min = 16 and Max = 25
        IQR=q3-q1=23-18=5
        18-1.5*5  - 23+1.5*5 = 10.5 -  30.5
        There is no potential outliers
8     Class=Station Wag
        Mean = 27.48, Median = 28.0
        Mean approximatly equal Median => 
        Because Mean ~ Median the distribution is approximatly symmetric. 
        The center is Mean and spread is Standard Deviation : 27.48 +- (N * 4.628) , n=1,2,3
        The Range Of Station Wag Min = 18 and Max = 42
        IQR=q3-q1=30.0-24.5=5.5
        24-1.5*5.5  - 30+1.5*5.5 = 15.75 -  38.5
        outliers are: 1 outlier
                Station Wag	42
9     Class=Subcompact
        Mean = 23.70, Median = 24.0
        Mean approximatly equal Median => 
        Because Mean ~ Median the distribution is approximatly symmetric. 
        The center is Mean and spread is Standard Deviation : 23.70 +- (N * 5.036) , n=1,2,3
        The Range Of Subcompact Wag Min = 15 and Max = 37
        IQR=q3-q1=27.0-20.0=7.0
        20-1.5*7.0  - 27+1.5*7.0 = 9.5 -  37.5
        There is no potential outliersoutliers
10     Class=Two Seaters
        Mean = 20.34, Median = 19.00
        Mean approximatly equal Median => 
        Because Mean ~ Median the distribution is approximatly symmetric. 
        The center is Mean and spread is Standard Deviation : 20.34 +- (N * 5.397) , n=1,2,3
        The Range Of Class=Two Seaters Min = 12 and Max = 37
        IQR=q3-q1=23.0-17.0=6.0
        17-1.5*6.0  - 23+1.5*6.0 = 8.0 -  32.0
        outliers are: 4 outlier
          Two Seaters	34
          Two Seaters	35
          Two Seaters	36
          Two Seaters	37
11     Class=Vans, Passe
        Mean = 13.67, Median = 13.00
        Mean approximatly equal Median => 
        Because Mean ~ Median the distribution is approximatly symmetric. 
        The center is Mean and spread is Standard Deviation : 13.67 +- (N * 1.862) , n=1,2,3
        The Range Of Vans, Passe Min = 12 and Max = 16
        IQR=q3-q1=16.0-12.0=4.0
        12-1.5*4.0  - 16+1.5*4.0 = 6.0 -  22.0
        There is no potential outliersoutliers
                                                         
/*#####################################################################################*/