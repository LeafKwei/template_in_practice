/**
 * 《自动推断非类型模板参数的类型》
 * 自C++17开始，我们可以使用关键字“auto”作为非类型模板参数的类型占位符，编译器将会从我们实例化模板时给出的参数值中推断出该参数的类型。需要注意的是，即使
 * 是使用auto而不是具体的类型，传递给该参数的值仍要满足非类型模板参数的限制。
 */

#include <iostream>

//================================
/* 使用auto作为Maxsize的类型的占位符，让编译器根据参数值进行推断 */
template<auto Maxsize>
class Chapter{
public:
    /* 使用decltype推断出Maxsize的类型，然后用using语句为该类型定义一个别名，方便后续使用 */
    using size_type = decltype(Maxsize);

    void print(){
        std::cout << Maxsize << std::endl;
        std::cout << typeid(size_type).name() << std::endl;
    }
};

void func1(){
    /* 即使使用了auto，传递给Maxsize的参数值类型也必须符合非类型模板参数的要求 */
    Chapter<100> chapter1;    //Maxsize的类型被推断为int
    Chapter<100U> chapter2; //Maxsize的类型被推断为unsigned int

    chapter1.print();
    chapter2.print();
}

int main(void){
    func1();
}
