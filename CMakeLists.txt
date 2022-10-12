cmake_minimum_required(VERSION 3.10)

# set the project name
project(libupnp_example)

# add the executable
add_executable(libupnp_example main.c)

# Includes from upnp lib that should be cloned next to this project (Windows)
target_include_directories(libupnp_example PUBLIC "../pupnp/upnp/inc")
target_include_directories(libupnp_example PUBLIC "../pupnp/ixml/inc")

# Finding libupnp to link to in Windows and Linux
find_library(LIBUPNP_PATH NAMES libupnp.lib libupnp.so PATHS /usr/local/lib .)
target_link_libraries(libupnp_example PUBLIC ${LIBUPNP_PATH} )
