#pragma once

class string {
public: 
    string();  
    ~string();
    string(const char *s); 
    string(string const &s); 
    string(string &&s);
    string &operator=(string const &s);
    string &operator=(string &&s);
    void push_back(char c);
    void print() const;
    const char *c_str();
private:
    struct context;
    struct context *c;
};
