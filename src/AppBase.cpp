#include <iostream>
#include <friend/appbase/AppBase.h>
#include <friend/appbase/AppName.h>


namespace Friend {
namespace AppBase {
    void AppBase::set_program_options(options_description &cli, options_description &cfg) {
        cli.add_options()("instance,i",bpo::value<int>()->default_value(0),
                "This application's external process number");
    }
    void AppBase::plugin_initialize(const variables_map &options) {
        std::cout << "initialize "<< name() <<"\n";
        auto i = options.find("instance");
        if (i == options.end()) std::cerr << "\n Unable to extract external process number from arguments \n";
        setInstance(i->second.as<int>());
        std::cout << "initialized "<< name() << " instance " << getInstance() << "\n";
    }
    void AppBase::plugin_startup() { std::cout << "starting "<< name() <<"\n"; }
    void AppBase::plugin_shutdown() { std::cout << "shutdown "<< name() <<"\n"; }

    // Public
    AppBase::AppBase() {}
    AppBase::~AppBase() {}
    int AppBase::getInstance() {
        return _instance;
    }
    string AppBase::getAppName() {
        return app_name_string;
    }
    // Private
    void AppBase::setInstance(const int &instance) {
        _instance = instance;
    }

    void AppBase::printVariableMap(const bpo::variables_map vm) {
        for (auto it = vm.begin(); it != vm.end(); it++) {
            std::cout << "> " << it->first;
            if (((boost::any) it->second.value()).empty()) {
                std::cout << "(empty)";
            }
            if (vm[it->first].defaulted() || it->second.defaulted()) {
                std::cout << "(default)";
            }
            std::cout << "=";

            bool is_char;
            try {
                boost::any_cast<const char *>(it->second.value());
                is_char = true;
            } catch (const boost::bad_any_cast &) {
                is_char = false;
            }
            bool is_str;
            try {
                boost::any_cast<std::string>(it->second.value());
                is_str = true;
            } catch (const boost::bad_any_cast &) {
                is_str = false;
            }

            if (((boost::any) it->second.value()).type() == typeid(int)) {
                std::cout << vm[it->first].as<int>() << std::endl;
            } else if (((boost::any) it->second.value()).type() == typeid(bool)) {
                std::cout << vm[it->first].as<bool>() << std::endl;
            } else if (((boost::any) it->second.value()).type() == typeid(double)) {
                std::cout << vm[it->first].as<double>() << std::endl;
            } else if (is_char) {
                std::cout << vm[it->first].as<const char *>() << std::endl;
            } else if (is_str) {
                std::string temp = vm[it->first].as<std::string>();
                if (temp.size()) {
                    std::cout << temp << std::endl;
                } else {
                    std::cout << "true" << std::endl;
                }
            } else { // Assumes that the only remainder is vector<string>
                try {
                    std::vector<std::string> vect = vm[it->first].as<std::vector<std::string> >();
                    uint i = 0;
                    for (std::vector<std::string>::iterator oit = vect.begin();
                         oit != vect.end(); oit++, ++i) {
                        std::cout << "\r> " << it->first << "[" << i << "]=" << (*oit) << std::endl;
                    }
                } catch (const boost::bad_any_cast &) {
                    std::cout << "UnknownType(" << ((boost::any) it->second.value()).type().name() << ")" << std::endl;
                }
            }
        }
    }


} // namespace DDSLinker
} // namespace Friend
