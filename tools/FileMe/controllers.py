#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-09 16:07
# Last modified: 2016-11-10 20:35
# Filename: controllers.py
# Description:
__metaclass__ = type

from random import randint
from multiprocessing import Lock


class Coordinator:
    def __init__(self, manager=None, gui=None):
        self.manager = manager
        self.gui = gui
        self.msgs = []
        self.msg_lock = Lock()

    def set_manager(self, manager):
        if self.manager is None:
            self.manager = manager
        else:
            print 'Already has a manager'
        self.unhandled_message()

    def set_gui(self, gui):
        if self.gui is None:
            self.gui = gui 
        else:
            print 'Already has a gui'
        self.unhandled_message()

    def message_hook(self, cli_msg, svr_msg):
        self.msg_lock.acquire()
        self.msgs.append((cli_msg, svr_msg))
        self.msg_lock.release()
        self.unhandled_message()

    def unhandled_message(self):
        if self.manager and self.gui:
            while True:
                if not self._handle_message():
                    break
        else:
            print 'No available manager or gui'

    def _handle_message(self):
        self.msg_lock.acquire()
        if not self.msgs:
            self.msg_lock.release()
            return False
        else:
            cli_msg, svr_msg = self.msgs.pop(0)
            self.msg_lock.release()
        cli_args = cli_msg.split(' ')
        svr_args = svr_msg.split(' ')
        cli_type = cli_args[0]
        svr_type = svr_args[0]
        if cli_type == 'REG' and svr_type == 'SRG':
            self.gui.append_new_addr(cli_args[1])
        elif cli_type == 'URE' and svr_type == 'ACK':
            self.gui.delete_addr(cli_args[1])
        elif cli_type == 'PUT' and svr_type == 'SPT':
            pass
        elif cli_type == 'GET' and svr_type == 'SGT':
            pass
        elif cli_type == 'SRG' and svr_type == 'ACK':
            self.gui.append_new_addr(cli_args[2])
        elif cli_type == 'SPT' and svr_type == 'ACK':
            pass
        elif cli_type == 'SGT' and svr_type == 'ACK':
            pass
        return True

    def send_file(self, path, host):
        self.manager.put(path, host, randint(10000, 10100))
