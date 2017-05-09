#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 13:44
# Last modified: 2017-05-09 13:50
# Filename: signal_handlers.py
# Description:
import asyncio
import signal
import os

from functools import partial


def ask_exit(signame):
    print('Got signal {}: exit'.format(signame))
    loop.stop()


loop = asyncio.get_event_loop()
for signame in ('SIGINT', 'SIGTERM'):
    loop.add_signal_handler(getattr(signal, signame),
                            partial(ask_exit, signame))

print('Event loop running forever, press Ctrl+C to interrupt.')
print('pid {}: send SIGINT or SIGTERM to exit.'.format(os.getpid()))
try:
    loop.run_forever()
finally:
    loop.close()
