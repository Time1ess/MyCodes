#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-08 20:15
# Last modified: 2016-11-09 10:17
# Filename: main.py
# Description:
__metaclass__ = type

import wx
import time

from threading import Thread

from gui.frames import ConsFrame
from core.manager import TransferManager

def message_hook(manager, frame):
    def action(cli_msg=None, svr_msg=None):
        cli_args = cli_msg.split(' ')
        svr_args = svr_msg.split(' ')
        cli_type = cli_args[0]
        svr_type = svr_args[0]
        if cli_type == 'REG' and svr_type == 'SRG':
            frame.append_new_addr(cli_args[1])
        elif cli_type == 'URE' and svr_type == 'ACK':
            frame.delete_addr(cli_args[1])
        elif cli_type == 'PUT' and svr_type == 'SPT':
            frame.append_log(cli_msg)
        elif cli_type == 'GET' and svr_type == 'SGT':
            frame.append_log(cli_msg)
    return action


def main():
    m = TransferManager(files_dir='files')
    app = wx.App(False)
    frame = ConsFrame(None, 'FileMe')
    hook = message_hook(m, frame)
    m.add_hook(hook)
    m.add_user_confirm_func('PUT', frame.confirm_action)
    m.add_user_confirm_func('GET', frame.confirm_action)
    app.MainLoop()
    m.terminate()


if __name__ == '__main__':
    main()
