/*

  performed by Inna Williams,
*/
proc import datafile='/folders/myfolders/data/week5/popularkids.csv' 
	out=pk dbms=csv replace;
	delimiter=',';
	getnames=yes;
run;
options nodate ps=60 ls=80;

/*proc sort data=pk;
  by Goals;
proc print data=pk;*/
  
/*1. What goal did all students choose most often as their most important
personal goal? Which goal was chosen least often? */
 
proc freq data=pk ;
  title " What goal did all students choose most often as their most important personal goal";
  tables Goals /nocum nopercent;
run;
/* 
               Interpretation 
We can see that that most often The students choose
Grades as a goal, the least often the students choose sports
as a goal

2. Does the personal goal that is chosen most often differ by gender? By
grade? By age? By race? By the UrbanRural variable? By school?
Use chi-square tests to answer these questions.
*/
data Personal_GOAL_Grades;
set pk;
if Goals eq 'Grades' then Group_grade="1_Chosen_More_Often";
if Goals eq 'Popular' or Goals eq 'Sports' then Group_grade ="2_Chosen_Less_Often";

proc freq data=Personal_GOAL_Grades;
  title "personal goal that is chosen most often differ by gender  race ";
  tables (Gender Race)*Group_grade /chisq cmh;
run;
proc freq data=Personal_GOAL_Grades;
  title "personal goal that is chosen most often differ by  grade age  UrbalRural School";
  tables Group_grade*(Grade   Age  UrbanRural School) /chisq trend;
run;

/*
3. In making a person popular, were grades ranked similarly for boys and
girls?
4. In making a person popular, were looks ranked similarly for boys and
girls?
5. In making a person popular, was money ranked similarly for boys and
girls?
*/
proc freq data=pk;
title "Gender Opnion On Popularity";
tables  Gender*(Grades Looks Money)/chisq expected cmh trend;
run;

proc sgpanel data=pk ;
panelby GENDER / layout=COLUMNLATTICE;
histogram Money;
run;

proc sgpanel data=pk ;
panelby GENDER / layout=COLUMNLATTICE;
histogram Looks;
run;

proc sgpanel data=pk ;
panelby GENDER / layout=COLUMNLATTICE;
histogram Grades;
run;

proc sort data=pk;
by Gender;

