#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-08 09:08
# Last modified: 2016-11-12 14:08
# Filename: settings.py
# Description:

import logging

DEBUG = True 
BUF_SIZE = 4096

logging.basicConfig(
    level=logging.DEBUG,
    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s: %(message)s',
    datefmt='%a, %m %d %Y %H:%M:%S',
    filename='debug.log',
    filemode='w')
