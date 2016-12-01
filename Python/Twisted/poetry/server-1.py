#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-12-01 09:46
# Last modified: 2016-12-01 15:23
# Filename: server-1.py
# Description:
import argparse
import os
import sys
import logging

logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

from twisted.internet.protocol import Protocol, ServerFactory


def parse_args():
    parser = argparse.ArgumentParser(
        description='Process to build a poetry server')
    parser.add_argument('--port', type=int, dest='port',
                        help='Port to serve poetry')
    parser.add_argument('path', metavar='path', type=str,
                        help='Path to a poetry file')
    parser.add_argument('--iface', type=str, dest='iface',
                        help='interface to listen on',
                        default='localhost')

    args = parser.parse_args()

    if not os.path.exists(args.path):
        parser.error('No such file: %s' % args.path)
    return args


class PoetryServerProtocol(Protocol):

    def connectionMade(self):
        logging.info('ConnectionMade by %s' % self.transport.getPeer())
        self.transport.write(self.factory.poem)
        self.transport.loseConnection()


class PoetryServerFactory(ServerFactory):

    protocol = PoetryServerProtocol

    def __init__(self, poem):
        self.poem = poem

    def buildProtocol(self, addr):
        proto = ServerFactory.buildProtocol(self, addr)
        return proto


def main():
    args = parse_args()
    poem = open(args.path, 'rb').read()
    factory = PoetryServerFactory(poem)

    from twisted.internet import reactor

    port = reactor.listenTCP(args.port or 0, factory,
                             interface=args.iface)

    logging.info('Serving %s on %s.' % (args.path, port.getHost()))

    reactor.run()

if __name__ == '__main__':
    main()
