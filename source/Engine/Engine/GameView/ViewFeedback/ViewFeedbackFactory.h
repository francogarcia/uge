#pragma once

#include <Utilities/PatternTemplates.h>

#include "IViewFeedback.h"

namespace uge
{

    class ViewFeedbackFactory
    {
    public:
        ViewFeedbackFactory();
        ~ViewFeedbackFactory();

        void Init();

        IViewFeedback* CreateViewFeedback(const std::string& eventSpecializationName);

    protected:
        virtual void vInitFactory();

    protected:
        GenericObjectFactory<IViewFeedback, std::string> m_StateFactory;
    };

}
