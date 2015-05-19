
%采用 db4的两层小波分解，并从三个方向上对小波系数进行硬阈值量化，
%为了方便起见，阈值的选择采用手动设定的方法，
%最后对图像进行小波重构，后面部分会给出重构的效果图和相应的峰值信噪比。
clear;
clc;
%X=imread('ori.bmp');
%X=rgb2gray(X);
%figure(1);
%subplot(121);
%imshow(X);
%title('原始图像');
%X=double(X);

%XX=imread('img.bmp'); 
%XX=rgb2gray(XX);
%subplot(122);
%imshow(uint8(XX));
%title('含噪图像');
READ

[c,l]=wavedec2(img,2,'db4'); 

n=[1,2];% detail levels
p=[10.28,10.08]; % corresponding thresholds
%N and T must be of the same length. The vector N must be such that 1 ≤ N(i) ≤ size(l,1)-2.
figure(2);

nc_h=wthcoef2('h',c,l,n,p,'h');

X1=waverec2(nc_h,l,'db4');
subplot(131);
imshow(uint8(X1));
title('第一次消噪后的图像'); 
 

nc_v=wthcoef2('v',nc_h,l,n,p,'h');

X2=waverec2(nc_v,l,'db4');
subplot(132);
imshow(uint8(X2));
title('第二次消噪后的图像');
 

nc_d=wthcoef2('d',nc_v,l,n,p,'h');

X3=waverec2(nc_d,l,'db4');
%subplot(133);
figure
imshow(uint8(X3));
title('DWT(db4小波)除噪');
 
snrIMG=snr(ori,img);
snrAFF1=snr(ori,X1);
snrAFF2=snr(ori,X2);
snrAFF3=snr(ori,X3);