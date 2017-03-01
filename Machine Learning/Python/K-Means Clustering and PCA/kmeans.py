#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-01 15:39
# Last modified: 2017-03-01 16:51
# Filename: kmeans.py
# Description:
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from scipy.io import loadmat


ITER_TIMES = 10


def find_closest_centroids(X, centroids):
    m, n = X.shape
    idx = np.zeros(m, dtype=int)
    K = centroids.shape[0]

    for i in range(m):
        min_dist = 1e9
        for k in range(K):
            dist = np.sum((X[i, :] - centroids[k, :]) ** 2)
            if dist < min_dist:
                idx[i] = k
                min_dist = dist

    return idx


def compute_centroids(X, idx, K):
    m, n = X.shape
    centroids = np.zeros((K, n))

    for i in range(K):
        indices = np.where(idx == i)[0]
        centroids[i, :] = np.sum(X[indices, :], axis=0) / indices.shape[0]

    return centroids


def run_k_means(X, initial_centroids, max_iter=10, random_times=10):
    centroids = initial_centroids
    opt_centroids = initial_centroids
    K = initial_centroids.shape[0]
    min_cost = 1e9

    for j in range(random_times):
        for i in range(max_iter):
            idx = find_closest_centroids(X, centroids)
            centroids = compute_centroids(X, idx, K)
        cost = cost_func(X, idx, centroids)
        if cost < min_cost:
            opt_idx = idx
            opt_centroids = centroids
            min_cost = cost
    return opt_idx, opt_centroids


def random_init_centroids(X, K):
    m, n = X.shape
    centroids = np.zeros((K, n))
    idx = np.random.randint(0, m, K)

    for i in range(K):
        centroids[i, :] = np.copy(X[idx[i], :])

    return centroids


def cost_func(X, idx, centroids):
    m, n = X.shape
    cost = 0
    for i in range(m):
        cost += np.sum((X[i, :] - centroids[idx[i], :]) ** 2)
    cost /= m

    return cost


data = loadmat('ex7data2.mat')
X = data['X']

initial_centroids = random_init_centroids(X, 3)
# initial_centroids = np.array([[3, 3], [6, 2], [8, 5]])
K = initial_centroids.shape[0]

print('Running K-Means...')
idx, centroids = run_k_means(X, initial_centroids)

clusters = []
for k in range(K):
    clusters.append(X[np.where(idx == k)[0], :])

print('Visualizing K-Means results...')
fig, ax = plt.subplots(figsize=(12, 8))
colors = ['r', 'g', 'b']
for idx, (cluster, c) in enumerate(zip(clusters, colors)):
    ax.scatter(centroids[idx, 0], centroids[idx, 1], s=1e3, color=c,
               marker='+')
    ax.scatter(cluster[:,0], cluster[:,1], s=10, color=c,
               label='Cluster {}'.format(idx))
ax.set_title('K-Means with K={}'.format(K))

print('Applying K-Means on Image')
image_data = loadmat('bird_small.mat')
A = image_data['A']
A = A / 255.
X = np.reshape(A, (A.shape[0] * A.shape[1], A.shape[2]))
initial_centroids = random_init_centroids(X, 16)
idx, centroids = run_k_means(X, initial_centroids, random_times=1)
idx = find_closest_centroids(X, centroids)
X_recovered = centroids[idx, :]
X_recovered = np.reshape(X_recovered, (A.shape[0], A.shape[1], A.shape[2]))
fig, ax = plt.subplots(figsize=(12, 8))
ax.imshow(X_recovered)
plt.show()
