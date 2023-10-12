add_library(pipeline_project_library
    example.cpp
)

add_library(pipeline_project ALIAS pipeline_project_library)

target_include_directories(pipeline_project_library
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

# target_link_libraries(pipeline_project_library
# PUBLIC
# library::library
# )