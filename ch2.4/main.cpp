/**
 * 《可变参数模板》
 * 从C++11开始，模板可以接受数量不固定、类型不固定的模板参数，这个特性可以用在那些需要传递任意数量、任意类型的参数的地方。可变参数模板通常需要结合递归使用，
 * 这是因为我们通常无法在一次调用中处理完所有的参数，而只能先处理部分参数，再以剩余的参数递归调用模板。
 */

#include <iostream>

//================================
/**
 * 《可变参数模板的例子》
 * 下方这个例子将演示可变参数模板的基本使用，我们将使用可变参数模板的特性来定义一个可以打印任意数量、任意类型(前提是std::cout支持的类型)的函数模板print。
 */

 /**
  * print函数的作用是用于终止函数模板的递归调用，按照C++编译器的函数匹配规则，当一个调用有一个普通函数和一个函数模板都匹配时，普通函数匹配地更好，因此
  * 我们定义了一个 普通的、无参的print函数，当print模板处理完参数包中所有的参数后，最后一次递归调用将是“print()”，按照函数匹配规则，编译器将会调用我们的
  * 普通print函数，而不是继续递归调用print模板。
  */
void print(){
    //do nothing
}

/**
 * typename... Types将Types声明为了一个模板参数包，这意味着Types将可以接收任意数量的类型。Types... args将args声明为了一个函数参数包，这意味着args将可以接收任意
 * 数量、任意类型的函数参数。
 */
template<typename T, typename... Types>
void print(const T &arg1, const Types... args){
    std::cout << arg1 << std::endl;

    /* args...将函数参数包中剩余的参数展开，以此作为调用print时传递的参数。 */
    print(args...);
}

void func1(){
    /**
     * 1.对于传递的参数(9.9, "Hello", std::string("World"))，对print的调用将展开为print<double, const char*, std::string>(9.9, "Hello", std::string("World"))，随后，参数列表
     *   中的首个参数将传递到print模板的第一个参数arg1，而剩余的参数则被收集到参数包args中。(注：如果参数包前还存在一个函数参数arg2，那么参数列表中的第二个参数将
     *   将传递给arg2，以此类推。总结起来就是参数包前有多少个非参数包参数，那么就消耗参数列表中等量的参数，剩余的参数才收集到参数包)。
     * 2.对于递归调用时传递的参数("Hello", std::string("World"))，对print的调用将展开为print<const char*, std::string>("Hello", std::string("World"))，此时参数"Hello"被消耗，
     *   传递给arg1，而剩余参数再次收集到参数包args中。
     * 3.对于递归调用时传递的参数(std::string("World"))，对print的调用将展开为print<std::string>(std::string("World"))，此时参数std::string("World")被消耗，传递给arg1，
     *   由于没有剩余的参数，所以参数包args现在为空。
     * 4.对于最后一次递归调用print，由于参数包为空，所以调用被展开为print()，由于print的模板版本需要参数，所以它不匹配该调用，因此编译器将选择我们的无参pirint函数，
     *   递归也到此为止。
     */
    print(9.9, "Hello", std::string("World"));
}

//================================
/**
 * 《重载的可变和非可变参数模板》
 * 对于上面的例子，我们也可以选择定义一个非可变参数模板版本的print2函数模板来结束递归，其原理是当两个模板都匹配一个调用时，没有尾随参数包的版本匹配的更好，因此
 * 当递归进行到最后一个参数时，编译器会选择我们的非可变参数版本，递归也就随之结束。
 */
template<typename T>
void print2(const T &arg){
    std::cout << arg << std::endl;
}

template<typename T, typename... Types>
void print2(const T &arg1, const Types... args){
    std::cout << arg1 << std::endl;
    print2(args...);
}

void func2(){
    print(9.9, "Hello", std::string("World"));
}

//================================
/**
 * 《操作符sizeof...》
 * C++11中还引入了一个用于可变参数模板的sizeof操作符的新形式，即“sizeof...”，它可以用于计算模板参数包(如typename... Types)和函数参数包(如const Types... &args)内
 * 的参数数量。
 */
template<typename... Types>
void counter(const Types... args){
    std::cout << sizeof...(Types) << std::endl;
    std::cout << sizeof...(args) << std::endl;
}

void func3(){
    counter(1, 3.4, 8U, std::string("Hello World!"), "C++ Templates!");
}

/**
 * 但是，不要指望可以通过sizeof...来检查参数数量的方式来终止可变参数模板的递归，这是因为if语句工作在运行时，而模板代码的生成则是在编译时进行，所以
 * 即使无参版本的print3不会被调用，但编译器却无法在编译时得知，所以依旧照常寻找无参版本的print3，而如果我们没有提供无参的print3，那么就会产生编译
 * 错误。
 */
template<typename T, typename... Types>
void print3(const T &arg1, const Types... args){
    std::cout << arg1 << std::endl;
    if(sizeof...(args) > 0){
        print3(args...);
    }

    /* 在C++17中，随着if constexpr的出现，if语句可以在编译时期执行，所以以下方式是正确的。 */
    #if 0
    if constexpr (sizeof...(args) > 0){
        print3(args...);
    }
    #endif
}

int main(void){
    func1();
    func2();
    func3();
}
