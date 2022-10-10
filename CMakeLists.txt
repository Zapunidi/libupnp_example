cmake_minimum_required(VERSION 3.10)

# set the project name
project(libupnp_example)

# add the executable
add_executable(libupnp_example main.c)

# Includes from upnp lib that should be cloned next to this project
target_include_directories(libupnp_example PUBLIC "../pupnp/upnp/inc")
target_include_directories(libupnp_example PUBLIC "../pupnp/ixml/inc")

target_link_libraries(libupnp_example ../libupnp)