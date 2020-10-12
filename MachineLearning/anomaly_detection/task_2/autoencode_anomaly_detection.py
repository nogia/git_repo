import keras
from keras import optimizers
from keras import losses
from keras.models import Sequential, Model
from keras.layers import Dense, Input, Dropout, Embedding, LSTM
from keras.optimizers import RMSprop, Adam, Nadam
from keras.preprocessing import sequence
from keras.callbacks import  TensorBoard

import sklearn
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix, roc_auc_score
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import classification_report
from keras import regularizers


import seaborn as sns
import pandas as pd
import numpy as np
import matplotlib

import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

import tensorflow
import sys
from viz.visualization import visualization

print("Python : ", pd.__version__)
print("numpy : ",np.__version__)
print("seaborn : ", sns.__version__)
print("matplotlib : ",matplotlib.__version__)
print("sklearn : ", sklearn.__version__)
print("Keras :", keras.__version__)
print("Tensorflow : ", tensorflow.__compiler_version__)

df = pd.read_csv('creditcard.csv', header=0,sep=',')
print(df.shape[0])
print(df.head())

df['Amount'] = StandardScaler().fit_transform(df['Amount'].values.reshape(-1,1))
df0 = df.query('Class == 0').sample(20000)
df1 = df.query('Class == 1').sample(400)
df = pd.concat([df0,df1])
x_train, x_test,y_train, y_test  = train_test_split(df.drop(labels=['Time','Class'],axis=1),df['Class'],test_size=0.2,random_state=42)
print(x_train.shape," train_samples")
print(x_test.shape, " test_samples")

# Deep Autoencoder
logfile_name ="deepautoencoder"
encoding_dim = 16
input_dim =x_train.shape[1]
inputArray = Input(shape=(input_dim,))
encoded = Dense(encoding_dim,activation='relu')(inputArray)
encoded = Dense(8,activation='relu')(encoded)
encoded = Dense(4,activation='relu')(encoded)

decoded = Dense(8,activation = 'relu')(encoded)
decoded = Dense(encoding_dim,activation = 'relu')(decoded)
decoded = Dense(input_dim,activation = 'softmax')(decoded)

autoencoder = Model(inputArray,decoded)
autoencoder.summary()
autoencoder.compile(optimizer=RMSprop(),loss = 'mean_squared_error',metrics=['mae','accuracy'])
batch_size = 32
epochs =20
history = autoencoder.fit(x_train,y_train,batch_size=batch_size,epochs=epochs,verbose=1,validation_data=(x_test,y_test),callbacks=[TensorBoard(log_dir='../logs/autoencoder1')])

threshold= [10, 1,5,15]
for th in threshold:
    print("Threshold = ",th)
    y_pred = autoencoder.predict(x_test)
    y_dist = np.linalg.norm(x_test - y_pred,axis = -1)
    z = zip(y_dist >= th,y_dist)
    y_label=[]
    error = []
    for idx,(is_anomaly,y_dist) in enumerate(z):
        if is_anomaly:
            y_label.append(1)
        else:
            y_label.append(0)
        error.append(y_dist)
    y_label = pd.Series(y_label)
    print(classification_report(y_test,y_label))
    print("roc_auc_score = ",roc_auc_score(y_test,y_label))
    viz = visualization()
    viz.draw_confusion_matrix(y_test,y_label)
    viz.draw_anomaly(y_test,error,threshold)
    print("End Threshold = " ,th)
##############################################################################

print("End")



