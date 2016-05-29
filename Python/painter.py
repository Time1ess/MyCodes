#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-04-27 15:00
# Last modified: 2016-04-27 15:00
# Filename: painter.py
# Description:
__metaclass__ = type
import socket
import time
from random import randint
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *


s = None
c = None
paint = True
SIZE = [800, 600]
data = []
clear = True
winId = 0


def convert(val, axis):
    ans = val
    if axis == 0:  # X axis
        ans = (ans*1.0/SIZE[0]*200-100)/100.0
    elif axis == 1:
        ans = -(ans*1.0/SIZE[1]*200-100)/100.0
    return ans


def gen_pos():
    return [randint(-100, 100), randint(-100, 100), randint(0, 1)]


def Draw():
    global data
    global clear
    glEnable(GL_POINT_SMOOTH)
    if clear:
        glClear(GL_COLOR_BUFFER_BIT)
        clear = False
    glPointSize(5)
    glBegin(GL_POINTS)
    for item in data:
        print item
        if item[2]:
            glVertex2f(convert(item[0], 0), convert(item[1], 1))
            print convert(item[0], 0), convert(item[1], 1)
    glEnd()
    glFlush()


def Update():
    glutPostRedisplay()


def keyboardHit(key, mouseX, mouseY):
    if key == 'q':
        global s
        glutDestroyWindow(winId)
        s.close()
        sys.exit()


def mouseHit(button, state, mouseX, mouseY):
    global paint
    global data
    global clear
    global c
    global s
    if button == 0 and state == 1:
        data = []
    elif button == 0 and state == 0:
        paint = True
    elif button == 2 and state == 1:
        data.append([0, 0, -1])
        clear = True
    else:
        paint = False


def mouseMotion(mouseX, mouseY):
    global paint
    global data
    global c
    if paint: 
        data.append([mouseX, mouseY, 1])
        try:
            c.send('|'.join(map(lambda x: ','.join(map(lambda y: str(y), x)), data)))
        except Exception, e:
            print e
            s.close()
            sys.exit(0)
        else:
            if len(data) == 500:
                data = []

def main():
    global winId
    global s
    global c

    s = socket.socket()
    host = socket.gethostname()
    port = 1234
    s.bind((host, port))
    s.listen(5)
    c, addr = s.accept()
    print 'Got connection from ', addr

    glutInit()
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
    glutInitWindowSize(SIZE[0], SIZE[1])
    winId = glutCreateWindow("David-paint")
    glutDisplayFunc(Draw)
    glutIdleFunc(Update)
    glutKeyboardFunc(keyboardHit)
    glutMouseFunc(mouseHit)
    glutMotionFunc(mouseMotion)
    glutMainLoop()

if __name__ == '__main__':
    try:
        main()
    except Exception, e:
        s.close()
        print e
