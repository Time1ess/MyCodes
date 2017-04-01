#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-31 21:52
# Last modified: 2017-04-01 08:58
# Filename: fab_file.py
# Description:
import os

from fabric.api import cd, run, env, sudo, hide

env.hosts = ['192.168.2.166']
env.user = 'david'


def fetch_movie_info():
    with hide('everything'):
        with cd('~/Downloads'):
            videos = []
            files = run('find . -type f -regex ".*\.\(mkv\|mp4\|wmv\|flv\|webm\|mov\)"')
            files = [f.strip('\n\r\t ') for f in files.split('\n')]
            for f in files:
                print(f[2:])
