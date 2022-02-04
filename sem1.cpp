#include <stdio.h>  
#include <iostream>
#include <string>

#define T printf("%s\n", __PRETTY_FUNCTION__)  

using namespace std; 

class car {
public: 
    car(int nam) {//Конструктор 
        T;  
        name = nam;
    } 

    ~car() {//Деструктор 
        T; 
    }

    void print() {
        cout << name << "\n";
    }  

    void set_name(int nam) {
        name = nam;
    } 

    auto get_name() {
        return name; 
    }
private: 
    int name; 
};

int main() {
    car mers(600), tt(34);  
    cout << mers.get_name() << "\n";
    return 0;
}