# message(STATUS "src/time_processing This is BINARY dir " ${PROJECT_BINARY_DIR})
# message(STATUS "src/time_processing This is SOURCE dir " ${PROJECT_SOURCE_DIR})

include_directories(.)
# add_compile_options(-I/opt/homebrew/Cellar/nlohmann-json/3.9.1_1/include -std=c++11)

aux_source_directory(. INCROOT)
aux_source_directory(../ MAIN)
aux_source_directory(../src SRCDIR)
#aux_source_directory(ETISrc/Times SRCDIR)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(2fa ${INCROOT} ${MAIN} ${NLOMAIN})

