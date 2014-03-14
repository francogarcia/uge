#pragma once

#include "../AudioTask.h"

namespace uge
{

    class ExplosionSoundTask : public Task
    {
    public:
        ExplosionSoundTask();
        ~ExplosionSoundTask();

    protected:
        virtual void vOnInit() override;
        virtual void vOnUpdate(const unsigned long dt) override;

        int m_State;
        std::shared_ptr<SoundTask> m_Sound;
    };

}
