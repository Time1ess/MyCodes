#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-10 14:17
# Last modified: 2016-08-18 15:47
# Filename: treepredict.py
# Description:
__metaclass__ = type
from PIL import Image, ImageDraw


my_data = [
    ['slashdot', 'USA', 'yes', 18, 'None'],
    ['google', 'France', 'yes', 23, 'Premium'],
    ['digg', 'USA', 'yes', 24, 'Basic'],
    ['kiwitobes', 'France', 'yes', 23, 'Basic'],
    ['google', 'UK', 'no', 21, 'Premium'],
    ['(direct)', 'New Zealand', 'no', 12, 'None'],
    ['(direct)', 'UK', 'no', 21, 'Basic'],
    ['google', 'USA', 'no', 24, 'Premium'],
    ['slashdot', 'France', 'yes', 19, 'None'],
    ['digg', 'USA', 'no', 18, 'None'],
    ['google', 'UK', 'no', 18, 'None'],
    ['kiwitobes', 'UK', 'no', 19, 'None'],
    ['digg', 'New Zealand', 'yes', 12, 'Basic'],
    ['slashdot', 'UK', 'no', 21, 'None'],
    ['google', 'UK', 'yes', 18, 'Basic'],
    ['kiwitobes', 'France', 'yes', 19, 'Basic']]


class DecisionNode:
    def __init__(self, col=-1, value=None, results=None,
                 tb=None, fb=None):
        self.col = col
        self.value = value
        self.results = results
        self.tb = tb
        self.fb = fb


def divide_set(rows, column, value):
    split_function = None
    if isinstance(value, int) or isinstance(value, float):
        split_function = lambda row: row[column] >= value
    else:
        split_function = lambda row: row[column] == value

    set1 = [row for row in rows if split_function(row)]
    set2 = [row for row in rows if not split_function(row)]

    return (set1, set2)


def unique_counts(rows):
    results = {}
    for row in rows:
        r = row[len(row)-1]
        results.setdefault(r, 0)
        results[r] += 1
    return results


def gini_impurity(rows):
    total = len(rows)
    counts = unique_counts(rows)
    imp = 0
    for k1 in counts:
        p1 = float(counts[k1])/total
        for k2 in counts:
            if k1 == k2:
                continue
            p2 = float(counts[k2])/total
            imp += p1*p2
    return imp


def entropy(rows):
    from math import log
    log2 = lambda x: log(x)/log(2)
    results = unique_counts(rows)
    ent = 0.0
    for r in results.values():
        p = float(r)/len(rows)
        ent = ent-p*log2(p)
    return ent


def build_tree(rows, scoref=entropy):
    if len(rows) == 0:
        return DecisionNode()
    current_score = scoref(rows)

    best_gain = 0.0
    best_criteria = None
    best_sets = None

    column_count = len(rows[0])-1
    for col in xrange(0, column_count):
        column_values = {}
        for row in rows:
            column_values[row[col]] = 1
        for value in column_values:
            set1, set2 = divide_set(rows, col, value)

            p = float(len(set1))/len(rows)
            gain = current_score - p*scoref(set1)-(1-p)*scoref(set2)
            if gain > best_gain and len(set1) > 0 and len(set2) > 0:
                best_gain = gain
                best_criteria = (col, value)
                best_sets = (set1, set2)
    if best_gain > 0:
        true_branch = build_tree(best_sets[0])
        false_branch = build_tree(best_sets[1])
        return DecisionNode(col=best_criteria[0], value=best_criteria[1],
                            tb=true_branch, fb=false_branch)
    else:
        return DecisionNode(results=unique_counts(rows))


def print_tree(tree, indent=' '):
    if tree.results is not None:
        print str(tree.results)
    else:
        print str(tree.col)+':'+str(tree.value)+'? '

        print indent+'T->',
        print_tree(tree.tb, indent+'  ')
        print indent+'F->',
        print_tree(tree.fb, indent+'  ')


def get_width(tree):
    if tree.tb is None and tree.fb is None:
        return 1
    return get_width(tree.tb)+get_width(tree.fb)


def get_depth(tree):
    if tree.tb is None and tree.fb is None:
        return 0
    return max(get_depth(tree.tb), get_depth(tree.fb))+1


def draw_tree(tree, jpeg='tree.jpg'):
    w = get_width(tree)*100
    h = get_depth(tree)*100+120

    img = Image.new('RGB', (w, h), (255, 255, 255))
    draw = ImageDraw.Draw(img)

    draw_node(draw, tree, w/2, 20)
    img.save(jpeg, 'JPEG')


def draw_node(draw, tree, x, y):
    if tree.results is None:
        w1 = get_width(tree.fb)*100
        w2 = get_width(tree.tb)*100

        left = x-(w1+w2)/2
        right = x+(w1+w2)/2

        draw.text((x-20, y-10), str(tree.col)+':'+str(tree.value), (0, 0, 0))

        draw.line((x, y, left+w1/2, y+100), fill=(255, 0, 0))
        draw.line((x, y, right-w2/2, y+100), fill=(255, 0, 0))

        draw_node(draw, tree.fb, left+w1/2, y+100)
        draw_node(draw, tree.tb, right-w2/2, y+100)
    else:
        txt = ' \n'.join(['%s:%d' % v for v in tree.results.items()])
        draw.text((x-20, y), txt, (0, 0, 0))


def classify(observation, tree):
    if tree.results is not None:
        return tree.results
    else:
        v = observation[tree.col]
        branch = None
        if isinstance(v, int) or isinstance(v, float):
            if v >= tree.value:
                branch = tree.tb
            else:
                branch = tree.fb
        else:
            if v == tree.value:
                branch = tree.tb
            else:
                branch = tree.fb
        return classify(observation, branch)


def prune(tree, min_gain):
    if tree.tb.results is None:
        prune(tree.tb, min_gain)
    if tree.fb.results is None:
        prune(tree.fb, min_gain)

    if tree.tb.results is not None and tree.fb.results is not None:
        tb, fb = [], []
        for v, c in tree.tb.results.items():
            tb += [[v]]*c
        for v, c in tree.fb.results.items():
            fb += [[v]]*c
        delta = entropy(tb+fb)-(entropy(tb)+entropy(fb))/2
        if delta < min_gain:
            tree.tb, tree.fb = None, None
            tree.results = unique_counts(tb+fb)


def md_classify(observation, tree):
    if tree.results is not None:
        return tree.results
    else:
        v = observation[tree.col]
        if v is None:
            tr, fr = md_classify(observation, tree.tb),\
                md_classify(observation, tree.fb)
            tc = sum(tr.values())
            fc = sum(fr.values())
            tw = float(tc)/(tc+fc)
            fw = float(fc)/(tc+fc)
            result = {}
            for k, v in tr.items():
                result[k] = v*tw
            for k, v in fr.items():
                result.setdefault(k, 0)
                result[k] += v*fw
            return result
        else:
            if isinstance(v, int) or isinstance(v, float):
                if v >= tree.value:
                    branch = tree.tb
                else:
                    branch = tree.fb
            else:
                if v == tree.value:
                    branch = tree.tb
                else:
                    branch = tree.fb
            return md_classify(observation, branch)


def variance(rows):
    if len(rows) == 0:
        return 0
    data = [float(row[len(row)-1]) for row in rows]
    mean = sum(data)/len(data)
    var = sum([(d-mean)**2 for d in data])/len(data)
    return var
