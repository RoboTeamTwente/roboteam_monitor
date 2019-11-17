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
        src/main.cpp
        src/presenters/ChartPresenter.cpp
        src/views/WelcomeDialog.cpp
        src/views/components/MenuBar.cpp
        src/views/NewGraphDialog.cpp
        src/views/MainWindow.cpp
        src/models/SeriesModel.cpp
        src/views/ChartSeriesDialog.cpp
        src/utils/Helpers.cpp
        src/views/components/SelectTypeWidget.cpp
        src/views/AddFilterDialog.cpp src/views/AddFilterDialog.h
        src/views/ChartView.cpp src/views/ChartView.h
        src/views/SeriesView.cpp
        src/views/SeriesView.h
        src/models/FilterModel.cpp
        src/views/FilterView.cpp
        src/views/FilterView.h
        src/views/components/ConfirmationWidget.cpp
        src/views/components/ConfirmationWidget.h
        src/presenters/SeriesInputSettingsPresenter.cpp
        src/presenters/SeriesInputSettingsPresenter.h
        src/views/SeriesInputSettingsView.cpp
        src/views/SeriesInputSettingsView.h
        src/presenters/SeriesInputSettingsPresenter.cpp
        src/presenters/SeriesInputSettingsPresenter.h
        src/models/SeriesInputSettingsModel.h
        src/models/ChartModel.h)

# link the exe against the libraries
target_link_libraries(roboteam_monitor
        PUBLIC roboteam_proto
        PUBLIC roboteam_utils
        PRIVATE Qt5::Widgets
        PRIVATE Qt5::Gui
        PRIVATE Qt5::Charts
        )

target_include_directories(roboteam_monitor
        INTERFACE include
        PRIVATE include
        PRIVATE src )
