#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-08 15:56
# Last modified: 2016-11-10 20:38
# Filename: settings.py
# Description:
__metaclass__ = type

import wx
import os

LOG_DIR = os.path.join(os.getcwd(), 'logs')
FILE_DIR = os.path.join(os.getcwd(), 'files')

COLOR_RED = wx.Colour(255, 0, 0)  # Red
COLOR_YELLOW = wx.Colour(255, 255, 0) # Yellow
COLOR_PURPLE = wx.Colour(255, 0, 255) # Purple
COLOR_LIGHT_BLUE = wx.Colour(0, 255, 255)  # Light Blue
ADDRS_BTN_BG = wx.Colour(224, 222, 210)
ADDRS_BTN_FOCUS_BG = wx.Colour(200, 200, 200)

