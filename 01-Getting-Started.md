<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [Getting Started Resources](#getting-started-resources)
  - [The C++ Language](#the-c-language)
    - [Study Guide](#study-guide)
    - [Language References](#language-references)
    - [Community](#community)
    - [Practitioner Knowledge](#practitioner-knowledge)
      - [Books](#books)
      - [Blogs and Videos](#blogs-and-videos)
    - [Tooling](#tooling)
  - [Starting a Project](#starting-a-project)
    - [Libraries](#libraries)
      - [Boost [∞](http://www.boost.org/)](#boost-)
      - [Leatherman [∞](https://github.com/puppetlabs/leatherman)](#leatherman-)
      - [horsewhisperer [∞](https://github.com/puppetlabs/horsewhisperer)](#horsewhisperer-)
      - [yaml-cpp [∞](https://github.com/jbeder/yaml-cpp)](#yaml-cpp-)
      - [INI [∞](https://github.com/benhoyt/inih)](#ini-)
      - [OpenSSL [∞](https://www.openssl.org/)](#openssl-)
      - [libssh [∞](http://www.libssh.org/)](#libssh-)
      - [websocketpp [∞](https://github.com/zaphoyd/websocketpp)](#websocketpp-)
      - [Valijson [∞](https://github.com/tristanpenman/valijson)](#valijson-)
    - [cpp-project-template [∞](https://github.com/puppetlabs/cpp-project-template)](#cpp-project-template-)
    - [Vanagon [∞](https://github.com/puppetlabs/vanagon)](#vanagon-)
    - [Cross-platform development](#cross-platform-development)
      - [Development Environment](#development-environment)
        - [Linux](#linux)
        - [Mac OS X](#mac-os-x)
        - [Windows](#windows)
        - [Testing](#testing)
      - [File Paths and System Calls](#file-paths-and-system-calls)
      - [Unicode and UTF-8](#unicode-and-utf-8)
        - [Handling Input/Output](#handling-inputoutput)
        - [Accessing Files](#accessing-files)
        - [Environment Variables](#environment-variables)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Getting Started Resources

Most likely you know of C++. We use a particular style of C++ referred to as modern C++, based on patterns enabled by new features in C++11. The Style Guide and FAQ will cover many of these patterns and hopefully provide simple, safe building blocks for programming in C++. For those who learned C++ before C++11, there are a number of patterns that we encourage versus what you’re used to, as they tend to produce fewer errors and result in safer code.

We use all of C++11 except for:
- std::regex, as GCC 4.8 doesn’t support it
- std::thread, as GCC 4.8 on AIX doesn't support it, and the mingw support is experimental

Once we update our tooling to use a newer version of GCC, we’ll likely bump our language support to C++14.

We also use [CMake](http://www.cmake.org/) for our project build system - usually to generate Makefiles that work for your target platform - so having some understanding of how it works is helpful.

## The C++ Language

Many of the books below are available in our library.

### Study Guide

Learn some basic CMake with [CMake Tutorial](http://www.cmake.org/cmake-tutorial/)

Add some more complete instruction from one of
- [LearnCpp Tutorials](http://www.learncpp.com/)
- [PluralSight C++ Fundamentals Course by Kate Gregory](http://app.pluralsight.com/courses/cpp-fundamentals) [Part 2](http://app.pluralsight.com/courses/cppfund2)
- [A Tour of C++](http://www.amazon.com/Tour-Depth-Series-Bjarne-Stroustrup/dp/0321958314) - a little too succinct for some, but good if you have experience with `C`.

Work through some exercises from [Exercism C++ Exercises](https://github.com/exercism/xcpp/blob/master/SETUP.md) with the [C++ Primer](http://www.amazon.com/Primer-5th-Stanley-B-Lippman/dp/0321714113) or [The C++ Programming Language](http://www.amazon.com/The-Programming-Language-4th-Edition/dp/0321563840) at hand.

Since the Puppet RAL is pretty familiar to many of us, it makes a useful example. Create a set of C++ classes representing the RAL, with the ability to print out a representation of them. Then create data structures to represent a catalog, including a relationship [DAG](https://en.wikipedia.org/wiki/Directed_acyclic_graph). A basic example is included in [ral-example](ral-example).

### Language References

- [C++ Language and Library Reference](http://en.cppreference.com/w/)
- [CMake Documentation](http://www.cmake.org/documentation/)

### Community
- [CppCon Conferences](http://cppcon.org/)
- [Official Standard C++ Site](https://isocpp.org/)

### Practitioner Knowledge

#### Books
- [Effective C++: 55 Specific ways to Improve your Programs and Design](http://www.amazon.com/dp/0321334876)
- [More Effective C++: 35 New Ways to Improve Your Programs and Designs](http://www.amazon.com/dp/020163371X)
- [Effective Modern C++: 42 Specific Ways to Improve Your Use of C++11 and C++14](http://www.amazon.com/dp/1491903996)

#### Blogs and Videos
- [Type Deduction and Why You Care - Scott Meyers](https://confluence.puppetlabs.com/pages/viewpage.action?pageId=52430319)
- [Universal References in C++11 - Scott Meyers](https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers)
- [C++ Seasoning - Sean Parent](https://channel9.msdn.com/Events/GoingNative/2013/Cpp-Seasoning)
- [Inheritance is the Base Class of Evil - Sean Parent](https://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil)

[Other material by Sean Parent](https://github.com/sean-parent/sean-parent.github.io/wiki/Papers-and-Presentations)

### Tooling
A development environment on most platforms is pretty straight-forward, get Clang 3.5+ or GCC 4.8+. On Mac OS X, the system Clang from Xcode Command-Line Tools (required by Homebrew) is sufficient. On Windows, I recommend installing CMake and [MinGW-w64 via Chocolatey](https://chocolatey.org/packages/mingw).

Visual Studio compatibility isn’t guaranteed in our projects due to bugs in Visual C++ and their incomplete C++11 support.

Our current release pipeline uses
- CMake 3.2.2
- Apple LLVM 6.1.0 (Clang 3.6) on Mac OS X
- MinGW GCC 4.8.3 with win32 threads on Windows, using Structured Exception Handling (SEH) for 64-bit exception handling and Set-jump-long-jump (SJLJ) for 32-bit (libpthread dropped because the library was buggy)
- GCC 4.8.2 on all other platforms

JetBrains provides an IDE, [CLion](https://www.jetbrains.com/clion/), that some of us find useful. For vim/emacs users, you may want to look at [ycmd](https://github.com/Valloric/ycmd) for C++ code completion based on Clang. On Mac, Xcode can also be used for building and debugging by preparing a project with `cmake -G Xcode …`.

## Starting a Project

### Libraries

Libraries approved by RelEng that are currently in use. Most libraries support UTF-8, although Boost on Windows needs to be rebuilt with ICU for full support.

A list of other libraries that may be useful is maintained at http://en.cppreference.com/w/cpp/links/libs. New libraries must be approved by RelEng.

Libraries we use are organized by a few rules:
- Header-only libraries are vendored into a project. If they seem generally useful, add them as components of Leatherman. [rapidjson](https://github.com/puppetlabs/leatherman/blob/master/rapidjson/CMakeLists.txt) is a useful example of how to do that.
- Statically-linked libraries will be built and packaged, to be hosted on platform-specific packaging feeds (Apt, Rpm, Nuget). The pipelines for building these are managed by RelEng. Project dependencies are then made build-time dependencies in Vanagon projects.
- Dynamically-linked libraries are built and packaged with the Vanagon project they will be shipped with.

#### Boost [∞](http://www.boost.org/)

Boost comes with many sub-components. Currently our C++ toolchain only builds out a few of them. We’re evaluating building several more so that in the future more options are available to developers.

Boost support for packaging is at 1.58 and has the following compiled libraries:
`chrono, date_time, filesystem, locale, log, program_options, random, regex, system, thread`

Boost also contains a number of header-only libraries that are also available. See the Boost documentation for all the details or [The Boost C++ Libraries](http://theboostcpplibraries.com/) for a more structured introduction to all the libraries).

Documentation for Boost isn’t the greatest, but it has a lot of useful utilities. In the FAQ I’ll call common patterns that use them. We generally use [chrono](http://www.boost.org/doc/libs/1_58_0/doc/html/chrono.html), [date_time](http://www.boost.org/doc/libs/1_58_0/doc/html/date_time.html), [filesystem](http://www.boost.org/doc/libs/1_58_0/libs/filesystem/doc/index.htm), [program_options](http://www.boost.org/doc/libs/1_58_0/doc/html/program_options.html), [random](http://www.boost.org/doc/libs/1_58_0/doc/html/boost_random.html), and [regex](http://www.boost.org/doc/libs/1_58_0/libs/regex/doc/html/index.html) directly. Particularly useful header-only libraries are [algorithm](http://www.boost.org/doc/libs/1_58_0/libs/algorithm/doc/html/index.html), [any](http://www.boost.org/doc/libs/1_58_0/doc/html/any.html), [format](http://www.boost.org/doc/libs/1_58_0/libs/format/), [lexical_cast](http://www.boost.org/doc/libs/1_58_0/doc/html/boost_lexical_cast.html), [range](http://www.boost.org/doc/libs/1_58_0/libs/range/doc/html/index.html), [uuid](http://www.boost.org/doc/libs/1_58_0/libs/uuid/), and [variant](http://www.boost.org/doc/libs/1_58_0/doc/html/variant.html). Log and locale are more easily used through Leatherman. System and thread are required by other libraries we use.

On Mac OS X and up-to-date Linux platforms you can get a recent build of [Boost](http://sourceforge.net/projects/boost/files/latest/download) using your package manager. On Windows build it from source in PowerShell with `.\bootstrap mingw && .\b2 toolset=gcc --build-type=minimal install --prefix=$install boost.locale.iconv=off`, or pull a [pre-built](https://s3.amazonaws.com/kylo-pl-bucket/boost_1_58_0-x86_64_mingw-w64_4.8.3_win32_seh.7z) package built with [MinGW-w64 4.8.3](https://www.myget.org/F/puppetlabs/api/v2/package/mingw-w64/4.8.3). C++ compilers generally require you build with an ABI-compatible compiler, so if you use the pre-built package you should also use that compiler.

#### Leatherman [∞](https://github.com/puppetlabs/leatherman)

We maintain a collection of libraries we’ve written that are useful to share across projects, or header-only libraries we’ve vendored to make available to those projects. Please add to this if you find yourself developing tools that would be useful to others. It covers a number of things:

- [**catch**](https://github.com/philsquared/Catch) - a C++ testing framework supporting TDD and BDD-style test structuring
- **curl** - a C++ wrapper for [libcurl](http://curl.haxx.se/libcurl/); requires libcurl is installed
- **dynamic_library** - cross-platform library for loading a dynamic library at runtime
- **execution** - cross-platform command execution with options for handling input/output
- **file_util** - useful filesystem utilities not covered by [Boost.Filesystem](http://www.boost.org/doc/libs/1_58_0/libs/filesystem/doc/index.htm)
- **json_container** - a container-oriented json abstraction built on [rapidjson](https://github.com/miloyip/rapidjson)
- **locale** - a cross-platform way to get a locale string to use with std::locale, because Windows; in the future this will also support i18n via [Boost.Locale](http://www.boost.org/doc/libs/1_58_0/libs/locale/doc/html/index.html) (or gettext directly)
- **logging** - a simple logging library built on [Boost.Log](http://www.boost.org/doc/libs/1_58_0/libs/log/doc/html/index.html) that takes care of Windows Unicode output; in the future it will also support lookup in message catalogs for i18n
- **nowide** - a cross-platform wrapper to use UTF-8 for standard library IO on Windows
- **ruby** - initializes and provides access to the Ruby runtime from a library loaded by Ruby or by loading the Ruby dynamic library
- **util** - cross-platform environment manipulation, a simple regex helper, scoped system resources via RAII, and string and time utilities
- **windows** - Windows-specific tools for accessing process and user info, the registry, WMI, and system errors

#### horsewhisperer [∞](https://github.com/puppetlabs/horsewhisperer)

An option parser supporting chained execution parsing, where parsing depends on what’s come before it. If [Boost.Program_options](http://www.boost.org/doc/libs/1_58_0/doc/html/program_options.html) doesn’t work for you, this might.

#### yaml-cpp [∞](https://github.com/jbeder/yaml-cpp)

#### INI [∞](https://github.com/benhoyt/inih)

#### OpenSSL [∞](https://www.openssl.org/)

#### libssh [∞](http://www.libssh.org/)

#### websocketpp [∞](https://github.com/zaphoyd/websocketpp)

#### Valijson [∞](https://github.com/tristanpenman/valijson)

### cpp-project-template [∞](https://github.com/puppetlabs/cpp-project-template)

We’ve started a C++ project template you can derive new projects from, based around having a command-line executable and an associated dynamic library that can be linked into other programs. It includes things like

- Enable [`make cpplint`](http://google-styleguide.googlecode.com/svn/trunk/cppguide.html#cpplint), a C++ linter for common style and programing errors
- Enable [`make cppcheck`](http://cppcheck.sourceforge.net/), for fast static analysis that avoids false-positives
- Enables `-Wall -Werror` to enforce most compiler static checking
- [AppVeyor CI](http://appveyor.com/) configuration for Windows CI on Pull Requests
  - Sign in to AppVeyor using your Github account
  - If there are multiple AppVeyor accounts associated with your Github account, select 'puppetlabs'
- [Travis CI](https://travis-ci.org/) configuration for Linux CI on Pull Requests
- Code Coverage metrics via [coveralls.io](https://coveralls.io/)
- Dummy Rake tasks for acceptance, to fit a standard [Jenkins CI](http://jenkins-ci.org/) template
- Documentation via Doxygen

It exemplifies a common organizational structure we use across C++ projects, where executable and libraries inhabit separate sub-directories (`exe` and `lib`).

We use ‘.cc’ for C++ source, ‘.hpp’ for C++ header files, and ‘.c’ for pure C headers.

### Vanagon [∞](https://github.com/puppetlabs/vanagon)

Vanagon is a packaging tool to build a single package out of a project, which can itself contain one or more components. It’s used by Release Engineering for building native code projects, including [Puppet Agent](https://github.com/puppetlabs/puppet-agent) and a number of the libraries and tools mentioned above for [pl-build-tools](https://github.com/puppetlabs/pl-build-tools-vanagon) (both are expected to be open-sourced in the future).

Vanagon contains the `build` command for generating a package. It also contains the `devkit` command for populating a build environment and building a project on a target platform, without completing packaging and tearing the machine down, allowing easier testing or reproduction of build problems on specific platforms.

TODO: We plan to add an example for the cpp-project-template. With a Jenkins pipeline?

### Cross-platform development

Cross-platform development can bring several challenges. This section provides instruction for how to approach each of them.

#### Development Environment

The first hurdle is often getting a development environment setup. One route is to use [CLion](https://www.jetbrains.com/clion/) everywhere, which provides a common GCC or Clang workflow with CMake on all major platforms.

##### Linux

Using an OS that updates packages regularly will make setup easier; look at ArchLinux or a recent Fedora release. The following commands will setup a dev environment with Boost and libcurl.

```
# ArchLinux
pacman -S make cmake gcc boost yaml-cpp curl git ruby
# Fedora
dnf install -y make cmake wget tar gcc-c++ boost-devel openssl-devel libcurl-devel git ruby
```

To setup [cpp-project-template](https://github.com/puppetlabs/cpp-project-template)

```
git clone https://github.com/puppetlabs/leatherman
mkdir -p leatherman/build
pushd leatherman/build
cmake .. && make install -j
popd

git clone https://github.com/puppetlabs/cpp-project-template
mkdir -p cpp-project-template/build
cd cpp-project-template/build
cmake .. && make -j
```

##### Mac OS X

Using [Homebrew](http://brew.sh/)

```
brew install cmake boost
```

Follow the steps above to setup [cpp-project-template](https://github.com/puppetlabs/cpp-project-template).

##### Windows

Using [Chocolatey](https://chocolatey.org/) and Powershell

```
choco install -source https://www.myget.org/F/puppetlabs -y 7zip.commandline cmake git.install mingw-w64 pl-boost-x64 pl-toolchain-x64 pl-zlib-x64 pl-openssl-x64 pl-curl-x64

# Update PATH to include GCC and DLLs (so executables can find them)
$env:PATH = "C:\tools\mingw64\bin;C:\tools\pl-build-tools\bin;$env:PATH"
$N = 4

git clone https://github.com/puppetlabs/leatherman
mkdir -Path leatherman/build
pushd leatherman/build
cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX="C:\tools\pl-build-tools" -DCMAKE_TOOLCHAIN_FILE="C:\tools\pl-build-tools\pl-build-toolchain.cmake" -DBOOST_STATIC=ON ..
mingw32-make install -j ${N}
popd

git clone https://github.com/puppetlabs/cpp-project-template
mkdir -Path cpp-project-template/build
cd cpp-project-template/build
cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="C:\tools\pl-build-tools\pl-build-toolchain.cmake" -DBOOST_STATIC=ON ..
mingw32-make -j ${N}
```

On Windows you want to limit the number of parallel processes, the example defaults to 4. These commands can be tweaked to work under Cygwin. In that case you want to use `PATH=/cygdrive/c/ProgramData/chocolatey/bin:/cygdrive/c/tools/mingw64/bin:/cygdrive/c/tools/pl-build-tools/bin cmake ...` to isolate the environment.

##### Testing

To run tests with verbose output, run `make test ARGS=-V` (or `mingw32-make test ARGS=-V` on Windows).

#### File Paths and System Calls

Obviously file paths on platforms differ. Refer to the [file_paths specification](https://github.com/puppetlabs/puppet-specifications/blob/master/file_paths.md).

Assume POSIX functions aren't available on Windows, and prefer Boost or C++ standard library functions. If specific POSIX functionality is needed, an equivalent will be needed for Windows; such helpers are good candidates for a library in Leatherman.

TODO: Add ways to get common paths on Windows.

#### Unicode and UTF-8

Windows chose UTF-16 as the default Unicode representation, and all system calls are based on that; C++ standard library functions only support ASCII or other fixed 8-bit encodings (such as [Latin-1](https://en.wikipedia.org/wiki/Windows-1252)). UNIX-based platforms generally support UTF-8 in system calls and the C++ standard library. `std::string` is just a byte container, so it safely holds UTF-8 characters; however when manipulating UTF-8 strings you should use a UTF-8 aware library such as [UTF8-CPP](http://utfcpp.sourceforge.net/) or Boost.Regex. Our practice is to represent strings as UTF-8 internally, and deal with conversion when text is read/written.

TODO: Evaluate UTF8-CPP and put it on Library list.

##### Handling Input/Output

The [driver in cpp-project-template](https://github.com/puppetlabs/cpp-project-template/blob/master/exe/driver.cc.in) contains useful examples of handling input/output safely across platforms.

```
// Use Boost.Nowide args to ensure command-line arguments are UTF-8.
// On Windows this accesses console arguments as UTF-16 and converts them to UTF-8.
// This uses the RAII pattern to modify argc/argv in-place, and revert them when exiting scope.
boost::nowide::args arg_utf8(argc, argv);

// Use Boost.Nowide cout/cerr to correctly print UTF-8 characters.
// On Windows this converts to UTF-16 before printing to the console.
setup_logging(boost::nowide::cerr);
boost::nowide::cout << "Hello!" << std::endl;

// Use Boost.Nowide cin to correctly read UTF-8 characters.
// On Windows this reads using a UTF-16 system call and converts to UTF-8.
std::string input;
boost::nowide::cin >> input;
```

Boost.Nowide's cout/cerr implementations come with the caveat that they aren't header-only, so if Boost.Nowide is statically linked into multiple shared libraries, input and output must be manually synchronized between those libraries.

##### Accessing Files

[Leatherman](#leathermanhttpsgithubcompuppetlabsleatherman) is designed around using UTF-8 everywhere. That principally involves the use of Boost.FileSystem and Boost.Nowide.

[Leatherman's file_utils](https://github.com/puppetlabs/leatherman/blob/master/file_util/src) make use of Boost.Nowide's iostream wrappers for reading and writing files, and Boost.FileSystem for accessing and manipulating files and directories.

```
// Initialize boost filesystem's locale to a UTF-8 default.
// Logging gets setup the same way via the default 2nd argument.
#if (!defined(__sun) && !defined(_AIX)) || !defined(__GNUC__)
    // Locale support in GCC on Solaris and AIX are busted, so skip it.
    boost::filesystem::path::imbue(leatherman::locale::get_locale());
#endif

// Open a UTF-8 path for reading or writing.
boost::nowide::fstream in("unicodeᐁfile");

// Rename a UTF-8 file.
boost::filesystem::rename("unicodeᐁfile", "unicode❄file");
```

##### Environment Variables

Environment variables can also contain Unicode characters, and should use Boost.Nowide wrappers for `getenv` and `setenv` to ensure they are UTF-8 encoded.
