cmake_minimum_required(VERSION 3.12)

# Project name
project(MedImGVisual)

set(CMAKE_CXX_STANDARD 17)


# Dinf VTK Modules used in the project
find_package(VTK COMPONENTS
  CommonColor
  CommonCore
  CommonDataModel
  IOImage
  IOXML
  ImagingCore
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

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")

set(exeName RenderImage)

add_executable(${exeName} MACOSX_BUNDLE main.cpp )
  target_link_libraries(${exeName} PRIVATE ${VTK_LIBRARIES}) 
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS ${exeName}
  MODULES ${VTK_LIBRARIES}
)
