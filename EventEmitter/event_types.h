#pragma once

#include <functional>
#include <type_traits>

// A list of semantic events that can be used freely.
// Before adding a new event to this list, first question if
// there is already an event close enough to suite your needs.
enum class Events
{
    Accept,
    Open,
    Close,
    CloseWrite,
    Read,
    Write,
    Change, // Used often by IO and Field
    Error,  // Used all over
    Upgrade,
    Create,
    Delete,
    Any,
    Ignore,
    Run,     // Used by Test
    Pass,    // Used by Test
    Fail,    // Used by Test
    Start,   // Used by Service
    Stop,    // Used by Service
    Enter,   // Used by Service
    Exit,    // Used by Service
    Process, // Used by Service
    High,    // Used by ButtonIO
    Low,     // Used by ButtonIO
    Queue,
    Defer,
    Arrange,
    Organize,
    Connect,
    Disconnect,
    Timeout,
    Valid,
    Invalid,
    Complete,
    Incomplete,
    Grant,      // Used by PermitIO
    Revoke,     // Used by PermitIO
    CursorDown, // Used by touch driver
    CursorUp,   // Used by touch driver
    SwipeUp,    // Used by touch driver
    SwipeRight, // Used by touch driver
    SwipeDown,  // Used by touch driver
    SwipeLeft,  // Used by touch driver
    ZoomOut,    // Used by touch driver
    ZoomIn,     // Used by touch driver
    Evaluate,   // Used by Component
    Actuate,    // Used by Component
    Measure,
    Reset,
    EnterCritical,
    ExitCritical,
    EnterFirmwareUpdate,
    ExitFirmwareUpdate,
    RefChange, // Used by ReferenceIO
};

// Declaring a hash function for Event so we cna use it in maps as a key.
namespace std
{
    template <>
    struct hash<Events>
    {
        std::size_t operator()(const Events &k) const
        {
            return std::hash<int>()(static_cast<std::underlying_type_t<Events>>(k));
        }
    };
} // namespace std
