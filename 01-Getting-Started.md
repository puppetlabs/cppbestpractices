<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [Getting Started Resources](#getting-started-resources)
  - [The C++ Language](#the-c-language)
    - [Study Guide](#study-guide)
    - [Learning References](#learning-references)
    - [Language References](#language-references)
    - [Community](#community)
    - [Tooling](#tooling)
  - [Starting a Project](#starting-a-project)
    - [Libraries](#libraries)
      - [[Boost](http://www.boost.org/)](#boosthttpwwwboostorg)
      - [[Leatherman](https://github.com/puppetlabs/leatherman)](#leathermanhttpsgithubcompuppetlabsleatherman)
      - [[horsewhisperer](https://github.com/puppetlabs/horsewhisperer)](#horsewhispererhttpsgithubcompuppetlabshorsewhisperer)
      - [[yaml-cpp](https://github.com/jbeder/yaml-cpp)](#yaml-cpphttpsgithubcomjbederyaml-cpp)
      - [[INI](https://github.com/benhoyt/inih)](#inihttpsgithubcombenhoytinih)
      - [[OpenSSL](https://www.openssl.org/)](#opensslhttpswwwopensslorg)
      - [[libssh](http://www.libssh.org/)](#libsshhttpwwwlibsshorg)
    - [[cpp-project-template](https://github.com/puppetlabs/cpp-project-template)](#cpp-project-templatehttpsgithubcompuppetlabscpp-project-template)
    - [[Vanagon](https://github.com/puppetlabs/vanagon)](#vanagonhttpsgithubcompuppetlabsvanagon)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Getting Started Resources

Most likely you know of C++. We use a particular style of C++ referred to as modern C++, based on patterns enabled by new features in C++11. The Style Guide and FAQ will cover many of these patterns and hopefully provide simple, safe building blocks for programming in C++. For those who learned C++ before C++11, there are a number of patterns that we encourage versus what you’re used to, as they tend to produce fewer errors and result in safer code.

We use all of C++11 except for:
- std::regex, as GCC 4.8 doesn’t support it
- std::thread, as GCC 4.8 on AIX doesn't support it, and the mingw support is experimental

Once we update our tooling to use a newer version of GCC, we’ll likely bump our language support to C++14.

We also use [CMake](http://www.cmake.org/) for our project build system - usually to generate Makefiles that work for your target platform - so having some understanding of how it works is helpful.

## The C++ Language

### Study Guide

If you want to dive right in, [C++ Koans](https://github.com/torbjoernk/CppKoans) and [Exercism C++ Exercises](https://github.com/exercism/xcpp/blob/master/SETUP.md) may be useful, as well as the reference links below.

### Learning References

Many of these are available in our library.

- [C++ Primer](http://www.amazon.com/Primer-5th-Stanley-B-Lippman/dp/0321714113/ref=sr_1_1?s=books&ie=UTF8&qid=1436562219&sr=1-1&keywords=C%2B%2B+primer)
- [CMake Tutorial](http://www.cmake.org/cmake-tutorial/)
- [The C++ Programming Language](http://www.amazon.com/The-Programming-Language-4th-Edition/dp/0321563840)
- [Effective C++: 55 Specific ways to Improve your Programs and Design](http://www.amazon.com/dp/0321334876/ref=wl_it_dp_v_S_ttl?_encoding=UTF8&colid=2KPYNF30H25OC&coliid=I3ULKDNY4KHV3U)
- [More Effective C++: 35 New Ways to Improve Your Programs and Designs](http://www.amazon.com/dp/020163371X/ref=wl_it_dp_v_nS_ttl?_encoding=UTF8&colid=2KPYNF30H25OC&coliid=I3QPYZRZY5RBNW)
- [Effective Modern C++: 42 Specific Ways to Improve Your Use of C++11 and C++14](http://www.amazon.com/dp/1491903996/ref=wl_it_dp_v_nS_ttl?_encoding=UTF8&colid=2KPYNF30H25OC&coliid=I3GAZZ5GDEIXB2)

### Language References

- [C++ Library Reference](http://en.cppreference.com/w/)
- [CMake Documentation](http://www.cmake.org/documentation/)

### Community
- [CppCon Conferences](http://cppcon.org/)
- [Official Standard C++ Site](https://isocpp.org/)

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

#### [Boost](http://www.boost.org/)

Boost comes with many sub-components. Currently our C++ toolchain only builds out a few of them. We’re evaluating building several more so that in the future more options are available to developers.

Boost support for packaging is at 1.57 and has the following compiled libraries:
`chrono, date_time, filesystem, locale, log, program_options, random, regex, system, thread`

Boost also contains a number of header-only libraries that are also available. See the Boost documentation for all the details.

Documentation for Boost isn’t the greatest, but it has a lot of useful utilities. In the FAQ I’ll call common patterns that use them. We generally use [chrono](http://www.boost.org/doc/libs/1_58_0/doc/html/chrono.html), [date_time](http://www.boost.org/doc/libs/1_58_0/doc/html/date_time.html), [filesystem](http://www.boost.org/doc/libs/1_58_0/libs/filesystem/doc/index.htm), [program_options](http://www.boost.org/doc/libs/1_58_0/doc/html/program_options.html), [random](http://www.boost.org/doc/libs/1_58_0/doc/html/boost_random.html), and [regex](http://www.boost.org/doc/libs/1_58_0/libs/regex/doc/html/index.html) directly. Particularly useful header-only libraries are [algorithm](http://www.boost.org/doc/libs/1_58_0/libs/algorithm/doc/html/index.html), [any](http://www.boost.org/doc/libs/1_58_0/doc/html/any.html), [format](http://www.boost.org/doc/libs/1_58_0/libs/format/), [lexical_cast](http://www.boost.org/doc/libs/1_58_0/doc/html/boost_lexical_cast.html), [range](http://www.boost.org/doc/libs/1_58_0/libs/range/doc/html/index.html), [uuid](http://www.boost.org/doc/libs/1_58_0/libs/uuid/), and [variant](http://www.boost.org/doc/libs/1_58_0/doc/html/variant.html). Log and locale are more easily used through Leatherman. System and thread are required by other libraries we use.

On Mac OS X and up-to-date Linux platforms you can get a recent build of [Boost](http://sourceforge.net/projects/boost/files/latest/download) using your package manager. On Windows build it from source in PowerShell with `.\bootstrap mingw && .\b2 toolset=gcc --build-type=minimal install --prefix=$install boost.locale.iconv=off`, or pull a [pre-built](https://s3.amazonaws.com/kylo-pl-bucket/boost_1_57_0-x86_64_mingw-w64_4.8.3_win32_seh.7z) package built with [MinGW-w64 4.8.3](https://www.myget.org/F/puppetlabs/api/v2/package/mingw-w64/4.8.3). C++ compilers generally require you build with an ABI-compatible compiler, so if you use the pre-built package you should also use that compiler.

#### [Leatherman](https://github.com/puppetlabs/leatherman)

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

#### [horsewhisperer](https://github.com/puppetlabs/horsewhisperer)

An option parser supporting chained execution parsing, where parsing depends on what’s come before it. If [Boost.Program_options](http://www.boost.org/doc/libs/1_58_0/doc/html/program_options.html) doesn’t work for you, this might.

#### [yaml-cpp](https://github.com/jbeder/yaml-cpp)

#### [INI](https://github.com/benhoyt/inih)

#### [OpenSSL](https://www.openssl.org/)

#### [libssh](http://www.libssh.org/)

#### [websocketpp](https://github.com/zaphoyd/websocketpp)

#### [Valijson](https://github.com/tristanpenman/valijson)

### [cpp-project-template](https://github.com/puppetlabs/cpp-project-template)

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

It exemplifies a common organizational structure we use across C++ projects.

We use ‘.cc’ for C++ source, ‘.hpp’ for C++ header files, and ‘.c’ for pure C headers.

### [Vanagon](https://github.com/puppetlabs/vanagon)

Vanagon is a packaging tool to build a single package out of a project, which can itself contain one or more components. It’s used by Release Engineering for building native code projects, including [Puppet Agent](https://github.com/puppetlabs/puppet-agent) and a number of the libraries and tools mentioned above for [pl-build-tools](https://github.com/puppetlabs/pl-build-tools-vanagon) (both are expected to be open-sourced in the future).

Vanagon contains the `build` command for generating a package. It also contains the `devkit` command for populating a build environment and building a project on a target platform, without completing packaging and tearing the machine down, allowing easier testing or reproduction of build problems on specific platforms.

TODO: We plan to add an example for the cpp-project-template. With a Jenkins pipeline?

