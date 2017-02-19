#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-19 15:35
# Last modified: 2017-02-19 17:47
# Filename: plots.py
# Description:
from functools import partial
from collections import defaultdict
from random import shuffle

import matplotlib.pyplot as plt
import numpy as np

from utils import colors as color_keys, LinesIndicator


base_colors = {key: 0 for key in color_keys}
colors = list(plt.cm.rainbow(np.linspace(0, 1, 10)))
shuffle(colors)


def calculate_bar_data(inputs, topn=4, thres=0.01):
    if len(inputs) < topn:
        return {'total_cnt': 0, 'data': None}
    total_cnt = sum(x for x in inputs.values())
    _inputs = defaultdict(int)
    for key, cnt in inputs.items():
        if cnt / total_cnt >= thres:
            _inputs[key] += cnt
        else:
            _inputs['其他'] += cnt
    items = list(_inputs.items())
    items.sort(key=lambda x: x[1], reverse=True)

    return {'total_cnt': total_cnt, 'data': items[:topn]}


def subplot_bar(inputs, plotnum, target, title='', thres=0.01, topn=4):
    """
    Plot bar chart with inputs.

    inputs[dict]: keys will be labels in chart, values are also [dict] which
        keys are second labels and values will be used to calculate.
    plotnum[int]: For add_subplot().
    target[Firgure]: Which figure should be ploted to.
    title[str]: Pie chart title.
    thres[float, 0 ~ 1]: any value in inputs will be categorized to 'other'
        if value / sum(valus) < thres.
    """
    items = [(key, calculate_bar_data(value, topn, thres))
             for key, value in inputs.items()]
    items.sort(key=lambda x: x[1]['total_cnt'], reverse=True)
    items = [x for x in items if x[1]['total_cnt'] > 0]

    # provinces
    labels = [key for key, _ in items]
    prov_cnt = len(items)

    # e.g: {'total_cnt': *, 'data': [(35, 200), (26, 300)]}
    values = (x[1]['total_cnt'] for x in items)

    p = target.add_subplot(plotnum)
    for idx in range(topn):
        x = [k + (idx - topn / 2) * topn / 20 for k in range(1, 1 + prov_cnt)]
        vals = []
        _labels = []
        for _, value_dict in items:
            label, val = value_dict['data'][idx]
            _labels.append(label)
            vals.append(val)
        p.bar(x, vals, width=topn/20, color=colors)
        for hor, vert, label in zip(x, vals, _labels):
            p.text(hor, vert, '{}'.format(label),
                   ha='left', va='bottom', fontsize='small')

    p.set_title(title+'(有效用户数:{})'.format(sum(values)))
    p.set_xticks(range(1, 1+prov_cnt))
    p.set_xticklabels(labels, rotation=45, size=10)


def subplot_pie(inputs, plotnum, target, title='', thres=0.01):
    """
    Plot pie chart with inputs.

    inputs[dict]: Keys will be labels in pie chart, values will be used to
        calculate angles.
    plotnum[int]: For add_subplot().
    target[Firgure]: Which figure should be ploted to.
    title[str]: Pie chart title.
    thres[float, 0 ~ 1]: any value in inputs will be categorized to 'other'
        if value / sum(valus) < thres.
    """
    total_cnt = sum(x for x in inputs.values())
    _inputs = defaultdict(int)
    for key, cnt in inputs.items():
        if cnt / total_cnt >= thres:
            _inputs[key] += cnt
        else:
            _inputs['其他'] += cnt
    items = list(_inputs.items())
    items.sort(key=lambda x: x[1], reverse=True)
    indices = ['{}'.format(key) for key, _ in items]
    values = [count for _, count in items]

    p = target.add_subplot(plotnum)
    p.pie(values, labels=indices, colors=colors, autopct='%3.1f%%',
          startangle=90)
    p.set_title(title+'(有效用户数:{})'.format(sum(values)))
    p.title.set_position([0.5, 1.1])


def plot_all(comments, details, info_key, info_title, ccnt=None):
    f = plt.figure(dpi=100)
    maps = defaultdict(partial(defaultdict, int))
    if ccnt is None:
        ccnt = len(comments)

    indicate = LinesIndicator(ccnt, title='Plot all:'+info_key)
    for comment in comments:
        indicate()
        iid = comment['iid']
        _key = comment[info_key]
        detail = details.get(iid, None)
        if detail is None or not _key:
            continue
        sex = detail['sex']

        if isinstance(_key, list):
            for key in _key:
                maps['所有'][key] += 1
                maps[sex][key] += 1
        else:
            maps['所有'][_key] += 1
            maps[sex][_key] += 1
    indicate(0)

    for idx, (key, value) in enumerate(maps.items()):
        subplot_pie(value, 221+idx, f, '{}鞋{}分布'.format(key, info_title))


def plot_by(comments, details, by_key, by_title, info_key,
            info_title, ccnt=None):
    maps = defaultdict(partial(defaultdict, partial(defaultdict, int)))
    if ccnt is None:
        ccnt = len(comments)

    indicate = LinesIndicator(ccnt, title='Plot by:'+by_key)
    for comment in comments:
        indicate()
        iid = comment['iid']
        _key = comment[info_key]
        _by_key = comment[by_key]
        detail = details.get(iid, None)
        if detail is None or not _by_key:
            continue
        sex = detail['sex']
        if not _key:
            continue
        if isinstance(_key, list):
            for key in _key:
                maps['所有'][_by_key][key] += 1
                maps[sex][_by_key][key] += 1
        else:
            maps['所有'][_by_key][_key] += 1
            maps[sex][_by_key][_key] += 1
    indicate(0)

    for key, value in maps.items():
        subplot_bar(value, 111, plt.figure(dpi=100),
                    '{}鞋{}按{}分布'.format(key, info_title, by_title))
