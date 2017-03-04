#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-04 09:36
# Last modified: 2017-03-04 10:21
# Filename: cofi.py
# Description:
import numpy as np
import matplotlib.pyplot as plt

from scipy.io import loadmat
from scipy.optimize import minimize


def cost_func(params, Y, R, feature_num, learning_rate):
    movie_num, user_num = Y.shape

    X = np.reshape(params[:movie_num*feature_num], (movie_num, feature_num))
    Theta = np.reshape(params[movie_num*feature_num:], (user_num, feature_num))

    J = 0
    t = (X.dot(Theta.T) - Y) * R
    J = 1. / 2 * np.sum(t**2)
    J += learning_rate / 2 * (np.sum(Theta ** 2) + np.sum(X ** 2))

    X_grad = (t * R).dot(Theta) + learning_rate * X
    Theta_grad = (t * R).T.dot(X) + learning_rate * Theta

    grad = np.append(X_grad.ravel(), Theta_grad.ravel())
    
    return J, grad


data = loadmat('ex8_movies.mat')
Y = data['Y']
R = data['R']

fig, ax = plt.subplots(figsize=(12, 12))
ax.imshow(Y)
ax.set_xlabel('Users')
ax.set_ylabel('Movies')

users = 4
movies = 5
features = 3

params_data = loadmat('ex8_movieParams.mat')
X = params_data['X']
Theta = params_data['Theta']

X_sub = X[:movies, :features]
Theta_sub = Theta[:users, :features]
Y_sub = Y[:movies, :users]
R_sub = R[:movies, :users]

params = np.append(X_sub.ravel(), Theta_sub.ravel())

print('Test cost_func: {0[0]}\nGrad:\n{0[1]}'.format(
    cost_func(params, Y_sub, R_sub, features, 1.5)))

movie_idx = {}
with open('movie_ids.txt', 'r') as f:
    for line in f:
        tokens = line.strip('\n').split(' ')
        movie_idx[int(tokens[0]) - 1] = ' '.join(tokens[1:])

ratings = np.zeros((1682, 1))
ratings[0] = 4
ratings[6] = 3
ratings[11] = 5
ratings[53] = 4
ratings[63] = 5
ratings[65] = 3
ratings[68] = 5
ratings[97] = 2
ratings[182] = 4
ratings[225] = 5
ratings[354] = 5

for idx in np.where(ratings != 0)[0]:
    print('Rated {0} with {1} stars.'.format(movie_idx[idx], int(ratings[idx])))

R = data['R']
Y = data['Y']

Y = np.append(Y, ratings, axis=1)
R = np.append(R, ratings != 0, axis=1)

movies, users = Y.shape
features = 10
learning_rate = 10.

X = np.random.random(size=(movies, features))
Theta = np.random.random(size=(users, features))
params = np.append(X.ravel(), Theta.ravel())

Ymean = np.zeros((movies, 1))
Ynorm = np.zeros((movies, users))

for i in range(movies):
    idx = np.where(R[i, :] == 1)[0]
    Ymean[i] = Y[i, idx].mean()
    Ynorm[i, idx] = Y[i, idx] - Ymean[i]

fmin = minimize(fun=cost_func, x0=params, args=(Ynorm, R, features,
                learning_rate), method='CG', jac=True,
                options={'maxiter': 100, 'disp': True})

X = np.reshape(fmin.x[:movies * features], (movies, features))
Theta = np.reshape(fmin.x[movies * features:], (users, features))

predictions = X.dot(Theta.T)
my_preds = predictions[:, -1].reshape(Ymean.shape) + Ymean
sorted_preds = np.sort(my_preds, axis=0)[::-1]

idx = np.argsort(my_preds, axis=0)[::-1]
print('Top 10 movie predictions:')
for i in range(10):
    j = int(idx[i])
    print('Predicted rating of {0:.3f} for movie {1}.'.format(
        float(my_preds[j]), movie_idx[j]))

plt.show()
