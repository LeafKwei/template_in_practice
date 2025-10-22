/**
 * 《成员模板》
 * 1.类成员也可以是一个模板，包括嵌套类或者成员函数。以前面用到的Stack为例，一般地，我们可以将两个相同类型的stack进行赋值，这意味着它们的元素拥有着相同的类型，
 *   然而我们却不能将其中一个stack与另一个类型不同的stack进行赋值，即使它们的元素类型存在着隐式类型转换关系。[例1]
 * 2.默认的赋值操作符要求两侧拥有相同的类型，而例1中的Statck<int>和Stack<float>显然并不在这种情况内。但是，通过将赋值操作符定义为一个模板，我们就可以实现将
 *   两个元素类型不同的Stack赋值，其原理是引入一个新的模板参数以及借助函数模板的类型推断能力，使得赋值操作符可以接受与当前Stack的元素类型不同的另一个Stack，
 *   然后再将该Stack的元素挨个保存到当前Stack中。当然，两种元素类型之间需要存在合适的类型转换关系。[例2]
 * 3.成员模板同样可以偏特/全例化(注意函数模板仅能全特化)，如果成员模板所在的类也是一个模板，那么必须先特例化类模板，并在特例中声明该成员模板，然后再对成员模板
 *   进行特例化。[例3]
 */
#include <iostream>
#include <deque>
#include <vector>

//===============例1===============
template<typename T>
class Stack{
public:
    void push(const T &e){ m_cont.push_back(e); }
    void pop()                   { m_cont.pop_back(); }
    T      top()                    { return m_cont.back(); }
    bool empty()               { return m_cont.empty(); }

private:
    std::vector<T> m_cont;
};

void func1(){
    Stack<int> istack1, istack2;
    Stack<float> fstack;

    istack1 = istack2;      //元素类型同为int的两个stack可以赋值
    istack1 = fstack;       //元素类型不同的两个stack不能赋值，即使float可以隐式转换为int
}

//===============例2===============
template<typename T>
class AssignedStack{
public:
    void push(const T &e){ m_cont.push_back(e); }
    void pop()                   { m_cont.pop_back(); }
    T      top()                    { return m_cont.back(); }
    bool empty()               { return m_cont.empty(); }

    /* 将赋值操作符声明为了一个模板，新增了模板参数T2，使得参数other可以接受与当前AssignedStack的元素类型不同的另一个AssignedStack */
    template<typename T2>
    AssignedStack& operator=(const AssignedStack<T2> &other);

private:
    /* 由于我们赋值时会从栈顶弹出元素，为了确保元素原本的顺序，我们需要把每个元素都插入列表头部，因此此处将vector替换为了提供了push_front函数的deque */
    std::deque<T> m_cont;
};

/**
 * 1.当我们选择将成员模板定义在模板类的外部时，需要同时声明类模板和成员模板的模板参数，此处我们将内部的模板参数进行了缩进以作区分。
 * 2.可以看到，我们为operator=的参数“AssignedStack<T2> &other“指定了另一个模板参数T2，这样一来other就可以接受与当前AssignedStack元素类型不同的
 *   AssignedStack。随后我们就可以将other的元素依次push到当前的AssignedStack，前提是T和T2之间存在类型转换关系。
 */
template<typename T>
  template<typename T2>
inline AssignedStack<T>& AssignedStack<T>::operator=(const AssignedStack<T2> &other){
    AssignedStack<T2> cpy(other);  //通过创建other的拷贝，我们可以避免自赋值问题；并且由于other是const的，所以不能调用它的非const成员函数，而拷贝则没有这个问题
    m_cont.clear();

    while(!cpy.empty()){
        m_cont.push_front(cpy.top()); //前提是T2可以隐式转换为T
        cpy.pop();
    }

    return *this;
}

void func2(){
    AssignedStack<int> istack;
    AssignedStack<float> fstack;

    istack = fstack; //元素类型不同，但依然可以赋值，注意float可以隐式转换为int
}

//===============例3===============
template<typename T>
struct Owner{
    template<typename T2>
    void message(const T2 &msg) { std::cout << msg<< std::endl; }
};

/* 首先特例化Owner */
template<>
struct Owner<bool>{
    /* 声明成员函数模板message */
    template<typename T2>
    void message(const T2 &msg);
};

/* 随后再特例化成员函数模板 */
template<>
inline void Owner<bool>::message<bool>(const bool &msg){
    std::cout << ((msg) ? "true" : "false") << std::endl;
}

void func3(){
    Owner<bool> owner;
    owner.message(true);
    owner.message(false);
}

int main(void){
    func2();
    func3();
}
