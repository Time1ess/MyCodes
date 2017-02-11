#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-11 13:45
# Last modified: 2017-02-11 13:45
# Filename: solution.py
# Description:
class Solution(object):
    def findWords(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        result = []
        key_groups = ['qwertyuiop', 'asdfghjkl', 'zxcvbnm']
        for word in words:
            for key_group in key_groups:
                if all([c.lower() in key_group for c in word]):
                    result.append(word)
                    break
        return result
