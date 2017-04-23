#ifndef EVENT_HPP_INCLUDED
#define EVENT_HPP_INCLUDED

struct Event {
    enum class EventType {
        Close,
        Key,
        Size
    };

    struct KeyEvent {
        int key;
        int scancode;
        int action;
        int mods;
    };

    struct SizeEvent {
        int width;
        int height;
    };

    //

    EventType type;

    union {
        KeyEvent key_ev;
        SizeEvent size_ev;
    };
};

#endif // EVENT_HPP_INCLUDED
