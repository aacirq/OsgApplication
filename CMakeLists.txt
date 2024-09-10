cmake_minimum_required(VERSION 3.12)

project(OsgApplication)

# cache variables
set(OSG_INCLUDE "" CACHE STRING "Path of include of osg src")
set(OSG_BUILD_INCLUDE "" CACHE STRING "Path of include in osg build dir")
set(OSG_BUILD_LIB "" CACHE STRING "Path of lib in osg build dir")

# check cache variables
macro(check_empty var)
    if(NOT ${var})
        message(FATAL_ERROR "${var} is not set")
    else()
        message(STATUS "${var} is [${${var}}]")
    endif()
endmacro(check_empty)
check_empty(OSG_INCLUDE)
check_empty(OSG_BUILD_INCLUDE)
check_empty(OSG_BUILD_INCLUDE)

# function to add a application
function(add_app EXE_NAME)
    message(STATUS "Create exe(${EXE_NAME}) with src(${ARGN})")

    if(NOT DEFINED EXE_NAME)
        message(FATAL_ERROR "EXE_NAME is not defined")
    else()
        list(LENGTH ARGN length)
        if(length LESS 1)
            message(FATAL_ERROR "src files are not defined")
        endif()
    endif()

    add_executable(${EXE_NAME} ${ARGN})

    set(OSG_INCLUDE_PATHS
        ${OSG_BUILD_INCLUDE}
        ${OSG_INCLUDE})

    target_include_directories(${EXE_NAME} PRIVATE ${OSG_INCLUDE_PATHS})

    target_link_directories(${EXE_NAME} PRIVATE ${OSG_BUILD_LIB})

    set(OSG_LIBRARYS
        debug osgd optimized osg
        debug osgDBd optimized osgDB
        debug osgViewerd optimized osgViewer
        debug osgGAd optimized osgGA
        debug osgAnimationd optimized osgAnimation
        debug osgFXd optimized osgFX
        debug osgManipulatord optimized osgManipulator
        debug osgUtild optimized osgUtil
        debug OpenThreadsd optimized OpenThreads)

    target_link_libraries(${EXE_NAME} ${OSG_LIBRARYS})
endfunction(add_app)

# applications
add_subdirectory(osgMini)
add_subdirectory(osgBillboard)
add_subdirectory(osgGeometry)
