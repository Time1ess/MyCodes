#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-27 10:07
# Last modified: 2016-08-27 10:09
# Filename: test_pool.py
# Description:
from multiprocessing import Pool
import os, time

def long_time_task(name, wait=3):
    print 'Run task %s (%s)...' % (name, os.getpid())
    start = time.time()
    time.sleep(wait)
    end = time.time()
    print 'Task %s runs %0.2f seconds.' % (name, end-start)


if __name__ == '__main__':
    print 'Parent process %s.' % os.getpid()
    p = Pool()
    for i in xrange(10):
        p.apply_async(long_time_task, args=(i,))
    print 'Waiting for all subprocesses done...'
    p.close()
    p.join()
    print 'All subprocesses done.'
