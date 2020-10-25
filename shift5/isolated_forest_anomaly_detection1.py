from sklearn.ensemble import IsolationForest
from sklearn.preprocessing import  LabelEncoder
from sklearn.metrics import confusion_matrix, roc_auc_score
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
from sklearn.metrics import classification_report
from sklearn.metrics import roc_curve, auc
import struct

import seaborn as sns
import pandas as pd
import numpy as np
import matplotlib

import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import tensorflow
import sys
from ctypes import *

Lower_bound = 0
Upper_bound = 0
n = 2

def convert(s):
    value = 0
    try:
        i = int(s, 32)                   # convert from hex to a Python int
        cp = pointer(c_int(i))           # make this into a c integer
        fp = cast(cp, POINTER(c_float))  # cast the int pointer to a float pointer
        value = fp.contents.value
        value = 1
    except ValueError:
        value = 0
    return value
def iqr_bounds(scores,k=1.5):
    print(type(scores))
    q1 = np.quantile(scores,0.25)
    q3 = np.quantile(scores,0.75)
    iqr = q3 - q1
    lower_bound=(q1 - k * iqr)
    upper_bound=(q3 + k * iqr)
    print("Lower bound:{} \nUpper bound:{}".format(lower_bound,upper_bound))
    return lower_bound,upper_bound

def predict(x,y,n,lower_bound,upper_bound,is_test = False):
    anomaly_scores = isolation_forest.decision_function(x)
    plt.figure(figsize=(15, 10))
    plt.hist(anomaly_scores, bins=100)
    plt.xlabel("Average path length", fontsize=14)
    plt.ylabel('Number of Data Points', fontsize=14)
    plt.show()

    arr = np.zeros(len(y))
    for i in range(0, len(y)):
        if (anomaly_scores[i] < lower_bound) | (anomaly_scores[i] > upper_bound):
            arr[i] = 1
        else:
            arr[i] = 0
    y = arr
    y = y == 1
    y_pred = isolation_forest.predict(x)
    y_pred = y_pred == -1
    ## calculate confusion matrix between y_val vs y_val_pred

    cf_matrix = confusion_matrix(y, y_pred)
    print(cf_matrix)
    report = classification_report(y, y_pred)
    print(report)
    #auc = roc_auc_score(y, y_pred)
    print("Validation Set AUC= ", auc)

    group_names = ['True Neg', 'False Pos', 'False Neg', 'True Pos']
    group_counts = ['{0:0.0f}'.format(value) for value in
                    cf_matrix.flatten()]
    group_percentages = ['{0:.2%}'.format(value) for value in
                         cf_matrix.flatten() / np.sum(cf_matrix)]
    labels = [f'{v1}\n{v2}\n{v3}' for v1, v2, v3 in
              zip(group_names, group_counts, group_percentages)]
    labels = np.asarray(labels).reshape(2, 2)
    #plt.figure(figsize=(15, 10))
    #sns.heatmap(cf_matrix, annot=labels, fmt='', cmap='Blues')
    #plt.show()
    if is_test:
        x['predicted'] = y_pred
        x.to_csv(r'x_test_with_predictions.csv', index=False, header=True)

df = pd.read_csv('data.csv')
print(df.dtypes)
print(df.shape[0])
print(df.head())

print(df.dtypes)
v = df.data.astype(str)

a_data = np.zeros( len(v), dtype = int)
for i in range(0,len(v)):
    value = convert(v[i])
    a_data[i] = value

encs = dict()
data = df.copy()  #.sample(frac=1)
for col in data.columns:
    if data[col].dtype == "object" or data[col].dtype == "bool":
        encs[col] = LabelEncoder()
        encs[col].fit(df[col])
        data[col] = encs[col].transform(data[col])

#data['is_hex'] = a_data
print(data.dtypes)

df_len = len(data)
for f in range(0,3):
    data=data.iloc[np.random.permutation(df_len)]
fig,ax = plt.subplots(figsize=(12,7))
sns.heatmap(data.corr(),fmt="",linewidths=0.3,ax=ax)
#plt.show()
data['Class'] = 0
Y = data['Class']
#Y = data['is_hex']
X = data.drop(['Class'],axis=1)
#X = data.drop(['is_hex'],axis=1)
print(X.shape)
print(Y.shape)
x_train,x_test,y_train, y_test = train_test_split(X,Y,test_size=0.2,random_state=42)
x_train, x_val,y_train,y_val = train_test_split(x_train,y_train,test_size=0.2,random_state=42)
####################################  model  #################################
isolation_forest = IsolationForest(n_estimators=22, max_samples='auto',contamination = float(0.03308),bootstrap=False,random_state = 42,behaviour='new',n_jobs=-1)
isolation_forest.fit(x_train)

###   Calculate anomaly in training set based on threshold
###   from the following plot
anomaly_scores_train = isolation_forest.decision_function(x_train)
lower_bound, upper_bound = iqr_bounds(anomaly_scores_train, k=n)
predict(x_train,y_train,n,lower_bound, upper_bound)
predict(x_val,y_val,n,lower_bound, upper_bound)
predict(x_test,y_test,n,lower_bound, upper_bound, True)

print("End")



