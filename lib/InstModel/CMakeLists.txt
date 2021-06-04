add_library (InstModel OBJECT
    InstModel.cpp
)

set_target_properties(InstModel PROPERTIES
    COMPILE_FLAGS "-g -std=c++14 -fno-rtti -fPIC"
)

add_subdirectory(GenericInstModel)
