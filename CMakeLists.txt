cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

include(NotePosterCMakePolicies)
SET_POLICIES()


if("${CMAKE_MAJOR_VERSION}" GREATER "2")
  project(NotePoster
          VERSION 1.0.0)
else()
  project(NotePoster)
  set(PROJECT_VERSION_MAJOR "1")
  set(PROJECT_VERSION_MINOR "0")
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

set(ICONS_DIR "${PROJECT_SOURCE_DIR}/icons")

if(MSVC)
  list(APPEND SOURCES NotePoster.rc)
endif()
  
if(APPLE)
  set(MACOSX_BUNDLE_INFO_STRING "${PROJECT_NAME} ${PROJECT_VERSION}")
  set(MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
  set(MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
  set(MACOSX_BUNDLE_COPYRIGHT "(c) 2014 Sergey Skoblikov, 2015-2016 Dmitry Ivanov")
  set(MACOSX_BUNDLE_ICON_FILE mainicon.icns)
  set(MACOSX_BUNDLE_ICON "${ICONS_DIR}/${MACOSX_BUNDLE_ICON_FILE}")
  set_source_files_properties(${MACOSX_BUNDLE_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
  list(APPEND SOURCES ${MACOSX_BUNDLE_ICON})
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "${PROJECT_DOMAIN_SECOND}.${PROJECT_DOMAIN_FIRST}")
  set(MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}")
  set(MACOSX_BUNDLE_RESOURCES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Resources")
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${MACOSX_BUNDLE_RESOURCES})
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MACOSX_BUNDLE_ICON} ${MACOSX_BUNDLE_RESOURCES})

  # use, i.e. don't skip the full RPATH for the build tree
  set(CMAKE_SKIP_BUILD_RPATH  FALSE)

  # when building, don't use the install RPATH already
  # (but later on when installing)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

  set(CMAKE_INSTALL_RPATH "@loader_path")

  # add the automatically determined parts of the RPATH
  # which point to directories outside the build tree to the install RPATH
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

  # the RPATH to be used when installing, but only if it's not a system directory
  list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
  if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  endif("${isSystemDir}" STREQUAL "-1")
endif()

add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32 ${HEADERS} ${SOURCES} ${${PROJECT_NAME}_FORMS_HEADERS})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${QEVERCLOUD_LIBS})

# Installation
if(APPLE OR WIN32)
  if(NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
  endif()

  if(APPLE)
    set(APPS "\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app")
  elseif(WIN32)
    set(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}.exe")
  endif()

  if(USE_QT5)
    if(APPLE)
      set (MACDEPLOYQT_APP ${Qt5Core_DIR}/../../../bin/macdeployqt)
      message(" - macdeployqt path: ${MACDEPLOYQT_APP}")
    endif()
    # we need to find path to windeployqt on windows
    if (WIN32)
      set (WINDEPLOYQT_APP ${Qt5Core_DIR}/../../../bin/windeployqt)
      message(" - windeployqt path: ${WINDEPLOYQT_APP}")
    endif()
  endif()

  install(TARGETS ${PROJECT_NAME}
          BUNDLE DESTINATION . COMPONENT Runtime
          RUNTIME DESTINATION bin COMPONENT Runtime)

  if(USE_QT5)
    if(APPLE)
      install(CODE "
      execute_process(COMMAND ${MACDEPLOYQT_APP} ${APPS})
      " COMPONENT Runtime)
    elseif(WIN32)
      install(CODE "
      execute_process(COMMAND ${WINDEPLOYQT_APP} ${APPS})
      " COMPONENT Runtime)
      if(USE_QT5)
        set(QEVERCLOUD_LIBNAME libQEverCloud-qt5.dll)
      else()
        set(QEVERCLOUD_LIBNAME libQEverCloud-qt4.dll)
      endif()
      get_filename_component(QEVERCLOUD_DIR ${QEVERCLOUD_LIBS} DIRECTORY)
      install(FILES ${QEVERCLOUD_DIR}/../bin/${QEVERCLOUD_LIBNAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
      set(DEPLOYED_QEVERCLOUD_LIB "\${CMAKE_INSTALL_PREFIX}/bin/${QEVERCLOUD_LIBNAME}")
      install(CODE "
      execute_process(COMMAND ${WINDEPLOYQT_APP} ${DEPLOYED_QEVERCLOUD_LIB})
      " COMPONENT Runtime)
    endif()
  endif()
else()
  install(TARGETS ${PROJECT_NAME} DESTINATION bin)
  install(FILES ${PROJECT_SOURCE_DIR}/icons/mainicon.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/icons)

  configure_file(${PROJECT_SOURCE_DIR}/NotePoster.desktop.in ${PROJECT_BINARY_DIR}/NotePoster.desktop @ONLY)
  if(XDG_APPS_DIR)
    set(DESKTOP_FILE_DIR ${XDG_APPS_DIR})
  else()
    set(DESKTOP_FILE_DIR ${CMAKE_INSTALL_PREFIX}/bin)
  endif()
  install(FILES ${PROJECT_BINARY_DIR}/NotePoster.desktop DESTINATION ${DESKTOP_FILE_DIR})
endif()
