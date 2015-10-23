#include <sound_player.h>
#include <lms/extra/time.h>
#include <SFML/Audio.hpp>
#include <lms/framework.h>

bool SoundPlayer::initialize() {

    config = getConfig();
    std::vector<std::string> motorsounds = config->getArray<std::string>("motorsound");
    std::vector<std::string> rpm = config->getArray<std::string>("rpm");

    buffersize = motorsounds.size();
    sounds.resize(buffersize);
    buffers.resize(buffersize);
    loudness.resize(buffersize);


    for(int i = 0; i < buffersize;i++){
        SoundBufferContainer container;
        if(!buffers.at(i).loadFromFile(lms::Framework::configsDirectory + "/" +motorsounds[i]))
            return false;
        container.buffer = buffers.at(i);
        container.sound.setBuffer(buffers.at(i));
        container.sound.setVolume(100);
        container.sound.setLoop(true);
        container.sound.setPitch(1.0);
        container.sound.play();
        container.name = motorsounds[i];
        container.rpm = atoi(rpm[i].c_str());
        sounds.at(i) = container;
        sounds.at(i).sound.setVolume(0);
        sounds.at(i).sound.play();

    }
    return true;
}

bool SoundPlayer::cycle() {

    for(int i = 0; i < sounds.size(); i++) {
        logger.info("cycle") <<  sounds.at(i).name << " | status: " << sounds.at(i).sound.getStatus() << " | volume: " << sounds.at(i).sound.getVolume();
    }
    k++;


    for(int i = 0; i< buffersize;i++){
        float factor =  (  float (k) / (sounds.at(i).rpm * 60));
        logger.info("cycle") << factor;
        if (factor <=0 && factor <= 0.9){
            loudness.at(i) = 0;
            sounds.at(i).sound.setVolume(0);
        } else if (factor > 0.9 && factor < 1 && loudness.at(i) < 100){
            if(cycleCounter() % 120 == 0)
                loudness.at(i)++;
            sounds.at(i).sound.setPitch(factor);
            sounds.at(i).sound.setVolume(loudness.at(i));
        } else if (factor >= 1 && factor <= 1.8){
            sounds.at(i).sound.setPitch(factor);
            sounds.at(i).sound.setVolume(100);
            loudness.at(i) = 100;
        } else if(factor >=1.8 && factor <= 2 && loudness.at(i) > 0){
            if(cycleCounter() % 50 == 0)
                loudness.at(i)--;
            sounds.at(i).sound.setPitch(factor);
            sounds.at(i).sound.setVolume(loudness.at(i));
        }else{
            sounds.at(i).sound.setVolume(0);
        }
    }

    return true;
}


bool SoundPlayer::deinitialize() {
    return true;
}
