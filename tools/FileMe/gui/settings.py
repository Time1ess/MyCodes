#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-08 15:56
# Last modified: 2016-11-08 21:18
# Filename: settings.py
# Description:
__metaclass__ = type

import wx
import os


LOG_DIR = os.path.join(os.getcwd(), 'logs')
FILE_DIR = os.path.join(os.getcwd(), 'files')

ADDRS_BTN_BG = wx.Colour(224, 222, 210)
ADDRS_BTN_FOCUS_BG = wx.Colour(200, 200, 200)
ADDRS_PANEL_BG = wx.Colour(246, 246, 246)
