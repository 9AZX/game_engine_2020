set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library PARENT_SCOPE)
set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library)
set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include")
set(HEADER_RESOURCE "${PROJECT_SOURCE_DIR}/resourcesHID")

file(
    GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${HEADER_DIR}/*.hpp"
    "${HEADER_RESOURCE}/*.h"
)

add_library(${PROJECT_SOURCES_LIBRARY} STATIC
    Core.cpp
    EngineWindow.cpp
    HID.cpp
    ${HEADER_LIST}
 )

find_package(Vulkan REQUIRED)
find_package(portaudio REQUIRED)

target_include_directories(
    ${PROJECT_SOURCES_LIBRARY} PUBLIC ${HEADER_DIR}
    ${PROJECT_SOURCES_LIBRARY} PUBLIC ${HEADER_RESOURCE}
)
target_link_libraries(
    ${PROJECT_SOURCES_LIBRARY} PRIVATE Vulkan::Vulkan portaudio
)

enable_warnings(${PROJECT_SOURCES_LIBRARY})
