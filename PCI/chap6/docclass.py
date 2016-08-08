#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-06 14:10
# Last modified: 2016-08-08 14:48
# Filename: docclass.py
# Description:
__metaclass__ = type
import re
import math
import sqlite3 as sqlite


def get_words(doc):
    splitter = re.compile(r'\W*')
    words = [s.lower() for s in splitter.split(doc)
             if len(s) > 2 and len(s) < 20]

    return {w: 1 for w in words}


def sample_train(cl):
    cl.train('Nobody owns the water.', 'good')
    cl.train('the quick rabbit jumps fences', 'good')
    cl.train('buy pharmaceuticals now', 'bad')
    cl.train('make quick money at the online casino', 'bad')
    cl.train('the quick brown fox jumps', 'good')


class Classifier:
    def __init__(self, get_features, filename=None):
        self.fc = {}
        self.cc = {}
        self.get_features = get_features

    def set_db(self, dbfile):
        self.con = sqlite.connect(dbfile)
        self.con.execute('create table if not exists fc(feature, category, count)')
        self.con.execute('create table if not exists cc(category, count)')

    def inc_f(self, f, cat):
        count = self.f_count(f, cat)
        if count == 0:
            self.con.execute("insert into fc values ('%s', '%s', 1)" %
                             (f, cat))
        else:
            self.con.execute("update fc set count=%d where feature='%s' \
                and category='%s'" % (count+1, f, cat))

    def inc_c(self, cat):
        count = self.c_count(cat)
        if count == 0:
            self.con.execute("insert into cc values ('%s',1)" % (cat))
        else:
            self.con.execute("update cc set count=%s where category='%s'" %
                             (count+1, cat))

    def f_count(self, f, cat):
        res = self.con.execute(
            "select count from fc where feature='%s' and category='%s'"
            % (f, cat)).fetchone()
        if not res:
            return 0
        else:
            return float(res[0])

    def c_count(self, cat):
        res = self.con.execute('select count from cc where category="%s"' %
                               (cat)).fetchone()
        if not res:
            return 0
        else:
            return float(res[0])

    def total_count(self):
        res = self.con.execute('select sum(count) from cc').fetchone()
        if not res:
            return 0
        else:
            return res[0]

    def categories(self):
        cur = self.con.execute('select category from cc')
        return [d[0] for d in cur]

    def train(self, item, cat):
        features = self.get_features(item)
        for f in features:
            self.inc_f(f, cat)
        self.inc_c(cat)
        self.con.commit()

    def f_prob(self, f, cat):
        if self.c_count(cat) == 0:
            return 0
        return self.f_count(f, cat)/self.c_count(cat)

    def weighted_prob(self, f, cat, prf, weight=1.0, ap=0.5):
        basic_prob = prf(f, cat)

        totals = sum([self.f_count(f, c) for c in self.categories()])

        bp = (weight*ap + totals*basic_prob)/(weight+totals)
        return bp


class NaiveBayesClassifier(Classifier):
    def __init__(self, get_features):
        super(NaiveBayesClassifier, self).__init__(get_features)
        self.thresholds = {}

    def doc_prob(self, item, cat):
        features = self.get_features(item)

        p = 1
        for f in features:
            p *= self.weighted_prob(f, cat, self.f_prob)
        return p

    def prob(self, item, cat):
        cat_prob = self.c_count(cat)/self.total_count()
        doc_prob = self.doc_prob(item, cat)
        return doc_prob*cat_prob

    def set_threshold(self, cat, t):
        self.thresholds[cat] = t

    def get_threshold(self, cat):
        return self.thresholds.get(cat, 1.0)

    def classify(self, item, default=None):
        probs = {}
        mmax = 0.0
        for cat in self.categories():
            probs[cat] = self.prob(item, cat)
            if probs[cat] > mmax:
                mmax = probs[cat]
                best = cat

        for cat in probs:
            if cat == best:
                continue
            if probs[cat]*self.get_threshold(best) > probs[best]:
                return default
        return best


class FisherClassifier(Classifier):
    def __init__(self, get_features):
        super(FisherClassifier, self).__init__(get_features)
        self.minimums = {}

    def c_prob(self, f, cat):
        clf = self.f_prob(f, cat)
        if clf == 0:
            return 0

        freq_sum = sum([self.f_prob(f, c) for c in self.categories()])

        p = clf/freq_sum

        return p

    def invchi2(self, chi, df):
        m = chi / 2.0
        sum = term = math.exp(-m)
        for i in range(1, df//2):
            term *= m / i
            sum += term
        return min(sum, 1.0)

    def fisher_prob(self, item, cat):
        p = 1
        features = self.get_features(item)
        for f in features:
            p *= self.weighted_prob(f, cat, self.c_prob)

        fscore = -2*math.log(p)

        return self.invchi2(fscore, len(features)*2)

    def set_minimum(self, cat, minimum):
        self.minimums[cat] = min

    def get_minimum(self, cat):
        return self.minimums.get(cat, 0)

    def classify(self, item, default=None):
        best = default
        maximum = 0.0
        for c in self.categories():
            p = self.fisher_prob(item, c)
            if p > self.get_minimum(c) and p > maximum:
                best = c
                maximum = p
        return best
