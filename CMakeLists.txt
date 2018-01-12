project(libsofa)
cmake_minimum_required(VERSION 2.8)

# 20171128 QBE; redoing the CMakeLists.txt so that it fits our build system.
# Currently this works for MinGW64 and should be adapted to Linux

set(libroot "${external_dependencies_dir}/dependencies/lib/${CMAKE_SYSTEM_NAME}/${BITS}/Release")

set(hdf5root "${libroot}/hdf5")
find_library(dep_libhdf5_lib libhdf5 PATHS ${hdf5root} NO_DEFAULT_PATH)
find_library(dep_libhdf5_hl_lib libhdf5_hl PATHS ${hdf5root} NO_DEFAULT_PATH)
find_library(dep_libhdf5_tools_lib libhdf5_tools PATHS ${hdf5root} NO_DEFAULT_PATH)

set(netcdfroot "${libroot}/netcdf")
find_library(dep_netcdf_lib netcdf PATHS ${netcdfroot} NO_DEFAULT_PATH)
find_library(dep_netcdf_cxx_lib netcdf-cxx4 PATHS ${netcdfroot} NO_DEFAULT_PATH)

load_dependencies(zlibstatic)

option(build_sofa_executables "Build sofainfo and sofamisc?" OFF)

include_directories(${external_dependencies_dir}/dependencies/include)

file(
	GLOB_RECURSE
	source_files
	libsofa/src/*.cpp
	libsofa/src/*.h
)
set(srcroot ${CMAKE_CURRENT_SOURCE_DIR}/libsofa/src)
#message(FATAL_ERROR ${source_files})
list(REMOVE_ITEM source_files
	${srcroot}/json2sofa.cpp ${srcroot}/sofa2json.cpp ${srcroot}/sofaexamples.cpp
	${srcroot}/sofainfo.cpp ${srcroot}/sofamisc.cpp)

add_library(sofa STATIC ${source_files})

# 20171128 QBE; in our build HDF5 and netcdf are built without sz and curl support
if(build_sofa_executables)
	set(libs
		${dep_netcdf_lib} ${dep_netcdf_cxx_lib} ${dep_hdf5_lib} ${dep_hdf5_hl_lib}
		${dep_zlibstatic_lib_static})

	add_executable(sofainfo libsofa/src/sofainfo.cpp)
	target_link_libraries(sofainfo sofa ${libs})

	add_executable(sofamisc libsofa/src/sofamisc.cpp)
	target_link_libraries(sofamisc sofa ${libs})
endif()
