//
// Created by grzegorz on 21.09.18.
//

#include "sound.h"

#include "sound_manager.h"
#include <iostream>

namespace engine {
    namespace audio {

        void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
        void LoopOnFinish(ga_Handle* in_handle, void* in_context);

        Sound::Sound(const std::string& name, const std::string& filename)
                : m_Name(name), m_FileName(filename), quit(0), m_Playing(false), m_Position(0){

            std::vector<std::string> file = split(filename, '.');
            if(file.size() < 2){
                std::cout << "[Sound] Invalid file name " << filename << std::endl;
                return;
            }

            m_Sound = gau_load_sound_file(filename.c_str(), file.back().c_str());

            if(!m_Sound) std::cout << "[Sound] Could not load file: " << filename << std::endl;
        }

        Sound::~Sound(){
            ga_sound_release(m_Sound);
        }

        void Sound::play(){

            m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &setFlagAndDestroyOnFinish, &quit, NULL);
            ga_handle_play(m_Handle);
            m_Playing = true;
            m_Handle->Sound = this;

            if(m_Position){
                ga_handle_seek(m_Handle, m_Position);
                m_Position = 0;
            }

        }

        void Sound::resume(){

            if(!m_Playing) return;
            ga_handle_play(m_Handle);
            m_Playing = true;
        }

        void Sound::stop(){
            if(m_Playing){
                ga_handle_stop(m_Handle);
                m_Playing = false;
                m_Position = 0;
            }else{
                std::cout << "[Sound] Cannot set stop! Sound is not currently playing!\n";
            }
        }


        void Sound::loop(){
            m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &LoopOnFinish, &quit, NULL);
            ga_handle_play(m_Handle);
            m_Handle->Sound = this;
            m_Playing = true;
        }

        void Sound::pause(){
            if(m_Playing){
                m_Position = ga_handle_tell(m_Handle, GA_TELL_PARAM_CURRENT);
                ga_handle_stop(m_Handle);
                m_Playing = false;
            }else{
                std::cout << "Cannot set pause! Sound is not currently playing!\n";
            }
        }

        void Sound::setGain(float gain){
            if(m_Playing){
                m_Gain = (gc_float32)gain;
                ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, m_Gain);
            }else{
                std::cout << "Cannot set gain! Sound is not currently playing!\n";
            }
        }

        void LoopOnFinish(ga_Handle* in_handle, void* in_context){
            Sound *temp = (Sound*) in_handle->Sound;
            temp->loop();
            ga_handle_destroy(in_handle);
        }

        void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context){
            Sound *temp = (Sound*) in_handle->Sound;
            temp->m_Playing = false;
            gc_int32* flag = (gc_int32*)(in_context);
            *flag = 1;
            ga_handle_destroy(in_handle);
        }


    }
}