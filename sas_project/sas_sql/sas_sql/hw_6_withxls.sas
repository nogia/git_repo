/*########################################################
  MATH 449 Statistical Data Management
  Homework 6
  performed by Inna Williams
  ########################################################
*/

proc import out = Customers
datafile = '/folders/myfolders/data/Northwind Traders.xls'
dbms=xls replace;
sheet = 'Customers';
getnames=yes;
mixed = yes;
run;

data Customers;
SET Customers;
CompanyName=compress(CompanyName,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
CustomerID=compress(CustomerID,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
ContactName=compress(ContactName,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
ContactTitle=compress(ContactTitle,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
Address=compress(Address,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
City=compress(City,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
Region=compress(Region,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
PostalCode=compress(PostalCode,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
Country=compress(Country,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
Fax=compress(Fax,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
run;

filename temp '/folders/myfolders/data/Northwind Traders.xls' ;
proc import datafile=temp
	out=Products dbms=xls replace;
	sheet = 'Products';
	getnames=yes;
run;
data Products;
SET Products;
ProductName=compress(ProductName,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
Supplier=compress(Supplier,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
run; 

filename temp '/folders/myfolders/data/Northwind Traders.xls' ;
proc import datafile=temp
	out=Employees dbms=xls replace;
	sheet = 'Employees';
	getnames=yes;
run; 

filename temp '/folders/myfolders/data/Northwind Traders.xls' ;
proc import datafile=temp
	out=Orders dbms=xls replace;
	sheet = 'Orders';
	getnames=yes;
run; 
data Orders;
SET Orders;
ShipName=compress(ShipName,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
ShipAddress=compress(ShipAddress,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
ShipCity=compress(ShipCity,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
ShipRegion=compress(ShipRegion,"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()-_=+\|[]{};:',.<>?/ " , "kis");
run; 

filename temp '/folders/myfolders/data/Northwind Traders.xls' ;
proc import datafile=temp
	out=OrdersDetails dbms=xls replace;
	sheet = 'Order Details';
	getnames=yes;
run; 

filename temp '/folders/myfolders/data/Northwind Traders.xls';
proc import datafile=temp
	out=Shippers dbms=xls replace;
	sheet = 'Shippers';
	getnames=yes;
run; 

PROC SQL;
TITLE1 "                   Problem 1                  ";
TITLE2 " Write a query that displays an alphabetical"; 
TITLE3 "( last name only) of all Northwind Traders employees. ";
SELECT LastName AS LastName
FROM Employees 
ORDER BY LastName;
QUIT;

PROC SQL;
TITLE1 "                   Problem 2                    ";
TITLE2 " Write a query that displays an alphabetical list of all "; 
TITLE3 "Northwind Traders employees that are sales representatives.";
TITLE4 "Include the employees title in this report.";
SELECT EmployeeID, LastName, FirstName, Title FROM Employees
WHERE Title = 'Sales Representative ' 
ORDER BY LastName;
QUIT;

PROC SQL;
TITLE1 "                   Problem 3                    ";
TITLE2 " Write a query that displays the names of all Northwind"; 
TITLE3 "Traders customers who are based in Germany.  Include";
TITLE4 "customer id, name, city, and country, sorted by name.";
SELECT CustomerID, CompanyName,City, Country 
FROM Customers 
WHERE Country = 'Germany'
ORDER BY CompanyName;
QUIT;

PROC SQL;
TITLE1 "                   Problem 4                   ";
TITLE2 " What were the total number of orders placed by order date? ."; 
SELECT OrderDate,count(OrderDate)
FROM Orders
GROUP BY OrderDate;
QUIT;

PROC SQL;
TITLE1 "                   Problem 5                    ";
TITLE2 "How many total orders were placed in the first quarter of 1995"; 
TITLE3 "(Jan, Feb, and Mar)?  Your answer should include a single number";
TITLE4 "that is based on the order date.";
SELECT Count(OrderDate) as NumOrdersInFrirstQuarter1995
FROM Orders
WHERE orderdate GE '01Jan1995'd AND orderdate LT '01Apr1995'd;
QUIT;

PROC SQL;
TITLE1 "                   Problem 6                    ";
TITLE2 "How many orders were sent to each customer?"; 
SELECT C.CompanyName AS CompanyName, COUNT(ShippedDate) AS NumOrdersSendToCustomer 
FROM Orders 
INNER JOIN Customers C ON C.CustomerID=Orders.CustomerID
GROUP BY CompanyName;
QUIT;

PROC SQL;
TITLE1 "                   Problem 7                    ";
TITLE2 "How many orders has each employee written?";  
TITLE3 "Your results should sort by employee last name."; 
SELECT Employees.LastName, Count(OrderDate) AS NumOrdersWritten 
FROM Orders, Employees 
WHERE
Orders.EmployeeID = Employees.EmployeeID 
GROUP BY(Employees.LastName) 
ORDER BY Employees.LastName;
QUIT;

PROC SQL;
Title1 "                   Problem 8                    ";
Title2 "How many units are in stock for each product in inventory?";  
Title3 "Create a report sorted by product name."; 
SELECT ProductName, SUM(UnitsInStock) AS UnitsInStock 
FROM Products 
GROUP BY ProductName;
QUIT;

PROC SQL;
TITLE1 "                   Problem 9                    ";
TITLE2 "What was the total units sold and total sales before a discount";  
TITLE3 "(Unit Price * Quantity) for products that have been discontinued? "; 
TITLE4 "Create a report sorted by product name.";
CREATE TABLE Sales AS
SELECT P.ProductName, O.Quantity AS UnitsSold , O.UnitPrice * O.Quantity AS Sales
FROM OrdersDetails O 
INNER JOIN Products P ON P.ProductID = O.ProductID
WHERE P.Discontinued = "Yes"
ORDER BY ProductName;
SELECT ProductName,SUM(UnitsSold) AS TotalUnitsSold, SUM(Sales) AS TotalSales
FROM Sales
GROUP BY ProductName
ORDER BY ProductName;
QUIT;

PROC SQL;
TITLE1 "                   Problem 10                    ";
CREATE TABLE ShippedToUnitedPackage1994 AS
SELECT S.CompanyName AS ShipperName ,O.ShippedDate AS ShippedDate ,C.CompanyName AS CompanyName
FROM   Orders O 
INNER JOIN Shippers S ON S.ShipperID=O.ShipVia
INNER JOIN Customers C ON C.CustomerID=O.CustomerID
WHERE S.CompanyName='United Package' 
AND O.ShippedDate GE '01Jan1994'd AND O.ShippedDate LT '01Jan1995'd
ORDER BY O.ShippedDate;

CREATE TABLE NumShippedByCustomerCompanyName AS
SELECT ShippedDate ,CompanyName ,ShipperName,Count(ShippedDate) AS NumShippedByDate 
FROM ShippedToUnitedPackage1994
GROUP BY ShippedDate ;
QUIT;

PROC PRINT DATA = NumShippedByCustomerCompanyName;
TITLE1 "                   Problem 10                    ";
TITLE2 "How many orders by day were shipped for the shipping company ";  
TITLE3 "United Package in 1994.  Show a report that includes Company Name,"; 
TITLE4 "Shipped Date, and numbers of orders by ship date for this company.";
TITLE5 "Number Of Orders By Customer Company Name";
RUN;
   



 
  

