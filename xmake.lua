add_rules("mode.debug", "mode.release")

-- Basic rules.
add_rules("c++")
set_languages("c++17")
add_rules("plugin.compile_commands.autoupdate", {outputdir = '.vscode'})
set_config("buildir", "build")
set_config("export_compile_commands", true)

-- Run the test cases.
target("test")
    set_kind("binary")

    -- Backend related files.
    add_includedirs("src/backend")
    add_files("src/backend/*.cpp")

    -- Test cases.
    add_includedirs("src/test")
    add_files("src/test/*.cpp")
    add_files("src/test.cpp")

-- Generate the Qt application.
target("qt-app")
    set_kind("binary")
    -- add_rules("qt.widgetapp")
    add_packages("qt6core", "qt6gui", "qt6widgets")
    add_rules("qt.application")
    add_frameworks("QtWidgets", "QtGui", "QtCore")

    -- Backend files.
    add_includedirs("src/backend")
    add_files("src/backend/*.cpp")
    
    -- Qt files.
    add_includedirs("src/qt")
    add_files("src/qt/mainwindow.h")
    add_files("src/qt/*.cpp")
    add_files("src/qt_main.cpp")