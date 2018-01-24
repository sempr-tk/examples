cmake_minimum_required(VERSION 2.8)

project(sempr_example_extension)

# a project that only uses the sempr core library
add_subdirectory(simple_use)

# a project that extends the sempr core library with a new entity
add_subdirectory(new_entity)
