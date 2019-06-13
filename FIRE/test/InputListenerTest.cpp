#include <FIRE/InputListener.h>
#include <FIRE/Key.h>
#include <FIRE/KeyAction.h>
#include <FIRE/RenderContext.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class AnInputListener : public ::testing::Test
{
protected:
    FIRE::InputListener inputListener;
};

TEST_F(AnInputListener, CallsARegisteredCallbackForAKeyEvent)
{
    bool called = false;
    auto callback = [&called] { called = true; };

    inputListener.Register(FIRE::Key::KEY_A, FIRE::KeyAction::PRESS, callback);
    inputListener.KeyboardInput(FIRE::Key::KEY_A, FIRE::KeyAction::PRESS);

    EXPECT_TRUE(called);
}

TEST_F(AnInputListener, CallsARegisteredCallbackForAMouseInputEvent)
{
    bool called = false;
    auto callback = [&called](double, double) { called = true; };

    inputListener.Register(callback);
    inputListener.MouseInput(1.0, 2.0);

    EXPECT_TRUE(called);
}