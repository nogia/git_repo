/*data survey;
infile 'C:\Users\inna\Desktop\DepaulClasses\ApplyMathClasses\StatisticalDataManagement\group_work\gw_6\drugstore1.csv' DLM=',' Firstobs=2;
input product $ chain $ store_id price

proc print data=drugstore;
run;*/
proc sql;
title "Problem 1";
SELECT * FROM drugstore where (chain = 'Target' And store_id = 305 and product = 'coughmedicine';
quit;

proc sql;
title "Problem 2";
SELECT DISTINCT store_id,product,price  FROM drugstore where product = 'aspirin';
quit;

proc sql;
title "Problem 3";
SELECT Distinct(store_id),chain FROM drugstore WHERE chain = 'CVS'; 
quit;


proc sql;
title "Problem 4";
SELECT * from drugstore ORDER BY price;
quit;

proc sql;
title "Problem 5";
SELECT chain,product,store_id,price from drugstore ORDER BY chain,product;
quit;

proc sql;
title "Problem 6";
select product,MIN(price) as Minimum, MAX(price) as Maximum, Avg(price) as Average from drugstore GROUP BY product;
quit;

proc sql;
title "Problem 8";
select chain,product as product, MIN(price) as Minimum, MAX(price) as Maximum, Avg(price) as Average from drugstore GROUP BY chain, product;
quit;


proc sql;
title "Problem 9";
select Distinct(chain),product as product, MIN(price) as Minimum, MAX(price) as Maximum, Avg(price) as Average from drugstore 
WHERE product = 'aspirin';
GROUP BY chain;
quit;






