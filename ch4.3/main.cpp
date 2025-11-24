/**
 *  《通过std::enable_if禁用模板》
 * 1.从C++11开始，标准库引入了一个工具模板std::enable_if，用于在给定编译时(compile-time)条件下忽略函数模板。例如，我们定义一个例1中的模板is32bit，
 *   当表达式“sizeof(T) >= 4”的结果为false时，模板is32bit将被编译器忽略，相反，如果结果为true，那么该模板将被展开为：
*      void is32bit(){
*      }
*  std::enable_if是一个类型萃取(type tarit)，作用是计算作为它的第一个模板参数传递的一个编译时表达式的结果，并且根据该结果产生如下作用：
*     a.如果表达式为true，并且没有传递第二个模板参数，那么std::enable_if::type将表达为void；其他情况下，type将表达为第二个模板参数
*     b.如果表达式为false，那么type将不会被定义，导致一个被称为SFINAE(替换失败不是一个错误)的模板特性生效，该std::enable_if表达式存在的模板将被编译器忽略，
*  因此，我们可以通过这个特性来避免函数模板被用于与其不适配的类型。[例1]
*  2.和所有的类型萃取模板一样，自C++14开始，std::enable_if存在一个对应的std::enable_if_t的别名模板，通过后者可以直接代替::type。前面提到过，
*    std::enable_if::type在表达式为true并且提供了第二个模板参数时会表达为第二个模板参数，在例2中，我们将get32bit的模板参数T(在例子中为int)用作了
*    std::enable_if的第二个模板参数，由于sizeof(int)的大小为4，因此表达式为true，所以std::enable_if::type将表达为int。[例2]
*  todo134
*/
#include <iostream>

//===============例1===============
namespace e1{
template<typename T>
typename std::enable_if<(sizeof(T) == 4)>::type is32bit(){
    std::cout << "YES." << std::endl;
}

void func1(){
    is32bit<char>();
    is32bit<int>();
}

}

//===============例2===============
namespace e2{

/* 使用std::enable_if_t */
template<typename T>
typename std::enable_if_t<(sizeof(T) == 4)> is32bit(){   //无需指定::type
    std::cout << "YES." << std::endl;
}

/* 使用第二个模板参数指定类型 */
template<typename T>
typename std::enable_if<(sizeof(T) == 4), T>::type get32bit(){
    return 1000000;
}

void func2(){
    is32bit<int>();
    get32bit<int>();
}    
}


//===============例3===============

int main(void){
    e1::func1();
    e2::func2();
}
