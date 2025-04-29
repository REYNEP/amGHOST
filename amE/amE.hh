#pragma once
#include "REY_Types.hh"

// amG = amGHOST    
// amE = amGHOST_Event
namespace amE {
        // UNREAL ENGINE's WAY        [unused in amGHOST, yet.]
    enum class EInputEvent : uint8_t {
        IE_Pressed,
        IE_Released,
        IE_Repeat,
        IE_DoubleClick,
        IE_Axis
    };

    enum class Type : uint16_t {
        None               = 0,
        WindowClose        = 101,
        WindowResize       = 102,

        MouseMove          = 201,
        MouseButtonPress   = 202,
        MouseButtonRelease = 203,

        KeyPress           = 1001,
        KeyRelease         = 1002,
    };

    enum class Category : uint8_t {
        None = 0,
        Window = 1,
        Mouse = 2,
        Keyboard = 10
    };
    
    static inline Category GetEventCategory(Type event);
};