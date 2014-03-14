#include "GameEngineStd.h"

#include "ViewFeedbackFactory.h"


namespace uge
{
    ViewFeedbackFactory::ViewFeedbackFactory()
    {

    }

    ViewFeedbackFactory::~ViewFeedbackFactory()
    {

    }

    void ViewFeedbackFactory::Init()
    {
        vInitFactory();
    }

    IViewFeedback* ViewFeedbackFactory::CreateViewFeedback(const std::string& eventSpecializationName)
    {
        IViewFeedback* pViewFeedback = m_StateFactory.Create(eventSpecializationName);

        return pViewFeedback;
    }

    void ViewFeedbackFactory::vInitFactory()
    {

    }
}

