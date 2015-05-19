%origin=imread('d:\MathorCup\ori.bmp');
%image=imread('d:\MathorCup\img.bmp');
%origin=double(rgb2gray(origin));
%image=double(rgb2gray(image));
clear all
clc
READ
[U,S,V]=svd(img);

%AFF=zeros(1,1000);
%for j=1:1000
for i=1:359
    if(S(i,i)<359)
        S(i,i)=0;
    end
end

after=U*S*V';
%imshow(uint8(after));
%hold on
%figure(2)
%imshow(uint8(image));
%a=snr(origin,after);
%b=snr(origin,image);
%AFF(1,j)=snr(origin,after);
%end
AFF=snr(ori,after);
IMG=snr(ori,img);
imshow(uint8(after));
title('SVD³ýÔë');
%IMG1=zeros(1,1200);
%IMG1(1,:)=IMG;
%plot(AFF)
%hold on
%plot(IMG1)
%grid