# External 

file(GLOB ExternalInclude ./Include/stb/*.h)

file(GLOB ExternalSrc ./Src/*.cpp)

set(ExternalIncludeDir ${CMAKE_CURRENT_SOURCE_DIR}/Include CACHE STRING "" FORCE ) 
set(External ${ExternalInclude} ${ExternalSrc} CACHE STRING "" FORCE) 