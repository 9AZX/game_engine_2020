set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library PARENT_SCOPE)
set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library)
set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include")

file(
    GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${HEADER_DIR}/*.hpp"
)

add_library(${PROJECT_SOURCES_LIBRARY} STATIC
    Engine.cpp
    ${HEADER_LIST}
)

find_package(Vulkan REQUIRED)

target_include_directories(
    ${PROJECT_SOURCES_LIBRARY} PUBLIC ${HEADER_DIR}
)
target_link_libraries(
    ${PROJECT_SOURCES_LIBRARY} PRIVATE Vulkan::Vulkan
)

enable_warnings(${PROJECT_SOURCES_LIBRARY})
