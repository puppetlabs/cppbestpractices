<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [Style Guide](#style-guide)
  - [Header Files](#header-files)
  - [Namespaces](#namespaces)
  - [TODO: Still under development.](#todo-still-under-development)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Style Guide

We generally follow the STL/Boost style conventions to avoid style clashing with core libraries. That means

- Use snake\_case classes, types, functions, and variables.
- Use \_name or name\_ for private variables in classes/structs.
- Use (4) spaces rather than tabs.

Other style guidelines

- Follow the style of the project you’re in.
- Enforce with cpplint.py (as done in cpp-project-template).
- Use [Doxygen](http://www.stack.nl/~dimitri/doxygen/) style annotations for documenting source code, preferably /** … */
- Use forward-declarations, especially with anything from windows.h
- Use {} for object initialization, as in `std::string s {“foo”};`. It’s easier to differentiate from function calls and function definition.
- Use override (and not virtual) when overriding methods through inheritance. Obviously the original method still needs virtual (and not override).
- Use `#pragma once` at the beginning of header files. It’s supported by every modern compiler, and is simpler to use than `#ifdef` guards.
- Avoid casts. If you have to cast, use C++ casts (static_cast, dynamic_cast, const_cast, reinterpret_cast, preferred in that order) and cry a little bit inside.

## Header Files

Header file inclusion<sup>[1](http://gamesfromwithin.com/physical-structure-and-c-part-1-a-first-look)</sup>:
- Every cpp file includes its own header file first.
- A header file must include all the header files necessary to parse it.
- A header file should have the bare minimum number of header files necessary to parse it. Prefer forward-declarations when possible, i.e. whenever you only need pointers/references to a class outside the std namespace<sup>[2](https://groups.google.com/forum/#!topic/comp.lang.c++.moderated/XBKFjGNquDM)</sup>.

Header file inclusion is done as a pre-processing step that literally in-lines the text from the header file into the text buffer the compiler is parsing. The only exception to this is the use of `#pragma once`, which skips including the file if it's previously been included.

## Namespaces

Never put `using namespace x` in a header file; doing so causes the effect to be applied to every header file that's included after it is included, and to every source file that includes it. If you want a short-hand in a header file, use aliases (i.e. `namespace x = long_namespace_x`) inside of a namespace declared in that header file, as in

```
namespace foo {
    namespace x = long_namespace_x;
    x::widget process_widget(x::widget);
}
```

The effect of the example above is to create a namespace `x` within the namespace `foo`, so that you could reference `long_namespace_x::widget` via `foo::x::widget`. The short-hand `x::widget` works because [name lookup](http://en.cppreference.com/w/cpp/language/lookup) will search for matches that share a parent namespace first.

Avoid using namespace aliases in header files outside of a namespace, as this can have unbounded effects on other header files. Be cautious even doing so in a namespace, as namespaces can be shared across multiple header files.

Prefer namespace aliasing in source files within the namespace as well.

## TODO: Still under development.
