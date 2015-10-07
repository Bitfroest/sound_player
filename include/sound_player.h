#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <lms/datamanager.h>

class SoundPlayer : public lms::Module {
public:
    bool initialize() override;
    bool cycle() override;
    bool deinitialize() override;
private:
    const Gamepad *gamepad;
    const lms::type::ModuleConfig *config;
};

#endif /* SOUND_PLAYER_H */
