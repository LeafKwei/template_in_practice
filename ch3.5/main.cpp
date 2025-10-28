/**
 * 《.template结构和通用lambda》
 * 1.某些情况下我们需要在调用成员模板时显式地限定出其中的模板参数，在该情况下，我们必须使用关键字template来确保左尖括号<被编译器解析为模板参数的开始标志而
 *   不是一个小于操作符。这种问题仅会在句点符号“.”前的内容依赖于模板参数并且成员模板还需要显式指定模板参数时发生，在例1中，bits依赖于模板参数N，同时to_string
 *   也显式指定了模板参数。此外还有两种类似的语法“-> template”和“::template”，分别用于通过指针调用成员和静态成员的调用的情况。[例1]
 * 2.通用lambda表达式在C++14时引入，它被用作成员函数模板的一种简便写法，我们可以使用关键字auto来作为函数参数类型的占位符，这样就得到了一个适用于任意类型
 *   的lambda表达式。这种通用lambda表达式是对例2中的函数对象的简化。[例2]
 */
#include <bitset>
#include <iostream>

//===============例1===============
template<unsigned int N>
void printBitset(const std::bitset<N> &bits){
    auto str = bits.template to_string<char, std::char_traits<char>, std::allocator<char>>(); //省略template关键字将会导致<被识别为小于操作符
    std::cout << str << std::endl;
};

void func1(){
    std::bitset<100> bits;
    printBitset<100>(bits);
}

//===============例2===============
/* 用于任意类型求和运算的函数对象，其函数调用操作符是一个成员函数模板 */
class NameGeneratedByComplier{
public:
    NameGeneratedByComplier(){}
    template<typename T1, typename T2>
    auto operator() (T1 x, T2 y){
        return x + y;
    }
};

void func2(){
    /* 一个用于求和运算的通用lambda，可以看作是NameGeneratedByComplier的一个简便写法 */
    auto add = [](auto x, auto y) {
        return x + y;
    };

    std::cout << add(10, 20) << std::endl;
    std::cout << add(10.1, 20.2) << std::endl;
    std::cout << add(10UL, 20UL) << std::endl;
    std::cout << NameGeneratedByComplier()(10, 20) << std::endl;
    std::cout << NameGeneratedByComplier()(10.1, 20.2) << std::endl;
    std::cout << NameGeneratedByComplier()(10UL, 20UL) << std::endl;
}

int main(void){
    func1();
    func2();
}
