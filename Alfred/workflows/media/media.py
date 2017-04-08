#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-04-01 09:01
# Last modified: 2017-04-01 10:24
# Filename: media.py
# Description:
import sys
import time
import subprocess

from workflow import Workflow


def main(wf):
    query = ''.join(sys.argv[1:])
    if query == 'stop':
        time.sleep(0.3)
        code = subprocess.run(['pkill', 'mpv']).returncode
        if code == 0:
            wf.add_item(title='成功停止播放!', subtitle='')
        elif code == 1:
            wf.add_item(title='无正在播放任务!', subtitle='')
        else:
            wf.add_item(title='未知错误!', subtitle='')
    else:
        from core import clean_medias, similarity
        data = wf.cached_data('clean_medias', clean_medias, max_age=60)
    
        sim_func = similarity(query)
        items = []
        for fname, path, keywords in data:
            sim = sim_func(keywords)
            item = {'title': fname, 'subtitle': '播放: '+fname,
                    'arg': path, 'valid': True}
            items.append((sim, item))
        items.sort(key=lambda x: (-x[0], x[1]['title']))
        for sim, item in items[:10]:
            wf.add_item(**item)

    wf.send_feedback()


if __name__ == '__main__':
    wf = Workflow()
    sys.exit(wf.run(main))
