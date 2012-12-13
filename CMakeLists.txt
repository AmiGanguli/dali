cmake_minimum_required (VERSION 2.6)

project (dali)
set (dali_VERSION_MAJOR 0)
set (dali_VERSION_MINOR 0)
set (LOG_LEVEL 9)
set (CMAKE_CXX_FLAGS -g)

add_definitions(-DBOOST_PARAMETER_MAX_ARITY=10)

include_directories(
	${PROJECT_SOURCE_DIR}/lib
	${PROJECT_BINARY_DIR}
)

add_executable(hello
	src/hello.C
)

add_executable(path
	src/path.C
	lib/Path.C
	lib/Constant.C
)

#target_link_libraries(hello
#)

