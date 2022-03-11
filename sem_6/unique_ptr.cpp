#include <memory> 
#include <iostream> 
using namespace std; 
//чтобы гарантировать что только одна функция имеет доступ к unique_ptr 
unique_ptr<int> print(unique_ptr<int> p) { // указатель p принадлежит функции тут же освобождается 
    cout << *p << "\n"; 
    return move(p); 
}
int main() {
    unique_ptr<int> p(new int(5)); // у unique_ptr нет копий 
    //print(p); 
    // нельзя передать в качеству аргумента в функцию (помогает move)
    p = print(move(p));
    // т.е тут Segmentation Fault
    //cout << *p << "\n";   
    if(p) {
        cout << *p << "\n";
    }
    
}