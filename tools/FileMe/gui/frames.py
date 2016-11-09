#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-08 09:33
# Last modified: 2016-11-09 16:57
# Filename: frames.py
# Description:
__metaclass__ = type

import wx
import sys
import os
import hashlib
import time

from wx.lib.pubsub import pub

from settings import *


class ConsFrame(wx.Frame):
    def _init_menus(self):
        filemenu = wx.Menu()
        menu_about = filemenu.Append(
            102, "关于", u'关于本程序')
        filemenu.AppendSeparator()
        menu_exit = filemenu.Append(
            103, "退出", u'结束程序')
        self.Bind(wx.EVT_MENU, self.on_about, menu_about)
        self.Bind(wx.EVT_MENU, self.on_exit, menu_exit)
        menuBar = wx.MenuBar()
        menuBar.Append(filemenu, u'文件')
        self.SetMenuBar(menuBar)

    def _init_addrs(self):
        self.addrs_panel = wx.ScrolledWindow(self, size=(200, 400))
        self.addrs_layout = wx.GridSizer(0, 1, 3, 0)
        self.main_layout.Add(self.addrs_panel, 1, wx.EXPAND)
        self.addrs_panel.SetSizer(self.addrs_layout)
        self.addrs_panel.SetScrollbars(0, 20, 0, 50)
        self.addrs_panel.SetBackgroundColour(ADDRS_PANEL_BG)

    def _init_logs(self):
        self.control = wx.TextCtrl(
            self, style=wx.TE_MULTILINE | wx.TE_READONLY, size=(400, 400))
        self.right_panel_layout = wx.BoxSizer(wx.VERTICAL)
        self.right_panel_layout.Add(self.control, 0,
                                    wx.EXPAND | wx.ALL, border=10)
        self.main_layout.Add(self.right_panel_layout, 0, wx.EXPAND)

    def _init_btns(self):
        btns_layout = wx.BoxSizer(wx.HORIZONTAL)
        self.right_panel_layout.Add(btns_layout, 0, wx.ALIGN_RIGHT)
        send_btn = wx.Button(self, -1, u'发送')
        request_btn = wx.Button(self, -1, u'请求')
        clear_btn = wx.Button(self, -1, u'清空日志')

        self.Bind(wx.EVT_BUTTON, self.on_clear, clear_btn)
        self.Bind(wx.EVT_BUTTON, self.on_send, send_btn)
        self.Bind(wx.EVT_BUTTON, self.on_request, request_btn)

        btns = [send_btn, request_btn, clear_btn]
        for btn in btns:
            btns_layout.Add(btn, flag=wx.ALL, border=10)

    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, title=title, size=(1000, 600),
                          style= wx.SYSTEM_MENU | wx.CAPTION | wx.CLOSE_BOX)
        self._last_btn = None
        self.Bind(wx.EVT_CLOSE, self.on_close)

        self.CreateStatusBar()
        self._init_menus()
        self.main_layout = wx.BoxSizer(wx.HORIZONTAL)
        self._init_addrs()
        self._init_logs()
        self._init_btns()

        self.SetSizer(self.main_layout)
        self.SetAutoLayout(1)
        self.main_layout.Fit(self)
        self.delete_addr('button 26')
        self.Show(True)

    def set_coordinator(self, coo):
        self.coo = coo

    def menu_event(self, event):
        print 'menu item selected.'

    def on_about(self, e):
        dlg = wx.MessageDialog(
            self,
            "FileMe is a cross-platform file transfer tool written in Python.",
            "About FileMe", wx.OK)
        dlg.ShowModal()
        dlg.Destroy()

    def on_exit(self, e):
        self.Close(True)

    def on_close(self, e):
        print 'Exit'
        if self._last_btn:
            self._last_btn.SetBackgroundColour(ADDRS_BTN_BG)
            addr = self._last_btn.GetLabel()
            self.write_logfile(addr, self.control.GetValue())
        self.Destroy()

    def change_user(self, btn):
        if self._last_btn:
            self._last_btn.SetBackgroundColour(ADDRS_BTN_BG)
            addr = self._last_btn.GetLabel()
            self.write_logfile(addr, self.control.GetValue())
            self._last_btn.Refresh()
        self._last_btn = btn
        btn.SetBackgroundColour(ADDRS_BTN_FOCUS_BG)
        addr = btn.GetLabel()
        self.read_logfile(addr)

    def on_target_user(self, e):
        btn = e.GetEventObject()
        self.change_user(btn)

    @staticmethod
    def _hash(msg):
        h = hashlib.md5()
        h.update(msg)
        return h.hexdigest()

    def write_logfile(self, addr, log):
        filename = self._hash(addr)+'.log'
        filepath = os.path.join(LOG_DIR, filename)
        with open(filepath, 'wb') as f:
            f.write(log)

    def read_logfile(self, addr):
        filename = self._hash(addr)+'.log'
        filepath = os.path.join(LOG_DIR, filename)
        try:
            with open(filepath, 'rb') as f:
                self.clear_log()
                self.set_log(''.join(f.readlines()))
        except IOError:
            pass

    def clear_log(self):
        self.control.SetValue('')

    def append_log(self, log):
        wx.CallAfter(self.control.AppendText, log)

    def set_log(self, log):
        self.control.SetValue(log)

    def on_clear(self, e):
        self.clear_log()

    def on_request(self, e):
        self.main_layout.Fit(self)

    def alert(self, msg):
        dlg = wx.MessageDialog(self, message=msg,
                               style=wx.OK,
                               caption=u'警告')
        dlg.ShowModal()
        dlg.Destroy()

    def on_send(self, e):
        if not self._last_btn:
            msg = u'请先选择发送对象'
            self.alert(msg)
            return
        dlg = wx.FileDialog(
            self, u'选择文件', '', "", "*.*", wx.OPEN)
        if dlg.ShowModal() == wx.ID_OK:
            filename = dlg.GetFilename()
            dirname = dlg.GetDirectory()
            path = os.path.join(dirname, filename)
            self.coo.send_file(path, self._last_btn.GetLabel())
        dlg.Destroy()

    def append_new_addr(self, addr):
        labels = map(lambda x: x.GetWindow().GetLabel(),
                     self.addrs_layout.GetChildren())
        if addr not in labels:
            btn = wx.Button(self.addrs_panel, -1, addr, style=wx.NO_BORDER,
                            size=(-1, 40))
            btn.SetBackgroundColour(ADDRS_BTN_BG)
            self.Bind(wx.EVT_BUTTON, self.on_target_user, btn)
            self.addrs_layout.Add(btn, 0, wx.SHAPED)
            self.main_layout.Layout()
            self.Fit()
            self.change_user(btn)

    def delete_addr(self, addr):
        for _btn in self.addrs_layout.GetChildren():
            btn = _btn.GetWindow()
            label = btn.GetLabel()
            if addr == label:
                btn.Destroy()
                break

    def confirm_dlg(self, msg):
        dlg = wx.MessageDialog(self, message=msg,
                               caption=u'确认操作')
        self.choice = dlg.ShowModal()
        dlg.Destroy()

    def confirm_action(self, args):
        msg = ' '.join(args)
        self.choice = None
        wx.CallAfter(self.confirm_dlg, msg)
        while self.choice is None:
            time.sleep(0.1)
        if self.choice == wx.ID_OK:
            return True
        else:
            return False

def main():
    app = wx.App(False)
    frame = ConsFrame(None, 'FileMe')
    app.MainLoop()


if __name__ == '__main__':
    main()
