cmake_minimum_required(VERSION 3.13)
project(RbusPlugin C)

find_library(RBUS_LIBRARY NAMES rbus)
find_library(RBUS_CORE_LIBRARY NAMES rbuscore)
find_path(
  RBUS_INCLUDE_DIR
  NAMES rbus.h
  PATH_SUFFIXES rbus)
find_path(
  RTMSG_INCLUDE_DIR
  NAMES rtMessage.h
  PATH_SUFFIXES rtmessage)
if(NOT RBUS_LIBRARY
   OR NOT RBUS_CORE_LIBRARY
   OR NOT RBUS_INCLUDE_DIR
   OR NOT RTMSG_INCLUDE_DIR)
  if(APPLE)
    message(
      FATAL_ERROR
        "rbus not found, run:\nbrew tap stepherg/tap\nbrew install rbus")
  else()
    message(FATAL_ERROR "rbus not found")
  endif()
endif()

find_library(PROTOBUF_C_LIBRARIES NAMES protobuf-c)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -fno-asynchronous-unwind-tables -ffunction-sections -fPIC"
)

set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -fno-omit-frame-pointer -fno-inline -O0 -g3 -ggdb3")

# Include directories for protobuf-c headers
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/protobuf
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/google ${RBUS_INCLUDE_DIR})

if(APPLE)
  include_directories(/opt/homebrew/include)
  set(CMAKE_C_FLAGS
      "${CMAKE_C_FLAGS} -Wno-typedef-redefinition -Wno-unused-but-set-variable")
endif()

# Define the source files
set(SOURCES
    rbus_plugin.c
    rbus.c
    protobuf/messages.pb-c.c
    protobuf/description.pb-c.c
    protobuf/descriptor.pb-c.c
    protobuf/value.pb-c.c
    protobuf/google/protobuf/any.pb-c.c
    protobuf/google/protobuf/empty.pb-c.c)

# Create executable
add_executable(rbus_plugin ${SOURCES})

# Link protobuf-c
target_link_libraries(rbus_plugin ${PROTOBUF_C_LIBRARIES} ${RBUS_LIBRARY}
                      ${RBUS_CORE_LIBRARY})
