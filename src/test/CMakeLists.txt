
# Generic tests, that only require libesdm
file(GLOB TESTFILES "${CMAKE_CURRENT_SOURCE_DIR}" "*.c")
foreach(TESTFILE ${TESTFILES})
  if(IS_DIRECTORY ${TESTFILE} )
    #message(STATUS ${TESTFILE})
  else()
    get_filename_component(TESTNAME_C ${TESTFILE} NAME)
    STRING(REGEX REPLACE ".c$" "" TESTNAME ${TESTNAME_C})


	# Build, link and add as test
    add_executable(${TESTNAME} ${TESTFILE})
	target_link_libraries(${TESTNAME} esdm)
	include_directories(${CMAKE_SOURCE_DIR}/include/ ${CMAKE_BINARY_DIR} ${GLIB_INCLUDE_DIRS} ${Jansson_INCLUDE_DIRS})

    add_test(${TESTNAME} ./${TESTNAME})
  endif()
endforeach()




# A special test with additional requirements
#add_executable(${TESTNAME} ${TESTFILE})
#target_link_libraries(${TESTNAME} "${PROJECT_BINARY_DIR}/libesdm.so" "libspecial.so")
#add_test(${TESTNAME} ./${TESTNAME})
