cmake_minimum_required(VERSION 3.10)
project(beam_yolo LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Require ERLANG_ERTS_DIR and ERL_INTERFACE_DIR from -D flags
if(NOT DEFINED ERLANG_ERTS_DIR)
    message(FATAL_ERROR "ERLANG_ERTS_DIR must be defined (pass -DERLANG_ERTS_DIR=...)")
endif()
if(NOT DEFINED ERL_INTERFACE_DIR)
    message(FATAL_ERROR "ERL_INTERFACE_DIR must be defined (pass -DERL_INTERFACE_DIR=...)")
endif()

set(ERTS_INCLUDE_DIR "${ERLANG_ERTS_DIR}/include")
set(ERL_INTERFACE_INCLUDE_DIR "${ERL_INTERFACE_DIR}/include")
set(ERL_INTERFACE_LIB_DIR "${ERL_INTERFACE_DIR}/lib")

include_directories(
    ${ERTS_INCLUDE_DIR}
    ${ERL_INTERFACE_INCLUDE_DIR}
)

link_directories(${ERL_INTERFACE_LIB_DIR})

add_library(beam-yolo SHARED c_src/yolo.c)
set_target_properties(beam-yolo PROPERTIES OUTPUT_NAME "beam-yolo" PREFIX "")

# Set output directory to priv/
set_target_properties(beam-yolo PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/priv"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/priv"
)

target_link_libraries(beam-yolo PRIVATE ei)
