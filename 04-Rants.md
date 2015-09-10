<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [Rants](#rants)
  - [Potential Tools](#potential-tools)
    - [Dynamic Analysis](#dynamic-analysis)
    - [[STL debug support in GDB](https://sourceware.org/gdb/wiki/STLSupport)](#stl-debug-support-in-gdbhttpssourcewareorggdbwikistlsupport)
    - [[cling](https://github.com/vgvassilev/cling) - an interactive C++ interpreter](#clinghttpsgithubcomvgvassilevcling---an-interactive-c-interpreter)
  - [Libraries](#libraries)
    - [Selection Criteria](#selection-criteria)
    - [Using libraries in a project](#using-libraries-in-a-project)
    - [Interesting Candidates](#interesting-candidates)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Rants

Why you should avoid class hierarchies and use duck-typing.
- [C++ Seasoning](https://channel9.msdn.com/Events/GoingNative/2013/Cpp-Seasoning)
- [Inheritance is the Base Class of Evil](https://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil)
- [Sean Parent Talks](https://github.com/sean-parent/sean-parent.github.io/wiki/Papers-and-Presentations)

Use structs for plain-old-data types (POD), classes for OOP (which you should use sparingly). Prefer PODs.

Re the [Google C++ style guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml): handy starting point, but don't have to drink all the koolaid.

Unicode: http://utf8everywhere.org/, [Unicode in C++ (CppCon 2014)](http://youtu.be/n0GK-9f4dl8)

## Potential Tools

### Dynamic Analysis

- [Coveralls.io](https://coveralls.io/) - code coverage analysis using gcov
  - Projects seem to be shared across users who have access, so sign in with your own account and create projects as needed.
  - Currently unpaid, so only OSS projects
- Clang [static analysis](http://clang-analyzer.llvm.org/) and [dynamic sanitizer](http://clang.llvm.org/docs/UsersManual.html#controlling-code-generation) tools? These are still under development, and not sufficiently broadly available to make part of CI tooling

### [STL debug support in GDB](https://sourceware.org/gdb/wiki/STLSupport)

### [cling](https://github.com/vgvassilev/cling) - an interactive C++ interpreter

## Libraries

### Selection Criteria

- Builds without warnings in Clang and GCC, including -Wextra
- Doesn't peg itself to an outdated version of Boost
- Unicode support, if it needs to interact with strings
- Is under active development. When was the last release? How often is there a new release? How often do we expect to need the new release?
- Supports building on Windows with MinGW-w64
- The security track record. Does upstream have a security mailing list?
- License requirements. With C++ based stuff, beyond the normal license concerns, we'd like to be able to statically link libraries in (or at least have that flexibility). That means no GPL (v2 or v3) if we can help it. Prefer BSD, MIT, or ASL 2.0.

Release Engineering requests all new libraries be screened through the [New Third-Party Library Request Process](https://confluence.puppetlabs.com/display/RE/New+Third-Party+Library+Request+Process).

### Using libraries in a project
How to include libraries in a project is a work-in-progress. Currently projects use CMake's find_package to find previously built/installed packages. On POSIX systems this works well for development with package managers, but a system for local dependency installation would be desirable (bundle vs gem). On Windows most packages don't have pre-compiled MinGW packages to host on Chocolatey, and Chocolatey is still a young project (timely package updates aren't always available). We should also make a distinction between OS functionality that simply may not be available on all installations - such as Windows SDKs and libblkid (Linux) - and other libraries.

Most large C++ presences end up with a monolithic repository for dependencies and interdependent projects. We would like to avoid this and keep our project environment more modular.

### Interesting Candidates
- [Okasaki](https://github.com/BartoszMilewski/Okasaki) - functional data structures
- [docopt](https://github.com/docopt/docopt.cpp) - nice command-line parsing
- [coroutines](https://github.com/maciekgajewski/coroutines) - go-style coroutines and channels
- [HAMT](https://github.com/chaelim/HAMT) - hash array-mapped trie
- [Mach7](https://github.com/solodon4/Mach7) - fast pattern-matching (often faster than the Visitor pattern)
- [RapidCheck](https://github.com/emil-e/rapidcheck) - generative property-based testing for C++
