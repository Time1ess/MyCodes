function accuracy=testMySpamEmails(model)
accuracy=0;
N=1397;
tmp_accu=zeros(1,N);
fileext='.txt';
rightCount=0;
for i=1:N
    file_contents = readFile(['./spam examples/',int2str(i),fileext]);
    word_indices  = processEmail(file_contents);
    x             = emailFeatures(word_indices);
    p = svmPredict(model, x);
    if p==1
        rightCount=rightCount+1;
    end
    accuracy=rightCount/i*1.0;
    

    fprintf('%d----%d-----%0.5f\n',i,rightCount,accuracy);
    tmp_accu(i)=accuracy;
    plot(tmp_accu);
end