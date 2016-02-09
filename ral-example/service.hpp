#pragma once

#include <boost/optional.hpp>
#include "resource.hpp"

namespace Puppet {

    class Service : public Resource {
    public:
        Service(std::string name, State ensure = State::present, boost::optional<bool> enable = {});
        ~Service() override {}

        boost::optional<bool> const& enable() const;

        std::string print() const override;
    private:
        boost::optional<bool> enable_;
    };

}
