#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-28 09:57
# Last modified: 2017-02-28 10:08
# Filename: svm_spam.py
# Description:
import numpy as np
import pandas as pd

from scipy.io import loadmat
from sklearn import svm

spam_train = loadmat('spamTrain.mat')
spam_test = loadmat('spamTest.mat')

X = spam_train['X']
Xtest = spam_test['Xtest']
y = spam_train['y'].ravel()
ytest = spam_test['ytest'].ravel()

svc = svm.SVC(max_iter=1000)
print('Training SVM...')
svc.fit(X, y)
print('Evaluate SVM...')
print('Test accuracy = {:%}'.format(svc.score(Xtest, ytest)))
