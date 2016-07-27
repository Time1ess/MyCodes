#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-07-27 14:10
# Last modified: 2016-07-27 19:23
# Filename: recommendations.py
# Description:
critics = {
    'Lisa Rose': {
        'Lady in the Water': 2.5,
        'Snakes on a Plane': 3.5,
        'Just My Luck': 3.0,
        'Superman Returns': 3.5,
        'You, Me and Dupree': 2.5,
        'The Night Listener': 3.0},
    'Gene Seymour': {
        'Lady in the Water': 3.0,
        'Snakes on a Plane': 3.5,
        'Just My Luck': 1.5,
        'Superman Returns': 5.0,
        'The Night Listener': 3.0,
        'You, Me and Dupree': 3.5},
    'Michael Phillips': {
        'Lady in the Water': 2.5,
        'Snakes on a Plane': 3.0,
        'Superman Returns': 3.5,
        'The Night Listener': 4.0},
    'Claudia Puig': {
        'Snakes on a Plane': 3.5,
        'Just My Luck': 3.0,
        'The Night Listener': 4.5,
        'Superman Returns': 4.0,
        'You, Me and Dupree': 2.5},
    'Mick LaSalle': {
        'Lady in the Water': 3.0,
        'Snakes on a Plane': 4.0,
        'Just My Luck': 2.0,
        'Superman Returns': 3.0,
        'The Night Listener': 3.0,
        'You, Me and Dupree': 2.0},
    'Jack Matthews': {
        'Lady in the Water': 3.0,
        'Snakes on a Plane': 4.0,
        'The Night Listener': 3.0,
        'Superman Returns': 5.0,
        'You, Me and Dupree': 3.5},
    'Toby': {
        'Snakes on a Plane': 4.5,
        'You, Me and Dupree': 1.0,
        'Superman Returns': 4.0}
}

from math import sqrt


def sim_distance(prefs, person1, person2):
    si = {}
    for item in prefs[person1]:
        if item in prefs[person2]:
            si[item] = 1
    if not si:
        return 0

    sum_of_squares = sum([pow(prefs[person1][item]-prefs[person2][item], 2)
                          for item in si])
    return 1/(1+sqrt(sum_of_squares))


def sim_pearson(prefs, person1, person2):
    si = {}
    for item in prefs[person1]:
        if item in prefs[person2]:
            si[item] = 1
    if not si:
        return 0

    n = len(si)

    sum1 = sum([prefs[person1][item] for item in si])
    sum2 = sum([prefs[person2][item] for item in si])

    power_sum1 = sum([pow(prefs[person1][item], 2) for item in si])
    power_sum2 = sum([pow(prefs[person2][item], 2) for item in si])

    p_sum = sum([prefs[person1][item]*prefs[person2][item] for item in si])

    # Pearson Coeerlation Score
    num = n*p_sum - sum1*sum2
    den = sqrt((n*power_sum1 - pow(sum1, 2))*(n*power_sum2 - pow(sum2, 2)))
    if den == 0:
        return 0
    r = num/den
    return r


def top_match(prefs, person, n=5, similarity=sim_pearson):
    scores = [(similarity(prefs, person, other), other)
              for other in prefs if person != other]

    scores.sort(reverse=True)
    return scores[0:n]


def get_recommendations(prefs, person, similarity=sim_pearson):
    totals = {}
    sim_sums = {}
    for other in prefs:
        if other == person:
            continue
        sim = similarity(prefs, person, other)
        if sim <= 0:
            continue
        for item in prefs[other]:
            if item not in prefs[person] or prefs[person][item] == 0:
                totals.setdefault(item, 0)
                totals[item] += prefs[other][item]*sim
                sim_sums.setdefault(item, 0)
                sim_sums[item] += sim

    rankings = [(total/sim_sums[item], item) for item, total in totals.items()]

    rankings.sort(reverse=True)
    return rankings


def transform_prefs(prefs):
    result = {}
    for person in prefs:
        for item in prefs[person]:
            result.setdefault(item, {})
            result[item][person] = prefs[person][item]
    return result


def calculate_similar_items(prefs, n=10):
    result = {}

    item_prefs = transform_prefs(prefs)
    c = 0
    for item in item_prefs:
        c += 1
        if c % 100 == 0:
            print '%d / %d' % (c, len(item_prefs))
        scores = top_match(item_prefs, item, n=n, similarity=sim_distance)
        result[item] = scores
    return result


def get_recommended_items(prefs, item_match, user):
    user_ratings = prefs[user]
    scores = {}
    total_sim = {}

    for item, rating in user_ratings.items():
        for similarity, item2 in item_match[item]:
            if item2 in user_ratings:
                continue

            scores.setdefault(item2, 0)
            scores[item2] += similarity*rating

            total_sim.setdefault(item2, 0)
            total_sim[item2] += similarity

    rankings = [(score/total_sim[item], item) for item, score in scores.items()]
    rankings.sort(reverse=True)
    return rankings


def load_movie_lens(path='./movielens'):

    movies = {}
    with open(path+'/u.item', 'r') as f:
        for line in f:
            movie_id, title = line.split('|')[:2]
            movies[movie_id] = title

    prefs = {}
    with open(path+'/u.data', 'r') as f:
        for line in f:
            user, movie_id, rating, ts = line.split('\t')
            prefs.setdefault(user, {})
            prefs[user][movies[movie_id]] = float(rating)

    return prefs
