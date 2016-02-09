#pragma once

#include <tuple>
#include "resource.hpp"

namespace Puppet {

    class Package : public Resource {
    public:
        using Version = std::tuple<unsigned int, unsigned int, unsigned int>;

        Package(std::string name, State ensure = State::present, Version version = {}, std::string source = {});
        ~Package() override {};

        Version const& version() const;
        std::string const& source() const;

        std::string print() const override;
    private:
        Version version_;
        std::string source_;
    };

}
