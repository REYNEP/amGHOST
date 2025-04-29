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

/** 
 * The purpose of this function, is to actually log more into the .json file. e.g. amVK_SurfaceLinks above
 * 
 * amVK/utils/amVK_InstanceProps   : Doesn't depend  on any other part of amVK. The entire amVK/utils directory is set up this way 💁‍♀️
 * amVK/core/ amVK_InstancePropsEXPORT: Does    depends on stuff that you can see above, right in this header 💁‍♀️
 */
class amVK_InstancePropsEXPORT : public amVK_InstanceProps {
  public:
    amVK_InstancePropsEXPORT() {}
   ~amVK_InstancePropsEXPORT() {}

  public:
    static inline REY_ArrayDYN<amVK_SurfaceLinks>                                  amVK_1D_SurfaceLinks;
        /** Must be created by amVK_SwapChainIMGs */
    static void      push_back_amVK_SurfaceLinks(amVK_SwapChainIMGs* SC_IMGs);  // amVK_1D_SurfaceLinks

  public:
    static void Export_nilohmannJSON_EXT(void);
};