#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-03 20:52
# Last modified: 2017-03-03 21:26
# Filename: anomaly.py
# Description:
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

from scipy import stats
from scipy.io import loadmat


def estimate_gaussion(X):
    mu = X.mean(axis=0)
    sigma2 = X.var(axis=0)

    return mu, sigma2


def select_threshold(pval, yval):
    best_epsilon = 0
    best_f1 = 0
    f1 = 0

    step = (pval.max() - pval.min()) / 1000

    for epsilon in np.arange(pval.min() + step, pval.max(), step):
        preds = pval < epsilon

        tp = np.sum(np.logical_and(preds == 1, yval == 1).astype(float))
        fp = np.sum(np.logical_and(preds == 1, yval == 0).astype(float))
        fn = np.sum(np.logical_and(preds == 0, yval == 1).astype(float))

        precision = tp / (tp + fp)
        recall = tp / (tp + fn)

        f1 = 2 * precision * recall / (precision + recall)

        if f1 > best_f1:
            best_f1 = f1
            best_epsilon = epsilon

    return best_epsilon, best_f1


data = loadmat('ex8data1.mat')
X = data['X']
Xval = data['Xval']
yval = data['yval']

fig, ax = plt.subplots(figsize=(12, 8))
ax.scatter(X[:, 0], X[:, 1])
ax.set_xlabel('Latency (ms)')
ax.set_ylabel('Throughput (mb/s)')
ax.set_xlim((0, 30))
ax.set_ylim((0, 30))

mu, sigma2 = estimate_gaussion(X)
p = np.zeros(X.shape)
p[:, 0] = stats.norm(mu[0], sigma2[0]).pdf(X[:, 0])
p[:, 1] = stats.norm(mu[1], sigma2[1]).pdf(X[:, 1])

pval = np.zeros(Xval.shape)
pval[:, 0] = stats.norm(mu[0], sigma2[0]).pdf(Xval[:, 0])
pval[:, 1] = stats.norm(mu[1], sigma2[1]).pdf(Xval[:, 1])

epsilon, f1 = select_threshold(pval, yval)
outliers = np.where(p < epsilon)
fig, ax = plt.subplots(figsize=(12, 8))
ax.scatter(X[:, 0], X[:, 1])
ax.scatter(X[outliers[0], 0], X[outliers[0], 1], s=50, color='r', marker='o')
ax.set_xlabel('Latency (ms)')
ax.set_ylabel('Throughput (mb/s)')
ax.set_xlim((0, 30))
ax.set_ylim((0, 30))


plt.show()
