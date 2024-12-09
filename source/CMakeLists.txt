cmake_minimum_required(VERSION 3.12)

# Project name
project(MedImGVisual)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL)
# Dinf VTK Modules used in the project
find_package(VTK COMPONENTS
  CommonColor
  CommonCore
  CommonDataModel
  IOImage
  IOXML
  GUISupportQt
  RenderingQt
  ImagingCore
  InteractionImage
  InteractionStyle
  InteractionWidgets
  FiltersSources
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  RenderingVolume
  RenderingVolumeOpenGL2
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "MedImGVisual: Unable to find the VTK build folder.")
endif()


### FIND QT Packages ####
set(qt_components Core Gui Widgets Xml)
if(${VTK_QT_VERSION} VERSION_GREATER_EQUAL 6)
  list(APPEND qt_components OpenGLWidgets)
endif()


# Instruct CMake to run moc and uic automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL Xml)

set(Gui_DIR ${CMAKE_SOURCE_DIR}/GUI)
include_directories(${Gui_DIR})

message (STATUS "VTK_VERSION: ${VTK_VERSION}, Qt Version: ${Qt${VTK_QT_VERSION}Widgets_VERSION}")



include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI )
file(GLOB_RECURSE SOURCES
    "${Gui_DIR}/*.ui"
    "${Gui_DIR}/*.h"
    "${Gui_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/GUI/mainwindow.cpp"  # Ensure mainwindow.cpp is included
)


set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${Gui_DIR})

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")

set(exeName RenderImage)

add_executable(${exeName} MACOSX_BUNDLE main.cpp ${SOURCES} ${QT_WRAP})
target_include_directories(${exeName} PRIVATE ${Gui_DIR})
target_link_libraries(${exeName} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGL Qt6::Xml)
target_link_libraries(${exeName} PRIVATE ${VTK_LIBRARIES})# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS ${exeName}
  MODULES ${VTK_LIBRARIES}
)
