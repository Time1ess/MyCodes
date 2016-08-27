#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-27 10:12
# Last modified: 2016-08-27 10:41
# Filename: lock_pool_queue.py
# Description:
from multiprocessing import Pool, Manager
import os, time, random

def write(q, lock):
    for v in xrange(20):
        lock.acquire()
        print 'PUT\t%s' % v
        q.put(v)
        lock.release()
        time.sleep(random.random()*0.5)
    lock.acquire()
    q.put('EXIT')
    lock.release()

def read(q, lock):
    while True:
        lock.acquire()
        if not q.empty():
            v = q.get()
        else:
            v = None
        lock.release()
        if v is None:
            continue
        if v == 'EXIT':
            break
        print 'GET\t\t%s' % v
        time.sleep(random.random()*0.5)


if __name__ == '__main__':
    manager = Manager()
    q = manager.Queue()
    p = Pool()
    lock = manager.Lock()
    p.apply_async(write, args=(q, lock))
    p.apply_async(read, args=(q, lock))
    p.close()
    p.join()
    print 'All data writed and readed.'
