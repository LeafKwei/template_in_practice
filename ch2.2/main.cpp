/**
 * 《非类型模板参数的限制》
 * 非类型模板参数存在某些限制，通常来说，它们可以是以下这些类型的值：
 *   1.整型常量，包括枚举
 *   2.指向对象、函数、类成员的指针
 *   3.对对象、函数的左值引用
 *   4.std::nullptr_t类型的数据，典型的是nullptr
 */

#include <iostream>

//================================
enum class Week{Mon, Tue, Wed, Thu, Fri, Sta, Sun};

template<Week Day>
void dummyWeek(){
    std::cout << static_cast<int>(Day) << std::endl;
}

void func1(){
    dummyWeek<Week::Fri>();        //使用枚举作为非类型参数
}

//================================
/* 浮点型数据或者类对象不允许用作非类型参数。 */
template<double Val>        //不允许使用浮点型数据作为非类型参数
double addValue(const double e){
    return e + Val;
}

template<std::string Str>   //不允许使用对象作为非类型参数
void print(){
    std::cout << Str << std::endl;
}

int main(void){
    func1();
}
