qt4_wrap_cpp(MOC_SOURCES smilestest.h)
add_executable(smilestest smilestest.cpp ${MOC_SOURCES})
target_link_libraries(smilestest chemkit chemkit-io ${QT_LIBRARIES})
add_chemkit_test(plugins.Smiles smilestest)
