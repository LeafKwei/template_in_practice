/**
 * 《可变表达式和可变索引》
 * 1.可变表达式(Variadic expressions)是指将参数包与一个表达式结合使用，使参数包中的每个参数都参与计算。
 * 2.可变索引是可变表达式的一种应用，通过在模板实例化时传递不同的索引值，从而实现对元素的灵活访问。
 */

#include <iostream>
#include <vector>

//================================
/* 参数包args出现在操作符左侧且右侧操作数空缺 */
template<typename... V>
int add(const V &...args){
    /**
     * “args + ...”表示按照“(arg1 + arg2) + arg3”的形式展开表达式，由于运算符“+”的右侧需要操作数，所以表达式展开后会变成“(arg1 + arg2) + arg3”的形式；
     * 相反如果我们使用的表达式是“args + args...”，那么该表达式将被展开为“arg1 + arg1, arg2 + arg2”，即以逗号分隔每个表达式，以此类推。总结起来就是，如果
     * 参数包args只出现在了操作符op的左侧，并且操作符右侧的操作数空缺时，参数包中的参数将被展开到以操作符op相连的一个整体的表达式中；而如果操作符op的两侧
     * 没有空缺，那么参数包中的参数将会依次展开到一个单独的表达式中，每个表达式间以逗号分隔。
     */
    return (args +...);
}

void print(){

}

template<typename T, typename... Args>
void print(const T &arg, const Args &...args){
    std::cout << arg << std::endl;
    print(args...);
}

/* 参数包args出现在操作符左侧，但操作符右侧存在操作数 */
template<typename... V>
void addOne(const V &...args){
    print((args + 1)...);  //需要注意，由于1后面直接跟dot会被编译器当作浮点数处理，因此此处需要添加括号或者在1和dot间添加空格
}

void func1(){
    //return (args +...)将展开为return((((1 + 2) + 3) + 4) + 5)
    std::cout << add(1, 2, 3, 4, 5) << std::endl;

    //print((args + 1)...)将展开为print(1+1, 2+1, 3+1, 4+1, 5+1)
    addOne(1, 2, 3, 4, 5);
}

//================================
/* 由于此处需要使用到索引值而非类型，因此要使用非类型模板参数Idx。为了避免编译器将我们传递给Idx的索引值当作类型参数，需要将Idx放到类型参数C的前边 */
template<std::size_t... Idx, typename C>
void printIndic(const C &container){
    /* 可变索引，即将下标操作符结合参数包使用，展开后将得到与参数包的参数数量一致的一组下标表达式 */
    print(container[Idx]...);
}

void func2(){
    /* 通过在每次调用printIndic时给出不同的索引值作为非模板参数包，实现每次调用打印容器中的不同元素 */
    printIndic<0, 2, 4>(std::vector<std::string>{"A", "B", "C", "D", "E"});  //展开为print(container[0], container[2], container[4])
}

int main(void){
    func1();
    func2();
}
