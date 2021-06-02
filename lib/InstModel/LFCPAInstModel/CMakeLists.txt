add_library (LFCPAInstModel OBJECT
    LFCPAInstModel.cpp
)

set_target_properties(LFCPAInstModel PROPERTIES
    COMPILE_FLAGS "-g -std=c++14 -fno-rtti -fPIC"
)
