#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <lms/datamanager.h>
#include <lms/module.h>
#include <lms/type/module_config.h>
#include <SFML/Audio.hpp>

class SoundPlayer : public lms::Module {
public:
    bool initialize() override;
    bool cycle() override;
    bool deinitialize() override;
    struct SoundBufferContainer {
        sf::SoundBuffer buffer;
        sf::Sound sound;
        std::string name;
        int rpm;
    };
private:
    const lms::type::ModuleConfig *config;
    std::vector<SoundBufferContainer> sounds;
    std::vector<sf::SoundBuffer> buffers;
    float k = 0;
    int buffersize;
    std::vector<int> loudness;
};

#endif /* SOUND_PLAYER_H */
