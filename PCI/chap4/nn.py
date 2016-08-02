#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-02 13:59
# Last modified: 2016-08-02 16:01
# Filename: nn.py
# Description:
from math import tanh
import MySQLdb


def dtanh(y):
    return 1.0 - y*y


class searchnet:
    def __init__(self, db='PCI', host='localhost', user='root', passwd='root',
                 port=3306):
        self.con = MySQLdb.connect(host=host, user=user, passwd=passwd,
                                   port=port, db=db)
        self.cur = self.con.cursor()

    def __del__(self):
        self.con.close()

    def dbcommit(self):
        self.con.commit()

    def make_tables(self):
        self.cur.execute('create table hiddennode(id integer primary key \
            auto_increment, create_key char(50))')
        self.cur.execute('create table wordhidden(id integer primary key \
            auto_increment, fromid integer, toid integer, strength float)')
        self.cur.execute('create table hiddenurl(id integer primary key \
            auto_increment, fromid integer, toid integer, strength float)')
    
    def drop_tables(self):
        self.cur.execute('drop table if exists hiddennode')
        self.cur.execute('drop table if exists wordhidden')
        self.cur.execute('drop table if exists hiddenurl')
        self.dbcommit()

    def get_strength(self, from_id, to_id, layer):
        if layer == 0:
            table = 'wordhidden'
        else:
            table = 'hiddenurl'

        self.cur.execute('select strength from %s where fromid=%d and \
            toid=%d' % (table, from_id, to_id))
        res = self.cur.fetchone()
        if not res:
            return -0.2 if layer == 0 else 0
        return res[0]

    def set_strength(self, from_id, to_id, layer, strength):
        if layer == 0:
            table = 'wordhidden'
        else:
            table = 'hiddenurl'
        self.cur.execute('select id from %s where fromid=%d and \
            toid=%d' % (table, from_id, to_id))
        res = self.cur.fetchone()
        if not res:
            self.cur.execute('insert into %s (fromid,toid,strength) values \
                (%d,%d,%f)' % (table, from_id, to_id, strength))
        else:
            iid = res[0]
            self.cur.execute('update %s set strength=%f where id=%d' %
                             (table, strength, iid))

    def generate_hiddennode(self, word_ids, urls):
        if len(word_ids) > 3:
            return None
        create_key = '_'.join(sorted([str(wi) for wi in word_ids]))
        self.cur.execute("select id from hiddennode where create_key='%s'" %
                         create_key)
        res = self.cur.fetchone()

        if not res:
            self.cur.execute("insert into hiddennode (create_key) values \
                ('%s')" % create_key)
            hidden_id = self.cur.lastrowid
            for word_id in word_ids:
                self.set_strength(word_id, hidden_id, 0, 1.0/len(word_ids))
            for url_id in urls:
                self.set_strength(hidden_id, url_id, 1, 0.1)
            self.dbcommit()

    def get_all_hidden_ids(self, word_ids, url_ids):
        ll = {}
        for word_id in word_ids:
            self.cur.execute('select toid from wordhidden where fromid=%d' %
                             word_id)
            for row, in self.cur.fetchall():
                ll[row] = 1
        for url_id in url_ids:
            self.cur.execute('select fromid from hiddenurl where toid=%d' %
                             url_id)
            for row, in self.cur.fetchall():
                ll[row] = 1
        return ll.keys()

    def setup_network(self, word_ids, url_ids):
        self.word_ids = word_ids
        self.hidden_ids = self.get_all_hidden_ids(word_ids, url_ids)
        self.url_ids = url_ids

        self.ai = [1.0]*len(self.word_ids)
        self.ah = [1.0]*len(self.hidden_ids)
        self.ao = [1.0]*len(self.url_ids)

        self.wi = [[self.get_strength(word_id, hidden_id, 0)
                    for hidden_id in self.hidden_ids]
                   for word_id in self.word_ids]
        self.wo = [[self.get_strength(hidden_id, url_id, 1)
                    for url_id in self.url_ids]
                   for hidden_id in self.hidden_ids]

    def feed_forward(self):
        for i in xrange(len(self.word_ids)):
            self.ai[i] = 1.0

        for j in xrange(len(self.hidden_ids)):
            total = 0.0
            for i in xrange(len(self.word_ids)):
                total += self.ai[i]*self.wi[i][j]
            self.ah[j] = tanh(total)

        for k in xrange(len(self.url_ids)):
            total = 0.0
            for j in xrange(len(self.hidden_ids)):
                total += self.ah[j] * self.wo[j][k]
            self.ao[k] = tanh(total)

        return self.ao[:]

    def get_result(self, word_ids, url_ids):
        self.setup_network(word_ids, url_ids)
        return self.feed_forward()

    def back_propagate(self, targets, N=0.5):
        # Errors in output layer
        output_deltas = [0.0]*len(self.url_ids)
        for k in xrange(len(self.url_ids)):
            error = targets[k]-self.ao[k]
            output_deltas[k] = dtanh(self.ao[k])*error

        # Errors in hidden layer
        hidden_deltas = [0.0]*len(self.hidden_ids)
        for j in xrange(len(self.hidden_ids)):
            error = 0.0
            for k in xrange(len(self.url_ids)):
                error += output_deltas[k]*self.wo[j][k]
            hidden_deltas[j] = dtanh(self.ah[j])*error

        # Update output weights
        for j in xrange(len(self.hidden_ids)):
            for k in xrange(len(self.url_ids)):
                change = output_deltas[k]*self.ah[j]
                self.wo[j][k] += N*change

        # Update input weights
        for i in xrange(len(self.word_ids)):
            for j in xrange(len(self.hidden_ids)):
                change = hidden_deltas[j]*self.ai[i]
                self.wi[i][j] += N*change

    def update_database(self):
        for i, word_id in enumerate(self.word_ids):
            for j, hidden_id in enumerate(self.hidden_ids):
                self.set_strength(word_id, hidden_id, 0, self.wi[i][j])
        for j, hidden_id in enumerate(self.hidden_ids):
            for k, url_id in enumerate(self.url_ids):
                self.set_strength(hidden_id, url_id, 1, self.wo[j][k])
        self.dbcommit()

    def train_query(self, word_ids, url_ids, selected_url):
        self.generate_hiddennode(word_ids, url_ids)

        self.setup_network(word_ids, url_ids)
        self.feed_forward()
        targets = [0.0]*len(url_ids)
        targets[url_ids.index(selected_url)] = 1.0
        self.back_propagate(targets)
        self.update_database()
