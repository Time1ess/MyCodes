#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-07-30 15:25
# Last modified: 2016-08-02 16:06
# Filename: searchengine.py
# Description:
import urllib2
from BeautifulSoup import *
from urlparse import urljoin
import MySQLdb
import re
import nn

ignore_words = set(['the', 'of', 'to', 'and', 'a', 'in', 'is', 'it'])
mynet = nn.searchnet()


class crawler:
    def __init__(self, db='PCI', host='localhost', user='root', passwd='root',
                 port=3306):
        self.con = MySQLdb.connect(host=host, user=user, passwd=passwd,
                                   port=port, db=db)
        self.cur = self.con.cursor()

    def __del__(self):
        self.con.close()

    def dbcommit(self):
        self.con.commit()

    def get_entry_id(self, table, field, value, create_new=True):
        lookup = "select id from %s where %s='%s'" % (table, field, value)
        insert = "insert into %s (%s) values ('%s')" % (table, field, value)
        res = self.cur.execute(lookup)
        if not res:
            self.cur.execute(insert)
            return self.cur.lastrowid
        else:
            res = self.cur.fetchone()
            return res[0]

    def add_to_index(self, url, soup):
        if self.is_indexed(url):
            return
        print 'Indexing %s' % url

        text = self.get_text_only(soup)
        words = self.separate_words(text)

        urlid = self.get_entry_id('urllist', 'url', url)

        for i in xrange(len(words)):
            word = words[i]
            if word in ignore_words:
                continue
            wordid = self.get_entry_id('wordlist', 'word', word)
            self.cur.execute('insert into wordlocation(urlid,wordid,location) \
                    values (%d,%d,%d)' % (urlid, wordid, i))

    def get_text_only(self, soup):
        v = soup.string
        if v is None:
            c = soup.contents
            result_text = ''
            for t in c:
                subtext = self.get_text_only(t)
                result_text += subtext+'\n'
            return result_text
        else:
            return v.strip()

    def separate_words(self, text):
        splitter = re.compile('\\W*')
        return [s.lower() for s in splitter.split(text) if s != '']

    def is_indexed(self, url):
        u = self.cur.execute("select id from urllist where url='%s'" %
                             url)
        if u:
            u = self.cur.fetchone()
            v = self.cur.execute('select * from wordlocation where urlid=%d' %
                                 u[0])
            if v:
                return True
        return False

    def add_link_ref(self, url_from, url_to, link_text):
        words = self.separate_words(link_text)
        from_id = self.get_entry_id('urllist', 'url', url_from)
        to_id = self.get_entry_id('urllist', 'url', url_to)
        if from_id == to_id:
            return
        self.cur.execute("insert into link(fromid,toid) values(%d,%d)" %
                         (from_id, to_id))
        link_id = self.cur.lastrowid
        for word in words:
            if word in ignore_words:
                continue
            word_id = self.get_entry_id('wordlist', 'word', word)
            self.cur.execute("insert into linkwords(linkid,wordid) values \
                    (%d,%d)" % (link_id, word_id))

    def crawl(self, pages, depth=2):
        for i in xrange(depth):
            newpages = set()
            for page in pages:
                try:
                    c = urllib2.urlopen(page)
                except:
                    print 'Could not open %s' % page
                    continue
                soup = BeautifulSoup(c.read())
                self.add_to_index(page, soup)

                links = soup('a')
                for link in links:
                    if 'href' in dict(link.attrs):
                        url = urljoin(page, link['href'])
                        if url.find("'") != -1:
                            continue
                        url = url.split('#')[0]
                        if url[0:4] == 'http' and not self.is_indexed(url):
                            newpages.add(url)
                        link_text = self.get_text_only(link)
                        self.add_link_ref(page, url, link_text)
                self.dbcommit()
            pages = newpages

    def create_index_tables(self):
        self.cur.execute('create table urllist(id integer primary key \
                auto_increment, url char(150))')
        self.cur.execute('create table wordlist(id integer primary key \
                auto_increment, word char(50))')
        self.cur.execute('create table wordlocation(id integer primary key \
                auto_increment, urlid integer, wordid integer, \
                location integer)')
        self.cur.execute('create table link(id integer primary key \
                auto_increment, fromid integer, toid integer)')
        self.cur.execute('create table linkwords(id integer primary key \
                auto_increment, wordid integer, linkid integer)')
        self.cur.execute('create index wordidx on wordlist(word)')
        self.cur.execute('create index urlidx on urllist(url)')
        self.cur.execute('create index wordurlidx on wordlocation(wordid)')
        self.cur.execute('create index urltoidx on link(toid)')
        self.cur.execute('create index urlfromidx on link(fromid)')
        self.dbcommit()

    def delete_index_tables(self):
        self.cur.execute('drop table urllist')
        self.cur.execute('drop table wordlist')
        self.cur.execute('drop table wordlocation')
        self.cur.execute('drop table link')
        self.cur.execute('drop table linkwords')

    def calculate_PageRank(self, iterations=20):
        self.cur.execute('drop table if exists pagerank')
        self.cur.execute('create table pagerank(urlid int primary key,\
            score float)')

        self.cur.execute('insert into pagerank select id, 1.0 from urllist')
        self.dbcommit()

        for i in xrange(iterations):
            print 'Iteration %d' % (i)
            self.cur.execute('select id from urllist')
            url_ids = self.cur.fetchall()
            for url_id, in url_ids:
                pr = 0.15

                self.cur.execute('select distinct fromid from link where \
                    toid=%d' % url_id)
                linkers = self.cur.fetchall()
                for linker in linkers:
                    self.cur.execute('select score from pagerank where \
                        urlid=%d' % linker)
                    linking_pr = self.cur.fetchone()[0]

                    self.cur.execute('select count(*) from link where \
                            fromid=%d' % linker)
                    linking_count = self.cur.fetchone()[0]
                    pr += 0.85*(linking_pr/linking_count)
                self.cur.execute('update pagerank set score=%f where \
                        urlid=%d' % (pr, url_id))

            self.dbcommit()


class searcher:
    def __init__(self, db='PCI', host='localhost', user='root', passwd='root',
                 port=3306):
        self.con = MySQLdb.connect(host=host, user=user, passwd=passwd,
                                   port=port, db=db)
        self.cur = self.con.cursor()

    def __del__(self):
        self.con.close()

    def get_match_rows(self, q):
        field_list = 'w0.urlid'
        table_list = ''
        clause_list = ''
        word_ids = []

        words = q.split(' ')
        table_number = 0

        for word in words:
            self.cur.execute("select id from wordlist where word='%s'" % word)
            word_row = self.cur.fetchone()
            if word_row:
                word_id = word_row[0]
                word_ids.append(word_id)
                if table_number > 0:
                    table_list += ','
                    clause_list += ' and '
                    clause_list += 'w%d.urlid=w%d.urlid and ' %\
                        (table_number-1, table_number)
                field_list += ',w%d.location' % table_number
                table_list += 'wordlocation w%d' % table_number
                clause_list += 'w%d.wordid=%d' % (table_number, word_id)
                table_number += 1

        full_query = 'select %s from %s where %s' %\
            (field_list, table_list, clause_list)
        self.cur.execute(full_query)
        rows = [row for row in self.cur.fetchall()]

        return rows, word_ids

    def get_scored_list(self, rows, word_ids):
        total_scores = {row[0]: 0 for row in rows}

        weights = [
            (1, self.frequency_score(rows)),
            (1, self.location_score(rows)),
            # (1, self.distance_score(rows)),
            # (1, self.inbound_link_score(rows)),
            (1, self.pagerank_score(rows)),
            (1, self.linktext_score(rows, word_ids)),
            ]

        for weight, scores in weights:
            for url in total_scores:
                total_scores[url] += weight*scores[url]

        return total_scores

    def get_url_name(self, id):
        self.cur.execute('select url from urllist where id=%d' % id)
        return self.cur.fetchone()[0]

    def query(self, q):
        rows, word_ids = self.get_match_rows(q)
        scores = self.get_scored_list(rows, word_ids)
        rank_scores = sorted(scores.items(), key=lambda x: x[1], reverse=True)
        for url_id, score in rank_scores[:10]:
            print '%f\t%s' % (score, self.get_url_name(url_id))
        return word_ids, [r[0] for r in rank_scores]

    def normalize_scores(self, scores, small_better=0):
        vsmall = 0.00001
        if small_better:
            mmin = min(scores.values())
            return {u: float(mmin)/max(vsmall, l) for u, l in scores.items()}
        else:
            mmax = max(scores.values())
            if mmax == 0:
                mmax = vsmall
            return {u: float(l)/mmax for u, l in scores.items()}

    def frequency_score(self, rows):
        counts = {row[0]: 0 for row in rows}
        for row in rows:
            counts[row[0]] += 1
        return self.normalize_scores(counts)

    def location_score(self, rows):
        locations = {row[0]: 10**6 for row in rows}
        for row in rows:
            loc = sum(row[1:])
            if loc < locations[row[0]]:
                locations[row[0]] = loc
        return self.normalize_scores(locations, small_better=1)

    def distance_score(self, rows):
        if len(rows[0]) <= 2:
            return {row[0]: 1.0 for row in rows}
        min_distance = {row[0]: 10**6 for row in rows}
        for row in rows:
            dist = sum([abs(row[i]-row[i-1]) for i in xrange(2, len(row))])
            if dist < min_distance[row[0]]:
                min_distance[row[0]] = dist
        return self.normalize_scores(min_distance, small_better=1)

    def inbound_link_score(self, rows):
        unique_urls = set([row[0] for row in rows])
        inbound_count = {}
        for url in unique_urls:
            self.cur.execute('select count(*) from link where toid=%d' % url)
            cnt = self.cur.fetchone()[0]
            inbound_count[url] = cnt
        return self.normalize_scores(inbound_count)

    def pagerank_score(self, rows):
        pageranks = {}
        for row in rows:
            self.cur.execute('select score from pagerank where \
                urlid=%d' % row[0])
            score = self.cur.fetchone()[0]
            pageranks[row[0]] = score
        return self.normalize_scores(pageranks)

    def linktext_score(self, rows, word_ids):
        link_scores = {row[0]: 0 for row in rows}
        for word_id in word_ids:
            self.cur.execute('select link.fromid,link.toid from linkwords,\
                link where wordid=%d and linkwords.linkid=link.id' % word_id)
            for fromid, toid in self.cur.fetchall():
                if toid in link_scores:
                    self.cur.execute('select score from pagerank where \
                            urlid=%d' % fromid)
                    pr = self.cur.fetchone()[0]
                    link_scores[toid] += pr
        return self.normalize_scores(link_scores)

    def nn_score(self, rows, word_ids):
        url_ids = [url_id for url_id in set(row[0] for row in rows)]
        nn_res = mynet.get_result(word_ids, url_ids)
        scores = {url_ids[i]: nnres[i] for i in xrange(len(url_ids))}
        return self.normalize_scores(scores)
