#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-08-29 11:19
# Last modified: 2017-08-29 12:30
# Filename: main.py
# Description:
import numpy as np
from numpy.linalg import norm
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import seaborn as sns


M = 500
NUM_CLUSTERS = 3
SCALE = 10
ITERS = 20
COLORS = sns.color_palette('muted', NUM_CLUSTERS)


def gen_data_vanilla(m, scale=1):
    return np.random.random((m, 2)) * scale


def gen_data_clusters(num_clusters, scale_clusters, scale=1):
    data = np.zeros((0, 2))
    for _ in range(num_clusters):
        d = np.random.uniform(-scale/5, scale/5, (scale_clusters, 2))
        d += np.random.random((1, 2)) * SCALE
        data = np.append(data, d, axis=0)
    return data


data = gen_data_clusters(NUM_CLUSTERS, M // NUM_CLUSTERS, SCALE)


def closest_centroid_idx(x, centroids):
    min_idx = -1
    min_dist = 1e9
    for cur_idx, c in enumerate(centroids):
        cur_dist = norm(x-c)
        if cur_dist < min_dist:
            min_dist = cur_dist
            min_idx = cur_idx
    return min_idx


def kmeans(data, num_clusters, iters=1000, centroids=None):
    if centroids is not None:
        assert num_clusters == len(centroids)
    else:
        centroids = np.random.random((num_clusters, 2)) * SCALE
    clusters = [[] for _ in range(num_clusters)]
    failed = False
    for _ in range(iters):
        for cluster in clusters:
            cluster.clear()
        for x in data:
            idx = closest_centroid_idx(x, centroids)
            clusters[idx].append(x)
        for idx in range(num_clusters):
            if not clusters[idx]:
                failed = True
                continue
            centroids[idx, :] = np.mean(clusters[idx], axis=0)
        if failed:
            centroids = np.random.random((num_clusters, 2)) * SCALE
            failed = False
    return centroids, clusters


centroids = np.random.random((NUM_CLUSTERS, 2)) * SCALE

fig, ax = plt.subplots()


def animate(i):
    global centroids
    centroids, clusters = kmeans(data, NUM_CLUSTERS, iters=1,
                                 centroids=centroids)

    centroids = np.array(centroids)
    for idx, cluster in enumerate(clusters):
        cluster = np.array(cluster)
        if len(cluster) == 0:
            continue
        ax.scatter(cluster[:, 0], cluster[:, 1], s=30, c=COLORS[idx])
        ax.scatter(centroids[idx, 0], centroids[idx, 1], s=300,
                   c=COLORS[idx], marker='x')


anim = animation.FuncAnimation(fig, animate, np.arange(ITERS),
                               interval=500, repeat=False)
plt.show()
