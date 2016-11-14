#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-08 09:33
# Last modified: 2016-11-14 16:27
# Filename: frames.py
# Description:
__metaclass__ = type

import wx
import os
import hashlib
import time

from random import randint

from settings import *


class ConsFrame(wx.Frame):
    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, title=title, size=(800, 600),
                          style=wx.SYSTEM_MENU | wx.CAPTION | wx.CLOSE_BOX)
        self._last_btn = None
        self.Bind(wx.EVT_CLOSE, self.on_close)

        self.main_layout = wx.BoxSizer(wx.HORIZONTAL)
        self.CreateStatusBar()
        self._init_menus()
        self._init_addrs()
        self._init_right_panel()

        self.SetSizer(self.main_layout)
        self.SetAutoLayout(1)
        self.main_layout.Fit(self)
        self.Show(True)

    def _init_menus(self):
        filemenu = wx.Menu()
        menu_about = filemenu.Append(
            102, u"关于", u'关于本程序')
        filemenu.AppendSeparator()
        menu_exit = filemenu.Append(
            103, u"退出", u'结束程序')
        self.Bind(wx.EVT_MENU, self.on_about, menu_about)
        self.Bind(wx.EVT_MENU, self.on_exit, menu_exit)
        menuBar = wx.MenuBar()
        menuBar.Append(filemenu, u'文件')
        self.SetMenuBar(menuBar)

    def _init_addrs(self):
        self.addrs_panel = wx.ScrolledWindow(
            self, size=(200, 600),
            style=wx.VSCROLL,
            name="addrs_panel")
        # self.addrs_layout = wx.GridSizer(0, 1, 3, 0)
        self.addrs_layout = wx.BoxSizer(wx.VERTICAL)
        self.addrs_panel.SetSizer(self.addrs_layout)
        self.addrs_panel.SetScrollbars(0, 20, 0, 50)

        self.main_layout.Add(self.addrs_panel, 0, wx.SHAPED | wx.ALL)

    def _init_right_panel(self):
        self.right_panel = wx.Panel(
            self, size=(600, 600), name="right_panel")
        self.right_layout = wx.BoxSizer(wx.VERTICAL)
        self.right_panel.SetSizer(self.right_layout)

        self.main_layout.Add(self.right_panel, 0, wx.SHAPED | wx.ALL)

        self._init_progress_panel()
        self._init_right_btns()

    def _init_progress_panel(self):
        self.progress_panel = wx.ScrolledWindow(
            self.right_panel, size=(600, 550),
            style=wx.VSCROLL,
            name="progress_panel")
        self.progress_panel_layout = wx.BoxSizer(wx.VERTICAL)
        self.progress_panel.SetSizer(self.progress_panel_layout)
        self.progress_panel.SetScrollbars(0, 20, 0, 50)

        self.right_layout.Add(self.progress_panel, 0, wx.ALL)

    def _init_right_btns(self):
        btns_panel = wx.Panel(
            self.right_panel, size=(600, 50), name="btns_panel")
        btns_layout = wx.BoxSizer(wx.HORIZONTAL)
        btns_panel.SetSizer(btns_layout)

        self.right_layout.Add(btns_panel, 0, wx.ALL)

        send_btn = wx.Button(btns_panel, -1, u'发送', size=(100, 50))

        self.Bind(wx.EVT_BUTTON, self.on_send, send_btn)

        btns_layout.Add(send_btn, 0, wx.LEFT, border=450)

        self.main_layout.Layout()
        self.Fit()

    def add_new_progress_bar(self, uuid, filename=u'未知',
                             speed=u'未知', eta=u'未知'):
        status = filter(lambda x: isinstance(x, wx.Panel) and
                        uuid == x.GetName(),
                        self.progress_panel.GetChildren())
        if status:
            return
        panel = wx.Panel(self.progress_panel, size=(600, 50), name=uuid)
        _title = wx.StaticText(panel, label=filename,
                               size=(450, -1), pos=(0, 5))
        _prog = wx.Gauge(panel, size=(450, -1), pos=(0, 25))
        _speed = wx.StaticText(panel, label=speed,
                               size=(150, -1), pos=(500, 5))
        _eta = wx.StaticText(panel, label=eta,
                             size=(150, -1), pos=(500, 25))
        panel.title = _title
        panel.progress = _prog
        panel.speed = _speed
        panel.eta = _eta
        self.progress_panel_layout.Add(panel, 0, wx.BOTTOM | wx.LEFT, border=10)
        self.main_layout.Layout()
        self.Fit()

    def update_progress(self, uuid, progress=None, speed=None, eta=None):
        status = filter(lambda x: isinstance(x, wx.Panel) and
                        uuid == x.GetName(),
                        self.progress_panel.GetChildren())
        if status:
            status = status[0]
            if progress:
                _progress = status.progress
                _progress.SetValue(progress % 100)
            if speed:
                _speed = status.speed
                _speed.SetLabel(speed)
            if eta:
                _eta = status.eta
                _eta.SetLabel(eta)

    def delete_progress_bar(self, uuid):
        status = filter(lambda x: isinstance(x, wx.Panel) and
                        uuid == x.GetName(),
                        self.progress_panel.GetChildren())
        if status:
            status[0].Destroy()
            self.main_layout.Layout()
            self.Fit()

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
        self.Destroy()

    def change_user(self, btn):
        if self._last_btn:
            self._last_btn.SetBackgroundColour(ADDRS_BTN_BG)
            self._last_btn.Refresh()
        self._last_btn = btn
        btn.SetBackgroundColour(ADDRS_BTN_FOCUS_BG)

    def on_target_user(self, e):
        btn = e.GetEventObject()
        self.change_user(btn)

    def on_clear(self, e):
        pass

    def on_request(self, e):
        pass

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
                            size=(200, 80))
            btn.SetBackgroundColour(ADDRS_BTN_BG)
            self.Bind(wx.EVT_BUTTON, self.on_target_user, btn)
            self.addrs_layout.Add(btn, 0, wx.SHAPED | wx.TOP, 5)
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
