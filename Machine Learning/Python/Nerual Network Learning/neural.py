#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-24 10:27
# Last modified: 2017-02-24 18:59
# Filename: neural.py
# Description:
from math import sqrt, floor, ceil

import numpy as np
import matplotlib.pyplot as plt

from sklearn.preprocessing import OneHotEncoder
from scipy.io import loadmat
from scipy import optimize as opt


input_layer_size = 400
hidden_layer_size = 25
num_labels = 10
iter_times = 0


def callback(nn_params):
    global iter_times
    iter_times += 1
    J = cost_func(nn_params, input_layer_size, hidden_layer_size, num_labels,
                  X, y, lamb)

    print('Iteration {:>4d}| Cost: {:.6f}'.format(iter_times, J))


def sigmoid(z):
    return 1 / (1 + np.exp(-z))


def sigmoid_gradient(z):
    return sigmoid(z) * (1-sigmoid(z))


def display_data(X):
    fig = plt.figure(dpi=80)
    f = fig.add_subplot(111)
    f.axis('off')

    m, n = X.shape
    ew = int(round(sqrt(n)))
    eh = int(n / ew)

    dr = floor(sqrt(m))
    dc = ceil(m / dr)

    pad = 1
    da = - np.ones((pad + dr * (eh + pad), pad + dc * (ew + pad)))

    cur_ex = 0

    for j in range(dr):
        for i in range(dc):
            if cur_ex > m:
                break

            max_val = max(abs(X[cur_ex, :]))
            r = pad + j * (eh + pad)
            c = pad + i * (ew + pad)
            da[r:r+eh, c:c+ew] = X[cur_ex, :].reshape((eh, ew)).T / max_val
            cur_ex += 1
        if cur_ex > m:
            break

    f.imshow(da, vmin=-1, vmax=1, cmap='gray')


def feedforward(X, theta1, theta2):
    # Feedforward
    m, n = X.shape  # m = 5000, n = 400
    a1 = np.append(np.ones((m, 1)), X, axis=1)  # a1: 5000 x 401
    z2 = a1.dot(theta1.T)  # z2: 5000 x 25
    a2 = np.append(np.ones((m, 1)), sigmoid(z2), axis=1)  # a2: 5000 x 26
    z3 = a2.dot(theta2.T)  # z3: 5000 x 10
    a3 = sigmoid(z3)  # a3: 5000 x 10
    h = a3
    return h, a1, z2, a2, z3, a3


def cost_func(nn_params, input_layer_size, hidden_layer_size, num_labels,
              X, y, lamb):
    m, n = X.shape  # m = 5000, n = 400
    theta1 = nn_params[:hidden_layer_size * (input_layer_size + 1)].copy()
    theta1 = theta1.reshape((hidden_layer_size, input_layer_size + 1))

    theta2 = nn_params[hidden_layer_size * (input_layer_size + 1):].copy()
    theta2 = theta2.reshape((num_labels, hidden_layer_size + 1))

    encoder = OneHotEncoder(sparse=False)
    y_mat = encoder.fit_transform(y)

    h, a1, z2, a2, z3, a3 = feedforward(X, theta1, theta2)

    J = -1/m*(np.sum(y_mat * np.log(h))+np.sum((1-y_mat) * np.log(1-h)))

    # Regularize
    regular_term = np.sum(theta1[:, 1:]**2) + np.sum(theta2[:, 1:]**2)
    regular_term = lamb / (2 * m) * regular_term
    J += regular_term

    return J


def back_propagation(nn_params, input_layer_size, hidden_layer_size,
                     num_labels, X, y, lamb):
    # Backpropagation
    m, n = X.shape  # m = 5000, n = 400
    theta1 = nn_params[:hidden_layer_size * (input_layer_size + 1)].copy()
    theta1 = theta1.reshape((hidden_layer_size, input_layer_size + 1))

    theta2 = nn_params[hidden_layer_size * (input_layer_size + 1):].copy()
    theta2 = theta2.reshape((num_labels, hidden_layer_size + 1))

    encoder = OneHotEncoder(sparse=False)
    y_mat = encoder.fit_transform(y)

    h, a1, z2, a2, z3, a3 = feedforward(X, theta1, theta2)

    d3 = a3 - y_mat
    d2 = d3.dot(theta2[:, 1:]) * sigmoid_gradient(z2)
    delta1 = d2.T.dot(a1)
    delta2 = d3.T.dot(a2)
    theta1_grad = delta1 / m
    theta2_grad = delta2 / m

    theta1[:, 0] = 0
    theta2[:, 0] = 0
    theta1_grad += theta1 * lamb / m
    theta2_grad += theta2 * lamb / m

    grad = np.append(theta1_grad.flatten(), theta2_grad.flatten())
    return grad


def rand_init_weights(lin, lout):
    init_e = 0.12
    w = np.random.random_sample((lout, lin + 1)) * 2 * init_e - init_e
    return w


def predict(theta1, theta2, X):
    m, n = X.shape

    h1 = sigmoid(np.append(np.ones((m, 1)), X, axis=1).dot(theta1.T))
    h2 = sigmoid(np.append(np.ones((m, 1)), h1, axis=1).dot(theta2.T))

    hypothesis = np.argmax(h2, axis=1) + 1

    return hypothesis


print('Loading and Visualizing Data...')
mat = loadmat('ex4data1.mat')
X, y = mat['X'], mat['y']

m, n = X.shape

sel = X[np.random.choice(m, 100, replace=False), :]

display_data(sel)

print('Loading Saved Neural Network Parameters')

weights = loadmat('ex4weights.mat')
theta1, theta2 = weights['Theta1'], weights['Theta2']
nn_params = np.append(theta1, theta2)

print('Feedforward Using Neural Network...')
lamb = 0
J = cost_func(nn_params, input_layer_size, hidden_layer_size, num_labels,
              X, y, lamb)
print('Cost at parameters (loaded from ex4weights): {:.6f}'.format(J))

print('Checking Cost Function(Regularization)...')
lamb = 1
J = cost_func(nn_params, input_layer_size, hidden_layer_size, num_labels,
              X, y, lamb)
print('Cost at parameters (loaded from ex4weights): {:.6f}'.format(J))

print('Initializing Neural Network Parameters...')
initial_theta1 = rand_init_weights(input_layer_size, hidden_layer_size)
initial_theta2 = rand_init_weights(hidden_layer_size, num_labels)
initial_nn_params = np.append(initial_theta1, initial_theta2)

print('Training Neural Network...')
options = {'full_output': True, 'maxiter': 100, 'callback': callback}

nn_params, cost, *rest = opt.fmin_cg(
    cost_func, x0=initial_nn_params, fprime=back_propagation,
    args=(input_layer_size, hidden_layer_size, num_labels, X, y, lamb),
    **options)

theta1 = nn_params[:hidden_layer_size * (input_layer_size + 1)].copy()
theta1 = theta1.reshape((hidden_layer_size, input_layer_size + 1))

theta2 = nn_params[hidden_layer_size * (input_layer_size + 1):].copy()
theta2 = theta2.reshape((num_labels, hidden_layer_size + 1))

print('Visualizing Neural Network...')
display_data(theta1[:, 1:])

print('Start Predicting...')
h = predict(theta1, theta2, X).reshape((-1, 1))

print('Training Set Accurary: {:.2%}'.format(np.sum(h == y) / m))

plt.show()
