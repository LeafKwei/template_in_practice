/**
 * 《完美转发(Perfect forwarding)》
 *   1.假设你需要编写一段通用代码，该代码需要将传递过来的参数的基本属性(例如左值/const左值/右值)原样转发到另一段代码，在不使用模板的情况下，我们不得不
 * 根据这些属性分别编写一段代码。例如我们需要将函数f的参数原样转发到函数g中，需要编写例1中的代码。[例1]
 *   2.现在，我们想要将这些函数整合到一段通用的代码中，就需要用到模板了，但这会存在一个问题，对于左值/const左值来说，函数f可以正常使用，但对于右值来说，
 * 函数f将会导致右值属性丢失，也就是说T会被推断为X，而非X&&。[例2]
 *   3.为了解决基本属性在类型推断时丢失的问题，C++11为了“完美转发”这些参数而引入了一个特别规则，其相应的代码如例3中所示的那样。注意，std::move没有
 * 任何模板参数或者“触发”条件来决定是否将传递的参数转换为右值引用(简而言之就是不管传递的是什么，都将其转换为右值引用)，而std::forward会根据给定的模板
 * 参数来“转发”传递的参数及其潜在的属性(例如移动语义)。[例3]
 *   4.在例3中我们使用到了一个新的模板参数形式“T&&”，它虽然和具体类型X的右值引用形式“X&&”很相似，但两者具有截然不同的规则：
 * (a) 用于具体类型X的X&&是一个右值引用，它只能绑定一个可移动的对象(例如纯右值、将亡值)，它是可修改的，并且也可以从中“窃取”资源。
 * (b) 模板参数形式的T&&是一个“转发引用”，也被称为万能引用，它可以绑定可修改、不可修改或者是可移动对象，并且也会保留原对象的基本属性。
 * 需要注意，作为转发引用，T必须是一个模板参数的名字，而不能是依赖于模板参数的名字(例如std::vector<T>)，像std::vector<T>&&这种形式的引用仅是一个右值
 * 引用，并不能是转发引用。
 */
#include <iostream>

struct X{ };

//===============例1===============
namespace e1{

void g(X &lvalue){ std::cout << "lvalue" << std::endl; }
void g(const X &cvalue){ std::cout << "cvalue" << std::endl; }
void g(X &&rvalue){ std::cout << "rvalue" << std::endl; }

/* 转发左值引用 */
void f(X &lvalue){
    g(lvalue);
}

/* 转发const左值引用 */
void f(const X &cvalue){
    g(cvalue);
}

/* 转发右值引用 */
/**
 * 这里需要说明一点，虽然rvalue的声明是一个右值引用，但按照语言规则，移动语义(move semantics)不会随着参数传递而传递，这个限制主要是为了防止对象在不经意间被窃取
 * 资源，因此当我们在表达式中使用rvalue时，它仍然表现为一个左值，所以如果我们想要将rvalue转发给函数g，就需要使用std::move显式地将rvalue转换为一个右值。反之，如果
 * 我们不使用std::move，那么rvalue会因为其左值的特性而被转发给g(X&)，而非g(X&&)。
 */
void f(X &&rvalue){
    g(std::move(rvalue));
}

void func1(){
    X x;
    const X cx;

    f(x);
    f(cx);
    f(std::move(X()));
}

}

//===============例2===============
namespace e2{

template<typename T>
void f(T val){
    e1::g(val);
}

void func2(){
    X x;
    const X cx;

    f(x);
    f(cx);                     //cx被const修饰，但在f中，T被推断为X，const限定符丢失
    f(std::move(X()));  //即使传递的是右值，但在f中，T仍然被推断为X，右值语义丢失
}

}

//===============例3===============
namespace e3{
    
template<typename T>
void f(T &&val){
    e1::g(std::forward<T>(val)); //std::forward会根据模板参数T是否存在移动语义来决定是否将val转发为右值引用
}

void func3(){
    X x;
    const X cx;

    f(x);
    f(cx);
    f(std::move(X()));
}

}

int main(void){
    e1::func1();
    std::cout << "----------" << std::endl;
    e2::func2();
    std::cout << "----------" << std::endl;
    e3::func3();
    std::cout << "----------" << std::endl;

}
