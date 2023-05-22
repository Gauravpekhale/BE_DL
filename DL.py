'''DL- 1.A  Linear regression by using Deep Neural network: Implement Boston housing
price.prediction problem by Linear regression using Deep Neural network. Use Boston House price'''
import numpy as np
import pandas as pd
import tensorflow as tf
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
data_url = "http://lib.stat.cmu.edu/datasets/boston"
raw_df = pd.read_csv(data_url, sep="\s+", skiprows=22, header=None)
data = np.hstack([raw_df.values[::2, :], raw_df.values[1::2, :2]])
target = raw_df.values[1::2, 2]

scaler = StandardScaler()  # Normalize the features
data = scaler.fit_transform(data)
X_train, X_test, y_train, y_test = train_test_split(data, target, test_size=0.2, random_state=42)     # Split the data into training and testing sets
# Build the model
model = tf.keras.Sequential([
    tf.keras.layers.Dense(units=1, input_shape=[13])
])
model.compile(optimizer='adam', loss='mean_squared_error')  # Compile the model
model.fit(X_train, y_train, epochs=100, batch_size=32, verbose=1) # Train the model
loss = model.evaluate(X_test, y_test, verbose=0) # Evaluate the model
print('Test loss:', loss)
predictions = model.predict(X_test)  # Make predictions
print('Example predictions:')       # Print example predictions and actual values
for i in range(10):
    print('Predicted:', predictions[i][0])
    print('Actual:', y_test[i])
    print()

#///////////////////////////////////////////
'''DL- 2 A Binary classification using Deep Neural Networks Example: Classify movie
reviews into positive" reviews and "negative" reviews, just based on the text content of the reviews.Use
IMDB dataset'''
import numpy as np
from tensorflow import keras
from tensorflow.keras.datasets import imdb
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, Embedding, Flatten
from tensorflow.keras.preprocessing import sequence
# Set the parameters
max_features = 5000  # Top most frequent words to consider
max_length = 300  # Maximum review length (in words)
batch_size = 64
epochs = 3
# Load the IMDB dataset
(x_train, y_train), (x_test, y_test) = imdb.load_data(num_words=max_features)
# Pad the sequences to the same length
x_train = sequence.pad_sequences(x_train, maxlen=max_length)
x_test = sequence.pad_sequences(x_test, maxlen=max_length)
# Build the model
model = Sequential()
model.add(Embedding(max_features, 32, input_length=max_length))
model.add(Flatten())
model.add(Dense(256, activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(1, activation='sigmoid'))
# Compile the model
model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
# Train the model
model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs, validation_data=(x_test, y_test))
# Evaluate the model
loss, accuracy = model.evaluate(x_test, y_test, verbose=0)
print(f'Test loss: {loss:.4f}')
print(f'Test accuracy: {accuracy:.4f}')

#///////////////////////////////////////////
'''DL 2B Multiclass classification using Deep Neural Networks: Example: Use the OCR
letter recognition dataset https://archive.ics.uci.edu/ml/datasets/letter+recognition'''

import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from keras.models import Sequential
from keras.layers import Dense
from keras.utils import np_utils
# Load the OCR letter recognition dataset
url = "https://archive.ics.uci.edu/ml/machine-learning-databases/letter-recognition/letter-recognition.data"
data = pd.read_csv(url, header=None)
# Split the dataset into features and labels
X = data.iloc[:, 1:].values
y = data.iloc[:, 0].values
# Encode the labels to integers
label_encoder = LabelEncoder()
y = label_encoder.fit_transform(y)
# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
# Scale the features
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)
# Convert the labels to one-hot encoded vectors
num_classes = len(np.unique(y))
y_train = np_utils.to_categorical(y_train, num_classes)
y_test = np_utils.to_categorical(y_test, num_classes)
# Define the model architecture
model = Sequential()
model.add(Dense(64, activation='relu', input_shape=(16,)))
model.add(Dense(64, activation='relu'))
model.add(Dense(num_classes, activation='softmax'))
# Compile the model
model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
# Train the model
model.fit(X_train, y_train, epochs=10, batch_size=32, verbose=1)
# Evaluate the model
loss, accuracy = model.evaluate(X_test, y_test, verbose=0)
print(f"Test Loss: {loss:.4f}")
print(f"Test Accuracy: {accuracy:.4f}")

#///////////////////////////////////////////
'''  Dl 3b- Use MNIST Fashion Dataset and create a classifier to classify fashion clothing
into categories. '''

import tensorflow as tf
from tensorflow.keras.datasets import fashion_mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Flatten

# Load the MNIST Fashion Dataset
(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()

# Normalize pixel values between 0 and 1
train_images = train_images / 255.0
test_images = test_images / 255.0

# Define the model
model = Sequential([
    Flatten(input_shape=(28, 28)),  # Flatten the 28x28 images into a 784-dimensional vector
    Dense(128, activation='relu'),  # Fully connected layer with 128 units and ReLU activation
    Dense(10, activation='softmax')  # Output layer with 10 units for 10 fashion categories and softmax activation
])

# Compile the model
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# Train the model
model.fit(train_images, train_labels, epochs=10, batch_size=32, verbose=1)

# Evaluate the model
test_loss, test_accuracy = model.evaluate(test_images, test_labels, verbose=0)
print('Test accuracy:', test_accuracy)

# Make predictions on new data
predictions = model.predict(test_images)
