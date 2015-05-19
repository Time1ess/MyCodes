clear all
clc
READ

%snr2=zeros(1,100);

%for i=1:100
j=dct2(img);
j(abs(j)<26)=0;
k=idct2(j);
K=uint8(k);
snrAFF=snr(ori,double(K));
%snr2(1,i)=snr(ori,K);
%end
figure
%subplot(1,2,1);
imshow(K);
title('DCT³ýÔë');
figure;
%subplot(1,2,2);
imshow(uint8(img));
title('º¬ÔëÉùÍ¼');


snrIMG=snr(ori,img);
