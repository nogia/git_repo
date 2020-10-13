#import required packages
import pandas as pd
import matplotlib.pyplot as plt
import datetime as dt
#read the data
#df = pd.read_csv("AirQualityUCI.csv",sep=';', parse_dates=[['Date', 'Time']])
#df = pd.read_excel('AirQualityUCI.xlsx',parse_dates=[['Date', 'Time']])
from keras.layers import LeakyReLU

import json
import numpy as np
from sklearn.model_selection import train_test_split
import tensorflow.keras as keras

print("Start")
DATA_PATH = "data.json"
def load_data(data_path):
    with open(data_path, "r") as fp:
        data = json.load(fp)

    X = np.array(data["mfcc"])
    y = np.array(data["labels"])
    map = np.array(data["mapping"])
    return X, y, map

def prepare_datasets(test_size,validation_size):
    # load data
    X, y, map = load_data(DATA_PATH)
    # create train, validation and test sets
    X_train, X_test,y_train,y_test = train_test_split(X,y,test_size = test_size)

    # create train/validation split
    X_train, X_validation, y_train, y_validation = train_test_split(X_train, y_train, test_size=validation_size)

    return X_train, X_validation, X_test, y_train, y_validation,y_test, map
leaky_relu_alpha = 0.1
dropout = 0.3
def build_model(input_shape):
    # create RNN-LSTM model
    model = keras.Sequential()
    # input layer
    model.add(keras.layers.LSTM(64,input_shape = input_shape, return_sequences=True))
    model.add(keras.layers.LSTM(64))

    # dense layer
    model.add(keras.layers.Dense(64, activation=LeakyReLU(alpha=leaky_relu_alpha)))
    model.add(keras.layers.Dropout(dropout))

    # Output layer
    model.add(keras.layers.Dense(10,activation = 'softmax', kernel_regularizer=keras.regularizers.l2(0.001)))

    return model

def predict(model,X,y,map):
    X =X[np.newaxis, ...]
    # prediction = [[0.1, 0.2, ...]]
    prediction = model.predict(X)  # x-> (1,130,13,1)

    # extract index with max value
    predicted_index = np.argmax(prediction,axis=1)  # [4]
    print("Expected index: {}, Predicted index: {} ".format(y,predicted_index))
    print("Expected Value: {}, Predicted Value: {} ".format(map[y], map[predicted_index]))
def plot_history(history):
    fig, axs = plt.subplots(2)
    # create accuracy subplot
    axs[0].plot(history.history["accuracy"], label="train accuracy")
    axs[0].plot(history.history["val_accuracy"], label="test accuracy")
    axs[0].set_ylabel("Accuracy")
    axs[0].legend(loc="lower right")
    axs[0].set_title("Accuracy eval")
    # create eoor subplot
    axs[1].plot(history.history["loss"], label="train error")
    axs[1].plot(history.history["val_loss"], label="test error")
    axs[1].set_ylabel("Error")
    axs[1].set_xlabel("Epoch")
    axs[1].legend(loc="upper right")
    axs[1].set_title("Error eval")

    plt.show()
if __name__ == "__main__":
     #create train, validation and test sets
    X_train, X_validation, X_test, y_train, y_validation, y_test, map = prepare_datasets(0.25, 0.2)

    # buid the CNN net
    input_shape = (X_train.shape[1], X_train.shape[2])  # 130 -> numver of Time steps ,13 -> number of features
    model = build_model(input_shape)

    # compile the network
    optimizer = keras.optimizers.Adam(learning_rate = 0.0001)
    model.compile(optimizer = optimizer,loss = "sparse_categorical_crossentropy", metrics=['accuracy'])

    model.summary()

    history = model.fit( X_train,y_train, validation_data=(X_validation,y_validation),batch_size=32,epochs=30)
    plot_history(history)

    # evaluate model on test set
    model.fit(X_train, y_train, batch_size=32, epochs=15)
    test_loss, test_acc = model.evaluate(X_test, y_test, verbose=2)
    print('\nTest accuracy:', test_acc)

    # make predictions on a sample
    X = X_validation[80]
    y = y_validation[80]

    predict(model, X, y, map)

print("End")