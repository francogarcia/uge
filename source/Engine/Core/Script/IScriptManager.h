#pragma once

namespace uge
{

    class IScriptManager
    {
    public:
        IScriptManager();
        virtual ~IScriptManager();

        virtual bool vInit() = 0;
        virtual void vExecuteFile(const char* pScriptFile) = 0;
        virtual void vExecuteString(const char* pScriptString) = 0;
    };

}
