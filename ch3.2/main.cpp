/**
 * 《值初始化与零值初始化》
 * 1.对于那些C++语言内置的类型(例如int、bool、指针)，没有默认的构造函数可以为它们提供一个默认值，这就会导致当我们没有显式地初始化这些类型的局部变量时，
 *   这些变量将会持有一个未定义的值(未定义指的是标准并未明确规定，根据编译器厂商的实现、系统的不同可能存在不同的结果)。[例1]
 * 2.在模板中，如果我们使用内置类型定义变量，在没有显式初始化的情况下，该变量同样是持有一个未定义的值。[例2]
 * 3.对于这种情况，我们可以通过显式地为内置类型调用一个默认构造函数来将它们初始化为该类型的零值(例如int初始化为0、bool为false)。通过使用例3中的初始化
 *   方式，可以确保严格意义上的初始化(即使是内置类型)。这种初始化方式被称为值初始化，在C++11中引入，它通过给定一系列的初始值来初始化一个对象，如果这
 *   些初始值可以匹配该类型的某个构造函数(包括使用std::initializer_list的构造函数)，那么就调用该构造函数进行初始化，如果没有提供任何初始值，那么就调用该类型
 *   的默认构造函数进行初始化(对于内置类型则是以它们的零值进行初始化)，即使这些构造函数是explict修饰的。[例3]
 * 4.在C++11以前，“T t{}”的替代办法是使用“T t = T{}”的方式，也就是先通过默认构造函数创建一个T类型的对象作为初始值，然后再以该对象初始化t，这种方式
 *   要求T类型提供拷贝构造函数。此外，不要认为可以使用“T t()”的形式来调用默认构造函数初始化变量t，这种语法形式是在进行函数声明而非变量初始化。[例4]
 * 5.值初始化还可以用于对非静态类成员变量以及函数的默认参数的初始化。[例5]
 */
#include <iostream>

//===============例1===============
void func1(){
    int v1;
    int *p1;

    printf("v1 = %d\n", v1);     //g++-linux编译得到的结果为0，g++-windows编译得到的结果为0
    printf("p1 = %p\n", p1);    //g++-linux编译得到的结果为随机地址，g++-windows编译得到的结果为0
}

//===============例2===============
template<typename T>
void foo(){
    T t;    //如果T是一个内置类型，那么t将会持有一个未定义值
    std::cout  << "t = " << t << std::endl;
}

void func2(){
    foo<int>();
}

//===============例3===============
class Man{
public:
    Man() : _str("Manba out"){}
    Man(const std::string &str) : _str(str){}
private:
    std::string _str;
};

//假设T为int
template<typename T>
void bar1(){
    T t{};       //零值初始化，可以确保调用类型T的默认构造函数将变量t初始化为默认值，即使T是内置类型
    std::cout  << "t = " << t << std::endl;
}

//假设T为Man
template<typename T>
void bar2(){
    T t1{};                             //调用T的默认构造函数
    T t2{"What can I say"};  //调用T的Man(const std::string &str)
}

void func3(){
    bar1<int>();
    bar2<std::string>();
}

//===============例4===============
template<typename T>
void before_cpp11(){
    T t = T();   //在C++11前的初始化方式
    std::cout  << "t = " << t << std::endl;
    //T t();      //错误！这样做是在声明一个返回值为T，名称为t的函数，而不是在初始化变量
}

void func4(){
    before_cpp11<int>();
}

//===============例5===============
template<typename T>
class NonStaticMember{
private:
    T t{};                                 //对非静态成员变量使用
};

template<typename T>
void default_arg(T t = T{}){  //不支持直接写为“T t{}”

}

void func5(){
    NonStaticMember<int> nsm;
    default_arg<int>();
}

int main(void){
    func1();
    func2();
    func3();
    func4();
    func5();
}
