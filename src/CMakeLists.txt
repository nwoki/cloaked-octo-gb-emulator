set(CloakedOctoGameBoyEmulator_SRCS
    cartridge.cpp
    core.cpp
    main.cpp
)

set(CloakedOctoGameBoyEmulator_HDRS
    cartridge.h
    core.h
)

qt4_wrap_cpp(CloakedOctoGameBoyEmulator_MOC_HDRS ${CloakedOctoGameBoyEmulator_HDRS})

# create exe
add_executable(CloakedOctoGameBoyEmulator ${CloakedOctoGameBoyEmulator_SRCS} ${CloakedOctoGameBoyEmulator_MOC_HDRS})

# link lib with Qt libs - QT_LIBRARIES takes care of linking ONLY with the needed libraries
# and their dependencies. This is fundamental in case the resulting binary is static.
target_link_libraries(CloakedOctoGameBoyEmulator ${QT_LIBRARIES})