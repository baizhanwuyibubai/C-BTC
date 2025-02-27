# CMakeLists.txt
cmake_minimum_required(VERSION 3.1)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)
project(Mode)#

add_executable(Project  src/main.cpp
                    #src/communication/BoostUDP.cpp
                    #src/communication/BoostPort.cpp
                    src/communication/BoostTCP.cpp
                    src/communication/InputToOutput.cpp
                    src/communication/QCurl.cpp
                    src/communication/Json.cpp
                    src/Timer/TimerCount.cpp
                    src/User/UserAnalysis.cpp
                    src/User/CurlThread.cpp 
                    src/OverallClass/Overall.cpp 
                    src/TradeRun/MainTrade.cpp 
                    src/TradeRun/Algorithm.cpp 
                    src/TradeRun/NewFileSave.cpp 
                    src/TradeRun/TradeMacd.cpp
                    src/TradeRun/BOLL.cpp 
                    src/TradeRun/KDJ.cpp 
                    src/TradeRun/MACD.cpp 
                    src/TradeRun/RSI.cpp 
                    src/TradeRun/SAR.cpp 
                    )

#if (WIN32 OR MSVC)
#    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
#elseif (UNIX)
    # 仅查找静态库，强制后缀为 .a
#    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

    # 如果只是优先查找静态库，保证 .a 后缀在前面即可，把默认的后缀加上
    # set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
#endif()

#find_library(FLATBUFFERS_LIB flatbuffers)
#target_link_libraries(Pro ${FLATBUFFERS_LIB})

#target_include_directories(run PRIVATE ${PROJECT_SOURCE_DIR} "D:/library/boost/include/boost_1_86/" "D:/library/boost/include/boost_1_86/boost/")
#message(PRIVATE)
###############################################
if(CMAKE_SYSTEM_NAME MATCHES "Linux")

    message(STATUS "This is Linux system.")
    target_include_directories(Project PRIVATE ${PROJECT_SOURCE_DIR} "/opt/boost_1_86/" "/opt/boost_1_86/boost/")
    find_package(Threads REQUIRED)
 
    # 链接Threads库到pthread_example目标
    target_link_libraries(Project Threads::Threads -static)

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")

    include_directories("E:/library/boost_1_86")
    include_directories("E:/library/boost_1_86/boost")

    include_directories("E:/library/libcurl/include/curl")

    include_directories("E:/library/jsoncpp/include")
    include_directories("E:/library/jsoncpp/include/json")

    include_directories("E:/library/talib/include")

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_libraries(Project E:/library/jsoncpp/lib/jsoncppd.lib
                                    -static)
        set(CMAKE_CXX_FLAGS_RELEASE "/MT")
        message(STATUS "Debug build1")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_link_libraries(Project E:/library/jsoncpp/lib/jsoncpp.lib
                                    -static)
        set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
        message(STATUS "Release build")
    else()
        message(STATUS "Other build type: ${CMAKE_BUILD_TYPE}")
    endif()

    if (MSVC)
    set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
    endif(MSVC)

    target_link_libraries(Project   ws2_32.lib 
                                    winmm.lib 
                                    wldap32.lib 
                                    Crypt32.lib 
                                    Normaliz.lib 
                                    E:/library/libcurl/lib/libcurl_a.lib 
                                    E:/library/talib/lib/ta_libc_cdr.lib
                                    E:/library/talib/lib/ta_func_cdr.lib
                                    E:/library/talib/lib/ta_common_cdr.lib
                                    E:/library/talib/lib/ta_abstract_cdr.lib
                                    -static)

    #LINK_LIBRARIES("/opt/MATLAB/R2012a/bin/glnxa64/libeng.so")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "This is MacOS system.")
else()
    message(STATUS "This is another system: ${CMAKE_SYSTEM_NAME}")
endif()
###############################################
