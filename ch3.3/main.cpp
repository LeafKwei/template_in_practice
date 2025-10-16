/**
 * 《使用this ->》
 * 1.对于一些继承自基类Base，而Base又依赖于模板参数T的类模板，在这些模板内部使用直接某个名字(假设为)foo有时可能并不等同于使用this -> foo，尽管
 *   foo是通过继承得到的。当我们直接使用foo时，等待我们的有两种情况：要么是编译出错，要么是foo被视为了定义在类外部的某个全局函数。解决这个问题
 *   的办法是通过this -> foo或Base<T>::foo的方式使用foo。[例1]
 */

 /**
  * 《用于数组和字符串字面量的模板》
  * 1.当我们向模板传递数组和字符串字面量时，如果模板的参数是引用形式，那么数组和字符串字面量的类型就不会退化(decay)，也就是说，当我们传递诸如
  *   "hello"这种字面量时，它的类型将会保持const char [6]，而不会退化为const char*，这可能会在我们传递不同长度的数组或字符串字面量时造成问题，
  *   因为这些数组或字符串字面量被视为不同的类型(例如char[5]和char[6]被视为不同类型)。[例2]
  * 2.我们可以编写专门用于处理数组和字符串字面量的模板，只要在参数中表现出数组的特征即可。编译器会在可用模板中选择最为特例、最契合参数的那一个。[例3]
  * 3.通过重载函数模板，我们甚至还可以提供一个专门处理字符串数组/字面量的模板。[例4]
  */
#include <iostream>

//===============例1===============
template<typename T>
class Base{
public:
  void foo(){}
};

template<typename T>
class Derived : public Base<T>{
public:
  void bar(){
    //foo();                 //直接调用foo时，G++会提示foo没有依赖模板参数的实参，然后终止编译
    this -> foo();       //使用this -> foo()可以通过编译
    Base<T>::foo();  //使用Base<T>::foo()也可通过编译
  }
};

void func1(){
  Derived<int> d;
  d.bar();
}

//===============例2===============
template<typename T>
void nondecay(T &arg){
  std::cout << typeid(arg).name() << std::endl;
}

template<typename T>
void decay(T arg){
  std::cout << typeid(arg).name() << std::endl;
}

void func2(){
  nondecay("Hello");
  decay("hello");
}

//===============例3===============
/* 一个通用模板 */
template<typename T>
void printArray(T array){
  std::cout << "I do noting." << std::endl;
}

/* 对数组特别处理的模板 */
template<typename T, int N>
void printArray(T (&array)[N]){
  for(int i = 0; i < N; i++){
    std::cout << array[i] << std::endl;
  }
}

void func3(){
  /* 不妨注释掉第二个模板printArray(T (&array)[N])，看看会发生什么 */
  const int a1[5] = {1, 2, 3, 4, 5};
  const char a2[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
  const char a3[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

  printArray(a1);      //printArray被实例化为T为int，N为5的版本
  printArray(a2);      //printArray被实例化为T为char，N为6的版本

  /**
   * 即使数组a2和a3的元素类型都为char，但由于两者的长度不同，所以a2和a3两者分别是不同的类型char[6]和char[7]，因此编译器不会采用为char[6]实例化的版本，而是
   * 会为char[7]重新实例化一个版本
   */
  printArray(a3);      //printArray被实例化为T为char，N为7的版本
}

//===============例4===============
template<int N>
void printArray(const char (&array)[N]){
  for(int i = 0; i < N; i++){
    std::cout << "ch" << i << " is " << array[i] << std::endl;
  }
}

void func4(){
  const int a1[5] = {1, 2, 3, 4, 5};
  const char a2[6] = {'a', 'b', 'c', 'd', 'e', 'f'};

  printArray(a1);   //采用printArray<T,int N>
  printArray(a2);   //采用printArray<int N>
  printArray("Hello World!"); //采用printArray<int N>
}

int main(void){
  func1();
  func2();
  func3();
  func4();
}
