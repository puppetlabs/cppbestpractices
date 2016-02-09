#pragma once

#include <string>
#include <memory>

namespace Puppet {

    class Resource {
    public:
        enum class State {
            present, absent
        };

        Resource(std::string name, State ensure);
        virtual ~Resource() {}

        State ensure() const;
        std::string const& name() const;

        virtual std::string print() const;
        static std::string print_ensure(State ensure);

        friend std::ostream& operator<< (std::ostream& stream, const Resource& r)
        {
            stream << r.print();
            return stream;
        }

    private:
        State ensure_;
        std::string name_;
    };

}
