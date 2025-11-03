#include "vt.hpp"
#include <array>

/**
 * 《变量模板》
 * 1.从C++14开始，一个变量也可以被一个指定类型参数化，这种变量被称为变量模板。如同例1中展示的那样，我们可以在尚未定义变量的类型前，定义变量的值。
 *   需要注意，变量模板和其他模板一样，不能在函数内部或局部作用域中定义。[例1]
 * 2.当我们使用一个变量模板时，必须显式指定它的模板参数类型，如果我们使用了该模板参数作为变量的类型，那么还要保证我们指定的类型和变量的初始值兼容。[例2]
 * 3.变量模板也支持默认模板参数，但在使用模板时，即使不指定模板参数，也需要保留一对尖括号“<>”。[例3]
 * 4.与普通的全局变量不同，变量模板即使定义于头文件，并且插入到多个翻译单元中(即多个.cpp文件)，也不会出现重定义问题，这些翻译单元将会共用同一个变量模板，
 *   因此，如果对变量模板的初始化和使用发生在不同的翻译单元中，需要确保初始化的内容先被执行。[例4]
 * 5.变量模板中也可以使用非类型模板参数。与类型参数一样，对同一个变量模板来说，使用相同的非类型参数实例化的变量模板对应着同一个变量实例，反之则对应不同
 *   的变量实例。[例5]
 * 6.变量模板的用途之一是用于代表类模板的一个成员变量，就像例6中展示的那样，通过将VALUE定义为变量模板，我们可以根据模板参数的不同，使得VALUE拥有不同
 *   的值，而这些值来自类模板ImmValue的成员变量value。[例6]
 */
#include <iostream>


//===============例1===============
template<typename T>
constexpr T PI{3.1415926};

//===============例2===============
void func2(){
    auto pi = PI<double>;     //使用变量模板时，需要显式指定出模板参数的类型
    auto pi2 = PI<int>;          //错误，PI的初始值为浮点型，不能进行窄化转换
    std::cout << pi << std::endl;
    std::cout << pi2 << std::endl;
}

//===============例3===============
template<typename T=int> //指定int为默认的模板类型参数
constexpr T G {10};

void func3(){
    auto g = G<>;                  //不能省略尖括号
    auto g2 = G<long>;
    std::cout << g << std::endl;
    std::cout << g2 << std::endl;
}

//===============例4===============
void init();

void func4(){
    init();

    /**
     * 对同一个变量模板而言，在它们实例化时，如果模板参数相同，那么它们都对应同一个变量模板实例，如果模板参数不同，
     * 则对应不同的变量模板实例，即使它们处于不同的翻译单元。
     */
    std::cout << PASSWORD<std::string> << std::endl; //此处的PASSWORD<std::string>和init.cpp中的PASSWORD<std::string>是同一个实例
    std::cout << PASSWORD<long> << std::endl;         //PASSWORD<long>和init.cpp中的PASSWORD<long>是同一个实例，但和PASSWORD<std::string>是不同实例
}

//===============例5===============
template<int N>
std::array<double, N> realnums;

void func5(){
    realnums<100>;    //等同于声明了一个std::array<double, 100>类型的全局变量，变量名称由编译器根据模板参数和模板名称生成
    realnums<1000>;  //等同于声明了一个std::array<double, 1000>类型的全局变量
}

//===============例6===============
template<typename T>
struct ImmValue{
public:
    constexpr static int value = 0;
};

template<typename T>
struct ImmValue<T*>{
public:
    constexpr static int value = 1;
};

template<>
struct ImmValue<double>{
public:
    constexpr static int value = 2;
};

/* 我们可以使用表达式VALUE<T>直接获取T类型对应的ImmValue<T>::value成员变量的值，而无需使用更冗长的表达式ImmValue<T>::value */
template<typename T>
constexpr int VALUE = ImmValue<T>::value;

void func6(){
    std::cout << VALUE<char> << std::endl;
    std::cout << VALUE<char*> << std::endl;
    std::cout << VALUE<double> << std::endl;
}

int main(void){
    func2();
    func3();
    func4();
    func5();
    func6();
}
