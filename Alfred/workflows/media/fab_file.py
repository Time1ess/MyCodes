#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-31 21:52
# Last modified: 2017-04-01 08:58
# Filename: fab_file.py
# Description:
import os
import sys
import itertools

from fabric.api import cd, run, env, sudo, hide

env.hosts = ['192.168.2.166']
env.user = 'david'

video_types = ['mkv', 'mp4', 'wmv', 'flv', 'webm', 'mov']
music_types = ['mp3', 'wma', 'wav']

types = [x for x in itertools.chain(video_types, music_types)]

search_cmd = 'find -L . -maxdepth 5 -type f -regex ".*\.\('+types[0]
for t in types[1:]:
    search_cmd += '\|' + t
search_cmd += '\)"'

def remove_file(file_path):
    with hide('everything'):
    	with cd('~/Downloads'):
    		run('rm "{}"'.format(file_path))


def fetch_media_info():
    with hide('everything'):
        with cd('~/Downloads'):
            videos = []
            files = run(search_cmd)
            files = [f.strip('\n\r\t ') for f in files.split('\n')]
            for f in files:
                print(f[2:])
