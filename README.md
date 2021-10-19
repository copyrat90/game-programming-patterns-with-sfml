# Game Programming Patterns with SFML

Examples from https://gameprogrammingpatterns.com, extended with [SFML](https://www.sfml-dev.org/).

### *Just started! Nothing to see now; Please visit later!*

> *(Placeholder: Screenshots should go here)*

This project aims to provide running demos
made out of the snippets from the famous design pattern book by Robert Nystrom,
called [Game Programming Patterns](https://gameprogrammingpatterns.com) (abbreviated as *GPP* from now).

Each folder consists of a demo for the design pattern introduced in each chapter of the book.



## Motivation
While the example snippets from the GPP book is good enough to demonstrate the patterns, they are still snippets;\
You cannot run them as they are.

The author provides the [demo source](https://github.com/munificent/game-programming-patterns/tree/master/code/cpp), but it runs on the *boring command line*.\
That is why I started this project; **To write an interactive GUI demo to extend the examples, complementing the GPP.**

### So, is it a full game?
Unfortunately, it is not; It is more like a small *interactive learning material*.

As I already mentioned above, this project aims to complement the book.\
Writing a full game is not only a huge work, but also beyond the scope of a learning material for the book.

### Why SFML?
SFML is one of the easiest multimedia library to accomplish the given task: writing a small demo.\
I considered [SDL](https://www.libsdl.org/) too, but it is a C library, so it is not very friendly to use with *object-oriented* fashion.

### I see you used smart pointers...
Right. The original snippets from the book only uses *raw pointers*, [for the readers who use languages other than C++.](http://gameprogrammingpatterns.com/introduction.html#about-the-sample-code)\
But, for the real running demo written in C++, I think it is a good idea to clearly show the ownerships of each variable by using smart pointers.

Also, it's been literally a decade when `C++11` introduced smart pointers;\
Learning to use smart pointers to manage ownership is necessary in modern C++, as it is quite common these days.

So, please go learn them; It is not that difficult concept to understand.



## Build
You need to install these along with your favorite [C++ compiler that supports **C++17 or later**](https://en.cppreference.com/w/cpp/compiler_support).
1. [**CMake**](https://cmake.org/), the meta build system for C/C++.
2. [**vcpkg**](https://vcpkg.io/), the C/C++ library manager by Microsoft.

When executing `cmake`, you need to locate the `vcpkg.cmake` which comes with the vcpkg.
```powershell
# Assuming that vcpkg is installed on C:\vcpkg
cmake ../my/project -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
```
Since this project uses vcpkg's [Manifest Mode](https://vcpkg.io/en/docs/users/manifests.html), **all the dependencies are automatically installed** when you specify the [vcpkg's CMake toolchain file](https://vcpkg.io/en/docs/users/integration.html#cmake-toolchain-file-recommended-for-open-source-cmake-projects) on executing CMake.



## Dependencies

This project relies on these libraries:
+ [**SFML**](https://www.sfml-dev.org/) [(GitHub link)](https://github.com/SFML/SFML) : Simple and Fast Multimedia Library
    - License: [zlib/libpng license](https://www.sfml-dev.org/license.php)



## License

Source code is licensed under the [MIT/Expat license](LICENSE).

> *(Placeholder: Put asset's license notice here)*
