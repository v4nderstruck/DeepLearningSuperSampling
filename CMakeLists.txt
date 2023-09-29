cmake_minimum_required (VERSION 3.20)
project (metal_dlss)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

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

file(GLOB SOURCE_FILES
  src/*.cpp
  src/x3d/*.cpp
 )
add_executable(metal_dlss
  ${SOURCE_FILES}
)

target_include_directories(metal_dlss
  SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/src/metal-cpp
)

target_include_directories(metal_dlss
  SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/src/metal-cpp/Metal
)

target_link_libraries(metal_dlss
  ${APPLE_FWK_FOUNDATION}
  ${APPLE_FWK_QUARTZ_CORE}
  ${APPLE_FWK_METAL}
)
