add_executable(test_executable
  test_example.cpp
)

target_link_libraries(test_executable
  PRIVATE
  pipeline_project
  GTest::GTest
  GTest::Main
)

include(GoogleTest)
gtest_discover_tests(test_executable)
