#include "PongGameStd.h"

#include <Debug/Logger.h>

float CPPExp(float value)
{
    return std::exp(value);
}

class CPPBaseClass
{
public:
    CPPBaseClass() : m_X(0)
    {

    }

    virtual ~CPPBaseClass()
    {

    }

    static void Hello()
    {
        std::cout << "Hello!" << std::endl;
    }

    void SetX(int x)
    {
        m_X = x;
    }

    virtual void vPrint()
    {
        std::cout << "x = " << m_X << std::endl;
    }

private:
    int m_X;
};

class CPPClass : public CPPBaseClass
{
public:
    CPPClass() : CPPBaseClass()
    {
        SetX(100);
    }

    virtual void vPrint() override
    {
        std::cout << "---> ";
        CPPBaseClass::vPrint();
    }
};

class CPPFlexibleClass
{
public:
    CPPFlexibleClass() : m_X(0)
    {

    }

    virtual ~CPPFlexibleClass()
    {

    }

    void SetX(int x)
    {
        m_X = x;
    }

    int GetX() const
    {
        return m_X;
    }

    virtual void vPrint()
    {
        std::cout << "x = " << m_X << std::endl;
    }

    static void SetLuaState(LuaPlus::LuaState* pLuaState)
    {
        assert(s_pLuaState == nullptr);
        assert(pLuaState != nullptr);

        s_pLuaState = pLuaState;
    }

    static LuaPlus::LuaObject CreateFromScript()
    {
        CPPFlexibleClass* pInstance = new CPPFlexibleClass();

        LuaPlus::LuaObject luaInstance;
        luaInstance.AssignNewTable(s_pLuaState);
        luaInstance.SetLightUserData("__object", pInstance);

        LuaPlus::LuaObject metaTable = s_pLuaState->GetGlobals().GetByName("CPPFlexibleClassMetaTable");
        luaInstance.SetMetaTable(metaTable);

        return luaInstance;
    }

private:
    int m_X;
    static LuaPlus::LuaState* s_pLuaState;
};

LuaPlus::LuaState* CPPFlexibleClass::s_pLuaState = nullptr;

int main(int argc, char* argv[])
{
    debug::log::Init("data/debug/LogConfig.xml");

    // Using LuaPlus API directly.
    bool bUseLuaSTDLibrary = true;
    LuaPlus::LuaState* pLuaState = LuaPlus::LuaState::Create(bUseLuaSTDLibrary);

    // Runs the code in the string.
    pLuaState->DoString("print(\"Hello, World!\");");

    // Runs the code in the chosen file.
    pLuaState->DoFile("data/scripts/test.lua");
    LuaPlus::LuaObject luaGlobals = pLuaState->GetGlobals();

    LuaPlus::LuaObject luaX = luaGlobals.GetByName("luaX");
    // Reads the value of the Lua variable.
    int x = luaX.GetInteger();
    std::cout << "x = " << x << std::endl;
    x += 10;
    // Assigns a new value.
    luaX.AssignInteger(pLuaState, x);
    int newX = luaX.GetInteger(); // Read the value again.
    assert(x == newX);
    std::cout << "x = " << newX << std::endl;

    // Reads a table.
    LuaPlus::LuaObject luaTable = luaGlobals.GetByName("luaTable");
    // Two ways to fetch the value of an attribute.
    LuaPlus::LuaObject luaTableX1 = luaTable.GetByName("x");
    LuaPlus::LuaObject luaTableX2 = luaTable["x"];
    assert((luaTableX1.IsNumber()) && (luaTableX2.IsNumber()) &&
        (luaTableX1.GetNumber() == luaTableX2.GetNumber()));
    // Assigns (or create a new) attribute to the Lua's table.
    luaTable.SetNumber("z", 100.0f);

    // Creates a new string as a global variable in Lua.
    luaGlobals.SetString("luaString", "From C++");

    // Calls a Lua function.
    LuaPlus::LuaFunction<float> LuaExp = pLuaState->GetGlobal("LuaExp");
    std::cout << "exp(1) = " << LuaExp(1) << std::endl;

    // Binds a C++ function to Lua.
    luaGlobals.RegisterDirect("CPPExp", &CPPExp);
    // Member function:
    CPPBaseClass* pBaseClass = new CPPClass;
    luaGlobals.RegisterDirect("cppMemberFunction", *pBaseClass, &CPPBaseClass::SetX);
    // Static function:
    luaGlobals.RegisterDirect("cppStaticFunction", &CPPBaseClass::Hello);
    // Virtual function:
    luaGlobals.RegisterDirect("cppVirtualFunction", *pBaseClass, &CPPBaseClass::vPrint);

    // More flexible way. This allows construction of C++ objects in Lua:
    CPPFlexibleClass::SetLuaState(pLuaState);
    LuaPlus::LuaObject metaTable = luaGlobals.CreateTable("CPPFlexibleClassMetaTable");
    metaTable.SetObject("__index", metaTable);
    // Other members should be added as well, if needed.
    metaTable.RegisterObjectDirect("SetX", (CPPFlexibleClass*) 0, &CPPFlexibleClass::SetX);
    metaTable.RegisterObjectDirect("GetX", (CPPFlexibleClass*) 0, &CPPFlexibleClass::GetX);
    metaTable.RegisterObjectDirect("vPrint", (CPPFlexibleClass*) 0, &CPPFlexibleClass::vPrint);
    // This function will be used to create the object.
    luaGlobals.RegisterDirect("CreateFlexibleClass", &CPPFlexibleClass::CreateFromScript);

    // A very simple Lua shell to test C++/Lua integration.
    pLuaState->DoFile("data/scripts/shell.lua");

    LuaPlus::LuaState::Destroy(pLuaState);
    pLuaState = nullptr;
    // End of LuaPlus.

    debug::log::Destroy();

    return 0;
}
