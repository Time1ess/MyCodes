#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-12-01 10:26
# Last modified: 2016-12-01 11:09
# Filename: proxy-1.py
# Description:
import argparse
import logging
import sys

logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

from twisted.internet.protocol import Protocol, ServerFactory, ClientFactory
from twisted.internet.defer import succeed, Deferred


def parse_args():
    parser = argparse.ArgumentParser(
        description='Process to build a poetry server')
    parser.add_argument('--server_host', type=str, dest='server_host',
                        help='Host of the poetry server',
                        default='localhost')
    parser.add_argument('--server_port', type=int, dest='server_port',
                        help='Port to connect to server')
    parser.add_argument('--proxy_port', type=int, dest='proxy_port',
                        help='Port to serve clients')
    parser.add_argument('--iface', type=str, dest='iface',
                        help='interface to listen on',
                        default='localhost')

    args = parser.parse_args()

    return args


class ProxyClientProtocol(Protocol):

    poem = ''

    def dataReceived(self, data):
        self.poem += data

    def connectionLost(self, reason):
        self.poem_received(self.poem)

    def poem_received(self, poem):
        self.factory.poem_finished(poem)


class ProxyClientFactory(ClientFactory):

    protocol = ProxyClientProtocol

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


class PoetryProxyProtocol(Protocol):

    def connectionMade(self):
        self.deferred = self.factory.get_poem()
        self.deferred.addCallback(self.transport.write)
        self.deferred.addCallback(lambda x: self.transport.loseConnection())


class PoetryProxyFactory(ServerFactory):

    protocol = PoetryProxyProtocol
    poem = None

    def __init__(self, server_host, server_port):
        self.server_port = server_port
        self.server_host = server_host

    def get_poem(self):
        if self.poem is not None:
            logging.info('Use poem cache.')
            return succeed(self.poem)

        logging.info('No cache, fetch from server')
        deferred = Deferred()
        deferred.addCallback(self.set_poem)

        factory = ProxyClientFactory(deferred)
        from twisted.internet import reactor

        reactor.connectTCP(self.server_host, self.server_port, factory)
        return deferred

    def set_poem(self, poem):
        self.poem = poem
        return poem


def main():
    args = parse_args()

    factory = PoetryProxyFactory(args.server_host, args.server_port)

    from twisted.internet import reactor

    port = reactor.listenTCP(args.proxy_port or 0, factory,
                             interface=args.iface)

    logging.info('Proxying poem from %s on %s.' % (args.server_port,
                                                   port.getHost()))

    from twisted.internet import reactor

    reactor.run()

if __name__ == '__main__':
    main()
