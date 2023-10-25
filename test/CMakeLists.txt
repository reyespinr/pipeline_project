add_executable(test_executable
  # test_example.cpp
  test_alu.cpp
  test_memory.cpp
  test_register_file.cpp
  test_immediate.cpp
)

target_link_libraries(test_executable
  PRIVATE
  pipeline_project
  GTest::GTest
  GTest::Main
)

include(GoogleTest)
gtest_discover_tests(test_executable)
