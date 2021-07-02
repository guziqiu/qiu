#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

class Array {
public:
   
    Array(int n = 10) {
        
        this->n = n;
        data = new int[n]; // new会调用构造函数，new是运算符,可以重载（malloc不会调用构造函数，malloc是函数）
    }
    Array(const Array &a) { // 深拷贝
        this->n = a.n;
        this->data = new int[this->n];
        for (int i = 0; i < this->n; i++) {
            this->data[i] = a.data[i];
        }
    }
    size_t size() const {
        return this->n;
    }

    int &operator[](int ind) {
        if (ind < 0 || ind >= n) return end;
        return data[ind];
    }

    const int &operator[](int ind) const {
        if (ind < 0 || ind >= n) return this->end;
        return this->data[ind];
    }
    
private:
    int *data;
    size_t n;
    int end;
   
};

ostream &operator<<(ostream &out, const Array &a) {// const 类型的引用只能调用const类型的方法
    out << "Array(" << &a << ") : ";
    for (int i = 0; i < a.size(); i ++) {  
        i && out << " ";
        cout << a[i];
    }
    return out;
}


int main() {

    Array a;
    for (int i = 0; i < a.size(); i++) {
        a[i] = rand() % 100;
    }

    cout << a << endl;

    Array b = a;
    cout << b << endl;
    b[1] = 16384;
    cout << a << endl;
    cout << b << endl;


    return 0;
}
