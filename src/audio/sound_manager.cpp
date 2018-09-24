//
// Created by grzegorz on 21.09.18.
//

#include "sound_manager.h"

namespace engine {
    namespace audio {
        std::vector<Sound*> SoundManager::m_Sounds;
        gau_Manager* SoundManager::m_Mgr = NULL;
        ga_Mixer* SoundManager::m_Mixer = NULL;

        void SoundManager::init(){
            gc_initialize(0);
            m_Mgr = gau_manager_create();
            m_Mixer = gau_manager_mixer(m_Mgr);
        }

        void SoundManager::add(Sound *sound){
            m_Sounds.push_back(sound);
        }

        Sound* SoundManager::get(const std::string name){

            for(unsigned int i = 0; i < m_Sounds.size(); i++){
                if(name == m_Sounds[i]->getName()) return m_Sounds[i];
            }

            return NULL;
        }

        void SoundManager::clean(){

            while(!m_Sounds.empty()){
                delete m_Sounds.back();
                m_Sounds.pop_back();
            }


            gau_manager_destroy(m_Mgr);
            gc_shutdown();
        }

        void SoundManager::update(){
            gau_manager_update(m_Mgr);
        }


    }
}