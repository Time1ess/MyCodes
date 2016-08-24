#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-19 14:07
# Last modified: 2016-08-24 16:54
# Filename: numpredict.py
# Description:
from random import random, randint
from pylab import *
import math


def wineprice(rating, age):
    peak_age = rating-50

    price = rating/2
    if age > peak_age:
        price *= (5-(age-peak_age))
    else:
        price *= (5*(age+1)/peak_age)
    if price < 0:
        price = 0
    return price


def wineset1():
    rows = []
    for i in xrange(300):
        rating = random()*50+50
        age = random()*50

        price = wineprice(rating, age)

        price *= (random()*0.4+0.8)
        rows.append({'input': (rating, age), 'result': price})
    return rows


def wineset2():
    rows = []
    for i in xrange(300):
        rating = random()*50+50
        age = random()*50
        aisle = float(randint(1, 20))
        bottlesize = [375.0, 750.0, 1500.0, 3000.0][randint(0, 3)]
        price = wineprice(rating, age)
        price *= (bottlesize/750)
        price *= (random()*0.9+0.2)
        rows.append({'input': (rating, age, aisle, bottlesize),
                     'result': price})
    return rows


def wineset3():
    rows = wineset1()
    for row in rows:
        if random() < 0.5:
            row['result'] *= 0.5
    return rows


def euclidean(v1, v2):
    d = 0.0
    for i in xrange(len(v1)):
        d += (v1[i]-v2[i])**2
    return math.sqrt(d)


def get_distances(data, vec1):
    distance_list = []
    for i in xrange(len(data)):
        vec2 = data[i]['input']
        distance_list.append((euclidean(vec1, vec2), i))
    distance_list.sort()
    return distance_list


def knn_estimate(data, vec1, k=5):
    d_list = get_distances(data, vec1)
    avg = 0.0

    for i in xrange(k):
        idx = d_list[i][1]
        avg += data[idx]['result']
    avg /= k
    return avg


def inverse_weight(dist, num=1.0, const=0.1):
    return num/(dist+const)


def subtract_weight(dist, const=1.0):
    if dist > const:
        return 0
    else:
        return const-dist


def gaussian(dist, sigma=10.0):
    return math.e**(-dist**2/(2*sigma**2))


def weighted_knn(data, vec1, k=5, weightf=gaussian):
    d_list = get_distances(data, vec1)
    avg = 0.0
    total_weight = 0.0

    for i in xrange(k):
        dist = d_list[i][0]
        idx = d_list[i][1]
        weight = weightf(dist)
        avg += weight*data[idx]['result']
        total_weight += weight
    avg /= total_weight
    return avg


def divided_data(data, test=0.05):
    train_set = []
    test_set = []
    for row in data:
        if random() < test:
            test_set.append(row)
        else:
            train_set.append(row)
    return train_set, test_set


def test_algorithm(algf, train_set, test_set):
    error = 0.0
    for row in test_set:
        guess = algf(train_set, row['input'])
        error += (row['result']-guess)**2
    return error/len(test_set)


def cross_validate(algf, data, trials=100, test=0.05):
    error = 0.0
    for i in xrange(trials):
        train_set, test_set = divided_data(data, test)
        error += test_algorithm(algf, train_set, test_set)
    return error/trials


def rescale(data, scale):
    scaled_data = []
    for row in data:
        scaled = [scale[i]*row['input'][i] for i in xrange(len(scale))]
        scaled_data.append({'input': scaled, 'result': row['result']})
    return scaled_data


def create_cost_function(algf, data):
    def costf(scale):
        sdata = rescale(data, scale)
        return cross_validate(algf, sdata, trials=10)
    return costf

weight_domain = [(0, 20)]*4


def prob_guess(data, vec1, low, high, k=5, weightf=gaussian):
    d_list = get_distances(data, vec1)
    n_weight = 0.0
    t_weight = 0.0

    for i in xrange(k):
        dist = d_list[i][0]
        idx = d_list[i][1]
        weight = weightf(dist)
        v = data[idx]['result']

        if v >= low and v <= high:
            n_weight += weight
        t_weight += weight

    if t_weight == 0:
        return 0
    return n_weight/t_weight


def cumulative_graph(data, vec1, high, k=5, weightf=gaussian):
    t1 = arange(0.0, high, 0.1)
    c_prob = array([prob_guess(data, vec1, 0, v, k, weightf) for v in t1])
    plot(t1, c_prob)
    show()


def probability_graph(data, vec1, high, k=5, weightf=gaussian, ss=5.0):
    t1 = arange(0.0, high, 0.1)

    probs = [prob_guess(data, vec1, v, v+0.1, k, weightf) for v in t1]

    smoothed = []
    for i in xrange(len(probs)):
        sv = 0.0
        for j in xrange(len(probs)):
            dis = abs(i-j)*0.1
            weight = gaussian(dis, sigma=ss)
            sv += weight*probs[j]
        smoothed.append(sv)
    smoothed = array(smoothed)

    plot(t1, smoothed)
    show()
