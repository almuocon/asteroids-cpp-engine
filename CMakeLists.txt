cmake_minimum_required(VERSION 3.10.0)
project(CMakeLists.txt VERSION 0.1.0 LANGUAGES C CXX)

add_executable(asteroides asteroides.cpp)
add_executable(rebote rebote.cpp)
add_executable(rebotes rebotes.cpp)
add_executable(testparticula testparticula.cpp)
add_executable(testlista testlista.cpp)
add_executable(testsobrecarga testsobrecarga.cpp)

include_directories(../bigs-linux/bigs/include)

add_library(asteroid Vector2D.cpp particula.cpp matematicas.cpp listaparticulas.cpp clasificacion.cpp)
target_link_libraries(asteroid bigs ${ALLEGRO_LIBRARIES})
target_link_libraries(asteroides asteroid)
target_link_libraries(rebote asteroid)
target_link_libraries(rebotes asteroid)
target_link_libraries(testlista asteroid)
target_link_libraries(testsobrecarga asteroid)
target_link_libraries(testparticula asteroid)

include(../bigs-linux/bigs/bigs.cmake)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CPACK_SOURCE_GENERATOR ZIP)
include(CPack)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})