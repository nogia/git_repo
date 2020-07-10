import pandas as pd
import datetime as dt
import matplotlib.pyplot as plt # for plotting graphs
import seaborn as sns # for plotting graphs

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

rfm= data.groupby(["CustomerID"]).agg({"InvoiceDate": lambda date: (current_time - date.max()).days,"Invoice": lambda num: len(num),"Price": lambda price: price.sum()})
rfm_columns = rfm.columns;
rfm.columns=['monetary','frequency','recency']
rfm_columns = rfm.columns;
rfm['recency'] = rfm['recency'].astype(int)
print(rfm.head())

rfm['recency_q'] = pd.qcut(rfm['recency'], 4, ['1','2','3','4'])
rfm['frequency_q'] = pd.qcut(rfm['frequency'], 4, ['4','3','2','1'])
rfm['monetary_q'] = pd.qcut(rfm['monetary'], 4, ['4','3','2','1'])
print(rfm.head())

rfm['RFM_Score'] = rfm.recency_q.astype(str)+ rfm.frequency_q.astype(str) + rfm.monetary_q.astype(str)
print(rfm.head())

rfm['RFM_Score'] = rfm['RFM_Score'].astype(int)
customer_profitability = rfm.sort_values(by=['RFM_Score','monetary'], ascending=[True,False])
filename = "customer_profitability.csv"
customer_profitability.to_csv(filename)

writer = pd.ExcelWriter('customer_profitability.xlsx', engine='xlsxwriter')
customer_profitability.to_excel(writer, sheet_name='Sheet1')
writer.save()

print("End")