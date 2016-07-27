if(NOT USE_QT5)
  find_package(Qt4 COMPONENTS QTCORE OPTIONAL QUIET)
  if(NOT QT_QTCORE_LIBRARY)
    message(STATUS "Qt4's core was not found, trying to find Qt5's libraries")
    set(USE_QT5 1)
  else()
    message(STATUS "Found Qt4 installation, version ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
  endif()
endif()

if(USE_QT5)
  find_package(Qt5Core REQUIRED)
  message(STATUS "Found Qt5 installation, version ${Qt5Core_VERSION}")

  find_package(Qt5Widgets REQUIRED)

  set(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
  set(QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES})
  set(QT_DEFINITIONS ${Qt5Core_DEFINITIONS} ${Qt5Widgets_DEFINITIONS})
else()
  find_package(Qt4 COMPONENTS QTCORE QTGUI)
  include(${QT_USE_FILE})
  # Workaround CMake > 3.0.2 bug with Qt4 libraries
  list(FIND QT_LIBRARIES "${QT_QTGUI_LIBRARY}" HasGui)
  if(HasGui EQUAL -1)
    list(APPEND QT_LIBRARIES ${QT_QTGUI_LIBRARY})
  endif()
endif()

include_directories(SYSTEM "${QT_INCLUDES} ${SYSTEM}")
add_definitions(${QT_DEFINITIONS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR "ON")
