#!/usr/bin/env python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-10-11 17:21
# Last modified: 2017-10-15 16:58
# Filename: config.py
# Description:
import torch


ENV_NAME = 'CartPole-v0'
EPOCHS = 10000
ITERATIONS = 300
TEST_INTERVAL = 500
TEST_EPOCHS = 100
TEST_ITERATIONS = 200
RELAY_SIZE = 10000
BATCH_SIZE = 128
EPSILON_START = 0.9
EPSILON_END = 0.05
GAMMA = 0.9

use_cuda = torch.cuda.is_available()
ByteTensor = torch.cuda.ByteTensor if use_cuda else torch.ByteTensor
FloatTensor = torch.cuda.FloatTensor if use_cuda else torch.FloatTensor
LongTensor = torch.cuda.LongTensor if use_cuda else torch.LongTensor
