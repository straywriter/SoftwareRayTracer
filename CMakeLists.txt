cmake_minimum_required(VERSION 3.0)

project(SoftwareRayTracing)

find_package(Doxygen)

if (DOXYGEN_FOUND)

endif (DOXYGEN_FOUND)

add_subdirectory(./Geometry)
add_subdirectory(./Math)
add_subdirectory(./Render)
add_subdirectory(./External)
set(Include ${Math} ${Geometry} ${Render} ${External}) 

# message(STATUS  " ${ExternalIncludeDir}")

set(IncludeDir ${MathIncludeDir} ${GeometryIncludeDir} ${RenderIncludeDir} ${ExternalIncludeDir})
# set(Src ${MathSrc} ${GeometrySrc} ${RenderSrc})

set(Source ${Include}  CACHE STRING "" FORCE)

# message(${Math})

include_directories(${IncludeDir})


add_subdirectory(./Demo/Base)

# other demo 


# doc
add_subdirectory(./Doc)
