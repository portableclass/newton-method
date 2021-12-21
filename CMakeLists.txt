cmake_minimum_required(VERSION 3.20)

project(newton-method VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

string(TIMESTAMP BUILD_DATE "%Y%m%d")
string(TIMESTAMP BUILD_TIME "%H%M%S")

configure_file(configure/config.txt resources/config.txt)

add_executable(
        newton-method
        src/main.cpp
        src/DataVector.cpp
        src/Equation.cpp
)

add_custom_command(
        TARGET newton-method POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:newton-method>/resources
)

enable_testing()

add_test(NAME OutputTest COMMAND newton-method)
set_tests_properties(
        OutputTest
        PROPERTIES PASS_REGULAR_EXPRESSION
        "resources output
Iteration 1
x_new = 4.476088245737467e+01
delta = 4.474971059529783e+01

Iteration 2
x_new = 2.239161169657246e+01
delta = 2.236927076080221e+01

Iteration 3
x_new = 1.121813563886922e+01
delta = 1.117347605770325e+01

Iteration 4
x_new = 5.653638505339631e+00
delta = 5.564497133529584e+00

Iteration 5
x_new = 2.915257874900043e+00
delta = 2.738380630439588e+00

Iteration 6
x_new = 1.629140351347546e+00
delta = 1.286117523552497e+00

Iteration 7
x_new = 1.121480503925372e+00
delta = 5.076598474221747e-01

Iteration 8
x_new = 1.006579478101629e+00
delta = 1.149010258237424e-01

Iteration 9
x_new = 1.000021503285648e+00
delta = 6.557974815981416e-03

Iteration 10
x_new = 1.000000000231191e+00
delta = 2.150305445725031e-05

Iteration 11
x_new = 1.000000000000000e+00
delta = 2.311906222018933e-10

Iteration 12
x_new = 1.000000000000000e+00
delta = 0.000000000000000e+00

Iteration 1
x_new = 4.476088245736047e+01
delta = 4.474971059523369e+01

Iteration 2
x_new = 2.239161169656612e+01
delta = 2.236927076079434e+01

Iteration 3
x_new = 1.121813563886757e+01
delta = 1.117347605769855e+01

Iteration 4
x_new = 5.653638505338777e+00
delta = 5.564497133528797e+00

Iteration 5
x_new = 2.915257874899551e+00
delta = 2.738380630439226e+00

Iteration 6
x_new = 1.629140351347291e+00
delta = 1.286117523552260e+00

Iteration 7
x_new = 1.121480503925292e+00
delta = 5.076598474219995e-01

Iteration 8
x_new = 1.006579478101621e+00
delta = 1.149010258236709e-01

Iteration 9
x_new = 1.000021503285648e+00
delta = 6.557974815972756e-03

Iteration 10
x_new = 1.000000000231191e+00
delta = 2.150305445725031e-05

Iteration 11
x_new = 1.000000000000000e+00
delta = 2.311906222018933e-10

Iteration 12
x_new = 1.000000000000000e+00
delta = 0.000000000000000e+00


Newton's method :
		root is 1.000000000000000e+00
		iteration number is 13


finite Newton's method :
		root is 1.000000000000000e+00
		iteration number is 13

||x_Newton - x_Newton.f|| = 0.0000000000000000000000000000000e+00"
)

add_test(NAME VersionTest COMMAND newton-method -v)
set_tests_properties(
        VersionTest
        PROPERTIES PASS_REGULAR_EXPRESSION "Version: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)