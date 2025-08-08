/**
 * 《非类型模板参数》
 * 对函数和类模板来说，模板参数并不一定要是类型，它们也可以是普通的值。就像是使用了类型参数的模板那样，在定义代码时，代码中的某些细节将保留到代码被使用时才
 * 确定下来。这些被保留的细节并不一定是类型，也可以是确切的值，而用于传递这些值的模板参数就被称为非类型参数。当我们使用一个这样的模板时，我们必须显式地指定
 * 出这个值。
 */

#include <iostream>

/**
 * 《非类型类模板参数》
 * 在本例中我们将演示如何对类模板使用非类型参数，我们将前面的Stack类改造为一个使用固定大小数组来保存元素的实现。就像定义旧版本的Stack一样，我们使用template
 * 声明了类型参数T，但不同之处在于我们还声明了一个非类型参数Size，非类型参数使用类型而非typename进行声明，该类型决定了非类型参数可以代表的值的类型，在本例
 * 中，我们使用了unsigned int声明了Size，因此在使用Stack模板时，我们可以为Size指定unsigned int类型的值。
 */
template<typename T, unsigned int Size>
class Stack{
public:
    void push(const T &e);
    T      top();
    void pop();

private:
    /* 可以看到，我们将Size用作了数组的长度，这样一来，数组的容量就可根据用户在使用Stack模板时为Size指定的值动态地调整 */
    T m_elements[Size];
    unsigned int m_index;
};

template<typename T, unsigned int Size>
void Stack<T,Size>::push(const T &e){
    if(m_index < Size){
        m_elements[m_index] = e;
        ++m_index;
    }
}

template<typename T, unsigned int Size>
T Stack<T,Size>::top(){
    if(m_index - 1 < Size) return m_elements[m_index - 1];
    return T();
}

template<typename T, unsigned int Size>
void Stack<T,Size>::pop(){
    if(m_index > 0) --m_index;
}

int main(void){
    Stack<int, 16> i16Stack;       //将Size指定为16，编译器将实例化一个数组容量为16的Stack版本
    Stack<int, 32> i32Stack;       //将Size指定为32，编译器将实例化一个数组容量为32的Stack版本

    /**
     * 一个需要注意的地方是，Stack<int,16>和Stack<int,32>是两个不同的类型，非类型参数的值不同会导致编译器生成不同的版本，这一点与类型参数类似。
     * 我们可以通过RTTI来验证这一点。
     */
    std::cout << typeid(i16Stack).name() << std::endl;
    std::cout << typeid(i32Stack).name() << std::endl;
}
