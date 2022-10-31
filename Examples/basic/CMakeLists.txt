if ( NOT DEFINED VERSION_COMMIT)
    set(VERSION_COMMIT 1) # @see https://github.com/BareCpper/Version.cmake
endif()

if(ANDROID)    
    apk_add_executable( AndroidPackaging_Examples_Basic )
else()
    add_executable( AndroidPackaging_Examples_Basic )
endif()

target_link_libraries( AndroidPackaging_Examples_Basic 
    $<$<BOOL:${ANDROID}>:android> # @note libandroid.so
    $<$<BOOL:${ANDROID}>:android::native_app_glue>
    $<$<BOOL:${ANDROID}>:log>
)
                       
target_sources( AndroidPackaging_Examples_Basic
    PRIVATE
        main.cpp
)