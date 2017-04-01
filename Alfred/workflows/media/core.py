#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-04-01 08:40
# Last modified: 2017-04-01 10:24
# Filename: core.py
# Description:
import subprocess
import string
import jieba
jieba.initialize()


def similarity(query):
    q_keywords = set(jieba.cut(query))
    def _wrapper(keywords):
        same_elements = len(q_keywords & keywords)
        all_elements = len(q_keywords)
        return same_elements / all_elements
    return _wrapper

def clean_movies():
    ret = subprocess.check_output(['/usr/local/bin/fab', '-f', 'fab_file.py',
                                   'fetch_movie_info'])
    data = ret.decode('utf-8').split('\n')[1:-4]
    movies = []
    for d in data:
        *path, fname = d.rsplit('/', 1)
        path = path[0] if path else ''
        keywords = set(jieba.cut(fname))
        movies.append([fname, d, keywords])
    return movies


if __name__ == '__main__':
    print(clean_movies())
