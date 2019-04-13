#include "ddslinker/Input.h"

#include <iostream>
#include <ddslinker/Input.h>


namespace Friend {
namespace DDS {
template<typename T>
Input<T>::Input() {}
template<typename T>
Input<T>::Input(const string &name) {

}
template<typename T>
Input<T>::Input(const string &name, const Input::readCallback &callback) {

}
template<typename T>
void Input<T>::create(const string &name) {

}
template<typename T>
void Input<T>::create(const string& name, const readCallback& callback) {

}


    void TemporaryFunction (){ Input<int> tempObj; } // Useless but crucial
} // namespace DDSLinker
} // namespace Friend
