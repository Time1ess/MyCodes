#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-04-01 09:01
# Last modified: 2017-04-01 10:24
# Filename: media.py
# Description:
import sys
from workflow import Workflow

from core import clean_movies, similarity


def main(wf):
    data = wf.cached_data('clean_movies', clean_movies, max_age=120)
    query = ''.join(sys.argv[1:])
    sim_func = similarity(query)
    items = []
    for fname, path, keywords in data:
        sim = sim_func(keywords)
        item = {'title': fname, 'subtitle': '播放: '+fname,
                'arg': path, 'valid': True}
        items.append((sim, item))
    items.sort(key=lambda x: -x[0])
    for sim, item in items[:5]:
        wf.add_item(**item)

    wf.send_feedback()


if __name__ == '__main__':
    wf = Workflow()
    sys.exit(wf.run(main))
