#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-09 16:07
# Last modified: 2016-11-11 11:34
# Filename: controllers.py
# Description:
__metaclass__ = type

import wx

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

    def create_session_bar(self, to_local=False, *args, **kwargs):
        if to_local:
            source = kwargs['source'][0]
            filename = kwargs['filename'][:50]
            uuid = source+':'+filename
            name = filename
            wx.CallAfter(self.gui.add_new_progress_bar, uuid, name)
        else:
            pass

    def update_session_bar(self, to_local=False, *args, **kwargs):
        if to_local:
            source = kwargs['source'][0]
            filename = kwargs['filename'][:50]
            uuid = source+':'+filename
        else:
            uuid = 'temp'
        progress = kwargs.get('progress', None)
        if progress:
            progress = int(progress)
        speed = kwargs.get('speed', None)
        if speed:
            speed = int(speed)
            if speed > 1024**2:
                speed = str(speed/(1024**2))+'MB/s'
            elif speed > 1024:
                speed = str(speed/1024)+'KB/s'
            else:
                speed = str(speed)+'B/s'
        eta = kwargs.get('eta', None)
        if eta:
            eta = int(eta)
            if eta > 24*(60**2):
                eta = u'超出一天'
            elif eta > 60**2:
                eta = str(eta/(60**2))+u'小时'
            elif eta > 60:
                eta = str(eta/60)+u'分钟'
            else:
                eta = str(eta)+u'秒'
        wx.CallAfter( self.gui.update_progress, uuid, progress, speed, eta)

    def delete_session_bar(self, to_local=False, *args, **kwargs):
        if to_local:
            source = kwargs['source'][0]
            filename = kwargs['filename'][:50]
            uuid = source+':'+filename
            wx.CallAfter(self.gui.delete_progress_bar, uuid)

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
