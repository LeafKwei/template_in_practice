/**
 * 《模板化聚合体》
 * 聚合体，是指满足如下条件的类或结构体：
 *   1.没有用户定义的、explict或继承的构造函数
 *   2.没有private、protected的非静态成员
 *   3.没有虚函数、虚基类、以private或者protected方式继承的基类
 * 这样的聚合体可以使用列表式初始化“{ }”对其中的每个成员按照声明顺序进行初始化。
 */

 #include <string>
#include <iostream>

//========================================
/**
 * 《聚合体的模板化》
 * 聚合体也可以模板化，我们只需要像对普通类型那样为其声明类型参数并在使用该聚合体时指定相应的类型即可。
 */
template<typename T>
struct StringPair{
    std::string name;
    T value;
};

void func1(){
    /* 列表式初始化 */
    StringPair<std::string> strPair = {"name", "Tom.Smith"};

    /* 单独赋值每个成员 */
    StringPair<int> intPair;
    intPair.name = "Height";
    intPair.value = 180;
}

//========================================
/**
 * 《聚合体的推断指示》
 * 推断指示对聚合体也适用，虽然聚合体不存在用户定义的构造函数，但我们可以根据初始化时的初始值的类型来编写推断指示。
 */

 /* 当初始值是两个const char*类型时，将StringPair实例化为StringPair<std::string> */
StringPair(const char*, const char*) -> StringPair<std::string>;

void func2(){
    /** 
     * 如果没有推断指示，那么这条语句是错误的，因为StringPair没有用户定义的构造函数，所以编译器无法通过构造函数的接收的参数类型推断出T的类型，
     * 只能显式地指定T的类型。
     */
    StringPair strPair = {"name", "Tom.Smith"};
}

int main(void){
    func1();
    func2();
}
