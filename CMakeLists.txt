cmake_minimum_required (VERSION 2.8)
project (OADR)
set(LIBOADR_MAJOR_VERSION 1)
set(LIBOADR_MINOR_VERSION 0)
set(LIBOADR_MICRO_VERSION 0)
set(LIBOADR_VERSION ${LIBOADR_MAJOR_VERSION}.${LIBOADR_MINOR_VERSION}.${LIBOADR_MICRO_VERSION})

# Library notes:
# apt-get install libxerces-c-dev
# apt-get install libcurl4-gnutls-dev

# options off-by-default that you can enable
option(WERROR "Set all warnings to errors" OFF)
option(STATICLIBS "Builds static versions of all installed libraries" OFF)
option(TEST "Build the test suite" OFF)
option(SAMPLE "Build sample ven manager" ON)

if(STATICLIBS)
  set(LIB_TYPE STATIC)
else()
  set(LIB_TYPE SHARED)
endif()

# assume gcc/clang otherwise
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

# different release and debug flags
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

if (WERROR)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

set(CMAKE_REQUIRED_FLAGS ${CMAKE_CXX_FLAGS})

# include paths for all the local libraries
include_directories(oadr)
include_directories(oadrsd)
include_directories(xsd-4.0.0)
#include_directories(mongoose)
#include_directories(Http)
include_directories(mysqlmgr)
include_directories(mysqlwrapper)

include_directories(goosemgr/c)


# ---- libmysqlmgr ----
file(GLOB_RECURSE mysqlmgr_SRC ./mysqlmgr/*.cpp)
add_library(mysqlmgr ${LIB_TYPE} ${mysqlmgr_SRC})
install(TARGETS mysqlmgr DESTINATION lib)
set(INSTALL_ARGS FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ./mysqlmgr DESTINATION include ${INSTALL_ARGS})
#must link the mysqlmgr with the library libmysqlclient.a
#after >sudo apt-get install libmysqlclient-dev, the libmysqlclient.a will be placed in /usr/lib/x86_64-linux-gnu/libmysqlclient.a
target_link_libraries (mysqlmgr ${CMAKE_SOURCE_DIR}/libmysqlclient/libmysqlclient.a)


# ---- libdbwrapper ----
file(GLOB_RECURSE dbwrapper_SRC ./mysqlwrapper/*.cpp)
add_library(dbwrapper ${LIB_TYPE} ${dbwrapper_SRC})
install(TARGETS dbwrapper DESTINATION lib)
set(INSTALL_ARGS FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ./mysqlwrapper DESTINATION include ${INSTALL_ARGS})
target_link_libraries (dbwrapper mysqlmgr)


# ---- libgoosemgr ----
file(GLOB_RECURSE goosemgr_SRC ./goosemgr/*.c)
add_library(goosemgr ${LIB_TYPE} ${goosemgr_SRC})
install(TARGETS goosemgr DESTINATION lib)
set(INSTALL_ARGS FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ./goosemgr DESTINATION include ${INSTALL_ARGS})
target_link_libraries (goosemgr ${CMAKE_SOURCE_DIR}/goosemgr/c/Lib/libpacket.a ${CMAKE_SOURCE_DIR}/goosemgr/c/Lib/libwpcap.a ${CMAKE_SOURCE_DIR}/goosemgr/c/Lib/Packet.lib ${CMAKE_SOURCE_DIR}/goosemgr/c/Lib/wpcap.lib -lpcap dbwrapper)


# ---- liboadr ----
file(GLOB_RECURSE oadr_SRC ./oadr/oadr/*.cpp)
add_library(oadr ${LIB_TYPE} ${oadr_SRC})
install(TARGETS oadr DESTINATION lib)
set(INSTALL_ARGS FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ./oadr/oadr DESTINATION include ${INSTALL_ARGS})
target_link_libraries (oadr mysqlmgr)


# ---- liboadrsd ----
file(GLOB_RECURSE oadrsd_SRC ./oadrsd/oadrsd/*.cxx)
add_library(oadrsd ${LIB_TYPE} ${oadrsd_SRC})
install(TARGETS oadrsd DESTINATION lib)
set(INSTALL_ARGS FILES_MATCHING PATTERN "*.hxx" PATTERN "*.txx" PATTERN "*.ixx")
install(DIRECTORY ./oadrsd/oadrsd DESTINATION include ${INSTALL_ARGS})
install(DIRECTORY ./xsd-4.0.0/xsd DESTINATION include ${INSTALL_ARGS})

# ---- libHttp ----
#file(GLOB_RECURSE Http_SRC ./Http/*.cpp)
#add_library(Http ${LIB_TYPE} ${Http_SRC})
#install(TARGETS Http DESTINATION lib)
#set(INSTALL_ARGS FILES_MATCHING PATTERN "*.h")
#target_link_libraries (${CMAKE_SOURCE_DIR}/pistache/libpistache.a)
#install(DIRECTORY ./Http DESTINATION include ${INSTALL_ARGS})

 




# ---- libmongoose ----
#file(GLOB_RECURSE mongoose_SRC ./mongoose/*.cpp)
#add_library(mongoose ./mongoose/Server.cpp ./mongoose/WebController.cpp)
#install(TARGETS mongoose DESTINATION lib)
#set(INSTALL_ARGS FILES_MATCHING PATTERN "*.h")
#install(DIRECTORY ./mongoose DESTINATION include ${INSTALL_ARGS})




# ---- libpistache ----
#add_library(pistache ./pistache/libpistache.a)


if (SAMPLE)
  # ---- samplevenmanager ----
  add_definitions(-DELPP_THREAD_SAFE -DELPP_NO_DEFAULT_LOG_FILE)
  file(GLOB_RECURSE samplevenmanager_SRC ./samplevenmanager/samplevenmanager/*.cpp)
  add_executable(samplevenmgr ${samplevenmanager_SRC})
  
  #link static lib "libpistache.a" to main.cpp
  # and static rapid61850 lib goosemgr which is in fact the shared lib "VEN_CPP_source/libgoosemgr.so"
  target_link_libraries (samplevenmgr LINK_PUBLIC ${CMAKE_SOURCE_DIR}/libpistache/libpistache.a oadr oadrsd mysqlmgr goosemgr curl xerces-c pthread)
  
  # as VENManager.cpp of oadr will use global variable MyDB db which is defined in main.cpp of samplevenmgr,
  # need to link samplevenmgr.so to liboadr
  #target_link_libraries (oadr samplevenmgr)
  #target_link_libraries (samplevenmgr LINK_PUBLIC ${CMAKE_SOURCE_DIR}/pistache/libpistache.a oadr oadrsd Http curl xerces-c pthread)
  #target_link_libraries (samplevenmgr LINK_PUBLIC -lpistache oadr oadrsd curl xerces-c pthread)
endif()

if (0)
  
  add_subdirectory(googletest-release-1.7.0)

  include_directories(googletest-release-1.7.0/include)
  link_directories(googletest-release-1.7.0/lib)
  set (CMAKE_REQUIRED_INCLUDES googletest-release-1.7.0/include)

  # file(COPY )
  file(REMOVE_RECURSE ./xml)
  file(COPY ./oadrtest/oadrtest DESTINATION ./xml FILES_MATCHING PATTERN "*.xml" PATTERN "*.txt")
  
  # ---- tests ----
  file(GLOB_RECURSE oadrtest_SRC ./oadrtest/oadrtest/*.cpp)
  add_executable(testoadr ${oadrtest_SRC})
  target_link_libraries (testoadr LINK_PUBLIC oadr oadrsd curl xerces-c gtest pthread)

endif()

