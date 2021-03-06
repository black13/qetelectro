#"c:\Program Files\CMake\bin\cmake.exe"  -G "Visual Studio 14 2015" -D CMAKE_PREFIX_PATH="C:\Qt-2015\4.8.6\msvc2015" ..
cmake_minimum_required(VERSION 3.9)

project(qet)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(
${QT_INCLUDE_DIR}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

  find_package(Qt4
               COMPONENTS QtCore
                          QtDesigner
                          QtGui
                          QtOpenGL
                          QtScript
                          QtSvg
                          QtXml
               REQUIRED)


# Generate code from ui files

# Generate rules for building source files from the resources
set(SOURCES 
aboutqet.cpp
borne.cpp
conducteur.cpp
contacteur.cpp
del.cpp
element.cpp
elementfixe.cpp
elementperso.cpp
entree.cpp
main.cpp
panelappareils.cpp
qetapp.cpp
schema.cpp
schemavue.cpp
aboutqet.h
borne.h
conducteur.h
contacteur.h
debug.h
del.h
element.h
elementfixe.h
elementperso.h
entree.h
panelappareils.h
qetapp.h
schema.h
schemavue.h
)

add_executable(qet ${SOURCES})

target_link_libraries(qet Qt4::QtGui Qt4::QtXml ${QT_LIBRARIES})