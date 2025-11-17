/**
 * 《特殊成员函数的模板》
 * 1.成员函数模板也可以用于特殊的成员函数，例如构造函数，并可能产生一些奇妙的特性。考虑例1中的代码，我们分别定义了两组构造函数，其中一组以字符串初始化
 *   Person，为了支持移动语义，我们重载了一个移动string对象的构造函数；另一组则是Person的拷贝构造函数和移动构造函数。当我们以左值初始化时，调用的是拷贝
 *   版本的构造函数，反之，使用右值初始化时，调用的是移动版本。[例1]
 * 2.现在让我们像例2一样把string那一组的构造函数改成函数模板，将传递过来的参数完美转发给成员str。在这之后，我们发现使用string初始化仍然正常，但如果使用
 *   一个左值的Person来初始化，就会得到“无匹配的函数”的错误，原因是编译器认为对于参数“Person&”，函数模板Person(Arg &&arg)要比我们定义的拷贝构造
 *   函数匹配的更好，所以使用函数模板而非我们的拷贝构造函数来初始化，导致了Person&被转发给了str，因此引发错误。而如果我们使用的是一个const的Person对象，
 *   则会因为比函数模板匹配的更好从而避免这个问题。我们可能会想到提供一个Person(Person&)版本的拷贝构造函数来解决这个问题，但这个办法只能解决一部分问题，
 *   当遇到Person的派生类时，编译器同样会选择函数模板而非我们的拷贝构造函数。彻底解决此问题需要使用到std::enable_if，我们将在后续介绍。[例2]
 */
#include <string>
#include <iostream>


//===============例1===============
namespace e1{
class Person{
public:
    Person(const std::string &str) : str_(str){ std::cout << "Person(string&)" << std::endl; }
    Person(std::string &&str) : str_(std::move(str)){ std::cout << "Person(string&&)" << std::endl; }

    Person(const Person &other) : str_(other.str_){ std::cout << "Person(Person&)" << std::endl; }
    Person(Person &&other) : str_(std::move(other.str_)){ std::cout << "Person(Person&&)" << std::endl;}

private:
    std::string str_;
};

void func1(){
    std::string str("Tom");
    Person p1(str);            //p1通过拷贝str进行初始化
    Person p2("Jerry");     //p2通过窃取从字面量Jerry生成的临时string对象的资源进行初始化

    Person p3(p1);           //p3通过拷贝p1进行初始化
    Person p4(std::move(p2)); //p4通过窃取p2的资源进行初始化
}
}

//===============例2===============
namespace e2{
class Person{
public:
    template<typename Arg>
    Person(Arg &&arg) : str_(std::forward<Arg>(arg)){ std::cout << "template Person(Arg)" << std::endl; }

    Person(const Person &other) : str_(other.str_){ std::cout << "Person(Person&)" << std::endl; }
    Person(Person &&other) : str_(std::move(other.str_)){ std::cout << "Person(Person&&)" << std::endl;}

private:
    std::string str_;
};

void func2(){
    std::string str("Tom");
    Person p1(str);
    Person p2("Jerry");

    //Person p3(p1);
    Person p4(std::move(p2));

    const Person cp1("Smith");
    Person p5(cp1);
}
}

int main(void){
    e1::func1();
    e2::func2();
}
