#pragma once

#include <appbase/application.hpp>

using namespace std;


namespace Friend {
namespace AppBase {

namespace bpo = boost::program_options;
using bpo::options_description;
using bpo::variables_map;

class AppBase : public appbase::plugin<AppBase> {
public:
    APPBASE_PLUGIN_REQUIRES();
    virtual void set_program_options( options_description& cli, options_description& cfg ) override;
    void plugin_initialize( const variables_map& options );
    void plugin_startup();
    void plugin_shutdown();

    AppBase();
    virtual ~AppBase();
    int getInstance();
    virtual string getAppName();
    void printVariableMap(const bpo::variables_map vm);
private:
    virtual void setInstance(const int &instance);
    int _instance;
};

} // namespace DDSLinker
} // namespace Friend

