# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WorkSheet_5_Exercise_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WorkSheet_5_Exercise_autogen.dir\\ParseCache.txt"
  "WorkSheet_5_Exercise_autogen"
  )
endif()
