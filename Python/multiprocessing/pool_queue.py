#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-27 10:12
# Last modified: 2016-08-27 10:25
# Filename: pool_queue.py
# Description:
from multiprocessing import Pool, Queue, Manager
import os, time, random

def write(q):
    print 'Write...(%s)' % os.getpid()
    for v in ['A', 'B', 'C']:
        print 'Put %s to queue...' % v
        q.put(v)
        time.sleep(random.random())

def read(q):
    print 'Read...(%s)' % os.getpid()
    while True:
        if not q.empty():
            v = q.get(True)
            print 'Get %s from queue...' % v
            time.sleep(random.random())
        else:
            break


if __name__ == '__main__':
    manager = Manager()
    q = manager.Queue()
    p = Pool()
    p.apply_async(write, args=(q,))
    time.sleep(0.5)
    p.apply_async(read, args=(q,))
    p.close()
    p.join()
    print 'All data writed and readed.'
