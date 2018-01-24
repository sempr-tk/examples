set(CMAKE_CXX_FLAGS "-std=c++11")
add_definitions(-Wall -Wno-unknown-pragmas)

find_package(PkgConfig REQUIRED)

# find & use sempr
pkg_check_modules(SEMPR REQUIRED sempr-core)
include_directories(${SEMPR_INCLUDE_DIRS})
link_directories(${SEMPR_LIBRARY_DIRS})
add_definitions(${SEMPR_CFLAGS_OTHER})  # for the database-flag (sqlite, postgresql, ...)

# find & use ODB
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(ODB REQUIRED)
include(${ODB_USE_FILE})
include_directories(${ODB_INCLUDE_DIRS}) # these are already added through sempr-cores dependencies
include_directories(${ODB_COMPILE_OUTPUT_DIR}) # the location of generated database code


# what database backend has been used by the sempr-core library?
# --> found this function here: https://bloerg.net/2015/03/06/pkg-config-variables-in-cmake.html
# used to extract the "database"-variable from sempr-cores pkgconfig file, to use it in odb_compile
function(pkg_check_variable _pkg _name)
    string(TOUPPER ${_pkg} _pkg_upper)
    string(TOUPPER ${_name} _name_upper)
    string(REPLACE "-" "_" _pkg_upper ${_pkg_upper})
    string(REPLACE "-" "_" _name_upper ${_name_upper})
    set(_output_name "${_pkg_upper}_${_name_upper}")

    execute_process(COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=${_name} ${_pkg}
                    OUTPUT_VARIABLE _pkg_result
                    OUTPUT_STRIP_TRAILING_WHITESPACE)

    set("${_output_name}" "${_pkg_result}" CACHE STRING "pkg-config variable ${_name} of ${_pkg}")
endfunction()

pkg_check_variable(sempr-core database)
message("database used by sempr-core: ${SEMPR_CORE_DATABASE}")


# call the odb-compiler to generate code from our ""#pragma db"-annotated header files
set(ODB_HDR SpecialEntity.hpp)
odb_compile(
    ODB_GENERATED_SRC
    FILES ${ODB_HDR}
    INCLUDE ${SEMPR_INCLUDE_DIRS}
    DB ${SEMPR_CORE_DATABASE}
    GENERATE_QUERY GENERATE_SESSION GENERATE_SCHEMA
    STANDARD c++11
)

# compile everything into a library
add_library(sempr_example_extension SHARED SpecialEntity.cpp ${ODB_GENERATED_SRC})
target_link_libraries(sempr_example_extension ${SEMPR_LIBRARIES}) # ${ODB_LIBRARIES})

# At this point you should think about installation routines and creating a pkg-config file.
# Maybe have a look at sempr-tk/sempr and how it's done there.
# Instead, lets just use the newly defined entity right now:
add_executable(test_extension main.cpp)
target_link_libraries(test_extension sempr_example_extension ${SEMPR_LIBRARIES})
