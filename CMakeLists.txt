cmake_minimum_required (VERSION 2.8)

project (cereal_demo)

set(SOURCE "./cereal_demo/main.cpp")
set(CEREAL_LIBRARY "./reference/cereal/include/")

include_directories(${CEREAL_LIBRARY})

add_executable(cereal_demo ${SOURCE})