# StudentHRM

广州大学 2024 年 12 月数据结构课程设计

This project is a solution to manage students' scores, which includes:

+ A C/C++ library that provides methods to operate `Student` objects.
+ A Qt Widget application that provides the graphic interface for it (in Simplified Chinese only).

You may get the Qt application for `x86-pc-windows-msvc` on GitHub Release, and you may also want to port it into other platforms.

## To build

**Requirements:**

+ Proper C/C++ toolchain (MSVC 2022 for example)
+ Qt ^6.7.1
+ Xmake ^2.9.2

To build&run the Qt application:

```sh
xmake build qt-app
xmake run qt-app
```

To run the test cases for the backend (which does not depends on Qt):

```sh
xmake b test && xmake r test
```

## File Structure

+ `xmake.lua`: The Xmake script of the project.
+ `src/backend`: The library that provides the class `Student` (on `student.h`).
+ `src/qt`: The source that defines the Qt window and widgets.
+ `src/test`: The two test cases for the backend.
+ `src/qt_main.cpp`: The `main()` for the Qt application.
+ `src/test.cpp`: The `main()` that runs the test cases.