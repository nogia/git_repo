import pandas as pd
data = pd.read_csv("../turnover.csv")
data.info()
print(data.head())
print(data.salary.unique())
# Change the type of the "salary" column to categorical
data.salary = data.salary.astype('category')
# Provide the correct order of categories
data.salary = data.salary.cat.reorder_categories(['low','medium','high'])
# Encode categories with integer values
data.salary = data.salary.cat.codes
print(data.head())
departments = pd.get_dummies(data.department)
print(departments)
departments = departments.drop("technical", axis = 1)
print(departments.head())

# Get the total number of observations and save it
n_employees = len(data)
# Print the number of employees who left/stayed
print(data.churn.value_counts())
# Print the percentage of employees who left/stayed
print(data.churn.value_counts()/n_employees*100)

import matplotlib.pyplot as plt
import seaborn as sns
corr_matrix = data.corr()
sns.heatmap(corr_matrix)
plt.show()