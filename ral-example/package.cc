//
// Created by Michael Smith on 12/8/15.
//

#include <boost/algorithm/string/join.hpp>
#include "package.hpp"

namespace Puppet {
    using namespace std;

    Package::Package(string name, State ensure, Version version, string source)
            : Resource(name, ensure), version_(move(version)), source_(move(source)) {}

    Package::Version const& Package::version() const
    {
        return version_;
    }

    string const& Package::source() const
    {
        return source_;
    }

    static string print_version(Package::Version const& version)
    {
        return to_string(get<0>(version)) + "." + to_string(get<1>(version)) + "." + to_string(get<2>(version));
    }

    string Package::print() const
    {
        return "package { '" + name() + "':\n\tensure => " + print_ensure(ensure()) + ",\n\tversion => '" + print_version(version()) + "',\n\tsource => '" + source() + "'\n}";
    }

}
