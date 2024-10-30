# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/math_inter_wrapper_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/math_inter_wrapper_autogen.dir/ParseCache.txt"
  "math_inter_wrapper_autogen"
  )
endif()
