#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-29 18:41
# Last modified: 2017-03-29 19:39
# Filename: web.py
# Description:
import random

import redis
from flask import Flask, render_template, request
from flask import redirect, url_for, abort

from articles import article_vote, article_downvote, post_article
from articles import get_articles, add_remove_groups, get_group_articles


app = Flask('Article Voting')
conn = redis.Redis(decode_responses=True)

words = ['python', 'cpp', 'java', 'hello', 'redis']
users = ['david', 'sam', 'alice']

@app.route('/')
def index():
    return render_template('base.html')


@app.route('/articles')
def article_list():
    articles = get_articles(conn, 1)
    return render_template('articles.html', articles=articles)

@app.route('/post/article', methods=['POST', 'GET'])
def new_article():
    if request.method == 'GET':
        return render_template('new_article.html')
    elif request.method == 'POST':
        form = request.form
        post_article(conn, form['poster'], form['title'], form['link'])
        return redirect(url_for('article_list'))


@app.route('/articles/action')
def action_on_acticle():
    action = request.args.get('action', '')
    article = request.args.get('article', '')
    user = 'steve'
    if action == 'vote':
        article_vote(conn, steve, article)
    elif action == 'downvote':
        article_downvote(conn, steve, article)
    else:
        abort(404)
    return redirect(url_for('article_list'))


def init_redis_data():
    for _ in range(3):
        title = ' '.join(random.sample(words, 2))
        user = random.choice(users)
        post_article(conn, user, title, '')


if __name__ == '__main__':
    init_redis_data()
    app.run()
