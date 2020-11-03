set(EXE_NAME ${PROJECT_NAME})

add_executable(${EXE_NAME} main.cpp)

find_package(portaudio REQUIRED)
find_package(libsndfile REQUIRED)

target_link_libraries(${EXE_NAME} ${PROJECT_SOURCES_LIBRARY} portaudio libsndfile)
target_include_directories(
    ${EXE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
)

enable_warnings(${EXE_NAME})
