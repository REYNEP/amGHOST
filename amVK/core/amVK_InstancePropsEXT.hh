#pragma once
#include "amVK/utils/amVK_InstanceProps.hh"

class amVK_Surface;
class amVK_SwapChain;
class amVK_SwapChainIMGs;
/** Must be created by amVK_SwapChainIMGs */
class amVK_SurfaceLinks {
  public:
    amVK_Surface *S;
    amVK_SwapChain *SC;
    amVK_SwapChainIMGs *SC_IMGs;
};

class amVK_InstancePropsEXT : public amVK_InstanceProps {
  public:
    amVK_InstancePropsEXT() {}
   ~amVK_InstancePropsEXT() {}

  public:
    static inline REY_ArrayDYN<amVK_SurfaceLinks>                                  amVK_1D_SurfaceLinks;
        /** Must be created by amVK_SwapChainIMGs */
    static void      push_back_amVK_SurfaceLinks(amVK_SwapChainIMGs* SC_IMGs);  // amVK_1D_SurfaceLinks

  public:
    static void Export_nilohmannJSON_EXT(void);
    static void EnumeratePhysicalDevices(void); // { amVK_InstanceProps::EnumeratePhysicalDevices(amVK_Instance::vk_Instance); }         [.cpp]
};