# CMakeList.txt : CMake project for helloLibevent, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

project ("HelloAsio" VERSION 0.0.1)



include(./cmake/checkBuildType.cmake)

#-------------------------------------
#  spdlog settings
#-------------------------------------
include(./cmake/utils.cmake)


include(./.SET_LOCAL_PATH.cmake)


# --------------------------------------------------------------------------
# specify the C++ standard
 set(CMAKE_CXX_STANDARD 17)
 set(CMAKE_CXX_STANDARD_REQUIRED True)
 set(CMAKE_CXX_FLAGS "-D__STDC_CONSTANT_MACROS ${CMAKE_CXX_FLAGS}")




if(MSVC)
    SET(CMAKE_CXX_FLAGS "/EHsc ${CMAKE_CXX_FLAGS}")  # deal with MSVC Warning C4530
    SET(CMAKE_CXX_FLAGS "/utf-8 ${CMAKE_CXX_FLAGS}")  # set default charset to utf-8
endif(MSVC)


macro(get_WIN32_WINNT version)
    if (WIN32 AND CMAKE_SYSTEM_VERSION)
        set(ver ${CMAKE_SYSTEM_VERSION})
        string(REPLACE "." "" ver ${ver})
        string(REGEX REPLACE "([0-9])" "0\\1" ver ${ver})
        set(${version} "0x${ver}")
    endif()
endmacro()

if(WIN32)
    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
endif()

#-------------------------------------
#  config.h.in settings
#-------------------------------------


option(BOOST_DATE_TIME_NO_LIB  "disable boost::Date_time in asio" ON)
option(BOOST_REGEX_NO_LIB  "disable boost::regex in asio" ON)

set(CPPHTTPLIB_THREAD_POOL_COUNT 64)

set(SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE)
set(LOG_FILE_NAME "littleGift.log")
set(CA_CERT_FILE "./resources/ca-bundle.crt")

configure_file(
	"./cmake/config.h.in" 
	"${PROJECT_SOURCE_DIR}/include/config.h"
	@ONLY
)



add_subdirectory(tutorial)

add_subdirectory(examples)

add_subdirectory(learning)


