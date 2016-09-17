#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-26 15:51
# Last modified: 2016-08-26 16:37
# Filename: test.py
# Description:
import advancedclassify


agesonly = advancedclassify.load_match('agesonly.csv', True)
matchmaker = advancedclassify.load_match('matchmaker.csv')

# advancedclassify.plot_age_matches(agesonly)
avgs = advancedclassify.linear_train(agesonly)

