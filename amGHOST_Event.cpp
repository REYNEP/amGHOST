/*

                   _____ ______ 
                  / ____|  ____|
   __ _ _ __ ___ | |  __| |__   
  / _` | '_ ` _ \| | |_ |  __|  
 | (_| | | | | | | |__| | |____ 
  \__,_|_| |_| |_|\_____|______|


 */
#include "amE.hh"
static inline bool operator>(amE::Type lhs, int rhs) {
    return static_cast<int>(lhs) > rhs;
}

static inline bool operator<(amE::Type lhs, int rhs) {
    return static_cast<int>(lhs) < rhs;
}

inline amE::Category amE::GetEventCategory(amE::Type event) {
    if (event > 100 && event < 200) {
        return Category::Window;
    }
    if (event > 200 && event < 300) {
        return Category::Mouse;
    }
    if (event > 1000 && event < 2000) {
        return Category::Keyboard;
    }
    return Category::None;
} 