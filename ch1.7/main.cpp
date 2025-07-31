/**
 * 《为类模板声明友元函数》
 */

#include <iostream>
#include <string>

//===================================================================
/* 要想在类模板中声明友元函数，最简单的办法是直接在类模板内部声明并定义友元函数 */
template<typename Mtype>
struct Message{
    Mtype m_msg;

    Message(const Mtype &msg) : m_msg(msg){}

     /* 直接在类模板中声明并定义友元函数。值得注意的是，operator<<并不是一个函数模板，而是一个需要时随着类模板实例化的普通函数 */
    friend std::ostream& operator<<(std::ostream &os, Message<Mtype> &msg){
        os << msg.m_msg;
        return os;
    }
};

//===================================================================
/**
  * 如果想要先在类模板中声明友元函数，而将其定义延后进行，那么事情将会变得复杂。我们有两种选择：其一是隐式声明一个函数模板，该模板
  * 使用与类模板不同的模板参数(否则会导致类模板参数被隐藏)。
  */
template<typename Mtype>
struct Message2{
    Mtype m_msg;

    Message2(const Mtype &msg) : m_msg(msg){}

    template<typename U>
    friend std::ostream& operator<<(std::ostream &os, Message2<U> &msg);
};

template<typename T>
std::ostream& operator<<(std::ostream &os, Message2<T> &msg){
    os << msg.m_msg;
    return os;
}

//===================================================================
/**
 * 其二是提前将类模板的友元函数声明为一个函数模板，然后在类模板中声明一个该函数模板的特例化版本。值得注意的是，由于operator<<的声明中
 * 需要使用到类模板Message3，因为我们还需要在operator<<的声明前先声明Message3。
 */
template<typename Mtype>
struct Message3;

template<typename T>
std::ostream& operator<<(std::ostream&, Message3<T> &msg);

template<typename Mtype>
struct Message3{
    Mtype m_msg;

    Message3(const Mtype &msg) : m_msg(msg){}

    /**
     * 声明一个operato<<r的模板参数类型为Mtype的特例化版本作为友元函数。注意operator<<后面的“<Mtype>”，这是模板特例化的标志，如果
     * 没有这个标志，那么我们就只是声明了一个新的非模板函数。
     */
    friend std::ostream& operator<<<Mtype>(std::ostream &os, Message3<Mtype> &msg);
};

template<typename T>
std::ostream& operator<<(std::ostream &os, Message3<T> &msg){
    os << msg.m_msg;
    return os;
}

//===================================================================
int main(void){
    /* case1 */
    Message<const char*> msg{"Hello World"};
    operator<<(std::cout, msg) << std::endl;

    /* case2 */
    Message2<const char*> msg2("Hoshimi Miyabi");
    operator<<(std::cout, msg2) << std::endl;

    /* case3 */
    Message3<const char*> msg3{"Sistine Fibel"};
    operator<<(std::cout, msg3) << std::endl;
}
