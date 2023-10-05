cmake_minimum_required (VERSION 3.20)
project (metal_dlss)

set(CMAKE_CXX_STANDARD 17)

find_library(APPLE_FWK_METAL Metal REQUIRED)
if(NOT APPLE_FWK_METAL)
  message(FATAL_ERROR "Metal library not found")
endif()
find_library(APPLE_FWK_FOUNDATION Foundation REQUIRED)
if(NOT APPLE_FWK_FOUNDATION)
  message(FATAL_ERROR "Metal library not found")
endif()
find_library(APPLE_FWK_QUARTZ_CORE QuartzCore REQUIRED)
if(NOT APPLE_FWK_QUARTZ_CORE)
  message(FATAL_ERROR "Metal library not found")
endif()
find_library(APPLE_FWK_APPKIT AppKit REQUIRED)
if(NOT APPLE_FWK_APPKIT)
  message(FATAL_ERROR "AppKit not found")
endif()
find_library(APPLE_FWK_METALKIT MetalKit REQUIRED)
if(NOT APPLE_FWK_METALKIT)
  message(FATAL_ERROR "MetalKit not found")
endif()

file(GLOB SOURCE_FILES
  src/*.cpp
  src/x3d/*.cpp
  src/x3d/engine/*.cpp
  src/x3d/mesh/*.cpp
  src/x3d/world/*.cpp
 )

add_executable(metal_dlss
  ${SOURCE_FILES}
)

add_compile_options(-g -O)

target_include_directories(metal_dlss
  PUBLIC ${CMAKE_SOURCE_DIR}/src/metal-cpp
  PUBLIC ${CMAKE_SOURCE_DIR}/src/metal-cpp/Metal
)

target_link_libraries(metal_dlss
  PRIVATE ${APPLE_FWK_FOUNDATION}
  PRIVATE ${APPLE_FWK_QUARTZ_CORE}
  PRIVATE ${APPLE_FWK_METAL}
  PRIVATE ${APPLE_FWK_APPKIT}
  PRIVATE ${APPLE_FWK_METALKIT}
)
