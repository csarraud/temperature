cmake_minimum_required(VERSION 3.10)
project (temperature)

# Compile the C code to executable
add_executable(temperature ${CMAKE_CURRENT_SOURCE_DIR}/src/temperature.c)

# Install executable to /usr/bin
install(TARGETS temperature RUNTIME DESTINATION /usr/bin)

# Install service
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/temperature.service DESTINATION /lib/systemd/system/)
