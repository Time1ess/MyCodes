#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-01 17:53
# Last modified: 2017-03-01 18:20
# Filename: pca.py
# Description:
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from scipy.io import loadmat


def pca(X):
    X = np.copy(X)
    X = (X - X.mean()) / X.std()

    cov = X.T.dot(X) / X.shape[0]

    U, S, V = np.linalg.svd(cov)

    return U, S, V


def project_data(X, U, k):
    U_reduce = U[:, :k]
    return X.dot(U_reduce)


def recover_data(Z, U, k):
    U_reduce = U[:, :k]
    return Z.dot(U_reduce.T)


data = loadmat('ex7data1.mat')
X = data['X']

U, S, V = pca(X)
K = 1

Z = project_data(X, U, K)
X_recovered = recover_data(Z, U, K)
print('PCA on X with K={}: {:.2%}'.format(K, np.sum(S[:K])/np.sum(S)))

fig, ax = plt.subplots(figsize=(12, 8))
ax.scatter(X[:, 0], X[:, 1])
ax.scatter(X_recovered[:, 0], X_recovered[:, 1], c='r')


faces = loadmat('ex7faces.mat')
X = faces['X']

fig, ax = plt.subplots(figsize=(12, 8))
face = np.reshape(X[0, :], (32, 32)).T
ax = fig.add_subplot(121)
ax.imshow(face, cmap='gray')

U, S, V = pca(X)
K = 200

Z = project_data(X, U, K)
X_recovered = recover_data(Z, U, K)
print('PCA on X with K={}: {:.2%}'.format(K, np.sum(S[:K])/np.sum(S)))
face = np.reshape(X_recovered[0, :], (32, 32)).T
ax = fig.add_subplot(122)
ax.imshow(face, cmap='gray')

plt.show()
