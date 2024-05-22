#include <iostream>
#include<memory>
using namespace std;

template<class T>
class MyUinque {
    T* p = nullptr;
    int* count = nullptr;
public:
    MyUinque(T* p) {
        this->p = p;
        this->count = new int(1);
        cout << "Construct" << endl;
    }
    ~MyUinque() {
        if (--(*count) == 0) {
            delete p;
            delete count;
            cout << "Destruct" << endl;
        }
    }
    T* get() const {
        return p;
    }
    T& operator*() {
        return *p;
    }
    T* operator->() {
        return p;
    }
    MyUinque(const MyUinque& other) : p(other.p), count(other.count) {
        ++(*count);
    }
    MyUinque& operator=(const MyUinque& other) {
        if (this != &other) {
            if (--(*count) == 0) {
                delete p;
                delete count;
            }
            p = other.p;
            count = other.count;
            ++(*count);
        }
        return *this;
    }
    MyUinque(MyUinque&& other) noexcept : p(other.p), count(other.count) {
        other.p = nullptr;
        other.count = nullptr;
    }
    MyUinque& operator=(MyUinque&& other) noexcept {
        if (this != &other) {
            if (--(*count) == 0) {
                delete p;
                delete count;
            }
            p = other.p;
            count = other.count;
            other.p = nullptr;
            other.count = nullptr;
        }
        return *this;
    }
};
template<class T, class... Args>
MyUinque<T> Make_MyUinque(Args&&... args) {
    return MyUinque<T>(new T(forward<Args>(args)...));
}
class MyPoint {
    int x, y;
public:
    MyPoint(int x, int y) : x(x), y(y) {}
    void print() const {
        cout << "Point(" << x << "," << y << ")" << endl;
    }
};

int main() {
    auto point1 = Make_MyUinque<MyPoint>(1, 2);
    auto point2 = point1;
    point1->print();
    point2->print();

    return 0;
}
