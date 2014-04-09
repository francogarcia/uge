/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser GPL v3
  * as published by the Free Software Foundation.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
  * http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
  *
  * You should have received a copy of the GNU Lesser GPL v3
  * along with this program; if not, write to the Free Software
  */

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

