#ifndef FIRE_COMPONENTSTUB_H
#define FIRE_COMPONENTSTUB_H

#include <FIRE/Component.h>
#include <functional>
#include <map>
namespace FIRE_tests
{
class ComponentStub : public FIRE::Component
{
public:
    void Setup(FIRE::SceneObject&) override
    {
    }

    void Update(double, FIRE::SceneObject&, FIRE::Scene&) override
    {
    }

    std::optional<std::any> Receive(FIRE::Message const& msg, FIRE::SceneObject&) override
    {
        if(auto it = m_messageHandlers.find(msg); it != m_messageHandlers.end())
        {
            return it->second();
        }

        return std::nullopt;
    }

    void AddMessageHandler(FIRE::Message msg, std::function<std::optional<std::any>()> handler)
    {
        m_messageHandlers.insert({msg, handler});
    }

private:
    std::map<FIRE::Message, std::function<std::optional<std::any>()>> m_messageHandlers;
};
} // namespace FIRE_tests

#endif //FIRE_COMPONENTSTUB_H
