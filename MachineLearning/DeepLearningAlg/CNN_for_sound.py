import json
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
import tensorflow.keras as keras
from keras.layers import LeakyReLU
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix, accuracy_score, f1_score, precision_score, recall_score
from sklearn.metrics import classification_report

print("Start")
DATA_PATH = "data.json"
DATA_PATH_2 = "data_100_files.json"
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
    print(X.shape)
    # create train, validation and test sets
    X_train, X_test,y_train,y_test = train_test_split(X,y,test_size = test_size)

    # create train/validation split
    X_train, X_validation, y_train, y_validation = train_test_split(X_train, y_train, test_size=validation_size)

    # 3d array -> (130,13,1)
    X_train = X_train[..., np.newaxis]  # 4 D array - > (num_samples,130,13,1)
    X_validation = X_validation[..., np.newaxis]  # 4 D array - > (num_samples,130,13,1)
    X_test = X_test[..., np.newaxis]  # 4 D array - > (num_samples,130,13,1)

    return X_train, X_validation, X_test, y_train, y_validation,y_test, map
leaky_relu_alpha = 0.3
dropout = 0.3
def build_model(input_shape):
    # create model
    model = keras.Sequential()
    # 1st conv layer
    model.add(keras.layers.Conv2D(32, (3, 3), activation=LeakyReLU(alpha=leaky_relu_alpha), input_shape=input_shape))
    model.add(keras.layers.MaxPool2D((3, 3), strides=(2, 2), padding='same'))
    model.add(keras.layers.BatchNormalization())
    model.add(keras.layers.Dropout(dropout))

    # 2nd conv layer
    model.add(keras.layers.Conv2D(32, (3, 3), activation=LeakyReLU(alpha=leaky_relu_alpha), input_shape=input_shape))
    model.add(keras.layers.MaxPool2D((3, 3), strides=(2, 2), padding='same'))
    model.add(keras.layers.BatchNormalization())
    model.add(keras.layers.Dropout(dropout))

    # 3rd conv layer
    model.add(keras.layers.Conv2D(32, (2, 2), activation=LeakyReLU(alpha=leaky_relu_alpha), input_shape=input_shape))
    model.add(keras.layers.MaxPool2D((2, 2), strides=(2, 2), padding='same'))
    model.add(keras.layers.BatchNormalization())
    model.add(keras.layers.Dropout(dropout))

    # flatten the output and feed it to the dense layer
    model.add(keras.layers.Flatten())
    model.add(keras.layers.Dense(64, activation=LeakyReLU(alpha=0.1)))  #,kernel_regularizer=keras.regularizers.l1(0.001)))
    model.add(keras.layers.Dropout(dropout))
    # output layer
    model.add(keras.layers.Dense(10, activation='softmax'))

    return model

def predict(model,X,y,map):
    X =X[np.newaxis, ...]
    # prediction = [[0.1, 0.2, ...]]
    prediction = model.predict(X)  # x-> (1,130,13,1)

    # extract index with max value
    predicted_index = np.argmax(prediction,axis=1)  # [4]
    print("Expected index: {}, Predicted index: {} ".format(y,predicted_index))
    print("Expected Value: {}, Predicted Value: {} ".format(map[y], map[predicted_index]))
    return prediction

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
    X_train, X_validation, X_test, y_train, y_validation, y_test, map = prepare_datasets(0.1, 0.1)
    # buid the CNN net
    input_shape = (X_train.shape[1], X_train.shape[2],X_train.shape[3])
    model = build_model(input_shape)
    # compile the network
    optimizer = keras.optimizers.Adam(learning_rate = 0.011)
    #model.compile(optimizer = optimizer,loss= "sparse_categorical_crossentropy", metrics=[tf.keras.metrics.SparseCategoricalAccuracy()])
    model.compile(optimizer=optimizer, loss="sparse_categorical_crossentropy",metrics=['accuracy'])
    model.summary()
    #history = model.fit(X_train, y_train, validation_data=(X_test, y_test), batch_size=32,epochs=70)
    #plot_history(history)
    # train the CNN
    model.fit(X_train,y_train,validation_data=(X_validation,y_validation),batch_size=32,epochs=32)
    # evaluate the CNN on the test set
    test_error, test_accuracy = model.evaluate(X_test,y_test)

    print("Acuracy on test set is: {}".format(test_accuracy))
    print("Error on test set is: {}".format(test_error))


    y_pred = model.predict(X_validation, batch_size=64, verbose=1)
    y_pred_bool = np.argmax(y_pred, axis=1)
    report = classification_report(y_validation, y_pred_bool)
    print(type(report))
    print(report)
    X =  X_validation[90]
    y =  y_validation[90]

    y_pred = predict(model,X,y,map)




