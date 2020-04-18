/*
  performed by Inna Williams,
/*
/****************************START CHAPTER 3*************************************/
/**************************START Problem 1****************************************/


proc format;
value FORMAT_GROUP
               1 = 'Control'
               2 = 'Aspirin'
               3 = 'Ibuprofen'
               ;
run;
/**************************END Problem 1****************************************/
/**************************START Problem 3****************************************/
/* a) */
proc format;
value $GENDER
          'M'='Male'
          'F'='Female'
          ;
value $PARTY
           '1'='Republican'
           '2'='Democrat'
           '3'='Not Registered'
   ;
value YESNO
           0='No'
           1='Yes'
           ;
data Survey_Data;
	input ID 1-3 GENDER $ 4 PARTY $ 5 VOTE 6 FOREIGN 7 SPEND 8;

label
	PARTY='Political Party'
	VOTE='Vote in the last election'
	FOREIGN='Agree with the government foreign policy?'
	SPEND='Should we increase domestic spending'
;
format GENDER $GENDER.
       PARTY $PARTY.
       VOTE FOREIGN SPEND YESNO.
;
cards;
007M1110
013F2101
137F1001
117 1111
428M3110
017F3101
037M2101
;
proc print data=Survey_Data;
title "Chapter 3 Problem 3 a";
run;
/*  b)  */
proc freq data=Survey_Data;
title "Chapter 3 Problem 3 b";
tables GENDER PARTY VOTE FOREIGN SPEND;
run;

/*  c)  */
proc freq data=Survey_Data;
title "Chapter 3 Problem 3 c";
tables VOTE*(SPEND FOREIGN) / CHISQ;
run;
/**************************END Problem 3****************************************/
/**************************START Problem 5****************************************/
/*using if  */
data DEMOG;
input WEIGHT HEIGHT GENDER $;
if WEIGHT >= 0 and WEIGHT <= 100 then CATEGORYW=1;
else if WEIGHT >=101  and WEIGHT <= 150 then CATEGORYW=2;
else if WEIGHT >=151 and WEIGHT <=200 then CATEGORYW=3;
else if WEIGHT >200 then CATEGORYW=4;

if HEIGHT>=0 and HEIGHT<=70 then CATEGORYH=1;
else if HEIGHT>70 then CATEGORYH=2;
cards;

155 68 M
98 60 F
202 72 M
280 75 M
130 63 F
.   57 F
166  . M
;

proc freq data=DEMOG;
title 'Chapter 3 Problem 5 creating categories using if';
tables CATEGORYW*CATEGORYH;
run;
/* using format  */
proc format;
value CATEGORYW
               0-100=1
               101-150=2
               151-200=3
               200-HIGH=4;
value CATEGORYH
               0-70=1
               70-HIGH=2;

run;
data DEMOG_1;
input WEIGHT HEIGHT GENDER $;
format WEIGHT CATEGORYW. HEIGHT CATEGORYH.
;
cards;

155 68 M
98 60 F
202 72 M
280 75 M
130 63 F
.   57 F
166  . M
;

proc freq data=DEMOG_1;
title 'Chapter 3 Problem 5 creating categories using format';
tables WEIGHT*HEIGHT;
run;
/**************************END Problem 5****************************************/
/**************************START Problem 6****************************************/
data LEUKEMIA_TO_EXPOSURE;
input group $ RADIATION $ COUNT;

cards;
CASE 1-EXPOSED 50
CASE 2-NEXPOSED 500
CONTROL 1-EXPOSED 40
CONTROL 2-NEXPOSED 500
;
proc freq data=LEUKEMIA_TO_EXPOSURE;
  title 'Chapter 3 Problem 6 Leukemia Exposure';
  tables RADIATION*GROUP / CHISQ cmh;
  weight count;
run;
/*                               Interpretation                   */
/*
Ho -> Having LEUKEMIA And being exposed to Radiation are independent
of each other
Chi-square = 1.0195, p-value = 0.3126 > 0.05
therefore Decision is:
fail to reject Ho
There is not enough evidence that
the people with LEUKEMIA And being exposed to Radiation have significant relationship

Odds Ratio = 1.25
95% confidence =(0.8100-1.9290)
This means we can say that the true population odds ratio is in interval
(0.8100-1.9290)
Since the interval contains 1 we can conclude that the odds ratio is not
significant for alpha=0.05
fail to reject Ho
There is not enough evidence that
the people with LEUKEMIA And being exposed to Radiation have significant relationship

*/

/**************************END Problem 6****************************************/
/**************************STARTProblem 7****************************************/
data SES_Astma;
input GROUP $ ASTMA $ COUNT;
cards;
LowSES 1-Yes 40
LowSES 2-No 100
HighSES 1-Yes 30
HighSES 2-No 130
;
proc freq data=SES_Astma;
  title 'Chapter 3 Problem 7 SES ASTMA';
  tables GROUP*ASTMA / CHISQ cmh;
  weight count;
run;
/*  Interpretation */
/*
Ho-> assume that Asthma and SES is independent variables
Chisq = 4.0262 p-value = 0.0448 ~ 0.05 = alpha = 0.05
therefore Decision is:
There is some not strong relationship between having
Asthma and SES

*/
/**************************END Problem 7****************************************/
/**************************START Problem 8****************************************/
proc freq data=SES_Astma;
  title 'Chapter 3 Problem 8 Relative Risk SES ASTMA';
  tables GROUP*ASTMA / CHISQ relrisk ;
  weight count;
run;
/* Interpretation */
/*
Relative Risk for Low SES = 0.6563	
95%CI = (0.4331	0.9943)
This means that with 95% confidence we can say that
Relative Risk for Low SES is in within (0.4331-0.6563) interval
*/

/**************************End Problem 8****************************************/
/**************************START Problem 11****************************************/

data VDT_MISCARRIAGES;
  input GROUP $ MISCARRIAGES $ COUNT;
cards;
CASE_MIS 1-Yes 30
CASE_MIS 2-No 50
CONTROL 1-Yes 90
CONTROL 2-No 200
;
  
proc freq data=VDT_MISCARRIAGES;
  title 'Chapter 3 Problem 11 VDT Miscarriages';
  tables GROUP*MISCARRIAGES / CHISQ cmh;
  weight count;
run;
/* Interpretation */
/*
Ho -> Assume that using VDT and having a miscarriage are independent variables
Chisq = 1.1961	p-value = 0.2741 > 0.05
therefore Decision is:
fail to reject Ho
There is not enough evidence that
using VDT and having a miscarriage have significant relationship
Odds Ratio = 1.3333	95% CI = (0.7955	2.2349)
We can say with 95% confidence that the odds ratio  is
in interval(0.7955 2.2349)
*/

/**************************END Problem 11****************************************/
/**************************START Problem 13****************************************/
data  SPB_Children;
input GROUP $ BEHAVIOR $ COUNT;

cards;
STANDARD 1-Yes 30
STANDARD 2-No 220
S_PROOFED 1-Yes 20
S_PROOFED 2-No 280
;
proc freq data=SPB_Children;
 title 'Chapter 3 Problem 13 Sound Proof Behaviour Of Children';
 tables GROUP*BEHAVIOR /  relrisk ;
 weight count;
run;
/* Interpretation */
/*
Ho ->Problems are depend on noise
Relative Risk (Column 1->noisy classroom) = 1.8000
95% CI = (1.0486 3.0898)
This interval does not contain 1
We can say with 95% confidence that Relative Risk  for
producing behavioral problems is
in interval(0.7955 2.2349)
We can say That Relative Risk is significant and we reject Ho
We can Conclude that noise and incidence of problems are depend
on each other. 
*/
/**************************END Problem 13****************************************/
/**************************START Problem 15****************************************/

proc format;
value SIZE
               1 = 'Small'
               2 = 'Medium'
               3 = 'Large'
               4 = 'Gigantic'
               ;
run;
data CLASS;
input SIZE PROBLEM $ COUNT @@;
format SIZE SIZE.;
cards;
1 1-YES 3 1 2-NO 12 2 1-YES 6 2 2-NO 22
3 1-YES 17 3 2-NO 38 4 1-YES 80 4 2-NO 120
;
proc freq data=CLASS;
title 'Chapter 3 Problem 15 CLASS Size and Behavior';
tables PROBLEM*SIZE / CHISQ;
weight count;
run;

/* Interpretation */
/*
Ho -> Assume that Problem is independent from SIZE
Ho ->Problems are depend on noise
Relative Risk (Column 1->noisy classroom) = 1.8000
95% CI = (1.0486 3.0898). This interval does not contain 1
We can say with 95% confidence that Relative Risk  for
producing behavioral problems is in interval(1.0486 3.089)
We can say That Relative Risk is significant and we reject Ho
We can Conclude that noise and incidence of problems are depend
on each other.
*/
/**************************START Problem 16****************************************/
data HEART_ATTACKS_AND_STROCKS;
input DESEASE_GROUP $ GROUP $ RESULTS $ COUNT;

cards;
HA ASPIRIN 1-YES  80
STROKE ASPIRIN 1-YES  65
HA ASPIRIN 2-NO  1000-80
STROKE ASPIRIN 2-NO  2000-65
HA PLASEBO 1-YES  80
STROKE PLASEBO 1-YES  65
HA PLASEBO 2-NO  1000-80
STROKE PLASEBO 2-NO  2000-65
;
proc freq data=heart_attacks_and_strocks;
title 'Chapter 3 Problem 16 Aspirin On HA and Strokes';
 tables DESEASE_GROUP*RESULTS*GROUP / cmh;
 weight COUNT;
run;
/**************************END Problem 16****************************************/
data HEART_ATTACKS_AND_STROCKS;
input DESEASE_GROUP $ GROUP $ RESULTS $ COUNT;

cards;
HA ASPIRIN 1-YES  80
STROKE ASPIRIN 1-YES  65
HA ASPIRIN 2-NO  920
STROKE ASPIRIN 2-NO  935
HA PLASEBO 1-YES  240
STROKE PLASEBO 1-YES  165
HA PLASEBO 2-NO  1760
STROKE PLASEBO 2-NO  1835
;
proc freq data=heart_attacks_and_strocks;
title 'Chapter 3 Problem 16 Aspirin On HA and Strokes';
 tables DESEASE_GROUP*GROUP*RESULTS / all;
 weight COUNT;
run;
/*   Interpretation   */
/*
Ho -> taking the Aspirin is independent from Heart Attack 
Prevention 
Test for HA
Relative Risk for Aspirin (Column 1)=0.6667 -> means 66% risk to get HA compared to
to those who took plasebo	
95% CI = (0.5237	0.8487)
This means that with 95% confidence that Relative Risk value is in
interval(0.5237	0.8487)
The confidence interval does not contain 1 we can reject the Ho 
and conclude that taking Aspirin does not prevent Heart Attack.

Ho -> taking the Aspirin is independent from Stroke 
Prevention
TEST for Stroke
Relative Risk for Aspirin (Column 1 )=0.7879 -> means 78% risk to get Stroke 
compared to those who took placebo
95% CI = (0.5974	1.0391)
This means that with 95% confidence that Relative Risk value is in
interval(0.5974	1.0391)
The confidence interval contains 1 therefore
we fail to reject the Ho and we conclude that there is a dependence
between taking the Aspirin and Stroke prevention but there is not
enouph evidence that this dependents prevent Stroke.
*/
/**************************START Problem 18****************************************/
data STUDY;
input STUDY $ RESULTS $ NAME $ COUNT;

cards;
STUDY_1 DIED 1-MGSO4 100
STUDY_1 DIED 2-PLACEBO 155
STUDY_1 SURV 1-MGSO4 20
STUDY_1 SURV 2-PLACEBO 25
STUDY_2 DIED 1-MGSO4 150
STUDY_2 DIED 2-PLACEBO 150
STUDY_2 SURV 1-MGSO4 25
STUDY_2 SURV 2-PLACEBO 21
STUDY_3 DIED 1-MGSO4 200
STUDY_3 DIED 2-PLACEBO 240
STUDY_3 SURV 1-MGSO4 30
STUDY_3 SURV 2-PLACEBO 28

;
proc freq data=STUDY;
title 'Chapter 3 Problem 18 Study Effects Of Magnesium';
tables STUDY*NAME*RESULTS/all;
weight count;
run;
/* Interpretation */
/*
Breslow-Day Test for
Homogeneity of the Odds Ratios=0.9836 is not significant so we can combine the result of 3 studies.
Chi-Square	for Study 1= 0.4357	p-value = 0.5092
Relative Risk for survival(Column 1)=1.2000	95% CI=(0.6988	2.0607)

Chi-Square	for Study 2= 0.3016	p-value =0.5829
Relative Risk for survival(Column 1)=1.1633	95% CI=(0.6775	1.9972)

Chi-Square	for Study 3= 0.8104	p-value = 0.3680
Relative Risk for survival(Column 1)=1.2484	95% CI=(0.7695	2.0256)

FROM Combined Studies :
Relative Risk Mantel-Haenszel for survival(Column 1)=0.9721	95% CI=(0.9288	1.0174) -> means that with 95% confidence the relative risk is inside the interval (0.9288	1.0174). Because the interval contains 1
we can conclude that the ratio is not significant for alpha=0.05
Therefore we fail to reject Ho and there is not enough evidence
to conclude that MgSO4 has improvement on survival.

*/
/**************************END Problem 18****************************************/
