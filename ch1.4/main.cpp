/**
 * 《警惕返回临时变量的引用导致的运行时错误》
 */

#include <iostream>
#include <cstring>

/* 模板1，引用传递 */
template<typename T>
T const& max(const T &a, const T &b){
    std::cout << "Calling max(const T&, const T&)" << std::endl;
    return b < a ? a : b;
}

/* 普通函数，值传递 */
const char* max(const char *a, const char *b){
    std::cout << "Calling max(const char*, const char*)" << std::endl;
    return std::strcmp(b, a) < 0 ? a : b;
}

/* 模板2，引用传递 */
template <typename T>
 T const & max(T const &a, T const &b, T const &c){
    std::cout << "Calling max(const T&, const T&, const T&)" << std::endl;
    std::cout << typeid(T).name() << std::endl;  //PKc means Pointer(P) to const(K) char(c)
    return max(max(a, b), c);
}

int main(void){
    const char *a = "abfd;jafkld;ajf;kdaslfc";
    const char *b = "ddafi;dajfl;afjef";
    const char *c = "hrioeaufiodjiaij";

    /**
     * 正确版本
     * 模板2匹配调用max(1,2,3)，T被推断为int，模板2内部的max(a, b)将匹配模板1，T被推断为int，max(max(a,b), c)同样匹配模板1，T被推断为int，
     * 在这整个过程中，参数传递都是通过引用进行的，而这些引用都是绑定在了main函数中的纯右值1、2、3，这意味着，即使对模板2、模板1的调用
     * 结束后，引用所绑定的值依然是存在的，这也是这段代码正确运行的原因
     */
    std::cout << max(1, 2, 3) << std::endl;

    /**
     * 错误版本
     * 模板2匹配调用max(1,2,3)，T被推断为const char *，内部的max(a,b)匹配到普通函数1，max(max(a,b),c)同样匹配到普通函数1，关键的地方在于，
     * max(max(a,b),c)返回的是一个临时的指针变量，而这个变量在模板2调用结束后就被回收，但模板2却返回了对该变量的一个引用，因此当对模板2
     * 的调用结束，回到main函数时，模板2返回的引用所绑定的变量已经不复存在，而访问该引用也将引发运行时错误
     */
    std::cout << max(a, b, c) << std::endl;
}