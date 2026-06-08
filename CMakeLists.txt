cmake_minimum_required( VERSION 3.10 )

project( mlr VERSION 0.1 LANGUAGES CXX C)
set(PROJECT_DESCRIPTION "C++ SIMD OpenMP linear algebra math library")

include(GNUInstallDirs)
include(FindPkgConfig)

if( NOT CMAKE_BUILD_TYPE )
        set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
endif()

set( CMAKE_C_STANDARD 23 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD 26)
set( CMAKE_CXX_STANDARD_REQUIRED ON )

if( CMAKE_BUILD_TYPE EQUAL Debug )
	add_compile_options(-g)
endif()

if( NOT MSVC )
	if( NOT CMAKE_CROSSCOMPILING )
		add_compile_options(-march=native)
		if( CMAKE_GENERATOR_PLATFORM STREQUAL "x64" OR CMAKE_GENERATOR_PLATFORM STREQUAL "x86_64" OR CMAKE_GENERATOR_PLATFORM STREQUAL "AMD64" )
			add_compile_options(-mfpmath=sse)
		endif()
	endif()
	if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
		add_compile_options(-Wno-gnu-alignof-expression)
	endif()
	add_compile_options(-O3)
	add_compile_options(-fopenmp-simd)
	add_compile_options(-ftree-vectorize)
	add_compile_options(-D_FILE_OFFSET_BITS=64)
	add_compile_options(-fdata-sections)
	add_compile_options(-fpermissive)
	add_compile_options(-ffunction-sections)
	add_compile_options(-Wno-array-bounds)
	add_compile_options(-Wno-unused-parameter)
	add_compile_options(-Wno-pedantic)
	add_compile_options(-Wno-narrowing)
	add_link_options(-Wl,--gc-sections)
	add_link_options(-Wl,--print-gc-sections)
	add_link_options(-Wl,-s)
endif()

include_directories( mlr INTERFACE
        PUBLIC_HEADER $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
add_executable( vector examples/vector.cpp )
add_library(mlr INTERFACE)
target_include_directories( mlr INTERFACE
        PUBLIC_HEADER $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/mlr DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT headers)

#add_executable( example examples/example.c )
#target_link_libraries( example alcvx )


  # Genuine BZip2 does not provide bzip2.pc, but some platforms have
  # it.  For better dependency in freetype2.pc, bzip2.pc is searched
  # regardless of the availability of libbz2. If bzip2.pc is found,
  # Requires.private is used instead of Libs.private.


  #add_library(alcvx-objlib OBJECT alcvx.c)
  #add_library(alcvx-shared SHARED)
  #set_target_properties(alcvx-shared PROPERTIES OUTPUT_NAME alcvx)
  #target_link_libraries(alcvx-shared PUBLIC alcvx-objlib)

  #add_library(alcvx-static STATIC)
  #set_target_properties(alcvx-static PROPERTIES OUTPUT_NAME alcvx)
  #target_link_libraries(alcvx-static PUBLIC alcvx-objlib)

