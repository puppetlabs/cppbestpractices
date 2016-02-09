#pragma once

#include <boost/filesystem.hpp>
#include "resource.hpp"

namespace Puppet {

    class File : public Resource {
    public:
        File(std::string name, State ensure = State::present, boost::filesystem::path path = {}, std::string source = {});
        ~File() override {}

        boost::filesystem::path const& path() const;
        std::string const& source() const;

        std::string print() const override;
    private:
        boost::filesystem::path path_;
        std::string source_;
    };

}
