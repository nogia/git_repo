/*
  Case Study 5
  performed by Inna Williams,
*/

data Problem_5_1_5_5;
input  X Y Z;

cards;
1 3 15
7 13 7
8 12 5
3 4 14
4 7 10
;
/*   a   */
proc corr data=Problem_5_1_5_5;
title "Pearson Correlation Coefficient Between X and Y, X and Z";
var X;
with Y Z;
run;

/*
X vs Y  R=0.96509 p=0.0078
This means that X and Y have Very strong
linear positive correlation. If Y increasing then
X also increasing. 
X vs Z  R=-0.97525 p=0.0047
This means that X and Y have Very strong
linear negative correlation. If Y increasing then
X  decreasing.

Ho -> correlation =zero
Ha -> correlation not = zero
p-value < 0.0078, p=0.0047 (less then 0.05 level).This means that 
we reject Ho We have an evidence that correlations 
between X and Y, and X and  Z is not zero. 
Graph shows also that X and Y and X and Z have linear relationship.
*/
proc sgplot data=Problem_5_1_5_5;
scatter x=Y y=X;
run;
proc sgplot data=Problem_5_1_5_5;
scatter x=Z y=X;
run;
/*   b  */
proc corr data=Problem_5_1_5_5;
title "Pearson Correlation Coefficient Between variables X, Y Z";
var X Y Z;
run;
/*
X vs Y R=0.96509 p=0.0078
This means that X and Y have Very strong
linear positive correlation. If Y increasing then
X is also increasing.

X Vs Z R=-0.97525 p=0.0047
This means that X and Y have Very strong
linear negative correlation. If Z increasing then
X is decreasing.

Y vs X R=0.96509 p=0.0078
This means that Y and X have Very strong
linear positive correlation. If X increasing then
Y is also increasing.

Y Vs Z R-0.96317 p=0.0084
This means that Y and Z have Very strong
linear negative correlation. If Z increasing then
Y is decreasing.

Z vs X R=0.97525 p=0.0047
This means that Z and X have Very strong
linear positive correlation. If X increasing then
Z is also increasing.

Z Vs Y R=0.96317 p=0.0084
This means that Z and Y have Very strong
linear negative correlation. If Y increasing then
Z is decreasing.

for each case above
Ho -> correlation =zero
Ha -> correlation not = zero
p-value < ... (less then 0.05 level).This means that 
we reject Ho We have an evidence that correlations between X,Y Z 
are not  zero. 
*/

/* 5_5  a   */
proc reg data=Problem_5_1_5_5;
title "Regression Y on X";
model  Y=X ;
run;
/*      5_5  a  
b 
Intercept = 0.78916 prob|t| = 0.5753
Slope     = 1.52410	prob|t| = 0.0078
c)
Ho -> slope is zero 
Ha -> slope is not zero
p-value < 0.0078 (less then 0.05 level).This means that 
we reject Ho We have an evidence that slope not equal zero

Ho -> intercept is zero 
Ha -> Intercept is not zero
p-value = 0.5753 (> than 0.05 level).This means that 
we fail to reject Ho We do not have enouph  evidence 
to conclude that the slope is not  equal zero.

*/

/*    5_3    */
data Problem_5_3;
input AGE SBP;
cards;
15 116
20 120
25 130
30 132
40 150
50 148
;

proc corr data=Problem_5_3;
title "Problem 5_3 SBP vs Age";
var SBP AGE;
run;
/*
SBP vs Age R=0.95258 p=0.0033
This means that SBP and AGE have Very strong
linear positive correlation. If AGE increasing then
SBP is also increasing.

Age vs SBP R=0.95258 p=0.0033
This means that AGE and SBP have Very strong
linear negative correlation. If SBP increasing then
AGE is also increasing.
*/
/*     5_8      */
data DOSE_RESPONCE;
input DOSE SBP DBP;
Label
     DOSE='Dose'
     SBP='Systolic Blood Pressure'
     DBP='Diastolic Blood Pressure'
;
cards;
4 180 110
1 190 108
4 178 100
8 170 100
8 180 98
8 168 88
16 160 80
16 172 86
16 170 86
32 140 80
32 130 72
32 128 70
;
proc reg data=DOSE_RESPONCE;
title 'Problem 5_8 Dose Response';
model SBP DBP =DOSE;
run;
/*
SBP VS DOSE
Intercept = 188.82998 Slope = -1.69469

DBP VS DOSE
Intercept = 105.33643 Slope = -1.05106
*/     
     
/*
The daily attendance and the number of hot dog sales at a local ball
park are studied ove a period of games. Given the following data,
answer the following questions.
*/
data DOG_SALES;
input ATT SALES;
Label
    ATT="Attendance"
    SALES="Hot Dog Sales";
    ;
cards;
8747 6845
5857 4168
8360 5348
6945 5687
8688 6007
4534 3216
7450 5018
5874 4652
9821 7001
5873 3896
;
proc sgplot data=DOG_SALES;
title 'Dog Sales';
scatter x=ATT y=SALES;
run;

proc corr data=DOG_SALES;
title 'Correlation Coefficient Dog Sales';
Var ATT SALES;
run;
/*
Attendance vs Sale Coefficient of Correlation R=0.93748
with significance p<.0001
This means that Attendance vs Sale have Very strong
linear positive correlation. If Sales is increasing then
Attendance is also increasing.

Sale vs Attendance  Coefficient of Correlation R=0.93748
with significance p<.0001
This means that  Sale vs Attendance have Very strong
linear positive correlation. If Attendance is increasing then
Sales is also increasing.


*/
/* testing for significance 
 testing for significance 
Ho -> correlation =zero
Ha -> correlation not = zero
p-value < 0.0001 (less then 0.05 level).This means that 
we reject Ho We have an evidence that correlation is not 
zero.
*/

proc reg data=DOG_SALES;
title 'Regression  Coefficient Dog Sales';
model SALES=ATT / clb;
run;

/*
(c) Find the regression line to predict hot dogs sales based on attendance.

for Sales VS Attendence
hot dog sales = 179.41977 + 0.69362	 * Attendance

(d) What is the estimate of standard deviation (root MSE)?

Root MSE = 458.64114

(e) Report and interpret the 95% condence interval for the slope
coeffcient.

95% CI for Slope = [0.48367, 0.90356]
0.48367	0.90356
with 95% confidence for each attander there is an associated increase
in dog sales between [0.48367,	0.90356]
*/
/*
2. Although the income tax system is structured so that people with
higher incomes should pay a higher percentage of their incomes in
taxes, there are many loopholes and tax shelters available for individ-
uals with higher incomes. A sample of 2017 tax returns gave the data
listed in the table.
*/
data TAX_DATA;
input INDIVIDUAL GROSS TAX;
Label
     GROSS='Gross Income (in 1000\'' s)'
     TAX='Taxes Paid (% of Total Income)'
     ;
cards;
1 44.2 16.0
2 92.0 20.1
3 17.0 11.1
4 54.0 24.3
5 10.4 10.2
6 172.2 30.4
7 63.9 27.3
8 125.9 27.9
9 83.6 16.2
10 167.7 29.8
11 114.7 23.4
;

proc corr data=TAX_DATA;
title 'Correlation Coefficient Tax vs Gross correlation';
var TAX GROSS ;
run;
/*
TAX vs Gross : Correlation Coefficient = 0.83412 significance = 0.0014
This means that Correlation Coefficient > 0.8 and therefore
it is strong positive correlation. If Gross is increasing then Tax is
increasing.
Ho -> correlation between Tax and Gross Income equal zero
Ha -> correlation between Tax and Gross Income !=zero
because significance =0.0014 < 0.05 we reject Ho. We have a evidence
that correlation between Tax and Gross Income is not zero.

*/
/*(b) Compute r-squared and interpet results.

*/
proc reg data=TAX_DATA;
title 'Regression Tax vs Gross';
model TAX=GROSS /clb;
run;
/*
R-square = 0.6958
this means 68% of tax variation can be accounted by variation 
of Gross income.
*/

/*(c)Is the correlation coeffcient signicant at alpha = 0:05?

 Is the correlation coefficient significant at = 0:05?
Coefficient Of Correlation = 0.83412 p=0.0014
Ho - >Correlation between Tax paid  and Gross Income is zero
Ha -> correlation between Tax paid and Gross income is not zero
p-value =0.0014 < alpha=0.05 -> We reject Ho. We conclude that
we have evidence that correlation between tax paid and the gross
income is not zero.

*/
/*
(d) Compute the estimated line of regression.

TaxPaid = 12.03199 + 0.11035 * GrossIncome
 
(e)What is the estimate of standard deviation (root MSE)?
 
 root MSE = 4.23394

(f) Predict the mean percentage of income paid in taxes by individ-
uals with a gross income of $80,000. Report and interpret the
condence interval for this estimate.

   TAX($80000) = 12.03199 + 0.11035 * 80 = 20.85999
*/
data TAX_DATA; 
set TAX_DATA end=last; 
output; 
if last then do; 
TAX=.; 
GROSS=80; 
output; 
end; 
run;

proc reg data=TAX_DATA;
model TAX=GROSS / clb;
output out=TAX_DATA_out (where=(TAX=.)) predicted=TAX_hat LCLM=LCL_mean UCLM=UCL_mean; 
run;

proc print data=TAX_DATA_OUT ; 
title 'Report Prediction Of Tax Data';
var GROSS TAX_hat LCL_mean UCL_mean; 
run;

/*
for 80000	of gross income estimated tax paid = 20.8601%
with 95% CI= [17.9537 ,	23.7665]
the mean tax of 80000 income will be in the interval [17.9537 ,	23.7665].
*/