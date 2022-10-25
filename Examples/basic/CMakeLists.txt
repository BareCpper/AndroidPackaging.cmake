# find_package(AndroidPackaging.cmake) # NOTE: Not required as using in-repo!

if(ANDROID)    
    apk_add_executable( AndroidPackaging_Examples_Basic )
    #apk_add_package( openxr-sandbox )
    #apk_add_ndk_activity( openxr-sandbox )
else()
    add_executable( AndroidPackaging_Examples_Basic )
endif()

target_compile_definitions(AndroidPackaging_Examples_Basic
    PRIVATE    
        $<$<BOOL:${ANDROID}>:PLATFORM_ANDROID>
        $<$<BOOL:${WIN32}>:PLATFORM_WIN32> 
)

# Set property for my_target only
set_target_properties( AndroidPackaging_Examples_Basic 
    PROPERTIES 
        RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time"
)

target_compile_features( AndroidPackaging_Examples_Basic
    PUBLIC 
        cxx_std_20 )
        
target_link_libraries( AndroidPackaging_Examples_Basic 
    $<$<BOOL:${ANDROID}>:android> # @note libandroid.so
    $<$<BOOL:${ANDROID}>:android::native_app_glue>
    $<$<BOOL:${ANDROID}>:log>
)
                       
target_sources( AndroidPackaging_Examples_Basic
    PRIVATE
        main.cpp
)