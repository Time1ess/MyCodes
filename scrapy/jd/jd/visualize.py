#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-19 10:09
# Last modified: 2017-02-20 15:31
# Filename: visualize.py
# Description:
import matplotlib.pyplot as plt

from plots import plot_all, plot_by, plot_detail, plot_detail_in
from extracters import CommentExtracter, DetailExtracter
from cleaners import ShoeCleaner


def main():
    comments, ccnt = CommentExtracter.extract('small_comments.csv',
                                              cleaner=ShoeCleaner)
    details, dcnt = DetailExtracter.extract()

    # Plot all sizes
    # plot_all(comments, details, 'size', '尺码')
    # Plot all colors
    # plot_all(comments, details, 'color', '颜色')

    # Plot sizes by province
    # plot_by(comments, details, 'user_province', '省份', 'size', '尺码')
    # Plot colors by province
    # plot_by(comments, details, 'user_province', '省份', 'color', '颜色')

    # Plot sizes by user_level
    # plot_by(comments, details, 'user_level', '会员级别', 'size', '尺码')
    # Plot colors by user_level
    # plot_by(comments, details, 'user_level', '会员级别', 'color', '颜色')
    # plot_detail(comments, details, 'size', '尺码', ccnt)
    plot_detail_in(comments, details, 'user_province', '四川', '省份', 'size',
                   '尺码', ccnt)

    plt.show()


if __name__ == '__main__':
    main()
