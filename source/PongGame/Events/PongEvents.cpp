#include "PongGameStd.h"

#include "PongEvents.h"

const uge::EventType EvtData_Player_Scored::sk_EventType(0xd9820000);
const uge::EventType EvtData_Ball_Wall_Collision::sk_EventType(0x285e83b);
const uge::EventType EvtData_Ball_Paddle_Collision::sk_EventType(0xc3771e27);
const uge::EventType EvtData_Paddle_Wall_Collision::sk_EventType(0x182ad93d);
const uge::EventType EvtData_Restart_Game::sk_EventType(0x1711f7b2);
const uge::EventType EvtData_Move_Paddle::sk_EventType(0x1a537841);
const uge::EventType EvtData_Stop_Paddle::sk_EventType(0x73cbe48a);
