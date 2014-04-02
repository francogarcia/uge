#include "SpaceshipGameStd.h"

#include "FeedbackFactory.h"

#include "AuralFeedback.h"

namespace sg
{

    FeedbackFactory::FeedbackFactory()
    {

    }

    FeedbackFactory::~FeedbackFactory()
    {

    }

    void FeedbackFactory::vInitFactory()
    {
        m_StateFactory.Register<sg::AuralFeedback>(sg::AuralFeedback::g_Name);
    }

}
