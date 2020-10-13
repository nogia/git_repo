# pip install librosa
import librosa , librosa.display
import matplotlib.pyplot as plt
import numpy as np
from sklearn.model_selection import train_test_split
import tensorflow.keras as keras
import json


DATASET_PATH = "data.json"
#load data
def load_data(dataset_path):
    with open(dataset_path, "r") as fp:
        data = json.load(fp)

    #convert lists into numpy arrays
    inputs = np.array(data["mfcc"])
    targets = np.array(data["labels"])

    return inputs, targets
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

print("Start")
if __name__ == "__main__":
    inputs, targets = load_data(DATASET_PATH)
    #split the data into train test
    inputs_train, inputs_test, targets_train, targets_test = train_test_split(inputs,targets,test_size = 0.3)
    #build the network architecture
    model = keras. Sequential([
        # imput layer
        keras.layers.Flatten(input_shape = ( inputs.shape[1], inputs.shape[2])  ),
        # 1st hidden layer
        keras.layers.Dense(512,activation = "relu",kernel_regularizer=keras.regularizers.l2(0.01)),
        keras.layers.Dropout(0.1),
        # 2nd hidden layer
        keras.layers.Dense(256, activation="relu",kernel_regularizer=keras.regularizers.l2(0.01)),
        keras.layers.Dropout(0.1),
        # 3 rd hidden layer
        keras.layers.Dense(64, activation="relu",kernel_regularizer=keras.regularizers.l2(0.01)),
        keras.layers.Dropout(0.1),
        # output layer
        keras.layers.Dense(10, activation = "softmax")
    ])
    # compile network
    optimizer =  keras.optimizers.Adam(learning_rate = 0.0001)
    model.compile(optimizer = optimizer, loss = "sparse_categorical_crossentropy",metrics = ["accuracy"])
    model.summary()

    # plot accuracy and error
    history = model.fit(inputs_train, targets_train, validation_data=(inputs_test, targets_test), batch_size = 32, epochs = 150)
    plot_history(history)
    # train network
    model.fit(inputs_train, targets_train,
              validation_data = (inputs_test,targets_test),
              epochs = 50,
              batch_size = 32)
print("End")
