---
export_on_save:
  prince: false
---
<div class="REY_TITLE" align=center>

# Chapter 8: `CommandBuffer` 📝

<div class="REY_TITLE_SUB1">

Rendering commands have to be Recorded in a CommandBuffer.
Only then the GPU can work on it 💁‍♀️.
That's the idea, since decades ago, so yeah, xD.

</div>
</div>


## 0. `amVK` wrap 🌯
```cpp
    #include "amVK_Synchronization.hh"
    #include "amVK_CommandPoolMAN.hh"

        // TwT
        REY_LOG("");
        #define amVK_S amVK_Sync
        #define CPCF CommandPoolCreateFlags
    amVK_CommandPoolMAN*CPMAN = new amVK_CommandPoolMAN(D);
                        CPMAN->init_CMDPool_Graphics(amVK_S::CPCF::RecordBuffer_MoreThanOnce);
                        CPMAN->CreateCommandPool_Graphics(flags);
                        CPMAN->AllocateCommandBuffers1_Graphics(1);

    amVK_CommandBufferPrimary *CB = new amVK_CommandBufferPrimary(CPMAN->BUFFs1.Graphics[0]);
```

## 1. `VkCommandPool`
#### 🛠️ `VkCommandPoolCreateInfo`
- 🌋 https://vkdoc.net/man/VkCommandPoolCreateInfo
    - `.sType` 🟪 `VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO`
    - `.pNext` 🟪 `NULL`
    - `.flags` 🏳️ `VkCommandPoolCreateFlagBits`
        - https://vkdoc.net/man/VkCommandPoolCreateFlagBits | [ivirtex-github](https://github.com/ivirtex/vulkan-hover-docs/tree/master/vscode_ext/vulkan_man_md_pages/VkCommandPoolCreateFlagBits.md)
            - 🏳️ `TRANSIENT`
            - 🏳️ `RESET_COMMAND_BUFFER`:- Lets you call `vkBeginCommandBuffer()` on same `CMDBUF` more than once
            - 🏳️ `PROTECTED`
        - 🟪 `0`:- Can't call `vkBeginCommandBuffer()` more than once on the same `CMDBUF`
        </br>

    - `.queueFamilyIndex` 
        - 🟪 CommandPool = `as per queueFamily`
        - i am not sure if you can have multiple CommandPool on the same QueueFamily

#### 📦 `vkCreateCommandPool()`
- 🌋 https://vkdoc.net/man/vkCreateCommandPool
    - `.device` 🟪 💁‍♀️
    - `.pCreateInfo` 🟪 💁‍♀️
    - `.pAllocator` 🟨 **ChapterZZZ**
    - `.pSemaphore` ↩️📦
    </br> 

#### 📜 REY_DOCs
- Copy Paste `amVK_FrameBuffer.hh` Current Implementation & Change it as needed
    - Trust me, this is the most fun way of doing this, xP

#### 🧊 `amVK` 🔗 [amVK_CommandPoolMAN.hh](https://github.com/REYNEP/amGHOST/blob/74cf5c96a9b12db4896f2f4c592cfd72923d6231/amVK/core/amVK_CommandPoolMAN.hh)





<div class="REY_NOSHOW_PDF">    </br></br></br></br></br></br>   </div><div class="REY_BR1_POSITIVE_PDF"></div>






## 2. `VkCommandBuffer`
#### 🛠️ `VkCommandBufferAllocateInfo`
- https://vkdoc.net/man/VkCommandBufferAllocateInfo
    - `.sType` 🟪 `VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO`
    - `.pNext` 🟪 `NULL`
    - `.commandPool` 🟪 💁‍♀️
    - `.level` 🔀 `PRIMARY/SECONDARY` [Toggle]
    - `.commandBufferCount` 🟪 💁‍♀️
    </br>

#### 📦 `vkAllocateCommandBuffers()`
- https://vkdoc.net/man/vkAllocateCommandBuffers
    - `.device`
    - `.pAllocateInfo` 🟪 💁‍♀️
    - `pCommandBuffers` ↩️📦
    </br>

#### 🧊 `amVK` 🔗 [amVK_CommandPoolMAN.hh#L63](https://github.com/REYNEP/amGHOST/blob/74cf5c96a9b12db4896f2f4c592cfd72923d6231/amVK/core/amVK_CommandPoolMAN.hh#L63)
- both Primary & Secondary commandBuffers are supported
    - But, as off `01 May, 2025`
        - amVK Users must use one of the `amVK_CommandPoolCATs` (Categories) e.g. Graphics/Compute 💁‍♀️
- 🔗 [amVK_Synchronization.hh](https://github.com/REYNEP/amGHOST/blob/74cf5c96a9b12db4896f2f4c592cfd72923d6231/amVK/common/amVK_Synchronization.hh)