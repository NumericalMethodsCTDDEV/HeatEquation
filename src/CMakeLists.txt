include_directories(utils schemes)

add_subdirectory(schemes)
add_subdirectory(ui)
add_subdirectory(utils)

add_executable(HeatEquation main.cpp)
target_link_libraries(HeatEquation UI Solver)
