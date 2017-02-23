#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-22 09:56
# Last modified: 2017-02-22 11:28
# Filename: linear_multi.py
# Description:
import numpy as np
import matplotlib.pyplot as plt

from numpy.linalg import inv


def feature_normalize(X):
    X_norm = X
    m = X.shape[1]
    mu = np.zeros((1, m))
    sigma = np.zeros((1, m))

    for f in range(m):
        mu[0, f] = np.mean(X[:, f])
        sigma[0, f] = np.std(X[:, f])
        X_norm[:, f] = (X_norm[:, f] - mu[0, f]) / sigma[0, f]

    return X_norm, mu, sigma


def gradient_descent_multi(X, y, theta, alpha, iterations):
    m = y.shape[0]
    J_history = []
    for it in range(iterations):
        h = np.dot(X, theta)
        errors = h - y
        theta_change = alpha / m * np.dot(X.T, errors)
        theta = theta - theta_change
        J_history.append(abs(sum(errors)))

    return theta, J_history


def normal_equation(X, y):
    return inv(X.T.dot(X)).dot(X.T).dot(y)


plt.Figure(dpi=80)


data = np.loadtxt('ex1data2.txt', delimiter=',')
X = data[:, 0:2]
y = data[:, -1]
X = X.reshape((-1, 2))
y = y.reshape((-1, 1))
m = y.shape


X, mu, sigma = feature_normalize(X)

X = np.append(np.ones(m), X, axis=1)
theta = np.random.random_sample((3, 1))

iterations = 100
alpha = 0.3


theta, J_history = gradient_descent_multi(X, y, theta, alpha, iterations)
print('Gradient Descent Theta:')
print(theta)
theta2 = normal_equation(X, y)
print('Normal Equation Theta:')
print(theta2)

plt.plot(range(len(J_history)), J_history)
plt.title('Gradient Descent Cost')
plt.xlim((0, iterations))
plt.xlabel('Iter times')
plt.ylabel('Cost')
plt.show()
