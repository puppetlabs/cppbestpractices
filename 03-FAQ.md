<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [FAQ](#faq)
  - [Q: Writing loops](#q-writing-loops)
  - [Q: Variable modifiers](#q-variable-modifiers)
  - [Q: Arguments and return types in class methods](#q-arguments-and-return-types-in-class-methods)
  - [Q: How do I use polymorphic objects?](#q-how-do-i-use-polymorphic-objects)
  - [Q: How do I share ownership of an object between multiple classes/data structures?](#q-how-do-i-share-ownership-of-an-object-between-multiple-classesdata-structures)
  - [Q: When does it make sense to use new/delete?](#q-when-does-it-make-sense-to-use-newdelete)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# FAQ

## Q: Writing loops
_A: Prefer [ranged-for](http://en.cppreference.com/w/cpp/language/range-for), it avoids mistakes in boundary checks._

`for (auto &&x : container) { … }`

We use `auto &&`, often referred to as perfect-forwarding, to have a reference to each object that doesn’t apply any implicit conversions.

If dealing with a structure that doesn’t support `begin(...)` and `end(...)`, or you want to use a slice of the container, you can use

`for (auto &&x : boost::make_iterator_range(begin, end)) { … }`

where `begin` and `end` are iterators or pointers.

## Q: Variable modifiers
_A: We prefer `type const& name`, `type &name`, `type const* name`, `type *name`, `type const* const name`, etc. Grouping modifiers together is kind of helpful in grokking the declaration._

## Q: Arguments and return types in class methods
_A: Pass-by-value in the constructor if creating a copy_

Use `object::object(type val) : _val(move(val)) {}`. This allows passing literal values to the object and avoiding copies, and otherwise creates a copy when the constructor is called that’s then moved into ownership by the class.

_Pass-by-pointer if optional or use multiple function signatures_

You probably don’t want to use raw-pointers; use shared_ptr or unique_ptr. So `object::object(unique_ptr<type> val) : _val(move(val)) {}` allows the unique_ptr to be moved into the object. Passing unique_ptr or shared_ptr by value and moving it in has the same benefit as pass-by-value above.

_Pass-by-reference everywhere else_

`object::method(type &val)` implies you’ll modify the argument.

`object::method(type const& val)` implies you need to use the argument and return something, or you’ll make a copy and store it locally. For making a copy, we prefer taking a reference over passing by value because in some cases it avoids extra heap memory allocation (which is expensive, especially versus copy operations that occur in cache). If you instead pass-by-value to the method, it creates a new copy which may require heap allocation, then moves it into the memory owned by the method, deallocating the memory previously held by the class’s value.

_Add perfect-forwarding (&&) overloads as an optimization_

If the default pass-by-reference has a performance cost, optimize by adding a new method overload that accepts an r-value reference (&&, also known as perfect forwarding) to allow values to be moved into the class.

_Return-by-reference if owned by the class_

Use `type& object::method()` if you want to allow the caller to modify the value (discouraged, think functional).

Use `type const& object::method()` if you want to grant access to data owned by the class. If the caller wants to hold onto the data for an extended period, they should create a copy. This philosophy works for shared_ptrs as well, where creating a copy increments the shared_ptr reference.

_Return-by-value if created in the method or giving up ownership_

Use `type object::method()` if the returned value is created in the method call, because otherwise you return a reference to freed memory; [copy elision](https://en.wikipedia.org/wiki/Copy_elision) makes returning a value easy and fast. This also makes sense if moving a value out of a class with the `std::move` operator.

_Return-by-pointer if initialization in the class is optional_

This should be rare, but if the value may not be initialized return-by-pointer instead of return-by-reference.

## Q: How do I use polymorphic objects?
_Use [unique_ptr](http://en.cppreference.com/w/cpp/memory/unique_ptr) if you never expect to share ownership. Otherwise use [shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) (with [weak_ptr](http://en.cppreference.com/w/cpp/memory/weak_ptr) to break cyclic dependencies, which are hopefully rare)._

If the class needs to return new instances of itself extend the [enable_shared_from_this](http://en.cppreference.com/w/cpp/memory/enable_shared_from_this) class.

Beware that using [shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) for recursive objects (like a functional list object) can cause stack overflows, because the destructor calls are recursive. A loop like that in https://github.com/puppetlabs/cpp-hocon/pull/11 can be used to release objects without overflowing the stack.

## Q: How do I share ownership of an object between multiple classes/data structures?
_A: [shared_ptr](http://en.cppreference.com/w/cpp/memory/shared_ptr) via [make_shared](http://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared). Please avoid raw new/delete._

## Q: When does it make sense to use new/delete?
_A: Use new when initializing a [unique_ptr](http://en.cppreference.com/w/cpp/memory/unique_ptr) (until [make_unique](http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique) in C++14) or creating an RAII wrapper class for interacting with a C API (consider [scoped_resource](https://github.com/puppetlabs/leatherman/blob/master/util/inc/leatherman/util/scoped_resource.hpp)). Use delete when creating an RAII wrapper class for interacting with a C API._
