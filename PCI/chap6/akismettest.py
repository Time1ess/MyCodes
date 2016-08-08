#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-08 15:21
# Last modified: 2016-08-08 15:38
# Filename: akismettest.py
# Description:
from akismet import Akismet


api = Akismet(agent='Test Script')
key = raw_input('API KEY:')
api.setAPIKey(key)

data = {}
data['user_ip'] = '127.0.0.1'
data['user_agent'] = 'Test Script'

def isspam(comment):
    if api.key is None:
        print "No 'apikey.txt' file."
    elif not api.verify_key():
        print "The API Key is invalid."
    else:
        if api.comment_check(comment, data):
            print 'This comment is spam.'
        else:
            print 'This comment is ham.'
