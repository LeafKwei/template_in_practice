/**
* 《类型别名》
* 我们可以通过为一整个类型定义一个新名字(称为类型的别名)，来简化一个类模板的使用。定义类型别名可通过“typedef”以及“using”(C++11引入)进行，相比于typedef，
* using的可读性更高。此外，using还支持通过模板为一簇类型定义别名。
*/

#include <list>
#include <vector>
#include <iostream>

//========================================
/** 
* 《类型别名(Typedefs)和别名声明(Alias declareations) 》
* 使用typedef定义的别名我们将其称为类型别名，使用using定义的别名我们将其称为别名声明。它们都是为一种已存在的类型定义一个新的名字。
*/
template<typename T, typename Cont=std::vector<T>>
class Stack{
public:
    void push(const T & e){
        m_container.push_back(e);
    }

    void pop(){
        m_container.pop_back();
    }

    T top(){
        return m_container.top();
    }

private:
    Cont m_container;
};

/* 使用typedef定义别名 */
typedef Stack<int> IntStack;

/* 使用using定义别名 */
using DoubleStack = Stack<double>;

/* 无论使用哪一种方式定义别名，类型和它的别名都是可相互替代的，因此Stack<int>和IntStack是相同的类型 */
void func1(){
    Stack<int> stack;
    IntStack stack2;

    Stack<double> stack3;
    DoubleStack stack4;
}

//========================================
/**
 * 《别名模板》
 * 不同于typedef，使用using定义的别名声明可以被模板化，这样就可以为一簇类型定义一个简化的名称。这个功能从C++11开始支持，
 * 被称为别名模板(Alias template)。
 */

/**
 * 假设我们最常用的Stack是以std::list为底层容器的，例如Stack<int, std::list<int>>，这样的写法过于冗长，并且可读性不高，此时我们可能会想到
 * 定义一个别名，例如“using IntStack = Stack<int, std::list<int>>”，但缺点是一旦元素类型发生改变，就需要重新定义一个别名。对此，我们就
 * 可以使用别名模板功能，按模板的规则为using声明一个类型参数T，将之作为元素类型，而容器类型则保持为std::list<T>，由此就得到了一个底层
 * 容器固定为std::list，元素类型灵活可变的别名模板ListStack。
 */
 template<typename T>
 using ListStack = Stack<T, std::list<T>>;

void func2(){
    Stack<int, std::list<int>> stack1;
    Stack<double, std::list<double>> stack2;
    ListStack<int> stack3;
    ListStack<double> stack4;
}

int main(void){
    func1();
    func2();
}