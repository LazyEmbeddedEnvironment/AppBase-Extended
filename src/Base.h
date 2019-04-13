//
// Created by jonb on 3/21/19.
//
#pragma once

#include <string>
#include <friendappbase/friend/GetTypeName.h>

using namespace std;

namespace Friend {
namespace DDS {

template <typename T>
class Base {
public:
    Base();
    virtual ~Base() {};
    explicit Base(const string& name);
    virtual void create(const string& name);
    virtual T read();
    virtual bool isConnected() = 0;
private:
    string _myName;
    T _lastState;
};

// Implemantation
template<typename T>
Base<T>::Base() = default;
template<typename T>
Base<T>::Base(const string &name) {
    this->create(name);
}
template<typename T>
void Base<T>::create(const string &name) {
    this->_myName = GetTypeName<T>()+"."+name;
}
template<typename T>
T Base<T>::read() {
    return _lastState; // TODO what to do for initial conditions
}

} // namespace DDS
} // namespace Friend

