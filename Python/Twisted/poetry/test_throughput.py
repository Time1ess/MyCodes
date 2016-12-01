#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-12-01 13:36
# Last modified: 2016-12-01 14:38
# Filename: test_throughput.py
# Description:
import argparse
import sys
import logging
import time

logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

from twisted.internet.defer import Deferred, DeferredList
from twisted.internet.protocol import Protocol, ClientFactory


def parse_args():
    parser = argparse.ArgumentParser(
        description='Process to download a poem')
    parser.add_argument('times', type=int)
    parser.add_argument('addrs', nargs='*')

    args = parser.parse_args()

    def parse_addrs(addr):
        if ':' not in addr:
            host = '127.0.0.1'
            port = addr
        else:
            host, port = addr.split(':')

        if not port.isdigit():
            parser.error('Ports must be integers.')

        return host, int(port)
    return args.times, map(parse_addrs, args.addrs)


class PoetryClientProtocol(Protocol):

    poem = ''

    def dataReceived(self, data):
        self.poem += data

    def connectionLost(self, reason):
        self.poem_received(self.poem)

    def poem_received(self, poem):
        self.factory.poem_got(poem)


class PoetryClientFactory(ClientFactory):

    protocol = PoetryClientProtocol
    count = 0
    err_count = 0
    suc_count = 0

    def __init__(self, deferred, count):
        self.deferred = deferred
        self.count = count

    def poem_got(self, poem):
        self.suc_count += 1
        self.poem_finished()

    def clientConnectionFailed(self, connector, reason):
        self.err_count += 1
        self.poem_finished()

    def poem_finished(self):
        if self.count == self.err_count + self.suc_count:
            if self.deferred is not None:
                logging.info(
                    'Succeed: %d, Failed: %d, rate: %f %%' % (
                        self.suc_count, self.err_count,
                        100.0 * self.err_count / self.count))
                d, self.deferred = self.deferred, None
                d.callback(None)


def get_poetry(host, port, times):
    d = Deferred()

    factory = PoetryClientFactory(d, times)
    from twisted.internet import reactor
    for i in xrange(times):
        reactor.connectTCP(host, port, factory)
    return d


def main():
    times, args = parse_args()

    ds = []
    for host, port in args:
        d = get_poetry(host, port, times)
        ds.append(d)

    from twisted.internet import reactor
    dlist = DeferredList(ds)
    dlist.addCallback(lambda res: reactor.stop())

    start = time.time()
    reactor.run()
    end = time.time()
    total = end-start
    per = total*1000.0/times
    logging.info('Total Cost: %f sec(s), Per Cost: %f msec(s)' % (total, per))


if __name__ == '__main__':
    main()
