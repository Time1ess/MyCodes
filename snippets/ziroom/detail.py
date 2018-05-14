import os
from datetime import datetime
from time import sleep
from random import choice

import requests

from agents import AGENTS

url = 'http://www.ziroom.com/detail/info'

params = {
    'id': '61155405',
    'house_id': '60185997',
}

headers = {
    'User-Agent': choice(AGENTS),
}

while True:
    resp = requests.get(url, params=params, headers=headers)
    now = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    if resp.status_code != 200:
        print(now, 'Failed')
        sleep(5)
        continue
    try:
        data = resp.json()['data']
        status = data['status']
        price = data['price']
        print(now, status, price)
        if status != 'tzpzz':
            break
    except Exception:
        print(data)
    sleep(10)
cmd = os.system('zsh -c "while true;do;afplay /System/Library/Sounds/Ping.aiff -v 30;done"')
