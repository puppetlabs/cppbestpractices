//
// Created by Michael Smith on 12/8/15.
//

#include "service.hpp"

namespace Puppet {
    using namespace std;

    Service::Service(std::string name, State ensure, boost::optional<bool> enable)
            : Resource(move(name), ensure), enable_(std::move(enable)) {}

    boost::optional<bool> const& Service::enable() const
    {
        return enable_;
    }

    std::string Service::print() const
    {
        auto enable_s = enable() ? (string(",\n\tenable => ") + (*enable() ? "true" : "false") + ",") : "";
        return "package { '" + name() + "':\n\tensure => " + print_ensure(ensure()) + enable_s + "'\n}";
    }

}
