set ( SOURCES
    "src/sound_player.cpp"
    "src/interface.cpp"
)

set (HEADERS
    "include/sound_player.h"
)

include_directories("include")

add_library ( sound_player MODULE ${SOURCES} ${HEADERS})
target_link_libraries(sound_player PRIVATE lmscore)
