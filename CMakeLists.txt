cmake_minimum_required(VERSION 3.8)
project(butler)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(gazebo REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
install(
  DIRECTORY launch model
  DESTINATION share/${PROJECT_NAME}
)
include_directories(
  ${GAZEBO_INCLUDE_DIRS}
  include
)
link_directories(${GAZEBO_LIBRARY_DIRS})
add_library(force_plugin SHARED src/force_plugin.cpp)
target_link_libraries(force_plugin ${GAZEBO_LIBRARIES})
install(TARGETS force_plugin
  LIBRARY DESTINATION lib/${PROJECT_NAME}
)


install(
    PROGRAMS
    scripts/order_handler.py
    scripts/simple_navigator.py
    scripts/exception_handler.py
    DESTINATION lib/${PROJECT_NAME}
)

install(
    PROGRAMS
    scripts/butler_manager.py
    DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
