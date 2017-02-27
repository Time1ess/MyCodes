#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-27 18:37
# Last modified: 2017-02-27 19:41
# Filename: svm.py
# Description:
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

from scipy.io import loadmat
from sklearn import svm


def gaussian_kernal(x1, x2, sigma):
    return np.exp(-(np.sum((x1-x2)**2)/(2*sigma**2)))

print('Linear SVM classification')

raw_data = loadmat('ex6data1.mat')

data = pd.DataFrame(raw_data['X'], columns=['X1', 'X2'])
data['y'] = raw_data['y']

print('Loading and Visualizing Data ...')
pos = data[data['y'].isin([1])]
neg = data[data['y'].isin([0])]

fig, ax = plt.subplots(figsize=(12, 8))
ax.scatter(pos['X1'], pos['X2'], marker='o', c='b', label='Positive')
ax.scatter(neg['X1'], neg['X2'], marker='x', c='r', label='Negative')
ax.legend()

print('Training Linear SVM ...')
svc = svm.LinearSVC(C=1, loss='hinge', max_iter=1000)
svc.fit(data[['X1', 'X2']], data['y'])
score = svc.score(data[['X1', 'X2']], data['y'])
print('Accuracy for C=1: ', score)

svc2 = svm.LinearSVC(C=100, loss='hinge', max_iter=1000)
svc2.fit(data[['X1', 'X2']], data['y'])
score = svc2.score(data[['X1', 'X2']], data['y'])
print('Accuracy for C=100: ', score)

data['SVM1 Confidence'] = svc.decision_function(data[['X1', 'X2']])
fig, ax = plt.subplots(figsize=(12, 8))
ax.scatter(data['X1'], data['X2'], s=50, c=data['SVM1 Confidence'], cmap='seismic')  
ax.set_title('SVM (C=1) Decision Confidence')  

# Plot Decision Boundry
x1_plot = np.linspace(data['X1'].min(), data['X1'].max(), 500)
x2_plot = np.linspace(data['X2'].min(), data['X2'].max(), 500)
mx1, mx2 = np.meshgrid(x1_plot, x2_plot)
z = svc.predict(np.c_[mx1.ravel(), mx2.ravel()])
z = z.reshape(mx1.shape)
ax.contourf(mx1, mx2, z, alpha=0.1)
ax.set_title('Linear SVM Decision Boundry(C=1)')

data['SVM2 Confidence'] = svc2.decision_function(data[['X1', 'X2']])
fig, ax = plt.subplots(figsize=(12, 8))
ax.scatter(data['X1'], data['X2'], s=50, c=data['SVM2 Confidence'], cmap='seismic')  
ax.set_title('SVM (C=100) Decision Confidence')  

# Plot Decision Boundry
x1_plot = np.linspace(data['X1'].min(), data['X1'].max(), 500)
x2_plot = np.linspace(data['X2'].min(), data['X2'].max(), 500)
mx1, mx2 = np.meshgrid(x1_plot, x2_plot)
z = svc2.predict(np.c_[mx1.ravel(), mx2.ravel()])
z = z.reshape(mx1.shape)
ax.contourf(mx1, mx2, z, alpha=0.1)
ax.set_title('Linear SVM Decision Boundry(C=100)')


print('Non-linear SVM classification')

raw_data = loadmat('ex6data2.mat')

data = pd.DataFrame(raw_data['X'], columns=['X1', 'X2'])
data['y'] = raw_data['y']

print('Loading and Visualizing Data ...')
pos = data[data['y'].isin([1])]
neg = data[data['y'].isin([0])]

fig, ax = plt.subplots(figsize=(12, 8))
ax.scatter(pos['X1'], pos['X2'], marker='o', c='b', label='Positive')
ax.scatter(neg['X1'], neg['X2'], marker='x', c='r', label='Negative')
ax.legend()

svc = svm.SVC(C=1e6, gamma=10, probability=True)  
svc.fit(data[['X1', 'X2']], data['y'])
data['prob'] = svc.predict_proba(data[['X1', 'X2']])[:,0]

# ax.scatter(data['X1'], data['X2'], s=30, c=data['prob'], cmap='Reds')  

# Plot Decision Boundry
x1_plot = np.linspace(data['X1'].min(), data['X1'].max(), 500)
x2_plot = np.linspace(data['X2'].min(), data['X2'].max(), 500)
mx1, mx2 = np.meshgrid(x1_plot, x2_plot)
z = svc.predict(np.c_[mx1.ravel(), mx2.ravel()])
z = z.reshape(mx1.shape)
ax.contourf(mx1, mx2, z, alpha=0.1)
ax.set_title('Non-linear SVM Decision Boundry(C=1e6)')


plt.show()
