file(GLOB TestSrc . *.cpp)

foreach(TestFile ${TestSrc})
  get_filename_component(TestFileName ${TestFile} NAME_WE)
  add_executable(${TestFileName} ${TestFile} ${Source})
endforeach()
