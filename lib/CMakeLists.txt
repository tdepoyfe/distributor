add_library(distributor_lib distributor.cpp)

target_include_directories(distributor_lib PUBLIC "${PROJECT_SOURCE_DIR}/headers")
