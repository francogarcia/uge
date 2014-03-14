#pragma once

#include "InputTypes.h"

namespace uge
{

    namespace InputMapping
    {
        class GameCommand
        {
        public:
            GameCommand();
            ~GameCommand();

            void Init(const std::string& gameCommandListFilename);

            Action GetAction(const std::string& actionName) const;
            State GetState(const std::string& stateName) const;
            Range GetRange(const std::string& rangeName) const;

        private:
            std::map<std::string, Action> m_Actions;
            std::map<std::string, State> m_States;
            std::map<std::string, Range> m_Ranges;
        };
    }

}
