#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-18 15:48
# Last modified: 2016-08-18 16:31
# Filename: zillow.py
# Description:
import xml.dom.minidom
import urllib2


zwskey = raw_input("Enter zws-id:")

def get_address_data(address, city):
    esc_address = address.replace(' ', '+')

    url = 'http://www.zillow.com/webservice/GetDeepSearchResults.htm?'
    url += 'zws-id=%s&address=%s&citystatezip=%s' % (zwskey, esc_address, city)

    data = urllib2.urlopen(url).read()
    doc = xml.dom.minidom.parseString(data)
    code = doc.getElementsByTagName('code')[0].firstChild.data

    if code != '0':
        print 'Error code:', code
        return None
    try:
        zipcode = doc.getElementsByTagName('zipcode')[0].firstChild.data
        use = doc.getElementsByTagName('useCode')[0].firstChild.data
        year = doc.getElementsByTagName('yearBuilt')[0].firstChild.data
        bath = doc.getElementsByTagName('bathrooms')[0].firstChild.data
        bed = doc.getElementsByTagName('bedrooms')[0].firstChild.data
        price = doc.getElementsByTagName('amount')[0].firstChild.data
    except Exception, e:
        print 'Error:', e
        return None

    return (zipcode, use, int(year), float(bath), int(bed), price)


def get_price_list(cnt=None):
    l1 = []
    lines = []
    with open('addresslist.txt') as f:
        for line in f:
            lines.append(line)
    for idx, line in enumerate(lines):
        if cnt and idx == cnt:
            break
        data = get_address_data(line.strip(), 'Cambridge,MA')
        print '%d/%d' % (idx+1, len(lines))
        if data:
            l1.append(data)
    return l1
