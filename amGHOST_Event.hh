#pragma once
#include "amGHOST_EventTypes.hh"

class amGHOST_Event {
  public:
    amGHOST_Event(amGE::Type T, amGE::Category C) : m_Type(T), m_Category(C) {}
   ~amGHOST_Event(void) {}

    amGE::Type     m_Type;
    amGE::Category m_Category;
};