#ifndef blocks_keyhandler_h
#define blocks_keyhandler_h

#include "keyhandlerListener.h"
#include <vector>

struct GLFWwindow;

namespace blocks
{
    class KeyHandler
    {
    public:
        void AddListener(KeyHandlerListener* listener);

        void KeyPressed(int key, int action);

    private:
        std::vector<KeyHandlerListener*> m_listeners;
    };
}

#endif // blocks_keyhandler_h
