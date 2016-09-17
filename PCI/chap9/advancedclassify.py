#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-26 14:42
# Last modified: 2016-08-30 10:29
# Filename: advancedclassify.py
# Description:
__metaclass__ = type
from pylab import *
from private_api_keys import GOOGLE_API_KEY
import math


class matchrow:
    def __init__(self, row, all_num=False):
        if all_num:
            self.data = [float(row[i]) for i in xrange(len(row)-1)]
        else:
            self.data = row[0:len(row)-1]
        self.match = int(row[len(row)-1])

    def __repr__(self):
        return str(self.data+[self.match])


def load_match(f, all_num=False):
    rows = []
    with open(f, 'r') as fd:
        for line in fd:
            rows.append(matchrow(line.split(','), all_num))
    return rows


def plot_age_matches(rows):
    xdm, ydm = [r.data[0] for r in rows if r.match == 1],\
               [r.data[1] for r in rows if r.match == 1]
    xdn, ydn = [r.data[0] for r in rows if r.match == 0],\
               [r.data[1] for r in rows if r.match == 0]

    plot(xdm, ydm, 'go')
    plot(xdn, ydn, 'ro')

    show()


def linear_train(rows):
    averages = {}
    counts = {}

    for row in rows:
        cl = row.match

        averages.setdefault(cl, [0.0]*len(row.data))
        counts.setdefault(cl, 0)

        for i in xrange(len(row.data)):
            averages[cl][i] += float(row.data[i])

        counts[cl] += 1

    for cl, avg in averages.items():
        for i in xrange(len(avg)):
            avg[i] /= counts[cl]

    return averages


def dot_product(v1, v2):
    if len(v1) != len(v2):
        raise Exception('Product Error: Unmatched length.')
    return sum([v1[i]*v2[i] for i in xrange(len(v1))])


def dp_classify(point, avgs):
    b = (dot_product(avgs[1], avgs[1])-dot_product(avgs[0], avgs[0]))/2
    y = dot_product(point, avgs[0])-dot_product(point, avgs[1])+b
    if y > 0:
        return 0
    else:
        return 1


def yes_no(v):
    if v == 'yes':
        return 1
    elif v == 'no':
        return -1
    else:
        return 0


def match_count(interest1, interest2):
    l1 = interest1.split(':')
    l2 = interest2.split(':')
    return len(set(l1).intersection(l2))


def miles_distance(a1, a2):
    lat1, lng1 = get_location(a1)
    lat2, lng2 = get_location(a2)
    lat_diff = 69.1*(lat2-lat1)
    lng_diff = 53.0*(lng2-lng1)
    return (lat_diff**2+lng_diff**2)**.5

loc_cache = {}


def get_location(address):
    if not loc_cache:
        _load_loc_cache()
    api_url = ('https://maps.googleapis.com/'
               'maps/api/geocode/xml?address=%s&key=%s')
    from urllib import quote_plus
    import urllib2
    from xml.dom.minidom import parseString
    import socks
    import socket
    host = '127.0.0.1'
    port = 1080
    if address in loc_cache:
        return loc_cache[address]
    socks.set_default_proxy(socks.SOCKS5, host, port)
    socket.socket = socks.socksocket
    query = api_url % (quote_plus(address), GOOGLE_API_KEY)
    request = urllib2.Request(query)
    data = urllib2.urlopen(request).read()
    doc = parseString(data)
    lat = doc.getElementsByTagName('lat')[0].firstChild.nodeValue
    lng = doc.getElementsByTagName('lng')[0].firstChild.nodeValue
    loc_cache[address] = (float(lat), float(lng))
    return loc_cache[address]


def _save_loc_cache(target='loc_cache.txt'):
    with open(target, 'wb') as f:
        for key, value in loc_cache.items():
            f.write(key+'\t'+str(value[0])+'\t'+str(value[1])+'\n')


def _load_loc_cache(target='loc_cache.txt'):
    data = []
    with open(target, 'rb') as f:
        for line in f:
            data.append(line.split('\t'))
    data = map(lambda x: (x[0], float(x[1]), float(x[2].rstrip('\n'))), data)
    for addr, lat, lng in data:
        loc_cache[addr] = (lat, lng)


def load_numerical():
    old_rows = load_match('matchmaker.csv')
    new_rows = []
    size = len(old_rows)
    for idx, row in enumerate(old_rows):
        print 'Processing original data %d / %d' % (idx+1, size)
        d = row.data
        data = [float(d[0]), yes_no(d[1]), yes_no(d[2]),
                float(d[5]), yes_no(d[6]), yes_no(d[7]),
                match_count(d[3], d[8]),
                miles_distance(d[4], d[9]),
                row.match]
        new_rows.append(matchrow(data))
    return new_rows


def scale_data(rows):
    low = [1e10]*len(rows[0].data)
    high = [-1e10]*len(rows[0].data)

    for row in rows:
        d = row.data
        for i in xrange(len(d)):
            low[i] = min(d[i], low[i])
            high[i] = max(d[i], high[i])

    def scale_input(d):
        return [(d[i]-low[i])/(high[i]-low[i])
                for i in xrange(len(low))]

    new_rows = [matchrow(scale_input(row.data)+[row.match])
                for row in rows]

    return new_rows, scale_input


def vec_length(v):
    return sum([p**2 for p in v])


def radial_basis(v1, v2, gamma=20):
    dv = [v1[i]-v2[i] for i in xrange(len(v1))]
    l = vec_length(dv)
    return math.e**(-gamma*l)


def nl_classify(point, rows, offset, gamma=10):
    sum0 = 0.0
    sum1 = 0.0
    cnt0 = 0
    cnt1 = 0

    for row in rows:
        if row.match == 0:
            sum0 += radial_basis(point, row.data, gamma)
            cnt0 += 1
        else:
            sum1 += radial_basis(point, row.data, gamma)
            cnt1 += 1
    y = (1.0/cnt0)*sum0-(1.0/cnt1)*sum1+offset

    if y > 0:
        return 0
    else:
        return 1


def get_offset(rows, gamma=10):
    l0 = []
    l1 = []
    for row in rows:
        if row.match == 0:
            l0.append(row.data)
        else:
            l1.append(row.data)

    sum0 = sum(radial_basis(v1, v2, gamma) for v1 in l0 for v2 in l0)
    sum1 = sum(radial_basis(v1, v2, gamma) for v1 in l1 for v2 in l1)

    return (1.0/(len(l1)**2))*sum1-(1.0/(len(l0)**2))*sum0
