/**
 * 《类模板特例化》
 * 我们可以为某个类型特例化类模板，这一点类似于函数重载，当我们以该类型作为模板的类型参数时，编译器将会优先使用我们的特例化版本。
 */

 #include <vector>
#include <iostream>

//==========================================
template<typename T>
class Stack{
public:
    void push(const T &element){
        m_vec.push_back(element);
    }

    void pop(){
        m_vec.pop_back();
    }

    T top(){
        return m_vec.at(m_vec.size() - 1);
    }

private:
    std::vector<T> m_vec;
};

/**
 * 模板的特例以“template<>”开始，随后在类名之后给出该特例针对的类型。在本例中，我们为std::string类型特例化了Stack模板。特例化时，原模板
 * 中所有的类型参数T都需要替换为std::string类型。
 */
template<>
class Stack<std::string>{
public:
    void push(const std::string &element){
        std::cout << "I am specializition." << std::endl;
        m_vec.push_back(element);
    }

    void pop(){
        m_vec.pop_back();
    }

    std::string top(){
        return m_vec.at(m_vec.size() - 1);
    }

private:
    std::vector<std::string> m_vec;
};

//==========================================
/**
 * 除了特例化整个类模板外，我们还可以只特例化单个的成员函数。但在这样做之后，我们就无法再特例化整个类模板了，原因是在特例化成员函数时，需要使用到类模板，
 * 这意味着我们需要实例化类模板，而类模板的特例化必须在其实例化之前进行，因此在特例化成员函数后，由于类模板已经实例化了，所以就无法进行特例化了。
 */
template<typename T>
class Stack2{
public:
    void push(const T &element){
        m_vec.push_back(element);
    }

    void pop(){
        m_vec.pop_back();
    }

    T top(){
        return m_vec.at(m_vec.size() - 1);
    }

private:
    std::vector<T> m_vec;
};

template<>
void Stack2<std::string>::push(const std::string &elements){  //注意，Stack2<std::string>实例化了Stack2模板
    std::cout << "I am specializition2." << std::endl;
    m_vec.push_back(elements);
}

//==========================================
int main(void){
    /* case1 */
    Stack<std::string> stack;   //优先使用特例化版本
    stack.push("Hello World");

    /* case2 */
    Stack2<std::string> stack2;
    stack2.push("Hello World");
}
