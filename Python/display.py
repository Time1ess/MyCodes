# coding: UTF-8
__metaclass__ = type
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import random
import socket

i = 0
winId = 0
s = None
poses = []
SIZE = [800, 600]
clear = True


def Draw():
    global poses
    global clear
    glEnable(GL_POINT_SMOOTH)
    if clear:
        glClear(GL_COLOR_BUFFER_BIT)
        clear = False
    glPointSize(5)
    glBegin(GL_POINTS)
    for item in poses:
        try:
            if item[2] == 1:
                glVertex2f(item[0], item[1])
            elif item[2] == -1:
                clear = True
        except:
            pass
    poses = []
    glEnd()
    glFlush()


def Update():
    global s
    global poses
    try:
        data = s.recv(4096).split('|')
        poses = map(lambda x: map(lambda y: int(y), x.split(',')), data)
        if not data:
            raise Exception
    except Exception, e:
        print e
        s.close()
        sys.exit(0)
    for item in poses:
            item[0] = (item[0]*1.0/SIZE[0]*200-100)/100.0
            item[1] = -((item[1]*1.0/SIZE[1]*200-100))/100.0
    print poses
    glutPostRedisplay()


def keyboardHit(key, mouseX, mouseY):
    if key == 'q':
        global s
        glutDestroyWindow(winId)
        s.close()
        sys.exit()


def mouseHit(button, state, mouseX, mouseY):
    pass


def mouseMotion(mouseX, mouseY):
    pass


def main():
    global winId
    global s
    s = socket.socket()
    host = socket.gethostname()
    s.connect((host, 1234))
    glutInit()
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
    glutInitWindowSize(SIZE[0], SIZE[1])
    winId = glutCreateWindow("David")
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
        print e
