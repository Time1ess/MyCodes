#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-30 12:36
# Last modified: 2016-10-30 15:25
# Filename: sender.py
# Description:
import socket

host = socket.gethostbyname(socket.gethostname())
port = 9001
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

rsock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
rsock.bind((host, port))

sock.bind(('', 0))
addr = (('<broadcast>', 9000))
reg_msg = 'REG %s %s' % (host, port)

print '[MSG]:', reg_msg,
sock.sendto(reg_msg, addr)
data, addr = rsock.recvfrom(4096)
print '\t\t[RET]:', data, addr

ack_sre = 'ACK SRG'
ure_msg = 'URE %s' % (host,)
put_msg = 'PUT -h 192.168.56.53 -p 10000 -f 123.mkv -F'
filename = '123.mkv'
ack_ack = 'ACK ACK'
msgs = [ack_sre, ack_ack, put_msg, ack_ack, ure_msg, ack_ack]
for msg in msgs:
    print '[MSG]:', msg,
    sock.sendto(msg, addr)
    if msg == ack_ack:
        print
        print 'IGNORE'
        continue
    data, addr = rsock.recvfrom(4096)
    print '\t\t[RET]:', data, addr
    if data == 'ACK PUT':
        s = socket.socket()
        s.connect((host, 10000))
        with open(filename, 'rb') as f:
            print 'Begin session.'
            fbts = f.read(4096)
            while fbts:
                s.send(fbts)
                fbts = f.read(4096)
            print 'End session.'
