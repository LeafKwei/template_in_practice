/**
 * 《偏特化》
 * 1.类模板可以部分地特例化，在这种情况下，我们可以提供一个针对特别情况的类模板实现，这个实现中仅指定了模板参数的一部分特性，而剩余的部分
 *   则需要由用户提供。当用户在使用类模板时，如果用户给定的模板参数匹配偏特化的类模板，那么编译器将采用我们的偏特化实现。
 * 2.在存在多个模板参数的情况下，类模板甚至还可以针对这些模板参数间的关系偏特化。例如两个模板参数是同一类型的情况。
 */

#include <iostream>

//========================================
/* 通用模板 */
template<typename T>
struct Dummy{
    void show(){
        std::cout << "I am Dummy<T>" << std::endl;
    };
};

/* 对指针类型的偏特化。我们仅声明了该模板用于指针，并未完全指定T的类型，这种部分地特例化就被称为偏特化 */
template<typename T>
struct Dummy<T*>{
    void show(){
        std::cout << "I am Dummy<T*>" << std::endl;
    }
};

template<typename T>
struct Dummy<T&>{
    /**
     * 我们可以在特例中对模板进行细微的修改，例如，在通用模板中show函数不返回任何值，但是在T&版本中，我们让show函数
     * 可以返回一个int值。
     */
    int show(){
        std::cout << "I am Dummy<T&>" << std::endl;
        return 114514;
    }
};

//========================================
/* 通用模板 */
template<typename T1, typename T2>
struct Rick{
    void show(){
        std::cout << "I am Rick<T1, T2>" << std::endl;
    }
};

/* 针对T1、T2是相同类型的偏特化 */
template<typename T>
struct Rick<T, T>{
    void show(){
        std::cout << "I am Rick<T, T>" << std::endl;
    }
};

/* 针对T2是int的偏特化 */
template<typename T>
struct Rick<T, int>{
    void show(){
        std::cout << "I am Rick<T, int>" << std::endl;
    }
};

//========================================

int main(void){
    std::cout << "---------- case1 ----------" << std::endl;
    Dummy<int> di;         //匹配Dummy<T>
    Dummy<int*> dip;     //匹配Dummy<T*>
    Dummy<int&> dir;    //匹配Dummy<T&>

    di.show();
    dip.show();
    int ret = dir.show();
    std::cout << ret << std::endl;

    std::cout << "---------- case2 ----------" << std::endl;
    Rick<int, double> rickid;                  //匹配Rick<T1,T2>
    Rick<double, double> rickii;            //匹配Rick<T,T>
    Rick<double, int> rickdi;                  //匹配Rick<T,int>
    rickid.show();
    rickii.show();
    rickdi.show();
}
