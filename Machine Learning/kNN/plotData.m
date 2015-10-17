clear all
clc
data=load('data.txt');
class0=data(find(data(:,3)==0),1:2);
class1=data(find(data(:,3)==1),1:2);
class2=data(find(data(:,3)==2),1:2);
class3=data(find(data(:,3)==3),1:2);

scatter(class0(:,1),class0(:,2))
hold on;
scatter(class1(:,1),class1(:,2),'d');
scatter(class2(:,1),class2(:,2),'s');
scatter(class3(:,1),class3(:,2),'v');
axis([0 4 0 4]);