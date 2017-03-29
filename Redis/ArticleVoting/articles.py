#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-29 17:14
# Last modified: 2017-03-29 19:39
# Filename: articles.py
# Description:
import time


ONE_DAY_IN_SECONDS = 86400
ONE_WEEK_IN_SECONDS = 7 * ONE_DAY_IN_SECONDS
VOTE_SCORE = 432
ARTICLES_PER_PAGE = 25


def article_vote_or_downvote(conn, user, article, vote_type='VOTE'):
    cutoff = time.time() - ONE_WEEK_IN_SECONDS
    if conn.zscore('time:', article) < cutoff:
        return

    article_id = article.partition(':')[-1]
    if vote_type == 'VOTE':
        if conn.srem('downvoted:' + article_id, user):
            conn.zincrby('score:', article, VOTE_SCORE)
            conn.hincrby(article, 'downvotes', -1)
        if conn.sadd('voted:' + article_id, user):
            conn.zincrby('score:', article, VOTE_SCORE)
            conn.hincrby(article, 'votes', 1)
    elif vote_type == 'DOWNVOTE':
        if conn.srem('voted:' + article_id, user):
            conn.zincrby('score:', article, -VOTE_SCORE)
            conn.hincrby(article, 'votes', -1)
        if conn.sadd('downvoted:' + article_id, user):
            conn.zincrby('score:', article, -VOTE_SCORE)
            conn.hincrby(article, 'downvotes', 1)
    else:
        raise TypeError('Wrong voting type')


def article_vote(conn, user, article):
    article_vote_or_downvote(conn, user, article)


def article_downvote(conn, user, article):
    article_vote_or_downvote(conn, user, article, 'DOWNVOTE')


def post_article(conn, user, title, link):
    article_id = str(conn.incr('article:'))

    voted = 'voted:' + article_id
    conn.sadd(voted, user)
    conn.expire(voted, ONE_WEEK_IN_SECONDS)

    now = time.time()
    article = 'article:' + article_id
    conn.hmset(article, {
        'title': title,
        'link': link,
        'poster': user,
        'time': now,
        'votes': 1,
        'downvotes': 0,
    })

    conn.zadd('score:', article, now + VOTE_SCORE)
    conn.zadd('time:', article, now)

    return article_id


def get_articles(conn, page, order='score:'):
    start = (page-1) * ARTICLES_PER_PAGE
    end = start + ARTICLES_PER_PAGE - 1

    ids = conn.zrevrange(order, start, end)
    articles = []
    for id in ids:
        article_data = conn.hgetall(id)
        article_data['id'] = id
        articles.append(article_data)
    return articles


def add_remove_groups(conn, article_id, to_add=[], to_remove=[]):
    article = 'article:' + article_id
    for group in to_add:
        conn.sadd('group:' + group, article)
    for group in to_remove:
        conn.srem('group:' + group, article)


def get_group_articles(conn, group, page, order='score:'):
    key = order + group
    if not conn.exists(key):
        conn.zinterstore(key, ['group:' + group, order], aggregate='max')
        conn.expire(key, 60)
    return get_articles(conn, page, key)
