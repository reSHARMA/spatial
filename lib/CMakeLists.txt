add_library (Spatial SHARED
    Token/Alias.cpp
    Token/AliasToken.cpp
    Benchmark/Benchmark.cpp
    Worklist/Worklist.cpp
    Utils/CFGUtils.cpp
    Utils/ReplaceIRVar.cpp
)

set_target_properties(Spatial PROPERTIES
    SOVERSION 0
    COMPILE_FLAGS "-g -std=c++14 -fno-rtti"
)

include(GNUInstallDirs)
install(TARGETS Spatial LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
