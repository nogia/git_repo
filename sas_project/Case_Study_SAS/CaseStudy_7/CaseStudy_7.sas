/*
  Case Study 7
  performed by Inna Williams,
*/

/*   Chapter 7     
#######################################################################
   Problem 7.1   
#######################################################################
 */
data Problem_7_1;
 do BRAND = 'A', 'N', 'T';
    do SUBJECT = 1 to 8;
       input TIME @;
       output;
    end;
 end;
cards;
8  10  9 11 10 10 8 12
4   7  5  5  6  7 6  4
12  8 10 10 11  9 9 12
; 

proc anova data=problem_7_1;
title "Problem_7_1";
class BRAND;
model TIME=BRAND;
means BRAND / tukey;
run;
/*
Ho-> the brands are equal in wear quality
Ha-> the the brands are not equal in wear quality
F value = 28.89	p-value = 0.0001 <= alpha = 0.005
Reject Ho.
Conclusion:
At least one of the brands are not equal to one of
others in wear quality.

At significance level alpha=0.05
From tukey test we can see that groups T and A are not 
significantly different and covered by blue bar.

but the Group N covered in the different color (red) than 
other 2 brands (blue) and therefore group 
N is significantly different from A and T at significance level
alpha = 0.05.

#################################################################
   Problem 7.2 
#################################################################
*/
data Problem_7_2;
 do TREAT = 'A', 'B', 'Placebo';
    do SUBJECT = 1 to 10;
       input READINGS @;
       output;
    end;
 end;
cards;
200 190 180 185 210 170 178 200 177 189
160 168 178 200 172 155 159 167 185 199
240 220 246 244 198 238 277 255 190 188
; 

proc anova data=problem_7_2;
title "Problem_7_2";
class TREAT;
model READINGS=TREAT;
means TREAT / tukey;
run;

/*
Ho-> the treats are equal in cholesterol lowering
Ha-> the treats are not equal in cholesterol lowering
F value = 19.26	p-value = 0.0001 <= alpha = 0.005

Reject Ho.

**************************************************************************
Conclusion:
At least one of the treats are not equal to one of others
in cholesterol lowering

At significance level alpha=0.05
From tukey test we can see that groups A and B are not
significantly different
and both covered by the same red bar.

but the Group P (placebo) covered in the different color(blue) from
other groups color (red).
Therefore group P is significantly different from
A and B at significance level alpha=0.05



###################################################################
Problem_7_3
###################################################################
*/
data Problem_7_3;
 do AGE = 'New', 'Old';
    do BRAND = 'W', 'P';
       do SUBJECT = 1 to 5;
          input BOUNCES @;
          output;
        end;
    end;
 end;
cards;
67 72 74 82 81
75 76 80 72 73
46 44 45 51 43
63 62 66 62 60
; 

proc anova data=problem_7_3;
title "Problem_7_3";
class BRAND AGE;
model BOUNCES=BRAND | AGE;
means BRAND | AGE;
run;
/*
*************************************************************
Effects Of Age:
*************************************************************
Ho-> The effects of AGE on number of bounces = zero
Ha-> The effects of AGE on number of bounces are not = zero
F-value = 138.03	p-value=0.0001 < alpha=0.05





Reject Ho.

**********************************************************
Conclusion about Age:
**********************************************************
At significance level alpha=0.05
effects of Age on number of bounces are significantly different
from zero.(effect of age  is significant)
*********************************************************************

Effects Of BRAND:
*********************************************************************
Ho-> The effects of BRAND on  number of bounces = zero
Ha-> The effects of BRAND on  number of bounces are not = zero
F-value = 22.08 p-value=0.0002 < alpha=0.05

Reject Ho.

*********************************************************
Conclusion about BRAND:
*********************************************************
At significance level alpha=0.05
effects of BRAND on number of bounces are significantly different
from zero. (effect of BRAND  is significant)

********************************************************************

Effects Of BRAND and Age Interaction:
********************************************************************
Ho-> The effects of Interaction of Brand and Age  on the number
                                       of bounces = zero
Ha-> The effects of Interaction of Brand and Age  on the number
                                      of bounces are not = zero
F-value = 22.08	p-value=0.0002 < alpha=0.05

Reject Ho.

*********************************************************
Conclusion about BRAND and AGE interaction:
*********************************************************
At significance level alpha=0.05
effects of BRAND and AGE on number of bounces are
significantly different from zero.
(effect of Age and Brand interaction  is significant)

###############################################################
Problem_7_4
###############################################################
This is one way design so we can use ANOVA
even the design is unbalanced.
*/
data Problem_7_4;
input GROUP $ SCORE @@;
cards;
A 560 A 520 A 530 A 525 A 575 A 527 A 580 A 620
B 565 B 522 B 520 B 530 B 510 B 522 B 600 B 590
C 512 C 518 C 555 C 502 C 510 C 520 C 516
D 505 D 508 D 513 D 520 D 543 D 523 D 517
;
proc anova data=problem_7_4;
title "Problem_7_4";
class GROUP;
model SCORE=GROUP;
means GROUP / snk;
Run;
/*
Multi Comparison
****************************************************************
Ho-> the methods are equal in preparing for college entrance exam
Ha-> the methods are not equal in preparing for college entrance exam entry
F value = 3.27	p-value=0.0371 < alpha = 0.005

Reject Ho.

****************************************************************************
Conclusion:
At significance level alpha=0.005
at least one of the methods are not equal to one of
others in preparing for college entrance exam.
**************************************************************************
snk test :
From snk test we can see that groups at significance level
alpha=0.05 the groups A, B, C and D are not
significantly different from each other and covered in the
same  color bar(blue).
***********************************************************
*/
proc glm  data=problem_7_4;
title "Problem_7_4 Contrasts";
class GROUP;
model SCORE=GROUP;
contrast 'A VS B AND C AND D' GROUP -3 1 1 1;
contrast 'D VS A AND B AND C' GROUP  1 1 1 -3;
run;
/*
For contract A VS B and C and D:
***********************************************************
Ho->method A have no difference from methods B, C and D.
Ha->method A different from methods B, C and D.
 
F=5.61 	p-value=0.0255 < alpha=0.05

Reject Ho.

***********************************************************************
Conclusion:
At significance level alpha=0.05
Method A is significantly different from methods B, C and D
***********************************************************************
For contrast D vs A and B and C:

Ho->method D have no difference from methods A, B and C.
Ha->method D different from methods A,B and C.
  
F=3.08	p-value=0.0908 > alpha=0.05
Fail to reject Ho

***********************************************************************
Conclusion:
At significance level alpha=0.05
Method D is not significantly different from methods B, C and D


###############################################################
Problem_7_5
###############################################################
Design is unbalanced so we use GLM
*/
data Problem_7_5;
input BRAND $ AGE SCORE @@;
cards;
C 1 7 C 1 6 C 1 6 C 1 5 C 1 6 P 1 9 P 1 8
P 1 9 P 1 9 P 1 9 P 1 8 C 2 9 C 2 8 C 2 8
C 2 9 C 2 7 C 2 8 C 2 8 P 2 6 P 2 7 P 2 6
P 2 6 P 2 5  
 ;
 
proc glm  data=problem_7_5;
title "Problem_7_5";
class BRAND AGE;
model SCORE=BRAND | AGE;
means BRAND | AGE;
run;

/*

Effects Of Age on consumer Preferences:  (Type 1)
**************************************************************
Ho-> The effects of AGE on consumer preferences = zero
Ha-> The effects of AGE on consumer preferences are not = zero
F-value = 0.43	p-value=0.5199	< alpha=0.05

Fail to Reject Ho.

*************************************************************
Conclusion about the effects of AGE on consumer preferences:
At significance level alpha=0.05
effects of Age on consumer preferences are not significantly
different from zero.(effect of age  is not significant)
***************************************************************
Effects Of Brand on consumer Preferences:  (Type 1)
***************************************************************
Ho-> Consumer Differences in choosing the brand = zero
Ha-> Consumer Differences in choosing the brand in not = zero
F-value = 0.56 	p-value=0.4646 > alpha=0.05

Fail to Reject Ho.

***************************************************************
Conclusion about the effects of BRAND on consumer preferences:
At significance level alpha=0.05
Consumer Differences in choosing the brand = zero.
(preference in choosing the BRAND  is not significant)
****************************************************************
Effects Of Brand and Age Interaction on consumer Preferences:  (Type 1)
****************************************************************
Ho-> Interaction of Brand and Age   on consumer preferences = zero
Ha-> Interaction of Brand and Age   on consumer preferences is not = zero
F-value = 75.63	p-value=0.0001 < alpha=0.05

Reject Ho.

Conclusion about BRAND and AGE interaction on consumer preferences:
At significance level alpha=0.05
effects of BRAND and AGE on number of bounces are
significantly different from zero.
(effect of Age and Brand interaction  is significant)

###############################################################
Problem_7_6
###############################################################
*/

data Problem_7_6;
 do GROUP = 'GeneticDeficiency', 'Normal';
    do DRUG = 'A', 'P';
       do SUBJECT = 1 to 4;
          input SCORE @;
          output;
        end;
    end;
 end;
cards;
 9 11 10 10
 9  6  6  7
 5  4  7  7
12 11 10 11
; 
proc print data=PROBLEM_7_6 noobs;
title "Problem_7_6";
var GROUP DRUG SCORE;
run;
/* Design is balanced so we use ANOVA*/
proc anova data=problem_7_6;
title "Problem_7_6";
class GROUP DRUG;
model SCORE=GROUP | DRUG;
means GROUP | DRUG /tukey;
run;
/*

Ho-> The effects of Genetic differences to cure depression = zero
Ha-> The effects of Genetic differences to cure depression is not = zero
F-value = 0.04 	p-value=0.8360 > alpha=0.05

Fail to Reject Ho.

********************************************************************
Conclusion for the effects of Genetic differences to cure depression:
At significance level alpha=0.05
the effects of Genetic differences to cure depression = zero
(effect of Genetic differences  is not significant)
*****************************************************************
Ho-> The effects of DRUG to cure depression = zero
Ha-> The effects of DRUG to cure depression are not = zero
F-value = 3.63	p-value=0.0811  > alpha=0.05
Fail to reject Ho.

Conclusion for the effects of DRUG to cure depression:
At significance level alpha=0.05
effects of DRUG to cure depression = zero
(effect of DRUG  is significant but much more significant
compare to the effects of Genetic differences)
***********************************************************************
Ho-> The effects of Interaction of Genetic Differences and Drug 
to cure depression are zero.
Ha-> The effects of Interaction of Genetic Differences and Drug 
to cure depression are not zero.                                          
F-value = 48.76	p-value= 0.0001	< alpha=0.05

Reject Ho.

***********************************************************************
Conclusion for Genetic DIfferences and Drug   interaction:
At significance level alpha=0.05
effects of Genetic DIfferences and Drug  interactions are
significantly different from zero.
(effect of Genetic DIfferences and Drug  interactions  are significant)
**********************************************************************
Multi Comparison:

tukey test shows no difference between
    group with genetic deficiencies and normal group.
tukey test shows no difference between
    Anti-depression drug and placebo.
***********************************************************************
*/