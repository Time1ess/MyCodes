clear all
clc
img=imread('img.bmp');
img=double(rgb2gray(img));
ori=imread('ori.bmp');
ori=double(rgb2gray(ori));