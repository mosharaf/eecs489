find_package(Protobuf CONFIG REQUIRED)

file(GLOB PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")

add_library(
        proto
        ${PROTO_FILES}
)

target_link_libraries(
        proto
        PUBLIC
        protobuf::libprotobuf
)

protobuf_generate(TARGET proto LANGUAGE cpp APPEND_PATH)