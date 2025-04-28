#pragma once
#include "amGHOST_Event.hh"

typedef int (*amGHOST_EventKonsumentPrototype)(amGHOST_Event lightweight_event, void* user_data);

class amGHOST_EK {
  public:
    explicit amGHOST_EK(void* userData) : m_userData(userData) {}
   ~amGHOST_EK() {}

    void* m_userData = nullptr;

    /** 
     * @param lightweight_event: 
     * @return int: reserved for future use cases
     */
    virtual int processEvent(amGHOST_Event lightweight_event) = 0;
};