#!/usr/bin/python
# coding:UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-04-09 11:19
# Last modified: 2016-04-09 14:19
# Filename: solution.py
# Description:
from math import sqrt, floor, log
from random import randint


def xn_mod_p2(x, n, p):
    res = 1
    n_bin = bin(n)[2:]
    for i in range(0, len(n_bin)):
        res = res**2 % p
        if n_bin[i] == '1':
            res = res * x % p
    return res


def miller_rabin_witness(a, p):
    if p == 1:
        return False
    if p == 2:
        return True
    n = p - 1
    t = int(floor(log(n, 2)))
    u = 1
    while t > 0:
        u = n / 2**t
        if n % 2**t == 0 and u % 2 == 1:
            break
        t = t - 1
    b1 = b2 = xn_mod_p2(a, u, p)
    for i in range(1, t+1):
        b2 = b1**2 % p
        if b2 == 1 and b1 != 1 and b1 != (p-1):
            return False
        b1 = b2
    if b1 != 1:
        return False
    return True


def prime_test_miller_rabin(p, k):
    while k > 0:
        a = randint(1, p - 1)
        if not miller_rabin_witness(a, p):
            return False
        k = k - 1
    return True


def is_prime(u):
    if u <= 1:
        return False
    if u == 2:
        return True
    if u % 2 == 0:
        return False
    i = 3
    while i * i <= u:
        if u % i == 0:
            return False
        i += 2
    return True


def jamcoin(N):
    jam_base_str = '0b1'+(N-2)*'0'+'1'
    cnt = 0
    while True:
        flag = True
        ans = bin(2*cnt + int(jam_base_str, base=2))[2:]
        for b in xrange(2, 11):
            tmp = int(ans, base=b)
            # if is_prime(tmp):
            if prime_test_miller_rabin(tmp, 10):
                flag = False
                break
        if flag:
            yield ans
        cnt += 1


def divisor(val):
    for i in xrange(2, int(sqrt(val)+1)):
        if val % i == 0:
            yield i
        if i > 1e5:
            yield None
    yield None

N = 32
J = 500
print 'Case #1:'
j = jamcoin(N)
for i in xrange(J):
    jm = j.next()
    divisors = []
    ans = 2
    legitimate = True
    for i in xrange(2, 11):
        ans_gen = divisor(int(jm, base=i))
        while True:
            ans = ans_gen.next()
            if not ans:
                legitimate = False
                break
            else:
                divisors.append(ans)
                break
        if not legitimate:
            continue
    print jm,
    for i in divisors:
        print ' ', i,
    print
