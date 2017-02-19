#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-19 10:09
# Last modified: 2017-02-19 17:50
# Filename: visualize.py
# Description:
import matplotlib.pyplot as plt

from clean_comments import extract as comment_extract
from clean_details import extract as detail_extract
from plots import plot_all, plot_by


def main():
    comments, ccnt = comment_extract()
    details, dcnt = detail_extract()

    # Plot all sizes
    plot_all(comments, details, 'size', '尺码')
    # Plot all colors
    plot_all(comments, details, 'color', '颜色')

    # Plot sizes by province
    plot_by(comments, details, 'user_province', '省份', 'size', '尺码')
    # Plot colors by province
    plot_by(comments, details, 'user_province', '省份', 'color', '颜色')

    # Plot sizes by user_level
    plot_by(comments, details, 'user_level', '会员级别', 'size', '尺码')
    # Plot colors by user_level
    plot_by(comments, details, 'user_level', '会员级别', 'color', '颜色')

    plt.show()


if __name__ == '__main__':
    main()
