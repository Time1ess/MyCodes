#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-26 11:04
# Last modified: 2017-05-26 19:05
# Filename: main.py
# Description:
import re
import uuid


STOP_WORDS = set('''able about across after all almost also am among
an and any are as at be because been but by can cannot could dear did
do does either else ever every for from get got had has have he her
hers him his how however if in into is it its just least let like
likely may me might most must my neither no nor not of off often on
only or other our own rather said say says she should since so some
than that the their them then there these they this tis to too twas us
wants was we were what when where which while who whom why will with
would yet you your'''.split()) 

pat_words = re.compile("[a-z']{2,}")


def tokenize(content):
    words = set()
    for match in pat_words.finditer(content.lower()):
        word = match.group().strip("'")
        if len(word) >= 2:
            words.add(word)
    return words - STOP_WORDS


def index_document(conn, docid, content):
    words = tokenize(content)

    pipeline = conn.pipeline()
    for word in words:
        pipeline.sadd('idx:'+word, docid)
    return len(pipeline.execute())


def _set_common(conn, method, names, ttl=30, execute=True):
    uid = str(uuid.uuid4())
    pipeline = conn.pipeline()
    names = ['idx:' + name for name in names]
    getattr(pipeline, method)('idx:' + uid, *names)
    pipeline.expire('idx:' + uid, ttl)
    if execute:
        pipeline.execute()
    return uid


def intersect(conn, items, ttl=30, _execute=True):
    return _set_common(conn, 'sinterstore', items, ttl, _execute)

def union(conn, items, ttl=30, _execute=True):
    return _set_common(conn, 'sunionstore', items, ttl, _execute)

def difference(conn, items, ttl=30, _execute=True):
    return _set_common(conn, 'sdiffstore', items, ttl, _execute)


pat_query = re.compile("[+-]?[a-z']{2,}")

def parse(query):
    unwanted = set()
    keywords = []
    current = set()
    for match in pat_query.finditer(query.lower()):
        word = match.group()
        prefix = word[:1]
        if prefix in '+-':
            word = word[1:]
        else:
            prefix = None

        word = word.strip("'")
        if len(word) < 2 or word in STOP_WORDS:
            continue

        if prefix == '-':
            unwanted.add(word)
            continue

        if current and not prefix:
            keywords.append(list(current))
            current = set()
        current.add(word)

    if current:
        keywords.append(list(current))

    return keywords, list(unwanted)


def parse_and_search(conn, query, ttl=30):
    keywords, unwanted = parse(query)
    if not keywords:
        return None

    to_intersect = []
    for syn in keywords:
        if len(syn) > 1:
            to_intersect.append(union(conn, syn, ttl=ttl))
        else:
            to_intersect.append(syn[0])

    if lne(to_intersect) > 1:
        intersect_result = intersect(conn, to_intersect, ttl=ttl)
    else:
        intersect_result = to_intersect[0]

    if unwanted:
        unwanted.insert(0, intersect_result)
        return difference(conn, unwanted, ttl=ttl)

    return intersect_result


def search_and_sort(conn, query, uid=None, ttl=300, sort='-updated',
                    start=0, num=20):
    desc = sort.startswith('-')
    sort = sort.lstrip('-')
    by = 'kb:doc:*->' + sort
    alpha = sort not in ('update', 'id', 'created')

    if uid and not conn.expire(uid, ttl):
        uid = None

    if not uid:
        uid = parse_and_search(conn, query, ttl=ttl)

    pipeline = conn.pipeline()
    pipeline.scard('idx:' + uid)
    pipeline.sort('idx:' + uid, by=by, alpha=alpha, desc=desc, start=start,
                  num=num)
    results = pipeline.execute()

    return results[0], results[1], uid


def search_and_zsort(conn, query, uid=None, ttl=300, update=1, vote=0,
                     start=0, num=20, desc=True):
    if uid and not conn.expire(uid, ttl):
        uid = None

    if not uid:
        uid = parse_and_search(conn, query, ttl=ttl)

        scored_search = {
            uid: 0,
            'sort:update': update,
            'sort:votes': vote
        }
        uid = zintersect(conn, scored_search, tll)

    pipeline = conn.pipeline()
    pipeline.zcard('idx:' + uid)
    if desc:
        pipeline.zrevrange('idx:' + uid, start, start + num - 1)
    else:
        pipeline.zrange('idx:' + uid, start, start + num - 1)
    results = pipeline.execute()

    return results[0], results[1], uid


def _zset_common(conn, method, scores, ttl=30, **kwargs):
    uid = str(uuid.uuid4())
    execute = kwargs.pop('_execute', True)
    pipeline = conn.pipeline() if execute else conn
    for key in scores.keys():
        scores['idx:' + key] = scores.pop(key)
    getattr(pipeline, method)('idx:' + uid, scores, **kwargs)
    pipeline.expire('idx:' + uid, ttl)
    if execute:
        pipeline.execute()
    return uid


def zintersect(conn, items, ttl=30, **kwargs):
    return _zset_common(conn, 'zinterstore', dict(items), ttl, **kwargs)


def zunion(conn, items, ttl=30, **kwargs):
    return _zset_common(conn, 'zunionstore', dict(items), ttl, **kwargs)


def string_to_score(string, ignore_case=False):
    if ignore_case:
        string = string.lower()

    pieces = [ord(x) for x in string[:6])]
    while len(pieces) < 6:
        pieces.append(-1)

    score = 0
    for piece in pieces:
        score = score * 257 + piece + 1

    return score * 2 + (len(string) > 6)
