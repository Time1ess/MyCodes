#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-27 10:12
# Last modified: 2016-08-27 10:12
# Filename: pool_queue.py
# Description:
from multiprocessing import Process, Queue
import os, time, random

def write(q):
    for v in ['A', 'B', 'C']:
        print 'Put %s to queue...' % v
        q.put(v)
        time.sleep(random.random())

def read(q):
    while True:
        if not q.empty():
            v = q.get(True)
            print 'Get %s from queue...' % v
            time.sleep(random.random())
        else:
            break


if __name__ == '__main__':
    q = Queue()
    pw = Process(target=write, args=(q,))
    pr = Process(target=read, args=(q,))
    pw.start()
    pw.join()
    pr.start()
    pr.join()
    print 'All data writed and readed.'
