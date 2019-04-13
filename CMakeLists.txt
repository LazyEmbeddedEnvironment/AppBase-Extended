cmake_minimum_required(VERSION 3.5)
project(libfriendappbase VERSION 1.0.0 LANGUAGES CXX)

###################################################
# Download and unpack appbase at configure time
configure_file(${CMAKE_SOURCE_DIR}/cmake/AppBase-CMakeLists.txt.in ${CMAKE_BINARY_DIR}/appbase/appbase-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/appbase/appbase-download )
if(result)
    message(FATAL_ERROR "CMake step for appbase failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/appbase/appbase-download )
if(result)
    message(FATAL_ERROR "Build step for appbase failed: ${result}")
endif()

# Add appbase directly to our build. This defines appbase
add_subdirectory(${CMAKE_BINARY_DIR}/appbase/appbase-src)


##############################################
#Make sure that custom modules like forked appbase are found
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

##############################################
# Declare dependencies
find_package(AppBase REQUIRED)

##############################################
# Create target and set properties

add_library(friendappbase
        src/AppBase.cpp
        )

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(Friend::AppBase ALIAS friendappbase)

#Set target properties
target_include_directories(friendappbase
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(friendappbase PRIVATE cxx_auto_type)
target_compile_options(friendappbase PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

target_link_libraries(friendappbase
    PRIVATE
        AppBase::appbase
)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/FriendAppBase)

install(TARGETS friendappbase
    EXPORT friendappbase-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name FriendAppBase and not friendappbase
set_target_properties(friendappbase PROPERTIES EXPORT_NAME FriendAppBase)
set_target_properties(friendappbase PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set_target_properties(friendappbase PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/library")

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT friendappbase-targets
  FILE
    FriendAppBaseTargets.cmake
  NAMESPACE
    Friend::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/FriendAppBaseConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FriendAppBaseConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/FriendAppBaseConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/FriendAppBaseConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/FriendAppBaseConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################

export(EXPORT friendappbase-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/FriendAppBaseTargets.cmake NAMESPACE Friend::)

#Register package in user's package registry
export(PACKAGE FriendAppBase)

add_subdirectory(test)
