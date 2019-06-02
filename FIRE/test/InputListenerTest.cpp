#include <FIRE/InputListener.h>
#include <FIRE/Key.h>
#include <FIRE/KeyAction.h>
#include <FIRE/RenderContext.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(AnInputListener, CallsARegisteredCallbackForAKeyEvent)
{
    bool called = false;
    auto callback = [&called] { called = true; };

    FIRE::InputListener inputListener;
    inputListener.Register(FIRE::Key::KEY_A, FIRE::KeyAction::PRESS, callback);
    inputListener.Call(FIRE::Key::KEY_A, FIRE::KeyAction::PRESS);

    EXPECT_TRUE(called);
}