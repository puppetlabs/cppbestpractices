#include <iostream>
#include <vector>
#include <map>
#include "resource.hpp"
#include "file.hpp"
#include "package.hpp"
#include "service.hpp"

using namespace std;

int main() {
    using namespace Puppet;

    //----- Using and printing individual resources. -----
    Resource r("foo", Resource::State::present);
    cout << r.print() << endl;

    File file_foo("foo");
    cout << file_foo << endl;

    Package pkg_foo("foo", Resource::State::absent);
    cout << pkg_foo << endl;

    Service svc_foo("foo");
    cout << svc_foo << endl;

    Service svc_bar("bar", Resource::State::present, true);
    cout << svc_bar << endl;

    cout << endl;

    //----- Creating a graph of resources. -----
    unique_ptr<Resource> file_f2{new File("f2")};

    vector<shared_ptr<Resource>> resources;
    resources.emplace_back(move(file_f2));
    resources.emplace_back(make_shared<File>("f1", Resource::State::present, "/tmp/f1", "file:///path/to/f1"));
    resources.emplace_back(make_shared<Service>("s1", Resource::State::present));
    resources.emplace_back(make_shared<Package>("p1", Resource::State::absent));

    for (auto &&r : resources) {
        cout << *r << endl;
    }

    multimap<shared_ptr<Resource>, shared_ptr<Resource>> graph;
    graph.insert(make_pair(resources[0], resources[2]));
    graph.insert(make_pair(resources[0], resources[1]));

    for (auto &&kv : graph) {
        cout << *kv.first << " ->\n";
        cout << *kv.second <<  endl;
    }

    return 0;
}
