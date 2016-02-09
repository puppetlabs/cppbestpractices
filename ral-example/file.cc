//
// Created by Michael Smith on 12/8/15.
//

#include "file.hpp"

namespace Puppet {
    using namespace std;

    File::File(string name, File::State ensure, boost::filesystem::path path, string source)
            : Resource(move(name), ensure), path_(move(path)), source_(move(source)) {}

    boost::filesystem::path const& File::path() const
    {
        return path_;
    }

    string const& File::source() const
    {
        return source_;
    }

    string File::print() const
    {
        return "file { '" + name() + "':\n\tensure => " + print_ensure(ensure()) + ",\n\tpath => '" + path().string() + "',\n\tsource => '" + source() + "'\n}";
    }

}
