# @note 3.20 required for `GENERATED` attribute to be project-wide i.e. Version.h isn't build until build-time
cmake_minimum_required(VERSION 3.20)

# Hint: `ANDROID_HOME` 
# Hint: `JAVA_HOME` = `C:/Program Files/Android/Android Studio/jre` on windows

# @defines
#   "CMAKE_SYSTEM_NAME": "Android",
#   "CMAKE_SYSTEM_VERSION": "29",
#   "CMAKE_ANDROID_STL_TYPE": "c++_static",
#   "CMAKE_ANDROID_EXCEPTIONS": "TRUE",
#   "CMAKE_ANDROID_ARCH_ABI": "arm64-v8a" ....OR.... "armeabi-v7a",# 
# @user-defines
#   "CMAKE_ANDROID_SDK": "$env{ANDROID_HOME}",
#   "CMAKE_ANDROID_NDK": "$env{ANDROID_HOME}/ndk/25.1.8937393",
#   "JAVA_HOME": "$env{JAVA_HOME}"

# Provide path for scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")

#include(GNUInstallDirs)
option(ANDROIDPACKAGING_BUILD_TESTING "Build unit-tests" YES)
option(ANDROIDPACKAGING_BUILD_EXAMPLES "Build examples" NO)

message(CHECK_START "AndroidPackaging")
list(APPEND CMAKE_MESSAGE_INDENT "  ")
unset(MISSING_ANDROID_COMPONENTS)


if ( NOT DEFINED ANDROID_HOME AND DEFINED ENV{ANDROID_HOME}) 
    set(ANDROID_HOME $ENV{ANDROID_HOME} )
endif()

if ( NOT DEFINED CMAKE_ANDROID_SDK AND DEFINED ANDROID_HOME) 
    message( STATUS  "Setting CMAKE_ANDROID_SDK from ENV{ANDROID_HOME}" )
	file(TO_CMAKE_PATH "${ANDROID_HOME}" CMAKE_ANDROID_SDK)
endif()

message(CHECK_START "Find Android SDK")
if( DEFINED CMAKE_ANDROID_SDK AND EXISTS "${CMAKE_ANDROID_SDK}")
    message( CHECK_PASS "CMAKE_ANDROID_SDK is ${CMAKE_ANDROID_SDK}" )
else()
    if( NOT DEFINED CMAKE_ANDROID_SDK )
        message( CHECK_FAIL "CMAKE_ANDROID_SDK was not defined.\n"
                            "Get Android SDK from Studio or Commandline-Tools:\n"
                            "https://developer.android.com/studio#downloads" )
    else()
        message( CHECK_FAIL "CMAKE_ANDROID_SDK '${CMAKE_ANDROID_SDK}' is not a valid directory." )
    endif()
    list(APPEND MISSING_ANDROID_COMPONENTS SDK)
endif()

message(CHECK_START "Find Android NDK")
# @todo We should detect the available NDK versions atm its hard-coded
if ( NOT DEFINED CMAKE_ANDROID_NDK AND DEFINED CMAKE_ANDROID_SDK) 
	file(TO_CMAKE_PATH "${CMAKE_ANDROID_SDK}/ndk/25.1.8937393" CMAKE_ANDROID_NDK)
endif()

if( DEFINED CMAKE_ANDROID_NDK AND EXISTS "${CMAKE_ANDROID_NDK}")
    message( CHECK_PASS "CMAKE_ANDROID_NDK is '${CMAKE_ANDROID_NDK}'" )
else()
    if( NOT DEFINED CMAKE_ANDROID_NDK )
        message( CHECK_FAIL "CMAKE_ANDROID_NDK was not defined." )
    else()
        message( CHECK_FAIL "CMAKE_ANDROID_NDK '${CMAKE_ANDROID_NDK}' is not a valid directory." )
    endif()
    list(APPEND MISSING_ANDROID_COMPONENTS NDK)
endif()

message(CHECK_START "Finding JAVA home")
# TODO: Document this behaviour....
# org.gradle.java.home=@JAVA_HOME@
find_package(Java 11 REQUIRED)
if ( NOT JAVA_HOME ) # Extract `JAVA_HOME` from parent path of `Java_JAVA_EXECUTABLE`
    cmake_path(GET Java_JAVA_EXECUTABLE PARENT_PATH  JAVA_HOME)
    cmake_path(GET JAVA_HOME PARENT_PATH JAVA_HOME)
endif()    
if( NOT JAVA_HOME )
    message( CHECK_FAIL "JAVA_HOME needs to be defined." )
    list(APPEND MISSING_ANDROID_COMPONENTS JAVA)
else()
    message( CHECK_PASS "JAVA_HOME is ${JAVA_HOME}" )
endif()    

list(POP_BACK CMAKE_MESSAGE_INDENT)
if(MISSING_ANDROID_COMPONENTS)
    message(CHECK_FAIL "Missing component(s): ${MISSING_ANDROID_COMPONENTS}")
else()
    message(CHECK_PASS "All components found")
endif()

# We support AndroidPackaging.cmake usage before `project(...)
# - This allows implicitly setting the Android Toolchain upon inclusion
# TODO: We could still set project but define the Android toolhcain here first.
get_directory_property(hasParent PARENT_DIRECTORY)
if ( NOT hasParent OR PROJECT_IS_TOP_LEVEL)
	project(AndroidPackaging.cmake)
endif()

include(CMake/AndroidPackaging.cmake)

add_subdirectory(Examples EXCLUDE_FROM_ALL)