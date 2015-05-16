MyCodes
=======
Codes about my CPP learning and my codes about AOAPC II ACM questions

# Hello World

tags： 测试 Markdown 语法

---
#标题1
##标题2
###标题3
####标题4
正文
...
*斜体*
**粗体**
***斜粗体***



[百度链接](http://www.baidu.com/)

- 无序列表一
- 无序列表二
- 无序列表三

1. 有序列表一
2. 有序列表二

>引用：野火烧不尽，春风吹又生

行内代码块 `f=mv`。(1左边的键)


    代码块，缩进4个空格
    hello world

![图片](https://www.baidu.com/img/bd_logo1.png)

[TOC]

~~删除这段文本~~

这是一个注脚[^footnote1]的样例。
这是一个注脚[^footnote2]的样例。

质能守恒方程可以使用一个很简洁的方程式 $E=mc^2$ 来表达

$$ 表示整行公式：

$$\sum_{i=1}^n a_i=0$$

$$f(x_1,x_2,\ldots,x_n)=x_1^2+x_2^2+\ldots+x_n^2$$

$$\sum_{k=0}^{j-1}{\widehat{\gamma}_{kj}}z_k$$

$$AA^T=[y_1,\ldots,y_{I_2}][y_1,\ldots,y{I_2}]^T=\sum_{j=1}^{I_2} y_j{y_j}^T=US^2U^T$$

$$PMSE=\tfrac{\sum_{j=0}^{N-1}\sum_{k=0}^{M-1}\{Q[f(j,k)]-Q[\widehat{f}(j,k)]\}^2}{M*N*A^2}$$

###非代码示例
```
$sudo apt-get install vim-gnome
```

###代码示例
```cpp
#include <iostream>
using namespace std;
int main()
{
    cout<<"hello world"<<endl;
}
```


###流程图

```flow 
st=>start: Start:>http://www.baidu.com
io=>inputoutput: verification 
op=>operation: Your Operation 
cond=>condition: Yes or No? 
e=>end

st->io->op->cond
cond(yes)->e
cond(no)->io
```

###序列图

```seq 
Alice-->Bob: Hello Bob, how are you? 
Note right of Bob: Bob thinks 
Bob-->Alice: I am good thanks! 
Note left of Alice:Alice gets
```

###表格

|项目|价格|数量|
|:------:|:---:|:---:|
|计算机|$1600|5|
|手机|$12|12|
|管线|$1|234|




[^footnote1]:这是一个*注脚*的**文本**。

[^footnote2]:这是一个*注脚2*的**文本**。