function [V,D,iter]=eigcj(A,tol,itermax)
% 古典Jaccobi方法计算实对称矩阵A的特征值和向量
% (eigen value and vector of classical Jaccobi algorithm)
%
% 参数说明
% A：实对称矩阵
% tol：精度，非对角元素平方和
% itermax：最大迭代次数
% V：特征值
% D：特征向量
% iter：实际迭代次数
%
% 实例说明
% A=[-12 3 3;3 1 -2;3 -2 7];
% [V,D,iter]=eigcj(A,1e-10,20)
% [V2,D2]=eig(A) % 使用MATLAB自带eig函数进行验证
%
% 基础知识
% 1、对于实对称矩阵A，古典雅克比算法必定收敛矩阵的全部特征根
% 2、实对称矩阵的特征值均为实数，且存在标准正交的特征向量系
% 3、对任意实对称矩阵A，总存在正交矩阵Q，使得QAQ'=diag(λ1,λ2,...)
%    λ为A的特征根，Q各列对应其特征向量
% 4、设A为实对称矩阵，Q为正交矩阵，则||A||=||QA||=||AQ||=||QAQ'||=特征根平方和
%    其中||X||表示X的F范数
%
% 算法说明
% 0、赋初值H=I，A0=A
% 1、选非对角线主元素|a(p,q)|=max(|a(i,j)|)
% 2、构造Givens矩阵R
% 3、对主元素a(p,q)进行Givens变换
% 3.1 更新H=R*H
% 3.2 更新A=H*A0*H'
% 4、计算SA，矩阵A的非对角元素平方和
% 5、SA是否到达指定精度，是否达到最大迭代次数
% 6、否，继续循环；是，退出
%
% 参考资料
% 封建湖《数值分析原理》.2005年7月.科学出版社.Page238-243
%
[m,n]=size(A);
H=eye(m,n);
A0=A;
SA=sum(A(:).^2)-sum(diag(A).^2);
iter=0;
while SA>tol && iter<itermax
    iter=iter+1;
    % 选主元素a(p,q)
    T=triu(A,1);
    [tmp,idx]=max(abs(T(:)));
    % 计算Givens矩阵中的cos，sin值
    [p,q]=ind2sub([m,n],idx);
    % 计算非对角元素平方和SA
    SA=SA-2*A(p,q).^2;
    if A(p,p)==A(q,q)
        cos=sqrt(2)/2;
        sin=sign(A(p,q))*cos;
    else
        d=(A(p,p)-A(q,q))/(2*A(p,q));
        tan=sign(d)/(abs(d)+sqrt(d^2+1));
        cos=1/sqrt(1+tan^2);
        sin=tan*cos;
    end
    % 计算Givens矩阵
    R=eye(m,n);
    R(p,p)=cos;
    R(p,q)=sin;
    R(q,p)=-sin;
    R(q,q)=cos;
    % 更新H矩阵
    H=R*H;
    % 更新A矩阵
    A=H*A0*H';
end
V=diag(A); % 特征根
D=H'; % 特征向量