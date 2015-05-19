clear all
clc

READ

%DWT
[c,l]=wavedec2(img,2,'db4'); 

n=[1,2];% detail levels
p=[10.28,10.08]; % corresponding thresholds

nc_h=wthcoef2('h',c,l,n,p,'s');
X1=waverec2(nc_h,l,'db4');
%figure
%imshow(uint8(X1));

nc_v=wthcoef2('v',nc_h,l,n,p,'s');
X2=waverec2(nc_v,l,'db4');
%figure
%imshow(uint8(X2));

nc_d=wthcoef2('d',nc_v,l,n,p,'s');
A1=waverec2(nc_d,l,'db4');
%figure
%imshow(uint8(X3));

AFFdwt1=snr(ori,X1);
AFFdwt2=snr(ori,X2);
AFFdwt3=snr(ori,A1);

%DCT
j=dct2(img);
j(abs(j)<26)=0;
k=idct2(j);
A2=uint8(k);
AFFdct=snr(ori,double(A2));
%figure
%imshow(uint8(K));



%ÆæÒìÖµ·Ö½â
[U,S,V]=svd(img);
for i=1:359
    if(S(i,i)<359)
        S(i,i)=0;
    end
end
A3=U*S*V';
AFFsvd=snr(ori,A3);
%figure
%imshow(uint8(after));

%PCA
[A4,s]=kl(img,53);

figure
subplot(2,3,1);
imshow(uint8(img));
title('ÔëÉùÍ¼');

subplot(2,3,2);
imshow(A2);
title('DCT');

subplot(2,3,3);
imshow(uint8(A3));
title('SVD');

subplot(2,3,4);
imshow(uint8(X1));
title('DWT-1');

subplot(2,3,5);
imshow(uint8(X2));
title('DWT-2');

subplot(2,3,6);
imshow(uint8(A1));
title('DWT-3');

A2=double(A2);
AFFave=zeros(5,10000);
cnt=1;
for i=50:1:55
    for j=0:1:100
        for k=0:1:100
            for l=100-i-j-k:1:100
            if(l<0)
             continue;
            end
            if(i+j+k+l>100)
                continue;
            end
            A5=double(i)/100.0*A1+double(j)/100.0*A2+double(k)/100.0*A3+double(l)/100.0*A4;
            AFFave(5,cnt)=snr(ori,A5);
            AFFave(1,cnt)=i;
            AFFave(2,cnt)=j;
            AFFave(3,cnt)=k;
            AFFave(4,cnt)=l;
            cnt=cnt+1;
            end
        end
    end
end  

%A4=(A1+A2+A3)/3.0;
%AFFave=snr(ori,A4);