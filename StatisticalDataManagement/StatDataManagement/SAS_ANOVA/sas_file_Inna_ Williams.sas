
/*
MAT 449
HW1
Inna WIlliams
SAS Code
*/
/******************     Problem 1     *******************************************/
proc format;
value ETHNIC
          1='White'
          2='Black'
          3='Hispanic'
          ;
value SMOKE
           1='non-smoker'
           2='light smoker'
           3='heavy smoker'
   ;
value $BREASTFED
           'Y'='Baby will be breastfed'
           'N'='Baby will not be breastfed'
           ;
;

run;

options pagesize=80 linesize=80 pageno=1 nodate;
data birthweight;
infile '/folders/myfolders/code/sdm/data/hw1/birthweight.txt' truncover;
input Ethnic 1 Age 2-3 Smoke 4 preweight 5-10 delweight 11-16 breastfed $ 17 brthwght 18-21 brthlngth 22-26;


proc print data=birthweight LABELnoobs split='/' noobs;
TITLE "Hw 1 birthweigh";
label
	Ethnic = ' Political/Party '
	Age='Age of/mother'
	Smoke='Smoking status/of mother'
	preweight='Weight of mother/before pregnancy'
	delweight='Weight of/mother at/delivery'
	breastfed='Indicator if baby was/breastfed'
	brthwght='Weight/of baby/at birth'
	brthlngth='Length/of baby/at birth'
;
format Ethnic ETHNIC.
       Smoke SMOKE.
       breastfed $BREASTFED.
       ;
run;
/******************     Problem 2     *******************************************/
data treeda;
infile '/folders/myfolders/code/sdm/data/hw1/treeda.txt' DELIMITER =' ';
input number species $ circumference_start code $ circumference_end;

run;
data treeda;
set treeda;
diameter_start=circumference_start/3.14;
diameter_end=circumference_end/3.14;
difference=diameter_end-diameter_start;
run;

proc sort data=treeda;
By code difference;
run;

proc print data=treeda noobs;
title "HW 1 Treeda";
run;

proc anova data=treeda;
title 'Anova One Way';
class code;
model diameter_start diameter_end difference=code ;
means code  / snk;
run;

/******************************************************************************/