#include <sound_player.h>
#include <gamepad/gamepad_types.h>
#include <lms/extra/time.h>
#include <SFML/Graphics.hpp>

bool SoundPlayer::initialize() {
    gamepad = datamanager()
                ->readChannel<Gamepad>(this, "GAMEPAD");
    config = getConfig();

    return true;
}

bool SoundPlayer::cycle() {
    Gamepad::axis ls = gamepad->getAxis("LS");
    Gamepad::axis rs = gamepad->getAxis("RS");
    Gamepad::axis lt = gamepad->getAxis("LT");
    Gamepad::axis rt = gamepad->getAxis("RT");
    bool ba = gamepad->buttonPressed("A");
    bool bb = gamepad->buttonPressed("B");
    bool bx = gamepad->buttonPressed("X");
    bool by = gamepad->buttonPressed("Y");


    return true;
}


bool SoundPlayer::deinitialize() {
    return true;
}
