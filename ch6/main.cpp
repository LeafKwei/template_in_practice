/**
 * ch6: 
 * 1.(成员)函数模板仅在调用时才实例化。对于类模板而言，其中的成员函数仅在使用时才实例化，这既是节约空间和时间的做法，同时也允许我们部分地使用类模板
 * 2.被用作类模板或函数模板的模板参数的类型，可以仅提供必须的而不是所有“可能”需要的操作
 */

#include <iostream>
#include <string>

struct PriorityMessage{
    int priority;
    std::string message;
};

struct Message{
    std::string message;
};

template<typename T>
class Printer{
public:
    Printer(int priority=10) : m_priority(priority){}

    void showMessages(std::initializer_list<T> messages){
        for(auto &m : messages){
            std::cout << m.message << std::endl;
        }
    }

    void showPriorityMessages(std::initializer_list<T> messages){
        for(auto &m : messages){
            if(m.priority < m_priority) continue;
            std::cout << m.message << std::endl;
        }
    }

private:
    int m_priority = 10;
};

/**
 * 在case1中，对于类模板Printer<T>的实例类型Printer<Message>而言，我们仅调用了它的showMessages函数，因此编译器也仅实例化showMessages函数，在
 * 该函数中我们仅使用了类型T的message成员。Printer<T>中使用了T的priority和message成员，因此对类型T而言，priority和message成员就是它“可能”需要提供
 * 的操作，但我们实际上仅在Printer<Message>类型中使用了message成员，因此message成员就是它必须提供的操作，所以类型Message可以仅提供message成员。
 */
void case1(){
    Printer<Message> printer;
    printer.showMessages({{"Hello"}, {"World"}});
}

/**
 * 在case2中，对于实例类型Printer<PriorityMessage>而言，我们调用了showPriorityMessages函数，因此该函数将被实例化，该函数中使用了T的priority和message
 * 成员，因此priority和message就是T必须提供的操作，所以PriorityMessage需要同时提供priority和message成员。
 */
void case2(){
    Printer<PriorityMessage> printer;
    printer.showPriorityMessages({{9, "Foo"}, {11, "Bar"}});
}

int main(void){
    case1();
    case2();
}
