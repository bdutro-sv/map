project(Logall_test)

add_executable(LogAll_test LogAll_test.cpp)

include(../TestingMacros.cmake)

sparta_test(LogAll_test LogAll_test_RUN)
sparta_copy(LogAll_test everything.log.basic.EXPECTED)
