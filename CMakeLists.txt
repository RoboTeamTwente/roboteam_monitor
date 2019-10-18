cmake_minimum_required(VERSION 3.10)
project(roboteam_monitor)

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC OFF)


# for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
if(APPLE)
    set(Qt5Widgets_DIR "/usr/local/opt/qt5/lib/cmake/Qt5Widgets")
    set(Qt5Core_DIR "/usr/local/opt/qt/lib/cmake/Qt5Core")
    set(Qt5Gui_DIR "/usr/local/opt/qt/lib/cmake/Qt5Gui")
    SET(Qt5Charts_DIR "/usr/local/opt/qt/lib/cmake/Qt5Charts")

    find_package(Qt5Core REQUIRED)
    find_package(Qt5Gui REQUIRED)
endif()

# for Linux, BSD, Solaris, Minix
if(UNIX AND NOT APPLE)
    SET(Qt5Widgets_DIR "/usr/include/x86_64-linux-gnu/qt5/QtWidgets")
    SET(Qt5Charts_DIR "/usr/include/x86_64-linux-gnu/qt5/QtCharts")
endif()

find_package(Qt5Charts REQUIRED)
find_package(Qt5Widgets REQUIRED)


# Add an executable
add_executable(roboteam_monitor
        src/main.cpp src/ChartView.cpp include/ChartView.h src/WelcomeDialog.cpp include/WelcomeDialog.h src/MenuBar.cpp include/MenuBar.h src/NewGraphDialog.cpp include/NewGraphDialog.h src/MainWindow.cpp include/MainWindow.h src/ChartSeries.cpp include/ChartSeries.h)

# link the exe against the libraries
target_link_libraries(roboteam_monitor
        PUBLIC roboteam_proto
        PRIVATE Qt5::Widgets
        PRIVATE Qt5::Gui
        PRIVATE Qt5::Charts
        PRIVATE roboteam_utils
        )

target_include_directories(roboteam_monitor
        INTERFACE include
        PRIVATE include/roboteam_monitor
        PRIVATE src )
