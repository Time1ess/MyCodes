#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-07-29 15:46
# Last modified: 2016-07-29 16:14
# Filename: downloadzebodata.py
# Description:
from BeautifulSoup import BeautifulSoup
import urllib2
import re

# IMPORTANT: the website is now unavailable.
chare = re.compile(r'[!-\.&]')
item_owners = {}
drop_words = ['a', 'new', 'some', 'more', 'my', 'own', 'the', 'many',
              'other', 'another']

current_user = 0
for i in xrange(1, 51):
    c = urllib2.urlopen(
        'http://member.zebo.com/Main?' +
        'event_key=USERSEARCH&wiowiw=wiw&keyword=car&page=%d' % (i))
    soup = BeautifulSoup(c.read())
    for td in soup('td'):
        if 'class' in dict(td.attrs) and td['class'] == 'bgverdanasmall':
            items = [re.sub(chare, '', str(a.contents[0]).lower()).strip()
                     for a in td('a')]
            for item in items:
                txt = ' '.join([t for t in item.split(' ')
                                if t not in drop_words])
                if len(txt) < 2:
                    continue
                item_owners.setdefault(txt, {})
                item_owners[txt][current_user] = 1
            current_user += 1

out = open('zebo.txt', 'w')
out.write('Item')
for user in xrange(currentuser):
    out.write('\tU%d' % user)
out.write('\n')
for item, owners in item_owners.items():
    if len(owners) > 10:
        out.write(item)
        for user in xrange(current_user):
            if user in owners:
                out.write('\t1')
            else:
                out.write('\t0')
        out.write('\n')
