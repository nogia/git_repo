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

#####               value n for calculation outliers bounds                          #####
n = 2
Lower_bound = 0
Upper_bound = 0

def iqr_bounds(scores,k=1.5):
    print(type(scores))
    q1 = np.quantile(scores,0.25)
    q3 = np.quantile(scores,0.75)
    iqr = q3 - q1
    lower_bound=(q1 - k * iqr)
    upper_bound=(q3 + k * iqr)
    print("Lower bound:{} \nUpper bound:{}".format(lower_bound,upper_bound))
    return lower_bound,upper_bound

#####                              Predict Function                                   #####
def predict(x,y,n,lower_bound,upper_bound,is_test = False):
    anomaly_scores = isolation_forest.decision_function(x)

    if is_test == False:
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
        ### calculate confusion matrix between y vs y_pred  for train and for validating sets   ###

        cf_matrix = confusion_matrix(y, y_pred)
        print(cf_matrix)
        report = classification_report(y, y_pred)
        print(report)
        auc = roc_auc_score(y, y_pred)
        print("AUC= ", auc)

        group_names = ['True Neg', 'False Pos', 'False Neg', 'True Pos']
        group_counts = ['{0:0.0f}'.format(value) for value in
                        cf_matrix.flatten()]
        group_percentages = ['{0:.2%}'.format(value) for value in
                             cf_matrix.flatten() / np.sum(cf_matrix)]
        labels = [f'{v1}\n{v2}\n{v3}' for v1, v2, v3 in
                  zip(group_names, group_counts, group_percentages)]
        labels = np.asarray(labels).reshape(2, 2)
        plt.figure(figsize=(15, 10))
        sns.heatmap(cf_matrix, annot=labels, fmt='', cmap='Blues')
        plt.show()

        if is_test:
                x['predicted'] = y_pred
                x.to_csv(r'x_test_with_predictions.csv', index=False, header=True)
    plt.figure(figsize=(15, 10))
    plt.hist(anomaly_scores, bins=100)
    plt.xlabel("Anomaly Scores  where outlier bounds = [" + str("{:.5}".format(round(lower_bound, 5))) + ',' + str(
        "{:.5}".format(round(upper_bound, 5))) + "]", fontsize=14)
    plt.ylabel('Number of Data Points', fontsize=14)
    plt.show()
df = pd.read_csv('data.csv')

#####           use lableEncoder to encode categorical data                          #####

print(df.dtypes)
encs = dict()
data = df.copy()  #.sample(frac=1)
for col in data.columns:
    if data[col].dtype == "object" or data[col].dtype == "bool":
        encs[col] = LabelEncoder()
        encs[col].fit(df[col])
        data[col] = encs[col].transform(data[col])
print(data.dtypes)

#####                          Shaffle Dataset                                       #####

df_len = len(data)
for f in range(0,3):
    data=data.iloc[np.random.permutation(df_len)]
fig,ax = plt.subplots(figsize=(12,7))
sns.heatmap(data.corr(),fmt="",linewidths=0.3,ax=ax)
plt.show()
data['Class'] = 0
Y = data['Class']
X = data.drop(['Class'],axis=1)

x_train,x_test,y_train, y_test = train_test_split(X,Y,test_size=0.2,random_state=42)
x_train, x_val,y_train,y_val = train_test_split(x_train,y_train,test_size=0.2,random_state=42)
###############################       Create Model         #################################
isolation_forest = IsolationForest(n_estimators=21, max_samples='auto',contamination = float(0.03306),bootstrap=False,random_state = 42,behaviour='new',n_jobs=-1)
isolation_forest.fit(x_train)

###   Calculate anomaly in training set based on threshold
anomaly_scores_train = isolation_forest.decision_function(x_train)
lower_bound, upper_bound = iqr_bounds(anomaly_scores_train, k=n)

predict(x_train,y_train,n,lower_bound, upper_bound)
predict(x_val,y_val,n,lower_bound, upper_bound)
predict(x_test,y_test,n,lower_bound, upper_bound, True)

print("End")



