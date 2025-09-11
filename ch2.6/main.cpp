/**
 * 《可变推断指示、可变基类和using》
 * 1.可变表达式也可使用在推断指示中，因此我们可以在可变参数模板上使用推断指示
 * 2.可以在类模板的继承中使用可变表达式，以此让该模板可以继承类型可变、数量可变的基类
 */
#include <iostream>

//================================
/**
 * 《可变推断指示》
 * 在这个例子中，我们定义了模板Is_same_types，该模板可用于判断多个类型是否都是相同的类型。然后我们利用推断指示，在原本的<T, U...>模板参数前添加了一个类型int，
 * 使其只能用于判断所有类型是否都是int类型的情况。
 */
template<typename T, typename... U>
struct Is_same_types{
    std::enable_if_t<(std::is_same_v<T, U> && ...), std::string> str; //“std::is_same_v<T, U> && ...”展开为std::is_same_v<T, U1> && std::is_same_v<T, U2> &&std::is_same_v<T, U3>以此类推
    constexpr operator bool() { return true; }
};

/* 通过推断指示让Is_same_types固定判断int类型 */
template<typename T, typename... U>
Is_same_types(T, U...) -> Is_same_types<int, T, U...>;  //可以看到，参数包可以在推断指示中展开，因此我们就可以对可变参数模板进行推断指示，将其推断为我们想要的版本

void func1(){
    std::cout << Is_same_types<int, int, int>() << std::endl;
}

//================================
/**
 * 《可变基类》
 * 通过定义一个可变参数模板Overlaoder，并且在继承时使用可变表达式，我们就得到了一个基类的数量可变、类型可变的派生类。当实例化Overloader时，
 * 通过指定不同数量、类型的基类作为类型参数，我们就可以让Overloader继承相应的基类。
 */

template<typename... Bases>
class Overloader : public Bases...{  //对继承操作使用可变表达式，Overloader就可继承参数包中的所有类型。即展开为Overloader : public Base1, Base2, Base3
public:
    using Bases::operator()...;           //对using声明使用可变表达式，从而引入参数包中每个基类的operator()操作符
};

/**
 * 以下是拥有可变基类的Overloader模板结合using声明的一种用途，我们将通过Overloader模板将CustomEq和CustomHash两个类型的operator()操作符
 * 合并到Overloader实例中。
 */
class Custom{
public:
    Custom(const std::string &name) : m_name(name){}
    std::string name() const { return m_name; }
private:
    std::string m_name;
};

class CustomEq{
public:
    bool operator() (const Custom &lhs, const Custom &rhs) const{
        return lhs.name() == rhs.name();
    }
};

class CustomHash{
public:
    std::size_t operator() (const Custom &custom) const{
        return std::hash<std::string>()(custom.name());
    }
};

class CustomSize{
public:
    std::size_t operator() (const Custom &custom) const{
        return custom.name().size();
    }
};

void func2(){
    /**
     * Overloader<CustomEq, CustomeHash>实例化了一个继承CustomEq和CustomHash的Overloader版本，由于可变表达式“using Bases::operator()...”的缘故，
     * CustomEq和CustomHash中的operator()操作符都被引入到Overloader中，两个操作符之间互相重载。然后，我们使用using为其声明了一个别名CustomOp，方便
     * 后续的使用。
     */
    using CustomOp = Overloader<CustomEq, CustomHash>; //展开为Overlaoder : public CustomEq, CustomHash
    
     /* 可以看到，我们现在只创建CustomOp的对象即可利用重载的特性分别对Custom对象进行处理，而无需再分别创建CustomEq和CustomHash对象 */
    CustomOp()(Custom("ABC"));
    CustomOp()(Custom("ABC"), Custom("ABC"));

    /**
     * 下方的例子是个错误的示范，由于CustomHash和CustomSize的operator()操作符都只接受一个Custom对象，按照重载的规则，当有多个重载函数匹配时就会产生歧义，
     * 因此在使用此特性时要注意引入的基类函数的参数列表之间要存在差异，避免出现歧义。
     */
    using Custom3Op = Overloader<CustomEq, CustomHash, CustomSize>;
    Custom3Op()(Custom("ABC"), Custom("ABC"));  //正常，由于单参数的operator()没有使用，因此该代码没有实例化
    //Custom3Op()(Custom("ABC"));                             //错误，使用到了单参数版本的operator()，由于有多个重载函数匹配，所以出错
}

int main(void){
    func1();
    func2();
}
