USE Northwind;

/*####################     Problem 1         ######################*/
/*1. Write a query that displays an alphabetical 
list ( last name only) of all Northwind Traders employees. */
GO
SELECT LastName as "Employees Last Name" 
FROM Employees 
ORDER BY LastName;
GO

/*####################     Problem 2         ######################*/
/*1. 2. Write a query that displays an alphabetical list of all 
Northwind Traders employees that are sales representatives.  
Include the employees title in this report. */

GO
SELECT EmployeeID, LastName, FirstName, Title FROM Employees
Where Title = 'Sales Representative ' 
ORDER BY LastName;
GO

/*####################     Problem 3         ######################*/
/*1. 3. Write a query that displays the names of all Northwind 
Traders customers who are based in Germany.  Include 
customer id, name, city, and country, sorted by name. */

GO
SELECT CustomerID, CompanyName,City, Country 
FROM Customers 
WHERE Country = 'Germany'
ORDER BY CompanyName

GO

/*####################     Problem 4         ######################*/
/*1.4. What were the total number of orders placed by order date? . */
DECLARE @TempTable TABLE
( 
	OrderDate  varchar(10) NOT NULL DEFAULT('Unknown')
);

INSERT INTO @TempTable  
SELECT  Convert(date, OrderDate) as  OrderDate FROM Orders;


SELECT OrderDate , Count(OrderDate) as NumOrdersByDate FROM @TempTable Group By OrderDate;
GO


/*####################     Problem 5         ######################*/
/*5. How many total orders were placed in the first quarter of 1995 
(Jan, Feb, and Mar)?  Your answer should include a single number
that is based on the order date. */

SELECT Count(OrderDate) FROM Orders
WHERE OrderDate >= '1996-07-01 00:00:00.000 AM' 
AND OrderDate < '1996-10-01 00:00:00.000 AM'

/*####################     Problem 6        ######################*/
/*6. How many orders were sent to each customer?  */

SELECT C.CompanyName, COUNT(ShippedDate) as NumOrdersSendToCustomer 
FROM Orders 
INNER JOIN [Customers] C ON C.CustomerID=Orders.CustomerID
Group BY C.CompanyName;



/*####################     Problem 7        ######################*/
/*6.7. How many orders has each employee written?  Your results
should sort by employee last name.  */

SELECT Employees.LastName, Count(OrderDate) as NumOrders 
FROM Orders, Employees 
WHERE
Orders.EmployeeID = Employees.EmployeeID 
GROUP BY(Employees.LastName) 
ORDER BY Employees.LastName;

/*####################     Problem 8        ######################*/
/*6.8. How many units are in stock for each product in inventory? 
Create a report sorted by product name.  */

SELECT ProductName, SUM(UnitsInStock) as UnitsInStock 
FROM Products Group By ProductName;

/*####################     Problem 9        ######################*/
/*9. What was the total units sold and total sales before a discount 
(Unit Price * Quantity) for products that have been discontinued?  
Create a report sorted by product name.*/
DECLARE @SALES TABLE
( 
    ProductName varchar(30) ,
	UnitsSold INT ,
	Sales  Decimal
);

INSERT INTO @SALES
SELECT P.ProductName, O.Quantity AS UnitsSold , O.UnitPrice * O.Quantity as Sales
FROM [Order Details] O 
INNER JOIN [Products] P On P.ProductID = O.ProductID
WHERE P.Discontinued = 1
ORDER BY ProductName

SELECT ProductName,SUM(UnitsSold)as TotalUnitsSold, SUM(Sales) as TotalSales
FROM @SALES
GROUP BY ProductName
Order BY ProductName


/*####################     Problem 10        ######################*/
/*10. How many orders by day were shipped for the shipping company 
United Package in 1994.  Show a report that includes Company Name, 
Shipped Date, and numbers of orders by ship date for this company.*/

SET ansi_warnings OFF
DECLARE @TempTable111 TABLE
( 
    ShippedDate  varchar(10) NOT NULL DEFAULT('Unknown'),
    CompanyName varchar(30) ,
	ShipperName varchar(10) 
	
);

INSERT INTO @TempTable111
SELECT Convert(date,ShippedDate) as ShippedDate ,
Customers.CompanyName,Shippers.CompanyName as ShipperName 
        
FROM   Orders,Shippers, Customers
WHERE Shippers.ShipperID = Orders.ShipVia And Shippers.CompanyName='United Package' And 
ShippedDate >= '1997-01-01 00:00:00.000 AM' And ShippedDate < '1998-01-01 00:00:00.000 AM'
ORDER BY ShippedDate;



SELECT (ShippedDate) as ShippedDate,ShipperName as ShipperName ,Count(ShippedDate) as NumShippedByDate 
FROM @TempTable111 
Group By ShippedDate,ShipperName ;

SELECT max(ShippedDate) as ShippedData,CompanyName , max(ShipperName) as ShippedName ,Count(ShippedDate) as NumShippedByDate 
FROM @TempTable111 
Group By ShippedDate,CompanyName ;

GO

SELECT * FROM Shippers




