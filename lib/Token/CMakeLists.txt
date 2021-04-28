add_library (Token OBJECT
    Token.cpp
    TokenWrapper.cpp
)

set_target_properties(Token PROPERTIES
    COMPILE_FLAGS "-g -std=c++14 -fno-rtti -fPIC"
)
