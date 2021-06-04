add_library (Worklist OBJECT
    Worklist.cpp
)

set_target_properties(Worklist PROPERTIES
    COMPILE_FLAGS "-g -std=c++14 -fno-rtti -fPIC"
)
