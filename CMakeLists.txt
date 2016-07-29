cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

include(NotePosterCMakePolicies)
SET_POLICIES()


if("${CMAKE_MAJOR_VERSION}" GREATER "2")
  project(NotePoster
          VERSION 1.1.0)
else()
  project(NotePoster)
  set(PROJECT_VERSION_MAJOR "1")
  set(PROJECT_VERSION_MINOR "1")
  set(PROJECT_VERSION_PATCH "0")
  set(PROJECT_VERSION_COUNT 3)
  set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
endif()

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
    Settings.h)

set(SOURCES
    MainWindow.cpp
    SettingsDialog.cpp
    Settings.cpp
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

if(APPLE)
    set(MACOSX_BUNDLE_INFO_STRING "${PROJECT_NAME} ${PROJECT_VERSION}")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
    set(MACOSX_BUNDLE_COPYRIGHT "(c) 2014 Sergey Skoblikov, 2015-2016 Dmitry Ivanov")
    set(MACOSX_BUNDLE_ICON_FILE mainicon.icns)
    set(MACOSX_BUNDLE_ICON "${PROJECT_SOURCE_DIR}/${MACOSX_BUNDLE_ICON_FILE}")
    SET_SOURCE_FILES_PROPERTIES(${MACOSX_BUNDLE_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    list(APPEND SOURCES ${MACOSX_BUNDLE_ICON})
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "${PROJECT_DOMAIN_SECOND}.${PROJECT_DOMAIN_FIRST}")
    set(MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}")
    set(MACOSX_BUNDLE_RESOURCES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Resources")
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${MACOSX_BUNDLE_RESOURCES})
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MACOSX_BUNDLE_ICON} ${MACOSX_BUNDLE_RESOURCES})
endif()

add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${HEADERS} ${SOURCES} ${${PROJECT_NAME}_FORMS_HEADERS})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${QEVERCLOUD_LIBS})

set(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}")
if(APPLE)
  set(APPS "\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app")
endif()

install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION . COMPONENT Runtime
        RUNTIME DESTINATION bin COMPONENT Runtime)

set(DIRS ${QT_LIBRARY_DIRS})
install(CODE "
        include(BundleUtilities)
        fixup_bundle(\"${APPS}\"   \"\"   \"${DIRS}\")
        " COMPONENT Runtime)
