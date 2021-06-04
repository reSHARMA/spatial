add_library (GenericInstModel OBJECT
    GenericInstModel.cpp
)

set_target_properties(GenericInstModel PROPERTIES
    COMPILE_FLAGS "-g -std=c++14 -fno-rtti -fPIC"
)
