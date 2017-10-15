#!/usr/bin/env python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-10-11 17:22
# Last modified: 2017-10-15 17:03
# Filename: model.py
# Description:
import random
from collections import deque, namedtuple

import numpy as np

from torch import nn
from torch.nn import functional as F
from torch.autograd import Variable
from torchvision import transforms as T
from PIL import Image

import config


Transition = namedtuple('Transition', ('state', 'action', 'reward',
                                       'next_state'))


class ReplayMemory(object):
    def __init__(self, maxlen, *args, **kwargs):
        self.maxlen = maxlen
        self.index = 0
        self.memory = []
        super(ReplayMemory, self).__init__(*args, **kwargs)

    def push(self, x):
        if len(self) < self.maxlen:
            self.memory.append(None)
        self.memory[self.index] = x
        self.index = (self.index + 1) % self.maxlen

    def sample(self, size):
        return random.sample(self.memory, size)

    def __len__(self):
        return len(self.memory)


class DQN(nn.Module):
    def __init__(self, env, epsilon=config.EPSILON_START):
        super(DQN, self).__init__()
        self.env = env
        self.replay_memory = ReplayMemory(config.RELAY_SIZE)
        self.action_dim = env.action_space.n
        self.epsilon = self.init_epsilon = 0.5

        self.fc1 = nn.Linear(4, 256)
        self.fc2 = nn.Linear(256, 2)

    def forward(self, x):
        x = F.relu(self.fc1(x))
        x = self.fc2(x)
        return x

    def _best_action(self, state):
        q_val = self(Variable(config.FloatTensor([state]), volatile=True))
        best_action = q_val.data.max(1)[1].view(1, 1)
        return best_action

    def _egreedy_action(self, state):
        best_action = self.get_action(state)
        if random.random() <= self.epsilon:
            best_action = config.LongTensor(
                [[random.randint(0, self.action_dim - 1)]])
        return best_action

    def get_action(self, state, method='best'):
        action_func = getattr(self, '_{}_action'.format(method), None)
        if not action_func:
            raise ValueError('Wrong action function')
        action = action_func(state)
        return action
