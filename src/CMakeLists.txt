include_directories(../include)

aux_source_directory(. SRCDIR)
aux_source_directory(../ MAIN)
#aux_source_directory(ETISrc/Times SRCDIR)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(2fa ${SRCDIR} ${MAIN})
