#ifndef blocks_keyhandlerListener_h
#define blocks_keyhandlerListener_h

namespace blocks
{
    class KeyHandlerListener
    {
    public:
        virtual void Notify(int key, int action) = 0;
    };
}

#endif // blocks_keyhandlerListener_h
