import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as  sns
import statsmodels.api as sm
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier

from sklearn import tree
import pydotplus
from sklearn.tree import DecisionTreeClassifier
from sklearn import linear_model
from sklearn.linear_model import Ridge

def get_float_rows(dataset) :
    col_float = []
    col_object = []
    for i in dataset.columns:
        if dataset[i].dtypes == np.float:
            col_float.append(i)
        elif dataset[i].dtypes == np.object:
            col_object.append(i)
    return col_float,col_object
# Load in data
df_train = pd.read_csv('exercise_02_train.csv')
x_test_set  = pd.read_csv('exercise_02_test.csv')

# check data types before training

df_train_types = df_train.dtypes
x_test_types = df_train.dtypes

x_train_set = df_train.iloc[:,0:len(df_train.columns)-1]

col_float,col_object = get_float_rows(x_train_set)

x_train_set[col_object[2]] =x_train_set[col_object[2]].replace('[\$,]', '', regex=True).astype(float)
x_train_set[col_object[3]] =x_train_set[col_object[3]].replace('[\%,]', '', regex=True).astype(float)
categorized = [col_object[0],col_object[1],col_object[4],col_object[5]]
for i in range(0,len(categorized)):
    codes, uniques = pd.factorize(x_train_set[categorized[i]])
    print(type(list(codes)))
    x_train_set[categorized[i]] = list(codes)

x_test_set[col_object[2]] =x_test_set[col_object[2]].replace('[\$,]', '', regex=True).astype(float)
x_test_set[col_object[3]] =x_test_set[col_object[3]].replace('[\%,]', '', regex=True).astype(float)
categorized = [col_object[0],col_object[1],col_object[4],col_object[5]]
for i in range(0,len(categorized)):
    codes, uniques = pd.factorize(x_test_set[categorized[i]])
    print(type(list(codes)))
    x_test_set[categorized[i]] = list(codes)

x_train = x_train_set
x_test = x_test_set

# using Nearest neighbors imputation
import numpy as np
from sklearn.impute import KNNImputer

x_train = x_train.replace(x_train.isnull(), np.nan)
x_test = x_test.replace(x_train.isnull(), np.nan)

miss_number_train = (x_train.isnull().sum() > 0).astype(np.int64).sum()
print("Before removing impurities = ",miss_number_train)
miss_number_test = (x_test.isnull().sum() > 0).astype(np.int64).sum()
print("Before removing impurities = ",miss_number_test)

imputer = KNNImputer(n_neighbors=1)
xtrain_filled = imputer.fit_transform(x_train)
xtest_filled = imputer.fit_transform(x_test)

x_train = pd.DataFrame(data=xtrain_filled, columns=x_train.columns)
x_test = pd.DataFrame(data=xtest_filled, columns=x_test.columns)


miss_number_train = (x_train.isnull().sum() > 0).astype(np.int64).sum()
print("After removing impurities = ",miss_number_train)
miss_number_test = (x_test.isnull().sum() > 0).astype(np.int64).sum()
print("Before removing impurities = ",miss_number_test)

X=x_train
y = df_train['y']
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)
############################################################################
# Finds Number Of Estimatore and depth
############################################################################
from sklearn import model_selection
from sklearn.model_selection import RandomizedSearchCV
# number of trees in random forest
n_estimators = [int(x) for x in np.linspace(start = 200, stop = 2000, num = 10)]
# number of features at every split
max_features = ['auto', 'sqrt']

# max depth
max_depth = [int(x) for x in np.linspace(100, 500, num = 11)]
max_depth.append(None)
# create random grid
random_grid = {
 'n_estimators': n_estimators,
 'max_features': max_features,
 'max_depth': max_depth
 }
# Random search of parameters
rfc = RandomForestClassifier()
rfc_random = RandomizedSearchCV(estimator = rfc, param_distributions = random_grid, n_iter = 100, cv = 3, verbose=2, random_state=42, n_jobs = -1)
# Fit the model
rfc_random.fit(X_train, y_train)
# print results
best_param = rfc_random.best_params_
#######################################################################
#Optimal Number Of Estimator = 200
#Optimal Number of Depth     = 100

#######################################################################
