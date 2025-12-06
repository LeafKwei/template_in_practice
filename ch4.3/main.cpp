#include <iostream>

struct A{ using type=int; };
struct B{};

template<typename T, typename=typename T::type>
void checkType(){
	std::cout << "Type A." << std::endl;
}
int main(void){
    //checkType<A>();
	checkType<B>();
}
