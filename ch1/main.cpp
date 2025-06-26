/**
 * ch1: 如果将定义于某个名称空间的类型用于模板时，C++在查找模板时除了在当前的作用域中查找外，还会去定义该模板的名称空间中查找，
 * 即使并未使用using引入该名称空间。因此，一旦当前作用域中存在着与名称空间中同名的模板，就可能产生二义性错误。避免此错误的方法
 * 是通过作用域操作符显式地指出模板的位置。
 */

 #include <iostream>

 namespace bar
 {
    struct Number{
        int data;
    };

    template<typename T>
    void showNumber(T number){
        std::cout << number.data << std::endl;
    }
 } 

template<typename T>
void showNumber(T number){
    std::cout << number.data << std::endl;
}
 
 int main(void){
    bar::Number number;
    number.data = 100;

    //showNumber(number);  //有多个匹配的模板
    ::showNumber(number);   //显式指出使用全局名称空间中的模板
 }
 