#include <vector>
#include <iostream>

//========================================
/**
 * 《类模板类型参数推断》
 * 在C++17以前，我们必须在实例化类模板时显式地为类模板指定每一个类型参数，除非该参数存在默认类型。在C++17之后，编译器可以从类模板的构造
 * 函数参数中推断出类模板的类型参数。但是，与函数模板不同，如果想要自动推断类型参数，那么就需要确保类型参数可以全部从构造函数中推断得到，否则
 * 就需要显式地指定每一个类型参数，而不能向函数模板那样只指定无法推断的那部分。
 */

template<typename T>
class Stack_A{
public:
    /* 为了能让编译器可以通过构造函数推断T的类型，我们为Stack编写了一个以单个元素e为参数的构造函数 */
    Stack_A(const T &e){
        m_container.push_back(e);
    }

    void push(const T &e){
        m_container.push_back(e);
    }

private:
    std::vector<T> m_container;
};

template<typename T, typename U>
struct Dummy_A{
    Dummy_A(const T &e){
        //do nothing
    }
};

void func1(){
    /* 以下两者都调用构造函数Stack_A(const T &e) */
    Stack_A stack1(100);    //T被推断为int，Stack_A被实例化为Stack_A<int>
    Stack_A stack2 = 100; //同上

    /* 如果通过构造函数参数无法推断出所有类型参数，那么就必须显式指定所有类型参数 */
    Dummy_A dummy1 = 100;                         //无法推断类型参数
    Dummy_A<int, double> dummy2 = 100;  //ok
}

//========================================
/* 《类型推断与字符串字面量》*/
template<typename T>
class Stack_B{
public:
    Stack_B(T e){
        m_container.push_back(e);
    }

    void push(const T &e){
        m_container.push_back(e);
    }

private:
    std::vector<T> m_container;
};

void func2(){

    /**
     * 我们也可以使用字符串字面量来初始化Stack_A，但是这会带来很多麻烦的问题。通常，以引用传递的方式向模板传递参数时，类型是不会退化的，因此
     * const char [6]不会退化为const char*，T也会被推断为const char [6]，这就导致了当我们使用push时，无法push类型不是const char [6]的字面量。
     */
    Stack_A stack1 = "Hello";
    stack1.push("Hello!");   //无法push长度不为6的字面量

    /**
     * 对此，我们可以将构造函数参数改为值传递的方式，也就是Stack_B的样子。当按值传递时，原始数组类型const char [6]将会退化为对应的原始指针类型const char*，
     * 因此T被推断为const char*，而整个类模板也被实例化为Stack_B<const char*>。出于这个原因，将类模板的构造函数声明为值传递可能是值得的。
     */
    Stack_B stack2 = "Hello";
    stack2.push("Hello!");  //ok
}

//========================================
/**
 * 《推断指示》
 * 在上文中，引发问题的主要原因是对const char [6]退化后的指针的处理。在此，我们可以采用另一种办法：推断指示(Deduction guides)，通过定义一个特定的推断指示，
 * 我们可以让一个模板在类型参数符合推断指示的要求时，按照指定的类型进行实例化。
 */
template <typename T>
struct Dummy_C{
    Dummy_C(T e){}
};

/* 提示编译器，一旦T被推断为const char*，就将Dummy_C以std::string实例化 */
Dummy_C(const char*) -> Dummy_C<std::string>;

void func3(){
    /** 
    * 想要调用拷贝构造函数初始化，但语法规则不允许。从const char [6]到std::string经过一次隐式类型转换，从std::string到Dummy_C<std::string>
    * 需要再经过一次隐式类型转换，而编译器仅允许进行一次隐式类型转换。
    */
    Dummy_C dummy1 = "Hello"; 

    /* 以下ok */
    Dummy_C dummy2("Hello");
    Dummy_C dummy3{"Hello"};
}

int main(void){
    func1();
    func2();
    func3();
}
