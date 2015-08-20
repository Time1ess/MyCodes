from Tkinter import *
def hello():
	print 'Hello,world'

win=Tk()
win.title('Hello,Tkinter!')
win.geometry('200x100')

btn=Button(win,text='Hello ',command=hello)
btn.pack(expand=YES,fill=BOTH)

mainloop()
