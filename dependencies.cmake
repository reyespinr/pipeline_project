# find_package(library_name REQUIRED)

if(pipeline_project_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
    find_package(GTest REQUIRED)
endif()