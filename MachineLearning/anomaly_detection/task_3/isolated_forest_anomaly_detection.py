from sklearn.ensemble import IsolationForest
from sklearn.preprocessing import  LabelEncoder
from sklearn.metrics import confusion_matrix, roc_auc_score
from sklearn.model_selection import train_test_split


import seaborn as sns
import pandas as pd
import numpy as np
import matplotlib

import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

import tensorflow
import sys

columns = [
    "duration","protocol_type","service","flag","src_bytes","dst_bytes","land","wrong_fragment","urgent",
    "hot","num_failed_logins","logged_in","num_compromised","root_shell","su_attempted","num_root",
    "num_file_creatin","num_shells","num_access_files","num_outbound_vmds","is_host_login",
    "is_guest_login","count","srv_count","serror_rate","srv_serror_rate","rerror_rate","srv_rerror_rate",
    "same_srv_rate","diff_srv_rate","srv_diff_host_rate","dst_host_cout","dst_host_srv_count",
    "dst_host_same_srv_rate","dst_host_diff_srv_rate","dst_host_same_src_port_rate","dst_host_srv_diff_host_rate",
    "dst_host_serror_rate","dst_host_srv_serror_rate","dst_host_rerror_rate","dst_host_srv_rerror_rate","label"
]
df = pd.read_csv('kddcup.data.corrected.csv', sep=",",names=columns,index_col=None)
print(df.shape[0])
print(df.head())
df=df[df['service'] == 'http']
df=df.drop("service",axis=1)
columns.remove("service")
print(df["label"].value_counts())
for col in df.columns:
    if df[col].dtype == "object":
        encoded = LabelEncoder()
        encoded.fit(df[col])
        df[col] = encoded.transform(df[col])

for f in range(0,3):
    df=df.iloc[np.random.permutation(len(df))]
df2 = df[:50000]
labels=df2["label"]
df_validate = df[50000:]
x_train,x_test,y_train, y_test = train_test_split(df2,labels,test_size=0.2,random_state=42)
x_val, y_val = df_validate, df_validate["label"]
####################################  model  #################################
isolation_forest = IsolationForest(n_estimators=100, max_samples=256,contamination=0.1,random_state =42)
isolation_forest.fit(x_train)
anomaly_scores = isolation_forest.decision_function(x_val)
plt.figure(figsize=(15,10))
plt.hist(anomaly_scores, bins =100)
plt.xlabel("Average path length",fontsize=14)
plt.ylabel('Number of Data Points',fontsize=14)
plt.show()
##############################################################################
anomalies = anomaly_scores > -0.19
anomalies = np.array(anomalies).reshape(anomalies.shape[0],-1)
matches = y_val == list(encoded.classes_).index("normal.")
auc = roc_auc_score(anomalies,matches)
print("Validation Set AUC= ",auc)

anomaly_scores_test = isolation_forest.decision_function(x_test)
plt.figure(figsize=(15,10))
plt.hist(anomaly_scores_test,bins=100)
plt.xlabel("Average path lengths",fontsize=14)
plt.ylabel('Number of Data Points',fontsize=14)
plt.show()

anomalies_test = anomaly_scores_test > -0.19
anomalies_test = np.array(anomalies_test).reshape(anomalies_test.shape[0],-1)
matches = y_test == list(encoded.classes_).index("normal.")
auc = roc_auc_score(anomalies_test ,matches)
print("Testing sesetAUC = ",auc)

print("End")



