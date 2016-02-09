//
// Created by Michael Smith on 12/8/15.
//

#include "resource.hpp"
#include <cassert>

namespace Puppet {

    Resource::Resource(std::string name, State ensure) : name_(std::move(name)), ensure_(ensure) { }

    Resource::State Resource::ensure() const
    {
        return ensure_;
    }

    std::string const& Resource::name() const
    {
        return name_;
    }

    std::string Resource::print_ensure(Resource::State state)
    {
        switch (state) {
            case Resource::State::present: return "present";
            case Resource::State::absent:  return "absent";
        }
    }

    std::string Resource::print() const
    {
        return "resource { '" + name() + "':\n\tensure => " + print_ensure(ensure()) + "\n}";
    }

}
