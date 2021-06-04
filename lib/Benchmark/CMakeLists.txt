add_library (Benchmark OBJECT
    PointsToBenchmark.cpp
    PTABenchmark.cpp
)

set_target_properties(Benchmark PROPERTIES
    COMPILE_FLAGS "-g -std=c++14 -fno-rtti -fPIC"
)
