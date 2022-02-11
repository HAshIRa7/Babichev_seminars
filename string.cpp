#include <stdio.h>  
#include <memory.h>

#define T printf("%s(%s)\n", __PRETTY_FUNCTION__, c_str())
class string {
    char* body; 
    size_t siz, allocated; 
public: 
    string() {  
        siz = 0; 
        allocated = 16; 
        body = new char[allocated];  
        T; 
    } 
    ~string() {  
        T; 
        delete [] body;  
    } 
    string(string const &s) { 
        siz = s.siz; 
        allocated = s.allocated; 
        body = new char[allocated]; 
        memcpy(body, s.body, allocated * sizeof(char));
    }

    string &operator=(string const &s) {
        delete [] body;  
        siz = s.siz; 
        allocated = s.allocated; 
        body = new char[allocated]; 
        memcpy(body, s.body, allocated * sizeof(char)); 
        return *this;
    }
    void push_back(char c) {
        if (siz + 1 >= allocated) {
            allocated *= 2; 
            char* newbody = new char[allocated]; 
            for(size_t i = 0; i < siz; i++) {
                newbody[i] = body[i]; 
            } 
            delete [] body; 
            body = newbody; 
        }
        body[siz++] = c; 
    } 
    void print() const { 
        for(size_t i = 0; i < siz; i++) {
            putchar(body[i]); printf("\n");
        }
    } 

    const char *c_str() { 
        body[siz] = '\0';
        return body;
    }
};    

/* 
Правило трех  
    если объект содержит нами управляемые указатели, то надо реализовать деструктор 
        1) Деструктор
        2) Конструктор копирования 
        3) Оператор копирования 
*/

int main() {
    string s; 
    s.push_back('f'); s.push_back('o'); s.push_back('o'); 
    s.print(); 
    string t; 
    t = s; 
    t.print(); 
    return 0;
}