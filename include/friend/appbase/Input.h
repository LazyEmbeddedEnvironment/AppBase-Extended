#pragma once

#include <string>
#include <functional>

#include "../../../src/Base.h"

using namespace std;

namespace Friend {
namespace DDS {

template <typename T>
class Input : public Friend::DDS::Base<T> {
public:
    typedef function<void(T&)> readCallback;
    Input();
    explicit Input(const string& name);
    Input(const string& name, const readCallback& callback);
    virtual void create(const string& name);
    virtual void create(const string& name, const readCallback& callback);
    bool isConnected() override { return false; };
private:
    T _lastState;
    readCallback _callback;

};
} // namespace DDSLinker
} // namespace Friend

