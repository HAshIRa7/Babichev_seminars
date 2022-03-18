#include <memory>
#include <memory.h>
#include <vector>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class matrix {
public:
    matrix(size_t n, size_t m): n(n), m(m) {
        body = new T[n*m];
    }

    matrix(matrix const &oth): m(oth.m), n(oth.n) {
        body = new T[n*m];
        memcpy(body, oth.body, sizeof(T)*n*m);
    }

    matrix & operator=(matrix const &oth) { 
        m = oth.m;
        n = oth.n; 
        delete [] body;
        body = new T[n*m];
        memcpy(body, oth.body, sizeof(T)*n*m);
        return *this;
    }

    ~matrix() {
        delete [] body;
    }

    size_t get_n() const { return n; }
    size_t get_m() const { return m; }

    matrix transpose() const {
        matrix ret(m,n);
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                ret[j][i] = this[0][i][j];
            }
        }
        return ret;
    }

    T* operator[](size_t arg) {
        assert(arg < n);
        return body + arg*m;
    }

    T const * operator[](size_t arg) const {
        assert(arg < n);
        return body + arg*m;
    }

    matrix operator *(matrix const &a) {
        assert(m == a.n);
        matrix c(n, a.m);
        matrix b = a.transpose();
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < a.m; j++) {
                c[i][j] = 0;
                for (size_t k = 0; k < m; k++) {
                    c[i][j] += this[0][i][k] * b[j][k];
                }
            }
        }
        return c;
    }

    static void 
         partial_mul(matrix const *a, 
                     matrix const *b,
                     matrix       *c,
                     size_t    start,
                     size_t      end) {
        for (size_t i = start; i < end; i++) {
            for (size_t j = 0; j < a->m; j++) {
                (*c)[i][j] = 0;
                for (size_t k = 0; k < a->m; k++) {
                    (*c)[i][j] += (*a)[i][k] * (*b)[j][k];
                }
            }                                                  
        }
    }

    matrix parallel_mul(matrix const &a) {
        assert(m == a.n);
        matrix c(n, a.m);                                      
        matrix b = a.transpose();

        thread t1(partial_mul,this, &b, &c, 0,       1*a.n / 4);
        thread t2(partial_mul,this, &b, &c, 1*a.n/4, 2*a.n / 4);
        thread t3(partial_mul,this, &b, &c, 2*a.n/4, 3*a.n / 4);
        thread t4(partial_mul,this, &b, &c, 3*a.n/4, 4*a.n / 4);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        return c;
    }
    

    template<typename Y>
    friend ostream & operator <<(ostream &os, matrix<Y> const &m);
private:
    size_t n, m;
    T* body; 
};

template <typename T>
ostream & operator <<(ostream &os, matrix<T> const &m) {
    os << "[" << m.n << "," << m.m << "]= \n";
    for (size_t i = 0; i < m.n; i++) {
        for (size_t j = 0; j < m.m; j++) {
            os << m[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

template<typename T>
void randomize_matrix(matrix<T> &m) {
    for (size_t i = 0; i < m.get_n(); i++) {
        for (size_t j = 0; j < m.get_m(); j++) {
            m[i][j] = rand()%10;
        }
    }
}

int main(int argc, char **argv) {
    const size_t SIZE = argc > 1 ? atoi(argv[1]) : 1000;
    matrix<int> a(SIZE,SIZE), b(SIZE,SIZE);
    randomize_matrix(a);
    randomize_matrix(b);
    clock_t start = clock();
    auto c = a * b;
    clock_t end = clock();
    long long sum = 0;
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            sum += c[i][j];
        }
    }
    printf("sum=%lld time=%.3f\n", 
            sum, (double)(end - start)/CLOCKS_PER_SEC);
    start = clock();
    c = a.parallel_mul(b);
    end = clock();
    sum = 0;
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            sum += c[i][j];
        }
    }
    printf("sum=%lld time=%.3f\n",                             
            sum, (double)(end - start)/CLOCKS_PER_SEC);

}
