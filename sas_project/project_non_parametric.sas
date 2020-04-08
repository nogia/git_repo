proc import datafile='/folders/myfolders/data/project/flights.txt'
    out=flights
    dbms=dlm
    replace;
	datarow=5;
    delimiter='09'x;
run;

data new;
set flights;
year_dec=scan(year,2,'.');
year=scan(year,1,'.');
if Month='January' then month_count=1;
else if Month='February' then month_count=2;
else if Month='March' then month_count=3;
else if Month='April' then month_count=4;
else if Month='May' then month_count=5;
else if Month='June' then month_count=6;
else if Month='July' then month_count=7;
else if Month='August' then month_count=8;
else if Month='September' then month_count=9;
else if Month='October' then month_count=10;
else if Month='November' then month_count=11;
else if Month='December' then month_count=12;

if   Month='December' or Month='January' Or Month='February' then season='winter' ;
else if Month='March' or Month='April' or Month='May' then season='spring';
else if Month='June' or Month='July' or Month='August' then season='summer';
else if Month='September' or Month='October' or Month='November' then season='autumn';

if season='winter' then season_count=1;
else if season='spring' then season_count=2;
else if season='summer' then season_count=3;
else if season='autumn' then season_count=4;

run;

data new;
set new;
if Year<=2005 then year_group='old_years';
else if Year> 2005 then year_group='new_years';
run;

data new;
set new;
condition=year_group || '_' || season; 
run;



proc sort data=new;
By season_count;
run;

proc print data=new;
run;
proc univariate data=new normal plot;
	TITLE 
		"Descriptive Statistics for Delayed_pct normal plot";
	BY season_count;
	var Delayed_pct;
	QQPLOT Delayed_pct;
	Histogram Delayed_pct;
run;
/*proc anova data=new;
title 'One Way Anova';
class condition;
model Delayed_pct=condition;
means condition / snk;
run;*/

proc glm data=new ORDER = DATA ;
title 'Delayed_pct By season  MULTIPLE COMPARISONS ON Season | Year';
class year_group season;
model Delayed_pct=year_group | season;
means year_group  season  year_group*season/ tukey;
run;

/*proc means data=new nway noprint;
class year_group season;
var Delayed_pct;
output out=means mean=M_HR std=stdev ;
          
run;*/

                                                                                                                         
 /* Calculate the mean and standard error for each X */                                                                                  
proc means data=new noprint;                                                                                                           
  class year_group season;
  var Delayed_pct;                                                                                                                        
   output out=meansout mean=mean stderr=stderr;                                                                                         
run;                                                                                                                                    
                                                                                                                                        
/* Reshape the data to contain three Y values for */                                                                                    
/* each X for use with the HILOC interpolation.   */                                                                                    
data reshape(keep=year_group season  min max mean);                                                                                                      
   set meansout;                                                                                                                        
                                                                                                                           
   min=mean - stderr;                                                                                                                  
   output;                                                                                                                              
                                                                                                                                        
   max=mean + stderr;                                                                                                                  
   output;                                                                                                                              
run;                
/*proc plot data=reshape;     
plot min*season max*season  mean*season ;
run;*/
/*proc sgplot data=reshape;
title  'Interaction Plot Cell Means';
styleattrs datasymbols=(squarefilled starfilled);
scatter x=season y=mean /group=year_group;
scatter x=season y=yvar /group=year_group;
yaxis label="Mean";
run;*/

proc sgplot data=reshape;
title  'Interaction Plot Cell Means +- STD';
styleattrs datasymbols=(squarefilled starfilled);
scatter x=season y=mean /group=year_group ;
series x=season y=mean / group=year_group;
band x=season lower=min upper=max / group=year_group transparency=0.5;
run;

proc sgplot data=reshape;
title  'Interaction Plot Cell Means +- STD';
styleattrs datasymbols=(squarefilled starfilled);
scatter x=year_group y=mean /group=season ;
series x=year_group y=mean / group=season;
band x=year_group lower=min upper=max / group=season transparency=0.5;
run;
/*proc sgplot data=SR;  
   scatter x=x y=y2 / group=gender;
   series x=x y=p_y2 / group=gender;
   band x=x lower=lcl_y2 upper=ucl_y2 / group=gender transparency=0.5;
   title2 "Continuous Response (Y2) - Transparency=0.5";
run;*/

proc npar1way data=new wilcoxon dscf ;
title 'By season multiple comparizons Delayed_pct wilcoxon';
class season ;
var Delayed_pct ;
run;
proc means data=new n mean median std ORDER=data nonobs;
Title 'Descriptive On Delayed_pct by year_group season';
class year_group  season ;
var Delayed_pct;
run;
/*proc ANOVA data=new ORDER=data ;
Title 'Anova By Season Tukey';
class season;
Model Delayed_pct=season;
MEANS season /tukey;
run;*/
/*proc iml;
use new;
summary class {season}
        var {Delayed_pct};
        opt {noprint save};
run;*/       
/*print Season_Summary;
print height[r=season c={Min Max Mean Std}], */
   



/*
NONPARAMETRIC ONE-WAY ANOVA
*/
proc npar1way data=new wilcoxon;
title 'ONE-WAY ANOVA Arrival_Delays  wilcoxon';
class season;
var Arrival_Delays;
run;
proc npar1way data=new wilcoxon;
title 'ONE-WAY ANOVA Onetime_Arrivals  wilcoxon';
class season;
var Onetime_Arrivals;
run;
proc npar1way data=new wilcoxon;
title 'ONE-WAY ANOVA Flights_Cancelled  wilcoxon';
class season;
var Flights_Cancelled;
run;

/*
multiple comparizons
*/
proc npar1way data=new wilcoxon dscf;
title 'By season multiple comparizons Arrival_Delays wilcoxon';
class season;
var Arrival_Delays;
run;

proc npar1way data=new wilcoxon dscf;
title 'By month multiple comparizons Onetime_Arrivals wilcoxon';
class Month;
var Arrival_Delays;
run;

/*
two way anova
*/

proc glm data=new;
title 'By Year Month two way anova';
class  Month season;
model Delayed_pct=Month season;
run;

/*MULTIPLE COMPARISONS ON Month*/
proc sort data=new;
By month_count;
run;
proc sort data=new;
By season_count;
run;
PROC SORT DATA = new;
BY Month_count ;   
RUN;

proc glm data=new ORDER = DATA ;
title 'By season Month MULTIPLE COMPARISONS ON Month';
class Month Year;
model Arrival_Delays=Month Year;
means Month / tukey;
run;

proc glm data=new ORDER = DATA ;
title 'By season Month MULTIPLE COMPARISONS ON Month';
class season Year;
model Arrival_Delays=season Year;
means season / tukey;
run;

proc sgscatter data=new;
title 'SCATTERPLOT MATRIX';
matrix Arrival_Delays Onetime_Arrivals Flights_Cancelled	Diverted Flight_Operations;
run;