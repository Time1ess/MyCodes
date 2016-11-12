#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-08 09:11
# Last modified: 2016-11-12 18:05
# Filename: tests.py
# Description:
__metaclass__ = type

import socket
import sys
import time
import os

from random import randint

from manager import TransferManager
from sessions import SessionManager


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
    cmds = [cmd_fmt % (host, 10000+randint(0, 10), x) for x
            in filenames]
    for cmd in cmds:
        m.terminal_put(cmd)
    raw_input('Press Enter to exit.')
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
    cmds = [cmd_fmt % (host, 10000+randint(0, 10), x) for x
            in filenames]
    for cmd in cmds:
        m.terminal_get(cmd)
    raw_input('Press Enter to exit.')
    m.terminate()
    return 0


def test_all(m, pn=4, gn=4):
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
    cmds = [cmd_fmt % (host, 10000+randint(0, 10), x) for x
            in filenames]
    for idx, cmd in enumerate(cmds, 1):
        if idx > pn:
            break
        m.terminal_put(cmd)

    cmd_fmt = 'GET -h %s -p %s -f %s'
    cmds = [cmd_fmt % (host, 10000+randint(0, 10), x) for x
            in filenames]
    for idx, cmd in enumerate(cmds, 1):
        if idx > gn:
            break
        m.terminal_get(cmd)
    raw_input('Press Enter to exit.')
    m.terminate()
    return 0


def test(port=9000):
    """
    Author: David
    Desc:
            Interface to start test function based on given message port.
    """
    m = TransferManager(port, 2, files_dir='files')
    sm = SessionManager(m, 10, m._files_dir)
    m.add_session_manager(sm)
    m.start()
    if port == 9000:
        raw_input('Server is listening.')
    elif port == 9001:
        test_put(m)
    elif port == 9002:
        test_get(m)
    elif port == 9003:
        if len(sys.argv) == 3:
            pn = int(sys.argv[2])
            test_all(m, pn)
        elif len(sys.argv) == 4:
            pn = int(sys.argv[2])
            gn = int(sys.argv[3])
            test_all(m, pn, gn)
        else:
            test_all(m)
    else:
        print 'Unknown usage.'

if __name__ == '__main__':
    os.chdir('..')
    port = int(sys.argv[1])
    test(port)
