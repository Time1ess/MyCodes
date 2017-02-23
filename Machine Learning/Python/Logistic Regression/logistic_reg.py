#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-23 14:21
# Last modified: 2017-02-23 16:15
# Filename: logistic_reg.py
# Description:
import numpy as np
import matplotlib.pyplot as plt
import scipy.optimize as opt


def sigmoid(z):
    g = 1 / (1 + np.exp(-z))
    return g


def map_feature(X1, X2):
    degree = 6
    out = np.ones(X1.shape).reshape((-1, 1))
    for i in range(1, degree+1):
        for j in range(i+1):
            nf = np.array(X1**(i-j) * X2**j).reshape((-1, 1))
            out = np.append(out, nf, axis=1)
    return out


def cost_func(theta, X, y, lamb):
    m = len(y)

    h = sigmoid(X.dot(theta))
    J = -(np.log(h).T.dot(y) + np.log(1-h).T.dot(1-y)) / m
    J = J + lamb / (m * 2) * np.sum(theta[1:]**2)
    return J


def gradient_func(theta, X, y, lamb):
    theta = theta.reshape((-1, 1))
    m, n = X.shape

    h = sigmoid(X.dot(theta))
    errors = h - y
    grad = X.T.dot(errors) / m
    grad = grad + lamb / m * theta
    grad[0] = X[:, 0].T.dot(h - y) / m
    return grad.flatten()


plt.Figure(dpi=80)

data = np.loadtxt('ex2data2.txt', delimiter=',').reshape((-1, 3))
X = data[:, :2]
y = data[:, 2:]

pos = np.where(y != 0)[0]
neg = np.where(y == 0)[0]

plt.scatter(X[pos, 0], X[pos, 1], marker='o', c='b', label='y = 1')
plt.scatter(X[neg, 0], X[neg, 1], marker='x', c='r', label='y = 0')

X = map_feature(X[:, :1], X[:, 1:])

theta = np.zeros((X.shape[1], 1))
# lambda
lamb = 1.0

options = {'full_output': True, 'maxiter': 400}
theta, cost, *rest = opt.fmin_bfgs(cost_func, x0=theta, fprime=gradient_func,
                                   args=(X, y, lamb), **options)

u = np.linspace(-1, 1.5, 50)
v = np.linspace(-1, 1.5, 50)

k = len(u)

z = np.zeros((k, k))
for i in range(k):
    for j in range(k):
        z[i, j] = map_feature(u[i], v[j]).dot(theta)
z = z.T

plt.contour(u, v, z, 1)

plt.xlabel('Microchip Test 1')
plt.ylabel('Microchip Test 2')

plt.legend(['y = 1', 'y = 0'])
plt.title('Regularized Logistic Regression with lambda {}'.format(lamb))
plt.show()
