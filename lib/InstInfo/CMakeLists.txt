add_library (InstInfo OBJECT
    InstInfo.cpp
)

set_target_properties(InstInfo PROPERTIES
    COMPILE_FLAGS "-g -std=c++14 -fno-rtti -fPIC"
)
