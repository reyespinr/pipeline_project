add_executable(test_executable
  # test_example.cpp
  test_alu.cpp
  test_memory.cpp
  test_register_file.cpp
  test_immediate.cpp
  test_control_flow_unit.cpp
  test_control_unit.cpp
  test_datapath.cpp
  test_simulator.cpp
  test_demo.cpp
)

target_link_libraries(test_executable
  PRIVATE
  pipeline_project
  GTest::GTest
  GTest::Main
)

include(GoogleTest)
gtest_discover_tests(test_executable)
