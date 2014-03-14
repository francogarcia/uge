#include "PongGameStd.h"

#include "PongFeedbackFactory.h"

#include "../AuralView/Events/AuralFeedback.h"

PongFeedbackFactory::PongFeedbackFactory()
{

}

PongFeedbackFactory::~PongFeedbackFactory()
{

}

void PongFeedbackFactory::vInitFactory()
{
    m_StateFactory.Register<AuralFeedback>(AuralFeedback::g_Name);
}
