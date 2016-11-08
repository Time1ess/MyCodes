#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-08 09:11
# Last modified: 2016-11-08 09:23
# Filename: tests.py
# Description:
__metaclass__ = type

import socket
import sys

from random import randint

from manager import TransferManager


def test_put(m):
    """
    Author: David
    Desc:
            Test PUT operations in parallel.
    """
    host = socket.gethostbyname(socket.gethostname())
    filenames = [
        '[APTX4869][CONAN][817][720P][AVC_AAC][CHS](59D42DBF).mp4',
        '[APTX4869][CONAN][818][720P][AVC_AAC][CHS](2FCED262).mp4',
        '[APTX4869][CONAN][819][720P][AVC_AAC][CHS](0B98AFC4).mp4',
        '[APTX4869][CONAN][820][720P][AVC_AAC][CHS](B8255B71).mp4']
    cmd_fmt = 'PUT -h %s -p %s -f /Users/youchen/Movies/%s'
    cmds = [cmd_fmt % (host, 10000+randint(0, 0), x) for x
            in filenames]
    for cmd in cmds:
        m.terminal_put(cmd)
    m.terminate()
    return 0


def test_get(m):
    """
    Author: David
    Desc:
            Test GET operations in parallel.
    """
    host = socket.gethostbyname(socket.gethostname())
    filenames = [
        '[APTX4869][CONAN][817][720P][AVC_AAC][CHS](59D42DBF).mp4',
        '[APTX4869][CONAN][818][720P][AVC_AAC][CHS](2FCED262).mp4',
        '[APTX4869][CONAN][819][720P][AVC_AAC][CHS](0B98AFC4).mp4',
        '[APTX4869][CONAN][820][720P][AVC_AAC][CHS](B8255B71).mp4']
    cmd_fmt = 'GET -h %s -p %s -f %s'
    cmds = [cmd_fmt % (host, 10000+randint(0, 0), x) for x
            in filenames]
    for cmd in cmds:
        m.terminal_get(cmd)
    m.terminate()
    return 0


def test_all(m):
    """
    Author: David
    Desc:
            Test PUT and GET operations in parallel together. Notice that
            force is not given so that port will be changed by remote
            server when the given port has been used.
    """
    host = socket.gethostbyname(socket.gethostname())
    filenames = [
        '[APTX4869][CONAN][817][720P][AVC_AAC][CHS](59D42DBF).mp4',
        '[APTX4869][CONAN][818][720P][AVC_AAC][CHS](2FCED262).mp4',
        '[APTX4869][CONAN][819][720P][AVC_AAC][CHS](0B98AFC4).mp4',
        '[APTX4869][CONAN][820][720P][AVC_AAC][CHS](B8255B71).mp4']
    cmd_fmt = 'PUT -h %s -p %s -f /Users/youchen/Movies/%s'
    cmds = [cmd_fmt % (host, 10000+randint(0, 0), x) for x
            in filenames]
    for cmd in cmds:
        m.terminal_put(cmd)

    cmd_fmt = 'GET -h %s -p %s -f %s'
    cmds = [cmd_fmt % (host, 10000+randint(0, 0), x) for x
            in filenames]
    for cmd in cmds:
        m.terminal_get(cmd)
    m.terminate()
    return 0


def test(port=9000):
    """
    Author: David
    Desc:
            Interface to start test function based on given message port.
    """
    m = TransferManager(port, 2)
    if port == 9000:
        raw_input('Server is listening.')
    elif port == 9001:
        test_put(m)
    elif port == 9002:
        test_get(m)
    elif port == 9003:
        test_all(m)
    else:
        print 'Unknown usage.'

if __name__ == '__main__':
    port = int(sys.argv[1])
    test(port)
