import os.path as osp
import pickle

import math
from random import choice

from agents import AGENTS

import requests

min_lng = 116.322535
max_lng = 116.345753
cen_lng = (min_lng + max_lng) / 2
min_lat = 39.981906
max_lat = 39.998476
cen_lat = (min_lat + max_lat) / 2
tar_lng = 116.333222
tar_lat = 39.990475
params = {
    'min_lng': min_lng,
    'max_lng': max_lng,
    'min_lat': min_lat,
    'max_lat': max_lat,
    'clng': cen_lng,
    'clat': cen_lat,
    'zoom': 17,
    'p': 1,  # Page
    'type': '6|7',  # 6: 2 rooms, 7: 3 rooms
    # 'leasetype': 2,  # 1: Day, 2: Year
}
headers = {
    'User-Agent': choice(AGENTS),
}
api_url = 'http://www.ziroom.com/map/room/list'


def fetch_data(params=params, headers=headers, **kwargs):
    resp = None
    params.update(kwargs)
    while resp is None:
        headers['User-Agent'] = choice(AGENTS)
        resp = requests.get(api_url, params=params, headers=headers)
        if resp.status_code == 200:
            jd = resp.json()
            if jd['code'] == 200:
                return jd['data']
        resp = None


def dist(lat1, lon1, lat2, lon2):
    lat1 = lat1 * math.pi / 180
    lon1 = lon1 * math.pi / 180
    lat2 = lat2 * math.pi / 180
    lon2 = lon2 * math.pi / 180
    hsinX = math.sin((lon1 - lon2) * 0.5)
    hsinY = math.sin((lat1 - lat2) * 0.5)
    h = hsinY * hsinY + (math.cos(lat1) * math.cos(lat2) * hsinX * hsinX)
    return 2 * math.atan2(math.sqrt(h), math.sqrt(1 - h)) * 6367000


class Room(object):
    full_fmt = '<Room: 价格:{:5d} 朝向:{:4s} 面积:{:5.2f} 距离:{:4d} '\
               '小区: {:10s} 楼层:{:>2d}/{:>2d} 阳台:{:1d} 厅室:{:1d} '\
               '卧室:{:1d} 链接: http:{:40s} 特点:{:20s} 状态:{:s}>'
    short_fmt = '<Room: 价格:{:5d} 朝向:{:4s} 面积:{:5.2f} 楼层:{:>2d}/{:>2d}>'

    def __init__(self, room):
        self.id = int(room['id'])
        self.status = '就绪' if room['room_status'] == 'dzz' else '不可用'
        self.price = room['sell_price']
        self.facing = room['house_facing']
        self.name = room['name']
        self.tag = room['style_tag']['name']
        self.area = room['usage_area']
        self.floor = int(room['floor'])
        self.floor_total = int(room['floor_total'])
        self.balcony = True if room['balcony_exist'] == 1 else False
        self.parlor = room['house_parlor']
        self.bedrooms = room['house_bedroom']
        self.url = room['url']
        self.resblock = room['resblock_name']
        self.resblock_id = room['resblock_id']
        self.longitude = room['longitude']
        self.latitude = room['latitude']
        self.dist = int(dist(self.latitude, self.longitude, tar_lat, tar_lng))

    def __str__(self):
        return self.full_fmt.format(
            self.price, self.facing, self.area, self.dist, self.resblock,
            self.floor, self.floor_total,
            self.balcony, self.parlor, self.bedrooms,
            self.url, self.tag, self.status)

    def __hash__(self):
        return self.id

    def __eq__(self, other):
        return self.id == other.id

    def __repr__(self):
        return self.short_fmt.format(self.price, self.facing, self.area,
                                     self.floor, self.floor_total)


rooms = set()
data = fetch_data()
if data:
    total_page = data['pages']
    total = data['total']
    rooms = rooms | set(Room(r) for r in data['rooms'])
    for p in range(1, total_page + 1):
        data = fetch_data(params, p=p)
        if data:
            rooms = rooms | set(Room(r) for r in data['rooms'])
processed = set()
for room in rooms:
    if room.resblock_id in processed:
        continue
    data = fetch_data(params, resblock_id=room.resblock_id, p=1)
    processed.add(room.resblock_id)
    if data:
        rooms = rooms | set(Room(r) for r in data['rooms'])


def custom_filter(room):
    if room.price > 5200:  # 不要超过5200房间
        return False
    if room.floor_total <= 6 and room.floor > 3:  # 不要无电梯的高层房间
        return False
    return True


def custom_sort(room):
    """Lower priority rank higher."""
    pri = room.price / room.area  # 单位面积价格, 低优先
    if room.status == '就绪':
        pri -= 50  #  就绪优先
    prefered_facing = ['南', '东']
    for facing in prefered_facing:
        pri -= 10 * room.facing.count(facing)  # 东,南向优先
    if room.resblock in ('清华园', '华清嘉园'):
        pri += 10  # 尽量不要老旧小区
    if room.bedrooms < 3:
        pri -= 10  # 二居室优先
    if room.dist > 1200:
        pri += 20  # 尽量不要远的房间
    if '拿铁' in room.tag:  # 尽量不要粉色系房间
        pri += 15
    return pri


rooms = [room for room in rooms if custom_filter(room)]
rooms.sort(key=custom_sort)
for idx, room in enumerate(rooms, 1):
    print(idx, room)
