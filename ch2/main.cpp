/**
 * ch2：隐式类型转换与模板参数推断
 */

#include <iostream>

int max(int a, int b){
    std::cout << "Ordinary function." << std::endl;
    return a < b ? b : a;
}

template<typename T>
T max(T a, T b){
    std::cout << "Templated function." << std::endl;
    return a < b ? b : a;
}

int main(void){
    /**
     * 普通版本的max接受int类型的参数，需要经过隐式类型转换，而模板版本的max可以直接生成T为double和char的版本，因此模板版本的max
     * 匹配的更好
     */
    max(10.1, 10.2);
    max('a', 'b');

    /** 
     *  模板版本的max的参数a、b使用的是同一类型T，但此处传递的参数a、b类型不一致，虽然char和double都能隐式转换为int，但是隐式类型转换
     *  对编译器推断出的模板参数类型不会生效，所以模板版本的max不匹配，编译器将采用普通版本的max
    */
    max(10, 'a');
    max(10, 10.1);

    /**
     * 尖括号代表强制使用模板(因此普通版本的max将排除在候选集之外)，并且显式指定T为int。显式指定模板参数后，隐式类型转换对模板也可生效，
    * 所以此处将使用模板版本的max 
    */
    max<int>(10, 10.1);
}