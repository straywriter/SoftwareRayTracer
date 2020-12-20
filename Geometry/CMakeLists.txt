# Geometry

file(GLOB GeometryInclude ./Include/*.h)

file(GLOB GeometrySrc ./Src/*.cpp)

set(GeometryIncludeDir ${CMAKE_CURRENT_SOURCE_DIR}/Include CACHE STRING "" FORCE ) 
set(Geometry ${GeometryInclude} ${GeometrySrc} CACHE STRING "" FORCE) 