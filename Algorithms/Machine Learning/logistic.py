# Simple logistic regression implementation
# Uses gradient descent for converging
import numpy as np


#Activation function.
def sigmoid(x):
    return 1 / (1 + np.exp(-1 * x))

# Initialize inital weight vector and bias term with zeros.
def initialize_weights(n):
    weight = np.zeros((n,1))
    bias = 0
    return weight,bias

#Calculating cost.
def calculate_cost(real_y,predicted_y):
    m = real_y.shape[1]
    cost = np.sum ( real_y * np.log(predicted_y)  + (1 - real_y) * np.log(1 - predicted_y))
    return cost * (-1/m)

def train(train_sample,real_y,num_iterations,learning_rate):
    # Find examples.
    m = train_sample.shape[1]
    w,b = initialize_weights(m)
    for i in range(num_iterations):
        # Forward Propagation
        activated_sample = sigmoid( np.dot(w.T,train_sample) + b)
        # Backward Propagation
        dw = np.dot(train_sample,(activated_sample - real_y).T)
        dw /= m
        db = np.sum(activated_sample - real_y)
        db /= m
        # Update weights and bias.
        w = w - dw * learning_rate
        b = b - db * learning_rate
        params = {"w":w,"b":b}
        grad = {"dw":dw,"db":db}
        print(calculate_cost(real_y,activated_sample))
    return params,grad

def predict(w,b,train_sample):
    m = train_sample.shape[1]
    w = w.reshape(train_sample.shape[0], 1)
    activated_sample = sigmoid( np.dot(w.T,train_sample) + b)
    predictions = np.zeros((1,m))
    for i in range(train_sample.shape[1]):
        if activated_sample[0,i] >= 0.5:
            predictions[0,i] = 1
        else:
            predictions[0,i] = 0
    return predictions
