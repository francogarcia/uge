#pragma once

#include <Engine/GameView/ViewFeedback/ViewFeedbackFactory.h>

namespace sg
{

    class FeedbackFactory : public uge::ViewFeedbackFactory
    {
    public:
        FeedbackFactory();
        ~FeedbackFactory();

    protected:
        virtual void vInitFactory() override;
    };

}
