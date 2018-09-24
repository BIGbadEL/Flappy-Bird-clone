//
// Created by grzegorz on 21.09.18.
//

#pragma once


#include <string>
#include <gorilla/gau.h>
#include <gorilla/ga.h>

#include "../utils/string_utils.h"



namespace engine {
    namespace audio {

        class Sound
        {
        private:
            std::string m_Name;
            std::string m_FileName;

            ga_Sound* m_Sound;
            ga_Handle* m_Handle;
            gc_int32 quit;
            gc_float32 m_Gain;
            bool m_Playing;
            int m_Position;
        public:
            Sound(const std::string& name, const std::string& filename);
            ~Sound();


            void play();
            void stop();
            void loop();
            void pause();
            void resume();
            void setGain(float gain);


            inline const float getGain() const { return (float)m_Gain; }
            inline ga_Sound* getSound() const { return m_Sound; }
            inline const std::string& getName() const { return m_Name; }
            inline const std::string& getFileName() const { return m_FileName; }
            inline const bool is_Playing() const { return m_Playing; }

            friend void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
            friend void LoopOnFinish(ga_Handle* in_handle, void* in_context);

        };
    }
}


