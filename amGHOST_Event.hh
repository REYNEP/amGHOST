#pragma once
#include "amGHOST_EventTypes.hh"

class amGHOST_Event {
  public:
    amGHOST_Event(void) {}
   ~amGHOST_Event(void) {}

    amGE::Type     m_Type;
    amGE::Category m_Category;
};