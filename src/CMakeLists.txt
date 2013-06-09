set(CloakedOctoGameBoyEmulator_SRCS
    main.cpp
)

# create exe
add_executable(CloakedOctoGameBoyEmulator ${CloakedOctoGameBoyEmulator_SRCS})

# link lib with Qt libs - QT_LIBRARIES takes care of linking ONLY with the needed libraries
# and their dependencies. This is fundamental in case the resulting binary is static.
target_link_libraries(CloakedOctoGameBoyEmulator ${QT_LIBRARIES})