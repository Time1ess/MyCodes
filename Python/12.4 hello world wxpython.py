import wx

def hello(event):
	print "Hello,world!"

app=wx.App()

win=wx.Frame(None,title='Hello,wxPython!',size=(200,100))

button=wx.Button(win,label='Hello')
button.Bind(wx.EVT_BUTTON,hello)

win.Show()
app.MainLoop()
