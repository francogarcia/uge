#pragma once

#include <Engine/GameView/ViewFeedback/ViewFeedbackFactory.h>

class PongFeedbackFactory : public uge::ViewFeedbackFactory
{
public:
    PongFeedbackFactory();
    ~PongFeedbackFactory();

protected:
    virtual void vInitFactory() override;
};
