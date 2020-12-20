# Render

file(GLOB_RECURSE RenderInclude ./Include/*.h)

file(GLOB_RECURSE   RenderSrc ./Src/*.cpp)

set(RenderIncludeDir ${CMAKE_CURRENT_SOURCE_DIR}/Include CACHE STRING "" FORCE) 
set(Render ${RenderInclude} ${RenderSrc} CACHE STRING "" FORCE)