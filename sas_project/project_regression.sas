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

log_ontime_pct=log(Ontime_pct);
run;




proc sort data=new;
By month_count;
run;
proc sort data=new;
By season_count;
run;

proc print data=new(obs=3);
run;


/*proc sql noprint;
	create table year as SELECT Year,
	SUM(Onetime_Arrivals) as Onetime_Arrivals,SUM(Ontime_pct) as Ontime_pct,SUM(Arrival_Delays)as Arrival_Delays,
	SUM(Delayed_pct) as Delayed_pct, SUM(Flights_Cancelled) as Flights_Cancelled,SUM(Cancelled_Pct) as Cancelled_Pct,	
	SUM(Diverted) as Diverted,	SUM(Flight_Operations)	 as Flight_Operations FROM new GROUP BY Year;
quit;


proc print data=year NOOBS;
	TITLE "By Year ";
run;
proc sgplot data=year;
title "Chapter 2 Problem 10 a sgplot x=HR y=SBP";
scatter x=Year y= Flight_Operations/ markerattrs=(symbol=diamond size=2.5mm color=blue) dataskin=sheen;
scatter x=Year y= Onetime_Arrivals/ markerattrs=(symbol=diamond size=2.5mm color=red) dataskin=sheen;
scatter x=Year y= Arrival_Delays/ markerattrs=(symbol=diamond size=2.5mm color=orange) dataskin=sheen;
scatter x=Year y= Flights_Cancelled/ markerattrs=(symbol=diamond size=2.5mm color=yellow) dataskin=sheen;
xaxis label="Year";
run;


proc corr data=new;
title 'Correlation Coefficient Arrival_Delays vs Flight_Operations';
var Arrival_Delays	 Flight_Operations ;
Run;

proc corr data=new;
title "Pearson Correlation Coefficient Between X and Y, X and Z";
var Flight_Operations;
with Diverted Delayed_pct Ontime_pct Cancelled_Pct;
Run;*/

/*proc reg data=new plots=ResidualByPredicted;
var month_count;
model Delayed_pct  = Ontime_pct / cli;
run;*/

/*proc reg data=new;
model Delayed_pct Arrival_Delays = Ontime_pct Onetime_Arrivals month_count Flight_Operations/clb;
run;*/

proc means data=new min max;
var Ontime_pct Onetime_Arrivals  Flight_Operations;
run;

data new; 
set new end=last; 
output;
ARRAY months(1:12) $ January February March April May June July August September October November December;
ARRAY monthcount[12] (1 2 3 4 5 6 7 8 9 10 11 12);
ARRAY Ontimepct[3] (60 75 90 );
ARRAY OnetimeArrivals[3] (300000 400000 500000 );
ARRAY FlightOperations[3] (450000 550000 650000 );

if last then 
do i = 1 to 12;
	do j = 1 to 3;
		do k = 1 to 3;
			do n = 1 to 3;
				Delayed_pct=.; 
				Arrival_Delays=.; 
				Month=months[i];
				month_count=monthcount[i];
				Ontime_pct=Ontimepct[j]; 
				Onetime_Arrivals=OnetimeArrivals[k];
				Flight_Operations=FlightOperations[n];
				output;
            end;        
        end;   
   end;
end; 
run;

 

proc reg data=new;
model Delayed_pct Arrival_Delays = Ontime_pct Onetime_Arrivals month_count Flight_Operations/clb;
output out=Delayed_pct_out (where=(Delayed_pct=. )) predicted=Delayed_pct_hat LCLM=LCL_mean UCLM=UCL_mean; 
output out=Arrival_Delays_out (where=(Arrival_Delays=.)) predicted=Arrival_Delays_hat LCLM=LCL_mean UCLM=UCL_mean; 
run;

proc print data=Delayed_pct_out ; 
title 'Report Prediction Of Delayed_pct';
var month_count Ontime_pct Onetime_Arrivals  Flight_Operations Delayed_pct_hat  LCL_mean UCL_mean; 
run;

proc print data=Arrival_Delays_out ; 
title 'Report Prediction Of Arraval Delays';
var month_count Ontime_pct Onetime_Arrivals  Flight_Operations Arrival_Delays_hat  LCL_mean UCL_mean; 
run;

proc sgscatter data=Delayed_pct_out;
title 'SCATTERPLOT MATRIX predicted Delayed_pct';
compare y=Delayed_pct_hat
          x=(month_count Ontime_pct Onetime_Arrivals Flight_Operations)  / pbspline;
run;
proc sgscatter data=new;
title 'SCATTERPLOT MATRIX Actual Delayed_pct';
compare y=Delayed_pct
          x=(month_count Ontime_pct Onetime_Arrivals Flight_Operations) /   pbspline;
run;

proc sgscatter data=Arrival_Delays_out;
title 'SCATTERPLOT MATRIX predicted Arrival_Delays';
compare y=Arrival_Delays_hat
          x=(month_count Ontime_pct Onetime_Arrivals Flight_Operations)  / pbspline;
run;
proc sgscatter data=new;
title 'SCATTERPLOT MATRIX Actual Arrival_Delays';
compare y=Arrival_Delays
          x=(month_count Ontime_pct Onetime_Arrivals Flight_Operations) /   pbspline;
/*proc sgscatter data=Delayed_pct_out;
title 'SCATTERPLOT MATRIX predicted Delayed_pct';
plot (Delayed_pct_hat )*(month_count Ontime_pct ) /   pbspline;
run;*/

/*proc sgscatter data=new;
title 'SCATTERPLOT MATRIX Actual Delayed_pct';
plot (Delayed_pct )*(month_count Ontime_pct) /   pbspline;
run;

proc sgscatter data=Delayed_pct_out;
title 'SCATTERPLOT MATRIX predicted Delayed_pct';
plot (Delayed_pct_hat )*(Onetime_Arrivals Flight_Operations) /   pbspline;
run;

proc sgscatter data=new;
title 'SCATTERPLOT MATRIX Actual Delayed_pct';
plot (Delayed_pct )*(Onetime_Arrivals Flight_Operations) /   pbspline;
run;*/

/*proc sgscatter data=Arrival_Delays_out;
title 'SCATTERPLOT MATRIX Predicted Arrival_Delays';
plot (Arrival_Delays_hat)*(month_count Ontime_pct Onetime_Arrivals Flight_Operations) /   pbspline;
run;

proc sgscatter data=new;
title 'SCATTERPLOT MATRIX Actual Delayed_pct';
plot (Arrival_Delays )*(month_count Ontime_pct Onetime_Arrivals Flight_Operations) /   pbspline;
run;*/



