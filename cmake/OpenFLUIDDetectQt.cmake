FIND_PACKAGE(Qt5 QUIET COMPONENTS Core Widgets Network Xml Svg Declarative Concurrent)

  IF(WIN32 AND Qt5Core_NOTFOUND)
    MESSAGE(FATAL_ERROR "Qt5 is required on Windows platforms")
  ENDIF()

  IF(Qt5Core_FOUND AND Qt5Widgets_FOUND AND Qt5Network_FOUND)

    CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
    CMAKE_POLICY(SET CMP0020 NEW)

    # redefinition of QT4_* macros for Qt5 compatibility
    MACRO(QT4_WRAP_UI)
      QT5_WRAP_UI(${ARGN})
    ENDMACRO()
  
    MACRO(QT4_WRAP_CPP)
      QT5_WRAP_CPP(${ARGN})
    ENDMACRO()
  
    MACRO(QT4_ADD_RESOURCES)
      QT5_ADD_RESOURCES(${ARGN})
    ENDMACRO()

    SET(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Network_INCLUDE_DIRS} ${Qt5Xml_INCLUDE_DIRS}
                    ${Qt5Svg_INCLUDE_DIRS} ${Qt5Declarative_INCLUDE_DIRS} )
                  
    SET(QT_QTCORE_LIBRARIES ${Qt5Core_LIBRARIES})
    SET(QT_QTGUI_LIBRARIES ${Qt5Widgets_LIBRARIES})
    SET(QT_QTNETWORK_LIBRARIES ${Qt5Network_LIBRARIES})
    SET(QT_QTXML_LIBRARIES ${Qt5Xml_LIBRARIES})
    SET(QT_QTSVG_LIBRARIES ${Qt5Svg_LIBRARIES})
    SET(QT_QTCONCURRENT_LIBRARIES ${Qt5Concurrent_LIBRARIES})
  
    # TODO use only LIBRARIES suffix
    SET(QT_QTCORE_LIBRARY ${Qt5Core_LIBRARIES})
    SET(QT_QTGUI_LIBRARY ${Qt5Widgets_LIBRARIES})
    SET(QT_QTNETWORK_LIBRARY ${Qt5Network_LIBRARIES})
    SET(QT_QTXML_LIBRARY ${Qt5Xml_LIBRARIES})
    SET(QT_QTSVG_LIBRARY ${Qt5Svg_LIBRARIES})
    SET(QT_QTCONCURRENT_LIBRARY ${Qt5Concurrent_LIBRARIES})
  
    MESSAGE(STATUS "Found Qt5 (version ${Qt5Core_VERSION})")
  
  ELSE()
  
    FIND_PACKAGE(Qt4 REQUIRED)
    
  ENDIF() 