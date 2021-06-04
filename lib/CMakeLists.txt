add_subdirectory(Token)
add_subdirectory(Benchmark)
add_subdirectory(Worklist)
add_subdirectory(Utils)
add_subdirectory(InstInfo)
add_subdirectory(InstModel)

# TODO: Write this in multiple lines
add_library (Spatial SHARED $<TARGET_OBJECTS:Token>  $<TARGET_OBJECTS:Benchmark> $<TARGET_OBJECTS:Worklist> $<TARGET_OBJECTS:Utils> $<TARGET_OBJECTS:InstInfo> $<TARGET_OBJECTS:InstModel> $<TARGET_OBJECTS:GenericInstModel>)

set_target_properties(Spatial PROPERTIES
    SOVERSION 0
)

include(GNUInstallDirs)
install(TARGETS Spatial LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
