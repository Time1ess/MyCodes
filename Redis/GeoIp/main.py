#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-04 11:03
# Last modified: 2017-05-04 14:25
# Filename: main.py
# Description:
import json
import csv

import redis


BLOCK_FILE = 'data/GeoLiteCity-Blocks.csv'
CITY_FILE = 'data/GeoLiteCity-Location.csv'


def ip_to_score(ip_addr):
    score = 0
    for v in ip_addr.split('.'):
        score = score * 256 + int(v, 10)
    return score


def import_ips_to_redis(conn, filename):
    if conn.exists('ip2cityid:'):
        return
    csv_file = csv.reader(open(filename))
    for count, row in enumerate(csv_file):
        start_ip = row[0] if row else ''
        if 'i' in start_ip.lower():
            continue
        if '.' in start_ip:
            start_ip = ip_to_score(start_ip)
        elif start_ip.isdigit():
            start_ip = int(start_ip, 10)
        else:
            continue

        city_id = row[2] + '_' + str(count)
        conn.zadd('ip2cityid:', city_id, start_ip)


def import_cities_to_redis(conn, filename):
    if conn.exists('cityid2city:'):
        return
    csv_file = csv.reader(open(filename))
    for count, row in enumerate(csv_file):
        if len(row) < 4 or not row[0].isdigit():
            continue
        city_id = row[0]
        country = row[1]
        region = row[2]
        city = row[3]
        conn.hset('cityid2city:', city_id,
                  json.dumps([city, region, country]))


def find_city_by_ip(conn, ip_addr):
    if isinstance(ip_addr, str):
        ip_addr = ip_to_score(ip_addr)
    city_id = conn.zrevrangebyscore(
        'ip2cityid:', ip_addr, 0, start=0, num=1)
    if not city_id:
        return None
    city_id = city_id[0].split('_')[0]
    return json.loads(conn.hget('cityid2city:', city_id))


def tests(conn, ip_list):
    for ip in ip_list:
        print(find_city_by_ip(conn, ip))


def main():
    conn = redis.Redis(decode_responses=True)
    import_ips_to_redis(conn, BLOCK_FILE)
    import_cities_to_redis(conn, CITY_FILE)
    ip_list = ['202.118.67.200', '59.46.92.105', '8.8.8.8']
    tests(conn, ip_list)


if __name__ == '__main__':
    main()
