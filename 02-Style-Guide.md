<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [Style Guide](#style-guide)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Style Guide

We generally follow the STL/Boost style conventions to avoid style clashing with core libraries. That means

- Use snake_case classes, types, functions, and variables.
- Use _name or name_ for private variables in classes/structs.
- Use (4) spaces rather than tabs.

Other style guidelines

- Follow the style of the project you’re in.
- Enforce with cpplint.py (as done in cpp-project-template).
- Use [Doxygen](http://www.stack.nl/~dimitri/doxygen/) style annotations for documenting source code, preferably /** … */
- Use forward-declarations, especially with anything from windows.h
- Use {} for object initialization, as in `std::string s {“foo”};`. It’s easier to differentiate from function calls and function definition.
- Use override (and not virtual) when overriding methods through inheritance. Obviously the original method still needs virtual (and not override).
- Use `#pragma once`. It’s supported by every modern compiler, and is simpler to use than `#ifdef` guards.
- Avoid casts. If you have to cast, use C++ casts (static_cast, dynamic_cast, const_cast, reinterpret_cast, preferred in that order) and cry a little bit inside.
- Header file inclusion<sup>[1](http://gamesfromwithin.com/physical-structure-and-c-part-1-a-first-look)</sup>:
  - Every cpp file includes its own header file first.
  - A header file must include all the header files necessary to parse it.
  - A header file should have the bare minimum number of header files necessary to parse it. Prefer forward-declarations when possible, i.e. whenever you only need pointers/references to a class outside the std namespace<sup>[2](https://groups.google.com/forum/#!topic/comp.lang.c++.moderated/XBKFjGNquDM)</sup>.

TODO: Still under development.
