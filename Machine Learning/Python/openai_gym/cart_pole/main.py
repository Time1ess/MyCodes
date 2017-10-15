#!/usr/bin/env python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-10-11 17:16
# Last modified: 2017-10-15 17:16
# Filename: main.py
# Description:
import gym
import torch
from torch import nn
from torch.nn import functional as F
from torch.autograd import Variable
from torch import optim

import config

from model import DQN, Transition


def main():
    env = gym.make(config.ENV_NAME)
    agent = DQN(env)
    optimizer = optim.Adam(agent.parameters(), lr=0.001)
    finished = False

    for epoch in range(config.EPOCHS):
        state = env.reset()
        for step in range(config.ITERATIONS):
            action = agent.get_action(state, 'egreedy')
            next_state, reward, done, _ = env.step(action[0, 0])
            if done:
                reward = -1
            agent.replay_memory.push(Transition(
                config.FloatTensor([state]),
                action,
                config.FloatTensor([reward]),
                config.FloatTensor([next_state]) if not done else None))
            state = next_state
            if len(agent.replay_memory) >= config.BATCH_SIZE:
                batch = agent.replay_memory.sample(config.BATCH_SIZE)
                batch = Transition(*zip(*batch))
                non_final_mask = config.ByteTensor(
                    [s is not None for s in batch.next_state])
                non_final_next_state_batch = Variable(torch.cat([
                    s for s in batch.next_state if s is not None]))

                state_batch = Variable(torch.cat(batch.state),
                                       requires_grad=False)
                action_batch = Variable(torch.cat(batch.action).view(-1, 1),
                                        requires_grad=False)
                reward_batch = Variable(torch.cat(batch.reward),
                                        requires_grad=False)

                q_values = agent(state_batch).gather(1, action_batch)
                s_values = Variable(torch.zeros(config.BATCH_SIZE).type(
                    config.FloatTensor), requires_grad=False)
                s_values[non_final_mask] = agent(
                    non_final_next_state_batch).max(1)[0]
                expected_q_values = config.GAMMA * s_values + reward_batch
                loss = F.smooth_l1_loss(torch.sum(q_values),
                                        torch.sum(expected_q_values))
                optimizer.zero_grad()
                loss.backward()
                optimizer.step()
            if done:
                break
        agent.epsilon = config.EPSILON_START - epoch / config.EPOCHS * (
            config.EPSILON_START - config.EPSILON_END)
        if epoch % config.TEST_INTERVAL == 0:
            sum_reward = 0
            for _epoch in range(config.TEST_EPOCHS):
                epoch_reward = 0
                state = env.reset()
                for step in range(config.TEST_ITERATIONS):
                    # env.render()
                    action = agent.get_action(state)  # Default
                    state, reward, done, _ = env.step(action[0, 0])
                    if done:
                        break
                    epoch_reward += reward
                sum_reward += epoch_reward
            avg_reward = sum_reward / config.TEST_EPOCHS
            print('Epoch: {}, Average Reward: {}'.format(epoch, avg_reward))
            print('Current Epsilon:', agent.epsilon)
            if avg_reward > 195:
                finished = True
        if finished:
            break

    while True:
        state = env.reset()
        round_reward = 0
        for step in range(config.TEST_ITERATIONS):
            env.render()
            action = agent.get_action(state)  # Default
            state, reward, done, _ = env.step(action[0, 0])
            if done:
                break
            round_reward += reward
        print('Round reward:', round_reward)


if __name__ == '__main__':
    main()
