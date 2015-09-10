function plotLCWithRSExamples(X,y,Xval,yval,lambda)


X_size=size(X,1);
Xval_size=size(Xval,1);
setsize=min(X_size,Xval_size);

error_train=zeros(setsize,1);
error_val=zeros(setsize,1);

for i=1:setsize
    trainnum=randperm(X_size);
    validationnum=randperm(Xval_size);
    
    X_temp=X(trainnum(1:i),:);
    y_temp=y(trainnum(1:i));
    
    Xval_temp=Xval(validationnum(1:i),:);
    yval_temp=yval(validationnum(1:i));
    
    [theta] = trainLinearReg(X_temp,y_temp, lambda);
    
    error_train(i) = linearRegCostFunction(X_temp,y_temp, theta, 0);
    error_val(i) = linearRegCostFunction(Xval_temp, yval_temp, theta, 0);
    
end

plot(error_train);
hold on
plot(error_val);
axis([0 13 0 100]);
hold off



end