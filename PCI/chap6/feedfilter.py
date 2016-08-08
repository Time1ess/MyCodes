#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-08 14:50
# Last modified: 2016-08-08 15:24
# Filename: feedfilter.py
# Description:
import feedparser
import re


def read(feed, classifier):
    f = feedparser.parse(feed)
    for entry in f['entries']:
        print
        print '-----'
        print 'Title:    '+entry['title'].encode('utf-8')
        print 'Publisher: '+entry['publisher'].encode('utf-8')
        print
        print entry['summary'].encode('utf-8')

        full_text = '%s\n%s\n%s' % \
            (entry['title'], entry['publisher'], entry['summary'])
        print 'Guess: '+str(classifier.classify(entry))

        cl = raw_input('Enter category: ')
        classifier.train(entry, cl)


def entry_features(entry):
    splitter = re.compile(r'\W*')
    f = {}

    title_words = [s.lower() for s in splitter.split(entry['title'])
                   if len(s) > 2 and len(s) < 20]
    for w in title_words:
        f['Title:'+w] = 1

    summary_words = [s.lower() for s in splitter.split(entry['summary'])
                     if len(s) > 2 and len(s) < 20]

    uc = 0
    for i in xrange(len(summary_words)):
        w = summary_words[i]
        f[w] = 1
        if w.isupper():
            uc += 1

        if i < len(summary_words)-1:
            two_words = ' '.join(summary_words[i:i+1])
            f[two_words] = 1

    f['Publisher:'+entry['publisher']] = 1

    if float(uc)/len(summary_words) > 0.3:
        f['UPPERCASE'] = 1
    return f
