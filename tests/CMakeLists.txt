macro(add_ncf_test_sample _SAMPLE_NAME _SAMPLE_CTG)
    add_executable(${_SAMPLE_NAME}_${_SAMPLE_CTG}_sample
        ${_SAMPLE_CTG}/${_SAMPLE_NAME}_${_SAMPLE_CTG}_sample.cpp)
    target_link_libraries(${_SAMPLE_NAME}_${_SAMPLE_CTG}_sample
        ${NCF_LIBRARIES}
        ncurses
        panel
        menu)
endmacro()

include_directories(${NCF_INCLUDE_DIRS})

add_ncf_test_sample(single menu)
add_ncf_test_sample(triple_in_row menu)
