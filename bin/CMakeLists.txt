add_executable(distributor main.cpp)

target_include_directories(distributor PUBLIC "${PROJECT_SOURCE_DIR}/headers")

target_link_libraries(distributor PUBLIC pthread distributor_lib)
