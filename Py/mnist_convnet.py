# -*- coding: utf-8 -*-
#------------------------------------------------------------------------------
#-- Federico Sarrocco, Alessandro Vacca, Davide Preatoni                     --
#-- Data: 28/02/2022                                                         --
#------------------------------------------------------------------------------

#library 
import numpy as np
import time
from tensorflow import keras
from tensorflow.keras import layers
import matplotlib.pyplot as plt
#----

"""## Prepare the data"""

 
num_classes = 10            # Model / data parameters
input_shape = (28, 28, 1)

(x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data()         # the data, split between train and test sets

x_train = x_train.astype("float32") / 255   # Scale images to the [0, 1] range
x_test = x_test.astype("float32") / 255

x_train = np.expand_dims(x_train, -1)   # Make sure images have shape (28, 28, 1)
x_test = np.expand_dims(x_test, -1)

print("x_train shape:", x_train.shape)
print(x_train.shape[0], "train samples")
print(x_test.shape[0], "test samples")

y_train = keras.utils.to_categorical(y_train, num_classes)      # convert class vectors to binary class matrices
y_test = keras.utils.to_categorical(y_test, num_classes)

"""## Build the model"""


model = keras.Sequential(
    [
        keras.Input(shape=input_shape),
        layers.Conv2D(32, kernel_size=(3, 3), strides = (1, 1), activation="relu"),
        layers.MaxPooling2D(pool_size=(2, 2)),
        layers.Flatten(),
        layers.Dropout(0.5),
        layers.Dense(num_classes, activation="softmax"),
    ]
)

model.summary()

weights = model.layers[4].get_weights()[0]
np.savetxt('output_weight.txt', weights, delimiter = ',')   #save thw weights
weights.shape

bias = model.layers[4].get_weights()[1]
np.savetxt('output_bias.txt', bias, delimiter = ',')    #save the bias
len(bias)

"""## Train the model"""

batch_size = 128 
epochs = 15     #iterazioni

model.compile(loss="categorical_crossentropy", optimizer="adam", metrics=["accuracy"])

model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs, validation_split=0.1)

"""## Evaluate the trained model"""

score = model.evaluate(x_test, y_test, verbose=0)
print("Test loss:", score[0])
print("Test accuracy:", score[1])

index = 21
out = model.predict(x_test[index:index + 1])
np.argmax(out)


#plt.imshow(x_test[index][:,:,0])


start = time.time()     #timing
for _ in range(100): 
  out = model.predict(x_test[index:index + 1])
end = time.time()

print((end - start)/100)

