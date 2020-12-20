# Math 


file(GLOB MathInclude ./Include/*.h)

file(GLOB MathSrc ./Src/*.cpp)
set(MathIncludeDir ${CMAKE_CURRENT_SOURCE_DIR}/Include CACHE STRING "" FORCE)
set(Math ${MathInclude} ${MathSrc} CACHE STRING "" FORCE) 