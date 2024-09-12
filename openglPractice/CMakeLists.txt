set(GLAD_INCLUDE_PATH "" CACHE STRING "Path of include of glad")
set(GLAD_SOURCE_PATH "" CACHE STRING "Path of src of glad")
set(GLFW_INCLUDE_PATH "" CACHE STRING "Path of include of glfw")
set(GLFW_LIB_PATH "" CACHE STRING "Path of release lib of glfw")

check_empty(GLAD_INCLUDE_PATH)
check_empty(GLAD_SOURCE_PATH)
check_empty(GLFW_INCLUDE_PATH)
check_empty(GLFW_LIB_PATH)

function(add_opengl_app EXE_NAME)
    message(STATUS "Create exe(${EXE_NAME}) with src(${ARGN})")

    if(NOT DEFINED EXE_NAME)
        message(FATAL_ERROR "EXE_NAME is not defined")
    else()
        list(LENGTH ARGN length)
        if(length LESS 1)
            message(FATAL_ERROR "src files are not defined")
        endif()
    endif()

    add_executable(${EXE_NAME} ${ARGN} "${GLAD_SOURCE_PATH}/glad.c")

    target_include_directories(${EXE_NAME} PRIVATE ${GLAD_INCLUDE_PATH} ${GLFW_INCLUDE_PATH})

    target_link_directories(${EXE_NAME} PRIVATE ${GLFW_LIB_PATH})

    target_link_libraries(${EXE_NAME}
        opengl32
        glfw3
    )
endfunction(add_opengl_app)

# applications
add_subdirectory(createWindow)
