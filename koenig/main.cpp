//
//  main.cpp
//  koenig
//
//  Created by Klaus Ahrens on 25.05.21.
//

#include <iostream>

namespace N {
  void foo(const class T&);
  class T {
  public:
      void foo() { N::foo(*this); }
        //N::foo(*this); } // OR ::N::foo(*this); NOT: foo(*this);
    friend std::ostream& operator<<(std::ostream&, const T&);
    friend void foo (const T&);
  };
  // void foo(const class T&);
}

std::ostream& N::operator<<(std::ostream& o, const T&) {
//std::ostream& operator<<(std::ostream& o, const T&) {
    return o<<"T-Object"<<std::endl;
}

void N::foo(const T& t) {  std::cout << t; }
//void foo(const T& t) {  std::cout << t; }

//int main() {
//    T t;
//    t.foo();
//    foo(t);
//
//    std::cout << t;
//}

int main() {
    N::T t;
    t.foo();     // OK: scope durch t festgelegt!
    //foo(t);      // wäre ohne ADL fehlerhaft !
                 // dank ADL ok:
    //::foo(t);    // wäre ohne ADL noch akzeptabel
    // nicht aber:
    N::operator<<(std::cout, t); // anstelle von:
    std::cout << t;  // nur mit ADL korrekt
}
