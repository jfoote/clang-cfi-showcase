#include <iostream>

struct Base {
    Base() {}
    virtual ~Base() {}
    virtual void printMe(int i) { 
        std::cout << "Base::printMe " << i << "\n";
    }
};

struct Derived : Base {
    Derived() {}
    virtual ~Derived() {}

    virtual void printMe(int i) {
        std::cout << "Derived::printMe " << i << "\n";
    }
};

// imagine this is an attacker-created structure 
// in memory
struct Evil {
    Evil() {}
    virtual ~Evil() {}

    virtual void makeAdmin(int i) {
        std::cout << "CFI Prevents this control flow " << i << "\n";
        std::cout << "Evil::makeAdmin\n";
    }
};

int main(int argc, const char *argv[]) {

    Evil *eptr = new Evil();
    Derived* dptr = new Derived();

    (void)(argc);
    (void)(argv);

    dptr->printMe(55);
    
    // imagine a type confusion vulnerability
    // that does something similar
    dptr = reinterpret_cast<Derived*>(eptr);
    dptr->printMe(66);

    return 0;
}
