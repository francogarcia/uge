/*
 * (c) Copyright 2014 Franco Eus�bio Garcia
 *
 * This file is part of UGE. 
 *
 * UGE is free software; you can redistribute it and/or
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */ 

#pragma once

#include <Engine/GameView/ViewFeedback/ViewFeedbackFactory.h>

namespace pg
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
