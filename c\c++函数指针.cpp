
#include <iostream> 
#include <string> 
using namespace std; 

int test(int a); 

int main(int argc,char* argv[]) 
{ 
cout<<test<<endl;//显示函数地址 
int (*fp)(int a); 
fp=test;//将函数test的地址赋给函数学指针fp 
cout<<fp(5)<<"|"<<(*fp)(10)<<endl; 
//上面的输出fp(5),这是标准c++的写法,(*fp)(10)这是兼容c语言的标准写法,两种同意,但注意区分,避免写的程序产生移植性问题! 
cin.get(); 
} 
int test(int a) 
{ 
return a; 
}

//typedef定义可以简化函数指针的定义，在定义一个的时候感觉不出来，但定义多了就知道方便了，上面的代码改写成如下的形式：

#include <iostream> 
#include <string> 
using namespace std; 

int test(int a); 

int main(int argc,char* argv[]) 
{ 
cout<<test<<endl; 
typedef int (*fp)(int a);//注意,这里不是生命函数指针,而是定义一个函数指针的类型,这个类型是自己定义的,类型名为fp 
fp fpi;//这里利用自己定义的类型名fp定义了一个fpi的函数指针! 
fpi=test; 
cout<<fpi(5)<<"|"<<(*fpi)(10)<<endl; 
cin.get(); 
} 

int test(int a) 
{ 
return a; 
}
