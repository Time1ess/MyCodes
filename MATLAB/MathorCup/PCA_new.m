clear all
clc

READ
[after,s]=kl(img,53);
snrPCA=snr(ori,after);
snrIMG=snr(ori,img);
