/**
 * 《默认模板参数》
 * 1.正如函数模板那样，我们也可以为类模板的“模板类型参数”定义默认类型，当我们在使用模板时，如果没有给对应位置的类型参数指定类型，那么
 *   该参数就将采用默认类型。
 * 2.应该确保具有默认类型的类型参数的右侧所有类型参数都具有默认参数，否则在使用类模板时，由于指定的类型将优先应用于左侧的类型参数，如果
 *   指定的类型数量不足，就会导致右侧不具有默认类型的类型参数缺少类型，从而无法通过编译。
 */

 #include <vector>
 #include <list>
#include <iostream>

//========================================
/* 我们为类型参数Cont指定了一个默认类型std::vector<T>，当我们使用Stack模板时，如果没有为Cont指定类型，那么Cont就将使用std::vector<T>  */
template<typename T, typename Cont=std::vector<T>>
class Stack{
public:
    void push(const T &e);
    void pop();
    T top();

private:
    Cont m_container;
};

/**
 * 注意：这里我们将成员函数声明在了Stack模板内部，而定义在了Stack模板之外， 因为它们属于类模板的成员，因此在定义时 
 * 必须先使用template声明一组与类模板个数一致模板类型参数，然后以Stack<T,Cont>作为前缀限定push。由于Cont的默认
 * 类型已在Stack模板声明，因此此处无需再次声明。
 */
template<typename T, typename Cont>
void Stack<T,Cont>::push(const T &e){
    m_container.push_back(e);
}

template<typename T, typename Cont>
void Stack<T,Cont>::pop(){
    return m_container.pop_back();
}

template<typename T, typename Cont>
T Stack<T,Cont>::top(){
    return m_container.back();
}

//========================================
/**
 * 为类型参数T指定了默认类型int，那么当我们以“Stack2<std::vector<int>>”的形式使用此模板时，由于std::vector<int>被应用于T，所以类型参数Cont
 * 没有被指定任何类型，因此无法通过编译。
 */
template<typename T=int, typename Cont>
class Stack2{
public:
    void push(const T &e){
        m_container.push_back(e);
    }

    void pop(){
        m_container.pop_back();
    }

    T top(){
        return m_container.back();
    }

private:
    Cont m_container;
};

int main(void){
    Stack<int> vstack;
    vstack.push(100);
    std::cout << vstack.top() << std::endl;

    Stack<int, std::list<int>> lstack;
    lstack.push(100);
    std::cout << lstack.top() << std::endl;

    Stack2<std::vector<int>> stack2;
}
