# CLTV = Customer LIfe Time Calue

# CLTV = ((Average Order Value x Purchase Frequency)/Churn Rate)
# Average Order Value = Total Revenue / TotalNumberOfOrders
# Purchase Frequency = TotalNumberOfOrders / Number Of Customers
# Churn Rate = Percentage Of Customers who have not ordered again
import pandas as pd
import datetime as dt
import matplotlib.pyplot as plt # for plotting graphs
import seaborn as sns # for plotting graphs
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn import metrics
import numpy as np

print("Start")

# Load in data
df = pd.read_excel('online_retail_II.xlsx')
print(df.head())
df.info()
df = df.rename({'Customer ID': 'CustomerID'}, axis='columns')
df.info()
print(df.describe())

df = df[(df['Quantity']>0) ]
df = df[(df['Price']>0) ]
print(df.describe())
#column_names = df.keys()
#print(column_names)
df= df[pd.notnull(df['CustomerID'])]
# remove duplicates
filtered=df[['Country','CustomerID']].drop_duplicates()
unique_country = df['Country'].unique()
print(unique_country)
filtered.Country.value_counts().plot(kind='bar')

data = df[df.Country == 'United Kingdom']
data=df[['CustomerID','InvoiceDate','Invoice','Quantity','Price']]
data['TotalProfit'] = data['Quantity'] * data['Price']

current_time = dt.datetime(2020,7,1)

cltk = data.groupby(["CustomerID"]).agg({"InvoiceDate": lambda date: (current_time - date.max()).days,
                                         "Invoice": lambda num: len(num),
                                         'Quantity': lambda quant: quant.sum(),
                                         "Price": lambda price: price.sum()
                                         })
# rename columns
cltk.columns=['NumberOfDays','NumberOfTransaction','NumberOfUnits','TotalMoney']
print(cltk.head())

#CLTV = ((Average Order Value x Purchase Frequency)/Churn Rate) x Profit margin.
#Customer Value = Average Order Value * Purchase Frequency
cltk['AvgOrderValue'] = cltk['TotalMoney']/ cltk['NumberOfTransaction']
print(cltk.head())

purchase_frequency = sum(cltk['NumberOfTransaction']) / cltk.shape[0]
# Repeat Rate
repeat_rate = cltk[cltk.NumberOfTransaction > 1].shape[0]/cltk.shape[0]
churn_rate=1-repeat_rate
print(purchase_frequency,repeat_rate,churn_rate)


# Profit Margin , assume bussiness have 5% of profit
cltk['ProfitMargin'] = cltk['TotalMoney']*0.05
print(cltk.head())
################################################################################
# Customer Value
cltk['CLV'] = (cltk.AvgOrderValue * purchase_frequency )/ churn_rate
print(cltk.head())
################################################################################
data['month_yr'] = data['InvoiceDate'].apply(lambda x: x.strftime('%b-%Y'))
print(data.head())

sale = data.pivot_table(index=['CustomerID'],columns=['month_yr'],values='TotalProfit',aggfunc='sum',fill_value=0).reset_index()
print(sale.head())

sale['CLV']=sale.iloc[:,2:].sum(axis=1)
print(sale.head())

################################################################################
#Selecting Feature
#Here, you need to divide the given columns into two types of variables
#dependent(or target variable) and independent variable(or feature variables).
# Select latest 6 month as independent variable.
X=sale[['Dec-2010','Nov-2010', 'Oct-2010','Sep-2010','Aug-2010','Jul-2010']]
y=sale[['CLV']]

X_train, X_test, y_train, y_test = train_test_split(X, y,random_state=0)
# instantiate
linreg = LinearRegression()

# fit the model to the training data (learn the coefficients)
linreg.fit(X_train, y_train)

# make predictions on the testing set
y_pred = linreg.predict(X_test)
print(linreg.intercept_)
print(linreg.coef_)

#How Well Does the Model Fit the data?
#In order to evaluate the overall fit of the linear model, we use the
# R-squared value. R-squared is the proportion of variance explained by the model.
# Value of R-squared lies between 0 and 1. Higher value or R-squared is
# considered better because it indicates the larger variance explained by the model.
print("R-Square:",metrics.r2_score(y_test, y_pred))

# calculate MAE using scikit-learn
print("MAE:",metrics.mean_absolute_error(y_test,y_pred))

#calculate mean squared error
print("MSE",metrics.mean_squared_error(y_test, y_pred))
# compute the RMSE of our predictions
print("RMSE:",np.sqrt(metrics.mean_squared_error(y_test, y_pred)))
################################################################################
filename = "customer_profitability.csv"
customer_profitability.to_csv(filename)

writer = pd.ExcelWriter('customer_profitability.xlsx', engine='xlsxwriter')
customer_profitability.to_excel(writer, sheet_name='Sheet1')
writer.save()

print("End")