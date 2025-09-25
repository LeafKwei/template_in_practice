/**
 * 《关键字 typename》
 * typename在C++标准需要明确地指出一个模板中的名字是一个类型时被引入。当我们编写模板代码时，由于模板尚未实例化，编译器无法得知我们引用的
 * 模板类型参数中的名字对应的实体是类型或是类成员，在不使用typename的情况下，编译器会假设该名字对应的实体为类成员，因此，如果我们希望编译器
 * 将该名字视为类型，那么我们必须使用typename进行限定。
 */
#include <iostream>

struct Foo{
    using Bar = int;
};

struct Delta{
    static int Bar;
};

int Delta::Bar = 100;

template<typename T>
class TypeA{
public:
    void run(){
        /** 
         * Bar未被typename限定，那么编译器将会假设其为T的类成员，因此下方的语句将被编译器视为T的Bar成员与变量ptr的一个乘法运算，而编译器并不一定会报告错误，
         * 这是因为当T真的存在可以参与乘法运算的成员Bar时，该语句就是正确的
         */
        int ptr = 200;
        T::Bar *ptr;
    }
};

template<typename T>
class TypeB{
public:
    /* 使用typename限定了Bar，编译器将Bar视为类型  */
    typename T::Bar bar;
};

int main(void){
    TypeA<Delta> va;
    TypeB<Foo> vb;
}
