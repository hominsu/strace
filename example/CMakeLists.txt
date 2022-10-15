cmake_minimum_required(VERSION 2.8.12)

if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif ()

set(EXAMPLES
        stack_trace_cc
        stack_trace_cxx
        )

foreach (example ${EXAMPLES})
    file(GLOB SOURCE_FILES
            ${example}/*.cc
            ${example}/*.c)
    add_executable(${example} ${SOURCE_FILES})
    target_link_libraries(${example} strace)
endforeach ()

add_custom_target(examples ALL DEPENDS ${EXAMPLES})
