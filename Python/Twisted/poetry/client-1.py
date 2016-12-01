#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-12-01 13:36
# Last modified: 2016-12-01 13:55
# Filename: client-1.py
# Description:
import argparse
import sys
import logging

logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

from twisted.internet.defer import Deferred, DeferredList
from twisted.internet.protocol import Protocol, ClientFactory

def parse_args():
    parser = argparse.ArgumentParser(
        description='Process to download a poem')
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
    return map(parse_addrs, args.addrs)


class PoetryClientProtocol(Protocol):

    poem = ''
    
    def dataReceived(self, data):
        self.poem += data

    def connectionLost(self, reason):
        self.poem_received(self.poem)

    def poem_received(self, poem):
        self.factory.poem_finished(poem)


class PoetryClientFactory(ClientFactory):
    
    protocol = PoetryClientProtocol

    def __init__(self, deferred):
        self.deferred = deferred

    def poem_finished(self, poem):
        if self.deferred is not None:
            d, self.deferred = self.deferred, None
            d.callback(poem)

    def clientConnectionFailed(self, connector, reason):
        if self.deferred is not None:
            d, self.deferred = self.deferred, None
            d.errback(reason)


def get_poetry(host, port):
    d = Deferred()

    def print_poem(poem):
        print poem

    d.addCallback(print_poem)
    factory = PoetryClientFactory(d)
    from twisted.internet import reactor
    reactor.connectTCP(host, port, factory)
    return d


def main():
    args = parse_args()

    ds = []
    for host, port in args:
        d = get_poetry(host, port)
        ds.append(d)

    from twisted.internet import reactor
    dlist = DeferredList(ds, consumeErrors=True)
    dlist.addCallback(lambda x: reactor.stop())

    reactor.run()


if __name__ == '__main__':
    main()
