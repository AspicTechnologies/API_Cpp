project(libsofa)
cmake_minimum_required(VERSION 2.8)

# 20171128 QBE; redoing the CMakeLists.txt so that it fits our build system.
# Currently this works for MinGW64 and should be adapted to Linux

option(build_sofa_executables "Build sofainfo and sofamisc?" OFF)

include_directories(
	${CMAKE_BINARY_DIR}/hdf5/include
	${CMAKE_BINARY_DIR}/netcdf/include)

set(srcroot ${CMAKE_CURRENT_SOURCE_DIR}/libsofa/src)

file(
	GLOB_RECURSE
	source_files
	${srcroot}/*.cpp
)

file(
	GLOB_RECURSE
	headers
	${srcroot}/*.h
)

list(REMOVE_ITEM source_files
	${srcroot}/json2sofa.cpp ${srcroot}/sofa2json.cpp ${srcroot}/sofaexamples.cpp
	${srcroot}/sofainfo.cpp ${srcroot}/sofamisc.cpp)

add_library(sofa STATIC ${source_files} ${headers})

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	set(BITS 64b)
else()
	set(BITS 32b)
endif()

install(FILES ${headers} DESTINATION ${export_lib_path}/include/src)
install(TARGETS sofa DESTINATION ${export_lib_path}/lib/${CMAKE_SYSTEM_NAME}/${BITS}/${CMAKE_BUILD_TYPE}/sofa)

# 20171128 QBE; in our build HDF5 and netcdf are built without sz and curl support
if(build_sofa_executables)
	set(hdf5root "${CMAKE_BINARY_DIR}/hdf5/lib")
	find_library(dep_libhdf5_lib libhdf5 PATHS ${hdf5root} NO_DEFAULT_PATH)
	find_library(dep_libhdf5_hl_lib libhdf5_hl PATHS ${hdf5root} NO_DEFAULT_PATH)

	set(netcdfroot "${CMAKE_BINARY_DIR}/netcdf/lib")
	find_library(dep_netcdf_lib netcdf PATHS ${netcdfroot} NO_DEFAULT_PATH)
	find_library(dep_netcdf_cxx_lib netcdf-cxx4 PATHS ${netcdfroot} NO_DEFAULT_PATH)

	set(libs
		${dep_netcdf_lib} ${dep_netcdf_cxx_lib} ${dep_libhdf5_lib} ${dep_libhdf5_hl_lib}
		zlibstatic)

	add_executable(sofainfo libsofa/src/sofainfo.cpp)
	target_link_libraries(sofainfo sofa ${libs})

	add_executable(sofamisc libsofa/src/sofamisc.cpp)
	target_link_libraries(sofamisc sofa ${libs})
endif()
