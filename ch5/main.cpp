/**
 * ch4：
 * 1.在类模板Bar<T>内部时，使用类模板类型的位置可以只提供类模板的名称Bar，等价于使用Bar<T>。一些特殊位置，例如构造函数或析构函数，它们仅需要类的名称
 *   而不是类型，因此只能使用Bar
 * 2.定义在类模板Bar<T>外部的成员函数，需要先使用template<typename T>将其标识成一个模板，然后再使用Bar<T>::限定其作用域
 * 3.对于定义在类外部的成员函数而言，在作用域声明“ClassName::”之后的部分被视为在类的内部。对于Bar<T>而言，条例1可以生效于定义在Bar<T>外部的成员函数
 * 在Bar<T>::之后的部分，例如函数参数类型
 */

#include <iostream>
#include <vector>

template <typename T>
class Bar{
public:
    /* 构造函数和析构函数需要类的名称而不是类型 */
    Bar(){
        std::cout <<"Constructor." << std::endl;
    }

    /* 在类模板内部需要使用到类型的地方，Bar可等价于Bar<T> ，下方的函数声明等价于Bar(const Bar<T> &oth) */
    Bar(const Bar &oth){
        std::cout << "Copy constructor." << std::endl;
        m_nums.insert(m_nums.begin(), oth.m_nums.begin(), oth.m_nums.end());
    }

    ~Bar(){
        std::cout << "Deconstructor." << std::endl;
    }

    void put(const T &e){
        m_nums.push_back(e);
    }

    T get(int index){
        return m_nums.at(index);
    }

    const std::vector<T>& elements(){
        return m_nums;
    }

    /* 定义在类模板之外 */
    bool operator==(Bar<T> &rhs);

private:
    std::vector<T> m_nums;
};

/** 
 * 使用template<typename T>将operator==标识为一个模板，然后再使用作用域声明Bar<T>::将其限定为Bar<T>的成员函数
 * Bar<T>::之后的内容被视为在Bar<T>内部，因此函数参数Bar &rhs等价于Bar<T> &rhs。
 */
template <typename T>
bool Bar<T>::operator==(Bar &rhs)
{
    return this -> m_nums == rhs.m_nums;
}

int main(void){
    Bar<int> bar;
    Bar<int> bar2;

    bar.put(1);
    bar.put(2);
    bar2.put(3);
    bar2.put(4);

    std::cout << "Values: ";
    for(auto &e : bar.elements()){
        std::cout << e << ", ";
    }

    std::cout << std::endl << "Compare: ";
    std::cout << (bar == bar2) << std::endl;
}
