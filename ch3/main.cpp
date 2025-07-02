/**
 * ch3
 * 1.函数模板在调用时可以仅指定一部分模板参数的类型(按从左到右的顺序)，剩下的模板参数由编译器从函数参数中推导
 * 2.任何时刻我们都应该保证只有一个函数模板匹配当前的调用，如果一个调用存在多个匹配的函数模板，那么就会引发“模糊”错误
 * 3.由于函数模板可以重载，并且如条例1所述的，我们可以仅为调用指定部分模板参数的类型，而这可能导致多个重载的模板都匹配
 *   该调用，从而引发模糊错误
 */

#include <iostream>

template<typename T1, typename T2>
auto max(T1 a, T2 b){
    return a < b ? b : a;  //如果返回值使用auto替代，并且没有在函数尾部使用“->”显式指定返回值类型，那么编译器将从return语句推断返回值类型
}

template<typename RT, typename T1, typename T2>
RT max(T1 a, T2 b){
    return a < b ? b : a;
}

int main(void){
    
}