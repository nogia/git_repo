/*
 Case Study 6
  performed by Inna Williams,
*/

/*   Chapter 6     
#######################################################################
   Problem 6.1   
#######################################################################
 */
data PROBLEM_6_1;
input DRUG $ TIME;

cards;
A 40
T 35
A 42 
T 37
A 48 
T 42
A 35 
T 22
A 62  
T 38
A 35 
T 29
;
proc ttest data=PROBLEM_6_1;
title "Problem 6.1 ";
class DRUG;
var TIME;
run;

/*
Ho -> The Aspirin and Tylenol  variances are equal.
Ha -> The Aspirin and Tylenol  variances are not equal.
F value = 2.01	p-value = 0.4606 > alpha = 0.05
Therefore we use the line for equal
for variances that is equal: 
     T value = 1.93	 Pr > |t|  -> 0.0827
Conclusion:
 Fail to reject H0
 At 0.05 Significance level the difference in
 The mean value of Aspirin time compared to the mean Value
 of the Tylenol time are not significant.
 T value = 1.93	 Pr > |t|  -> 0.0827
 With 95% confidence the mean values of the times of the
 subject to feel relief from Aspirin and from Tylenol
 are in  the interval [-1.5292,	21.1959]
 

#########################################################################
     Problem 6.3 
########################################################################
 */

proc npar1way data=PROBLEM_6_1 wilcoxon;
title "Problem 6.3 ";
class DRUG;
var TIME;
exact wilcoxon;
run;
/*
Ho -> The distribution of Aspirin time and Tylenol time are the same
Ha -> The distribution of Aspirin time and Tylenol time are not the same
Sum of Scores:
   Aspirin = 48.50
   Tylenol = 29.50
Exact Two-Sided Z test : Pr >= |S - Mean|	=  0.0179  < alpha=0.05
Conclusion:
    Fail to reject Ho. Approximation using normal approximation with
    z-correction = 1.4539 , p = 0.1460

##################################################################
Problem 6.2
##################################################################
*/
data PROBLEM_6_2;
input PROGRAM $ SCORE @@;
cards;
C 500 C 450 C 505 C 404 C 555 C 567 C 588 C 577 C 566 C 644 C 511 C 522 C 543 C 578
S 355 S 388 S 440 S 600 S 510 S 501 S 502 S 489 S 499 S 489 S 515 S 520 S 520 S 480
;
proc npar1way data=PROBLEM_6_2 wilcoxon;
title "Problem 6.2 ";
class PROGRAM;
var SCORE;
exact wilcoxon;
run;
/*
Ho -> The distribution of Scores Cody Program and Smith program are the same
Ha -> The distribution of Scores Cody Program and Smith program are not the same
Sum of Scores:
   Cody Program = 254.0
   Smith Program = 152.0
Exact Two-Sided Z test : Pr >= |S - Mean|	=  0.0179  > alpha=0.05
Conclusion:
    Reject Ho.
    The distribution of Scores Cody Program and Smith program
    are not the same.
     
##################################################################     
Problem 6.4
##################################################################
*/
DATA QUES6_4;
   DO GROUP = 'A','B','C';
      DO I = 1 to 10;
         X = ROUND(RANNOR(135)*10+300 *5*(GROUP EQ 'A') - 7 *(GROUP EQ 'C'));
         Y = ROUND(RANUNI(135)*100 + X);
         OUTPUT;
      END;
   END;
   DROP I;
run;

proc print data=QUES6_4;
title 'Problem_6_4';
run;

proc ttest data=QUES6_4;
title 'Problem_6_4 Tests for X and Y using only group A and C';
where GROUP in('A','C');
class GROUP;
var X Y;
run;
/*
Ha -> The A and C  variances are not equal for var X.
For var X : F value = 2.41		p-value = 0.2068 > alpha = 0.05
Therefore we use the line for equal.
Conclusion:
 Fail to reject H0
 At 0.05 Significance level the difference in
 The mean value of A compared to the mean Value
 of the C are not significant. Use Equal T stat
 T value = 345.27	 Pr > |t|  -> 0001
 With 95% confidence the mean values of the Group A
 and Group C are in the interval [1502.5	1520.9]

Ho -> The A and C  variances are equal for var Y
Ha -> The A and C  variances are not equal for var Y.
FOr var Y : F value = 2.56          p-value = 0.1777 > alpha =0.05
Therefore we use the line for equal.
Conclusion:
 Fail to reject H0
 At 0.05 Significance level the difference in
 The mean value of A compared to the mean Value
 of the C are not significant. Use Equal T stat
 T value = 107.24	 Pr > |t|  -> 0001
 With 95% confidence the mean values of the Group A
 and Group C are in the interval [1500.6	1560.6
/*


/*
##################################################################
Problem 6.5 
##################################################################   
*/
data Problem_6_5;
input SUBJECT $ A_TIME B_TIME;
cards;
1 20 18 
2 40 36 
3 30 30 
4 45 46 
5 19 15 
6 27 22 
7 32 29 
8 26 25
;

proc ttest data=Problem_6_5;
title "Problem 6.5";
paired A_TIME*B_TIME;
run;

/*
Ho->difference between A_TIME-B_TIME=0
Ha->difference between A_TIME-B_TIME != 0
t value = 3.00	p-value = 0.0199 < alpha=0.05
At significance level alpha=0.05 we reject Ho
Conclude:
At significance level alpha=0.05 the difference
between Drug A time and drug B time are significantly
different from zero.
It means that A_TIME - B_TIME = 3
therefore A_TIME > B_TIME
Or drug B works faster.
With 95% confidence difference A_TIME-B_TIME
are in the interval [0.4765	4.0235]

#######################################################
Problem 6_6
#######################################################
*/
data Problem_6_6;
input SUBJECT $ A_WEIGHT   B_WEIGHT  @@;
cards;

1  290  300
2  331  350
3  200  190
4  395  400
5  240  244
6  300  321
7  332  330
8  242  250
9  185  190
10 158  160
11 256  260
12 220  240
;
proc ttest data=Problem_6_6;
title "Problem 6.6";
paired A_WEIGHT*B_WEIGHT;
run;
/*
Ho->difference between A_WEIGHT-B_WEIGHT=0
Ha->difference between A_WEIGHT-B_WEIGHT != 0
t value = -2.69	p-value = 0.0212 < alpha=0.05
we reject Ho
Conclusion:
At significance level alpha=0.05 the difference
between WEIGHT after diet A  and WEIGHT after
diet B  are significantly different from zero.
It means that A_WEIGHT - B_WEIGHT = -2.69
therefore A_WEIGHT < B_WEIGHT
Or after diet B the weight is higher.
With 95% confidence difference A_WEIGHT - B_WEIGHT
are in the interval [-1.2942	,  -13.0391]

*/
data Problem_6_6_NOT_PAIRED;
input GROUP $ WEIGHT  @@;
cards;

A 290 B 300 A 331 B 350 A 200 B 190 A 395 B 400 A 240 B 244 A 300 B 321
A 332 B 330 A 242 B 250 A 185 B 190 A 158 B 160 A 256 B 260 A 220 B 240
;
proc ttest data=Problem_6_6_NOT_PAIRED;
title "Problem 6.6 IF NOT PAIRED";
class GROUP;
VAR WEIGHT;
run;

/*
Ho -> Before and After WEIGHT variances are equal.
Ha -> Before and After WEIGHT variances are not equal.
F value = 1.09 p-value = 0.8940 > alpha = 0.05
Therefore we fail to reject Ho use the line for equal
for variances that is equal:
T value = -0.25 0.8064 Pr > |t| -> 0.8064
Conclusion:
Fail to reject H0
At 0.05 Significance level the difference in
The mean value of WEIGHT Before compared to the mean Value
of the WEIGHT After are not significant.
t value = -0.25 Pr > |t| -> 0.8064
With 95% confidence the mean values of the WEIGHT Before
compare to mean values of the WEIGHT After the diet
are in the interval [-67.0951 52.7618]
for paired t value = -2.69 p-value = 0.0212
fo non paired t value = -0.25 Pr > |t| -> 0.8064
p-value for paired is much smaller 0.0212 << 0.8064
for paired : A_WEIGHT-B_WEIGHT = 3
for non-paired A_WEIGHT and B_WEIGHT variances are equal.
Or difference in mean value are not significant.



*/

