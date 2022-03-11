#include <stdio.h>  
#include <memory.h>
#include <string.h>
#include <vector>
#include <utility>

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
   
    string(const char *s) {
        siz = strlen(s);
        allocated = siz+1; 
        body = new char[allocated]; 
        memcpy(body, s, allocated * sizeof(char));
        T;
    }

    string(string const &s) { 
        siz = s.siz; 
        allocated = s.allocated; 
        body = new char[allocated]; 
        memcpy(body, s.body, allocated * sizeof(char));
        T;
    }

    string(string &&s) {
        siz = s.siz;
        allocated = s.allocated;
        body = s.body;
        s.body = nullptr;
        T;
    }

    string &operator=(string const &s) {
        delete [] body;  
        siz = s.siz; 
        allocated = s.allocated; 
        body = new char[allocated]; 
        memcpy(body, s.body, allocated * sizeof(char)); 
        T;
        return *this;
    }

    string &operator=(string &&s) {
        delete [] body;  
        siz = s.siz; 
        allocated = s.allocated; 
        body = s.body;
        s.body = nullptr;
        T;
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
        if (body == nullptr) return "(null)";
        body[siz] = '\0';
        return body;
    }
};    

/* 
Правило пяти 
    если объект содержит нами управляемые указатели, то надо реализовать деструктор 
        1) Деструктор
        2) Конструктор копирования 
        3) Оператор копирования 
        4) Конструктор переноса
        5) Оператор переноса
*/

int main() {
#if 0
    string s; 
    s.push_back('f'); s.push_back('o'); s.push_back('o'); 
    s.print(); 
    string t; 
    t = s; 
    t.print(); 
#endif    
    std::vector<string> v;
    for (int i = 0; i < 5; i++) {
        string s("abra");
        string t = std::move(s);
        t.push_back('0' + i);
        v.emplace_back(t);
    }
    return 0;
}