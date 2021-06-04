add_library (Utils OBJECT
    CFGUtils.cpp
    ReplaceIRVar.cpp
)

set_target_properties(Utils PROPERTIES
    COMPILE_FLAGS "-g -std=c++14 -fno-rtti -fPIC"
)
