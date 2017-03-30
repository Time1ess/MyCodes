#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-30 16:47
# Last modified: 2017-03-30 18:22
# Filename: bath.py
# Description:
import sys
from workflow import Workflow

from core import get_bath_data


def main(wf):
    data = wf.cached_data('bath_data', get_bath_data, max_age=10)
    for title, info in data:
        wf.add_item(title+': '+info, '')

    wf.send_feedback()


if __name__ == '__main__':
    wf = Workflow()
    sys.exit(wf.run(main))
