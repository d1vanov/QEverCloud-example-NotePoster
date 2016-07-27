cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

include(NotePosterCMakePolicies)
SET_POLICIES()

project(NotePoster)

include(NotePosterSetupQt)
include(NotePosterCompilerSettings)

if(USE_QT5)
  find_package(LibQEverCloud-qt5 REQUIRED)
  include_directories(${LIBQEVERCLOUD_QT5_INCLUDE_DIRS})
  add_definitions(${LIBQEVERCLOUD_QT5_DEFINITIONS})
  set(QEVERCLOUD_LIBS ${LIBQEVERCLOUD_QT5_LIBRARIES})
else()
  find_package(LibQEverCloud-qt4 REQUIRED)
  include_directories(${LIBQEVERCLOUD_QT4_INCLUDE_DIRS})
  set(QEVERCLOUD_LIBS ${LIBQEVERCLOUD_QT4_LIBRARIES})
endif()

set(HEADERS
    MainWindow.h
    SettingsDialog.h
    settings.h)

set(SOURCES
    MainWindow.cpp
    SettingsDialog.cpp
    settings.cpp
    main.cpp)

set(FORMS
    MainWindow.ui
    SettingsDialog.ui)

if(USE_QT5)
  qt5_wrap_ui(${PROJECT_NAME}_FORMS_HEADERS ${FORMS})
else()
  qt4_wrap_ui(${PROJECT_NAME}_FORMS_HEADERS ${FORMS})
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${${PROJECT_NAME}_FORMS_HEADERS})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${QEVERCLOUD_LIBS})
