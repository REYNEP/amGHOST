#pragma once
#include "amGHOST_EventTypes.hh"

class amGHOST_Event {
  public:
    amGHOST_Event(amE::Type T, amE::Category C) : m_Type(T), m_Category(C) {}
   ~amGHOST_Event(void) {}

    amE::Type     m_Type;
    amE::Category m_Category;
};