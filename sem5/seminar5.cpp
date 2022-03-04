#include <iostream> 
#include <map>
#include <vector> 
#include <sstream>
#include <string>
#include <cassert>  

using namespace std; 

class figure {
public: 
    figure() {}
    //этих функций не было и не должно быть в базовом классе 
    virtual figure *clone(vector<string> const & arg) = 0;  
    virtual void print() const = 0;  
    virtual string name() const = 0;  
};

class circle: public figure {  
public: 
    circle() {} 
    virtual figure *clone(vector<string> const &args) {
        assert(args.size() >= 3);
        circle *ret = new circle();  
        ret->x = stoi(args[0]);
        ret->y = stoi(args[1]); 
        ret->radius = stoi(args[2]); 
        return ret ; 
    }
    virtual string name() const {return "circle";} 
    virtual void print() const { 
        cout << "circle " << x << " " << y << " " << radius << "\n"; 
    }
private: 
    int x, y, radius; 
}; 

class line: public figure {  
public: 
    line() {}
    virtual figure *clone(vector<string> const &args) {
        assert(args.size() >= 4);
        line *ret = new line();  
        ret->x1 = stoi(args[0]);
        ret->y1 = stoi(args[1]); 
        ret->x2 = stoi(args[2]);
        ret->y2 = stoi(args[3]); 
        return ret ;
    }
    virtual string name() const {return "line";} 
    virtual void print() const { 
        cout << "line " << x1 << " " << y1 << " " << x2 << " " << y2 << "\n"; 
    }
private: 
    int x1, x2, y1, y2;  
};  

auto split(string const &s) { 
    stringstream inp(s);  
    vector<string> ret; 
    while(true) {
        string val; 
        inp >> val; 
        if(!inp) break; 
        ret.push_back(val);
    }
    return ret; 
}

int main() {
    map<string, figure*> factory; 
    vector<figure*> zigotes{
        new circle(), 
        new line() 
    }; 

    for(auto z: zigotes) {
        factory[z->name()] = z; 
    }
    vector<figure*> figures;  

    string s; 
    while(getline(cin, s)) { 
        auto args = split(s);  
        assert(!args.empty());
        string name = args[0]; 
        args.erase(args.begin());
        auto it = factory.find(name); 
        if(it == factory.end()) continue; 
        figures.push_back(it->second->clone(args)); 
    }

    for(auto f: figures) {
        f->print(); 
    } 
    return 0;
}