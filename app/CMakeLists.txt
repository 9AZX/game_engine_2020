set(EXE_NAME ${PROJECT_NAME})

add_executable(
    ${EXE_NAME}
    main.cpp
)

target_link_libraries(${EXE_NAME} ${PROJECT_SOURCES_LIBRARY})

enable_warnings(${EXE_NAME})
