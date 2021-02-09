cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS -g)

project(TikzView)

include_directories(.)

add_library(tikz dfs.cpp)

add_library(test testutil.cpp)
target_link_libraries(test tikz)

add_executable(testmain testmain.cpp)
target_link_libraries(testmain test)

add_custom_target(testmain_run
  COMMAND testmain
  BYPRODUCTS tikztree.tex
  SOURCES testmain.cpp)

add_custom_target(tikztree.pdf
  COMMAND pdflatex tikztree.tex
  DEPENDS testmain_run
  SOURCES tikztree.tex)

add_custom_target(tikzpdf evince tikztree.pdf
  DEPENDS tikztree.pdf)



#add_custom_target()
#add_custom_command(
#  OUTPUT build/tikztree.pdf
#  COMMAND pdflatex )
