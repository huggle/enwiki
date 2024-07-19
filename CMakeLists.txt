# This is a build file for Huggle (used with cmake)
# You will need to update it by hand!
cmake_minimum_required (VERSION 2.8.7)
PROJECT(huggle_en)
#  cmake <folder> -DQT5_BUILD=true
option(QT5_BUILD "Build huggle using the Qt5 framework" FALSE)
SET(QT_USE_QTNETWORK TRUE)
SET(QT_USE_QTXML TRUE)
SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
include_directories(../../)
if (QT6_BUILD)
    SET(CMAKE_CXX_FLAGS "-std=c++17")
    find_package(Qt6Core REQUIRED)
    find_package(Qt6Gui REQUIRED)
    find_package(Qt6Xml REQUIRED)
    find_package(Qt6Widgets REQUIRED)
    find_package(Qt6Network REQUIRED)
    set(QT_INCLUDES ${Qt6Gui_INCLUDE_DIRS} ${Qt6Widgets_INCLUDE_DIRS} ${Qt6Network_INCLUDE_DIRS} ${Qt6Xml_INCLUDE_DIRS} ${Qt6Svg_INCLUDE_DIRS})
    include_directories(${QT_INCLUDES})
elseif(QT5_BUILD)
    SET(CMAKE_CXX_FLAGS "-std=c++11")
    find_package(Qt5Core REQUIRED)
    find_package(Qt5Gui REQUIRED)
    find_package(Qt5Xml REQUIRED)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5Network REQUIRED)
    set(QT_INCLUDES
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Network_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS}
        ${Qt5Svg_INCLUDE_DIRS}
    )
    include_directories(${QT_INCLUDES})
endif()

file(GLOB enwiki_srcx
    "src/*.cpp"
)
file (GLOB enwiki_resx
    "src/*.qrc"
)
file (GLOB enwiki_uixx
    "src/*.ui"
)

SET(enwiki_SOURCES ${enwiki_srcx})
SET(enwiki_FORMS ${enwiki_uixx})
SET(enwiki_RESOURCES ${enwiki_resx})
if(QT6_BUILD)
    QT6_WRAP_CPP(enwiki_HEADERS_MOC ${enwiki_HEADERS})
    QT6_WRAP_UI(enwiki_FORMS_HEADERS ${enwiki_FORMS})
    QT6_ADD_RESOURCES(enwiki_RESOURCES_RCC ${enwiki_RESOURCES})
elseif(QT5_BUILD)
    QT5_WRAP_CPP(enwiki_HEADERS_MOC ${enwiki_HEADERS})
    QT5_WRAP_UI(enwiki_FORMS_HEADERS ${enwiki_FORMS})
    QT5_ADD_RESOURCES(enwiki_RESOURCES_RCC ${enwiki_RESOURCES})
else()
    QT4_WRAP_CPP(enwiki_HEADERS_MOC ${enwiki_HEADERS})
    QT4_WRAP_UI(enwiki_FORMS_HEADERS ${enwiki_FORMS})
    QT4_ADD_RESOURCES(enwiki_RESOURCES_RCC ${enwiki_RESOURCES})
endif()
if (NOT QT5_BUILD AND NOT QT6_BUILD)
  INCLUDE(${QT_USE_FILE})
endif()
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS( -DQT_USE_QSTRINGBUILDER )
ADD_LIBRARY(huggle_en SHARED ${enwiki_SOURCES} ${enwiki_HEADERS_MOC} ${enwiki_FORMS_HEADERS} ${enwiki_RESOURCES_RCC})
TARGET_LINK_LIBRARIES(huggle_en ${QT_LIBRARIES})
TARGET_LINK_LIBRARIES(huggle_en huggle_core huggle_ui)
if (QT6_BUILD)
    TARGET_LINK_LIBRARIES(huggle_en Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Xml)
elseif (QT5_BUILD)
    TARGET_LINK_LIBRARIES(huggle_en Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml)
endif()
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
if (LINUX_SNAP)
    INSTALL(TARGETS huggle_en DESTINATION bin/extensions)
else()
    INSTALL(TARGETS huggle_en DESTINATION share/huggle/extensions)
endif()
