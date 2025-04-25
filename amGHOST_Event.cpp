/*
 ___________    ____  _______ .__   __. .___________.   .___________.____    ____ .______    _______     _______.
|   ____\   \  /   / |   ____||  \ |  | |           |   |           |\   \  /   / |   _  \  |   ____|   /       |
|  |__   \   \/   /  |  |__   |   \|  | `---|  |----`   `---|  |----` \   \/   /  |  |_)  | |  |__     |   (----`
|   __|   \      /   |   __|  |  . `  |     |  |            |  |       \_    _/   |   ___/  |   __|     \   \    
|  |____   \    /    |  |____ |  |\   |     |  |            |  |         |  |     |  |      |  |____.----)   |   
|_______|   \__/     |_______||__| \__|     |__|            |__|         |__|     | _|      |_______|_______/    
                                                                                                                 
 */
#include "amGHOST_EventTypes.hh"
static inline bool operator>(amGE::Type lhs, int rhs) {
    return static_cast<int>(lhs) > rhs;
}

static inline bool operator<(amGE::Type lhs, int rhs) {
    return static_cast<int>(lhs) < rhs;
}

inline amGE::Category amGE::GetEventCategory(amGE::Type event) {
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