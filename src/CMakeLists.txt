cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 20)
add_executable(search_engine 
                            main.cpp 
                            ConverterJSON.cpp 
                            InvertedIndex.cpp 
                            SearchServer.cpp 
                            ${HEADERS}/ConverterJSON.h 
                            ${HEADERS}/InvertedIndex.h 
                            ${HEADERS}/SearchServer.h)

include(FetchContent)

FetchContent_Declare(json GIT_REPOSITORY https://github.com/nlohmann/json/ GIT TAG v3.11.3)
FetchContent_MakeAvailable(json)
target_link_libraries(search_engine PUBLIC nlohmann_json::nlohmann_json)

target_include_directories(search_engine PUBLIC ${HEADERS})
