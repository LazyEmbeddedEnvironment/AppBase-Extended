#include <iostream>
#include <friend/appbase/AppBase.h>


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

    AppBase::AppBase() {}
    AppBase::~AppBase() {}
    int AppBase::getInstance() {
        return _instance;
    }

    void AppBase::setInstance(const int &instance) {
        _instance = instance;
    }




} // namespace DDSLinker
} // namespace Friend
