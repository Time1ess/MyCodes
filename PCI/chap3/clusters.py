#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-07-28 13:39
# Last modified: 2016-07-30 15:06
# Filename: clusters.py
# Description:
from math import sqrt
from PIL import Image, ImageDraw
import random


def readfile(filename):
    lines = [line for line in open(filename)]

    colnames = lines[0].strip().split('\t')[1:]
    rownames = []
    data = []
    for line in lines[1:]:
        p = line.strip().split('\t')
        rownames.append(p[0])
        data.append([float(x) for x in p[1:]])
    return rownames, colnames, data


def pearson_score(v1, v2):
    sum1 = sum(v1)
    sum2 = sum(v2)

    power_sum1 = sum([pow(elem, 2) for elem in v1])
    power_sum2 = sum([pow(elem, 2) for elem in v2])

    power_sum = sum([v1[i]*v2[i] for i in xrange(len(v1))])

    n = len(v1)

    num = power_sum*n - sum1*sum2
    den = sqrt((power_sum1*n - pow(sum1, 2))*(power_sum2*n - pow(sum2, 2)))

    if den == 0:
        return 0
    return 1.0 - num/den


class bicluster:
    def __init__(self, vec, left=None, right=None, distance=0.0, iid=None):
        self.left = left
        self.right = right
        self.vec = vec
        self.iid = iid
        self.distance = distance


def hcluster(rows, distance=pearson_score):
    distances = {}
    current_clust_id = -1

    # At beginning, cluster will be all rows
    clust = [bicluster(rows[i], iid=i) for i in xrange(len(rows))]

    while len(clust) > 1:
        lowestpair = (0, 1)
        closest = distance(clust[0].vec, clust[1].vec)

        # loop through every pair looking for the smallest distance
        for i in xrange(len(clust)):
            for j in xrange(i+1, len(clust)):
                if(clust[i].iid, clust[j].iid) not in distances:
                    distances[(clust[i].iid, clust[j].iid)] = \
                        distance(clust[i].vec, clust[j].vec)

                d = distances[(clust[i].iid, clust[j].iid)]

                if d < closest:
                    closest = d
                    lowestpair = (i, j)

        # Calculate the avg value between two clusters
        mergevec = [
            (clust[lowestpair[0]].vec[i]+clust[lowestpair[1]].vec[i])/2.0
            for i in xrange(len(clust[0].vec))]

        newcluster = bicluster(mergevec, left=clust[lowestpair[0]],
                               right=clust[lowestpair[1]], distance=closest,
                               iid=current_clust_id)
        current_clust_id -= 1
        del clust[lowestpair[1]]
        del clust[lowestpair[0]]
        clust.append(newcluster)

    return clust[0]


def print_clust(clust, labels=None, n=0):
    for i in xrange(n):
        print ' ',
    if clust.iid < 0:
        print '-'
    else:
        if labels is None:
            print clust.iid
        else:
            print labels[clust.iid]

    if clust.left is not None:
        print_clust(clust.left, labels=labels, n=n+1)
    if clust.right is not None:
        print_clust(clust.right, labels=labels, n=n+1)


def get_height(clust):
    if clust.left is None and clust.right is None:
        return 1
    return get_height(clust.left)+get_height(clust.right)


def get_depth(clust):
    if clust.left is None and clust.right is None:
        return 0
    return max(get_depth(clust.left), get_depth(clust.right))+clust.distance


def draw_node(draw, clust, x, y, scaling, labels):
    if clust.iid < 0:
        h1 = get_height(clust.left)*20
        h2 = get_height(clust.right)*20
        top = y - (h1+h2)/2
        bottom = y + (h1+h2)/2

        ll = clust.distance*scaling

        draw.line((x, top + h1/2, x, bottom - h2/2), fill=(255, 0, 0))

        draw.line((x, top + h1/2, x+ll, top + h1/2), fill=(255, 0, 0))

        draw.line((x, bottom - h2/2, x+ll, bottom - h2/2), fill=(255, 0, 0))

        draw_node(draw, clust.left, x+ll, top + h1/2, scaling, labels)
        draw_node(draw, clust.right, x+ll, bottom - h2/2, scaling, labels)
    else:
        draw.text((x+5, y-7), labels[clust.iid], (0, 0, 0))


def draw_dendrogram(clust, labels, jpeg='clusters.jpg'):
    h = get_height(clust)*20
    w = 1200
    depth = get_depth(clust)

    scaling = float(w-150)/depth

    img = Image.new('RGB', (w, h), (255, 255, 255))
    draw = ImageDraw.Draw(img)
    draw.line((0, h/2, 10, h/2), fill=(255, 0, 0))

    draw_node(draw, clust, 10, h/2, scaling, labels)
    img.save(jpeg, 'JPEG')


def rotate_matrix(data):
    newdata = []
    for i in xrange(len(data[0])):
        newrow = [data[j][i] for j in xrange(len(data))]
        newdata.append(newrow)
    return newdata


def kcluster(rows, distance=pearson_score, k=4, iter_times=100):
    # Determine the minimum and maximum values for each point
    ranges = [(min([row[i] for row in rows]), max([row[i] for row in rows]))
              for i in xrange(len(rows[0]))]

    # Create k randomly placed centroids
    clusters = [[random.random()*(ranges[i][1]-ranges[i][0])+ranges[i][0]
                 for i in xrange(len(rows[0]))] for j in xrange(k)]

    last_matches = None
    for t in xrange(iter_times):
        print 'Iteration %d' % t
        best_matches = [[] for i in xrange(k)]

        # Find which centroid is the closest for each row
        for j, row in enumerate(rows):
            best_match = 0
            for i, centroid in enumerate(clusters):
                d = distance(centroid, row)
                if d < distance(clusters[best_match], row):
                    best_match = i
            best_matches[best_match].append(j)

        # If the results are the same as last time, it's complete
        if best_matches == last_matches:
            break
        last_matches = best_matches

        # Move the centroids to the average of their members
        for i in xrange(k):
            avgs = [0.0]*len(rows[0])
            if len(best_matches[i]) > 0:
                for row_id in best_matches[i]:
                    for m in xrange(len(rows[row_id])):
                        avgs[m] += rows[row_id][m]
                for j in xrange(len(avgs)):
                    avgs[j] /= len(best_matches[i])
                clusters[i] = avgs

    return best_matches


def tanimoto_score(v1, v2):
    c1, c2, shr = 0, 0, 0

    for i in xrange(len(v1)):
        if v1[i] != 0:
            c1 += 1
        if v2[i] != 0:
            c2 += 1
        if v1[i] != 0 and v2[i] != 0:
            shr += 1
    return 1.0 - float(shr)/(c1+c2-shr)


def scaledown(data, distance=pearson_score, rate=0.01):
    n = len(data)

    real_dist = [[distance(data[i], data[j]) for j in xrange(n)]
                 for i in xrange(n)]

    loc = [[random.random(), random.random()] for i in xrange(n)]
    fake_dist = [[0.0 for j in xrange(n)] for i in xrange(n)]

    last_error = None
    for m in xrange(1000):
        for i in xrange(n):
            for j in xrange(n):
                fake_dist[i][j] = sqrt(sum([pow(loc[i][x]-loc[j][x], 2)
                                            for x in xrange(len(loc[i]))]))
        grad = [[0.0, 0.0] for i in xrange(n)]

        total_error = 0
        for k in xrange(n):
            for j in xrange(n):
                if j == k:
                    continue
                error_term = (fake_dist[j][k]-real_dist[j][k])/real_dist[j][k]

                grad[k][0] += ((loc[k][0]-loc[j][0])/fake_dist[j][k]) * \
                    error_term
                grad[k][1] += ((loc[k][1]-loc[j][1])/fake_dist[j][k]) * \
                    error_term

                total_error += abs(error_term)
        print total_error

        if last_error and last_error < total_error:
            break
        last_error = total_error

        for k in xrange(n):
            loc[k][0] -= rate*grad[k][0]
            loc[k][1] -= rate*grad[k][1]

    return loc

def draw_2d(data, labels, jpeg='mds2d.jpg'):
    img = Image.new('RGB', (2000, 2000), (255, 255, 255))
    draw = ImageDraw.Draw(img)
    for i in xrange(len(data)):
        x = (data[i][0]+0.5)*1000
        y = (data[i][1]+0.5)*1000
        draw.text((x, y), labels[i], (0, 0, 0))
    img.save(jpeg, 'JPEG')
