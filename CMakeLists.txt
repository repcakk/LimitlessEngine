cmake_minimum_required(VERSION 3.9)

project(LimitlessEngine)

# Turn on the ability to create folders to organize projects (.vcproj)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Command to output information to the console
message ("cxx Flags:" ${CMAKE_CXX_FLAGS})

# Sub-directories
add_subdirectory(LimitlessEngineGraphics)
add_subdirectory(LimitlessEngineCore)
