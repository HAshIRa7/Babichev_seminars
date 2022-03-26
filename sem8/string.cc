#include <stdio.h>  
#include <memory.h>
#include <string.h>
#include <vector>
#include <utility>
#include "string.h"

struct string::context {
    char* body;                                                        
    size_t siz, allocated; 
    ~context() {
        delete [] body;
    }
};

#define T printf("%s(%s)\n", __PRETTY_FUNCTION__, c_str())
string::string() {  
        c = new context();
        c->siz = 0; 
        c->allocated = 16; 
        c->body = new char[c->allocated];  
        T; 
    } 
string::~string() {  
        T; 
        delete c;
    }
   
string::string(const char *s) {
        c = new context();
        c->siz = strlen(s);
        c->allocated = c->siz+1; 
        c->body = new char[c->allocated]; 
        memcpy(c->body, s, c->allocated * sizeof(char));
        T;
    }

string::string(string const &s) { 
        c = new context();
        c->siz = s.c->siz; 
        c->allocated = s.c->allocated; 
        c->body = new char[c->allocated]; 
        memcpy(c->body, s.c->body, c->allocated * sizeof(char));
        T;
    }

string::string(string &&s) {
        c = s.c;
        s.c->body = nullptr;
        T;
    }

string & string::operator=(string const &s) {
        delete [] c->body;  
        c->siz = s.c->siz; 
        c->allocated = s.c->allocated; 
        c->body = new char[c->allocated]; 
        memcpy(c->body, s.c->body, c->allocated * sizeof(char)); 
        T;
        return *this;
    }

string & string::operator=(string &&s) {
        delete [] c->body;  
        c->siz = s.c->siz; 
        c->allocated = s.c->allocated; 
        c->body = s.c->body;
        s.c->body = nullptr;
        T;
        return *this;
    }
    
void string::push_back(char d) {
        if (c->siz + 1 >= c->allocated) {
            c->allocated *= 2; 
            char* newbody = new char[c->allocated]; 
            for(size_t i = 0; i < c->siz; i++) {
                newbody[i] = c->body[i]; 
            } 
            delete [] c->body; 
            c->body = newbody; 
        }
        c->body[c->siz++] = d; 
    } 

void string::print() const { 
        for(size_t i = 0; i < c->siz; i++) {
            putchar(c->body[i]); printf("\n");
        }
    } 

    const char *string::c_str() { 
        if (c->body == nullptr) return "(null)";
        c->body[c->siz] = '\0';
        return  c->body;
    }

