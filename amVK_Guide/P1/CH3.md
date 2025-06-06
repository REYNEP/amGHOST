### Chapter 3: Common Patterns: _if someone missed to catch it yet_ 😉
```ruby
Object  Vk      VkInstance
Types   Vk      VkInstanceCreateInfo
Funcs   vk      vkCreateInstance()
Enums   VK_     VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO

Extensions
    KHR:- Khronos authored,
    EXT:- multi-company authored

Creating "VkZZZ" object
    1. take `VkZZZCreateInfo` --> fill it up
    2. call `vkCreateZZZ()`
    3. also `vkDestroyZZZ()` before closing your app

    4. Some objects get "allocated" rather than "created"
        `VkZZZAllocateInfo` --> `vkAllocateZZZ` --> `vkFreeZZZ`

    5. Sometimes there will be `.zzzCreateInfoCount` & `.pZZZCreateInfos`
                        e.g. `.queueCreateInfoCount` & `.pQueueCreateInfos``
            -> So you could like pass in an array/vector
            -> You will see this in lots of other places

Getting List/Properties
    6. vkEnumerateZZZ() --> \see `[Chapter2.1.] vkEnumeratePhysicalDevices()` example
```
-- | -- | -- | ----------------------------------------------------------------------------

7. 🟪 almost every `VkStruct` is gonna have these 3 field/member 💁‍♀️
    1. `sType`:-
        - It may seem somewhat redundant, but this information can be useful for the `vulkan-loader` and actual `gpu-driver-implementations` to know what type of structure was passed in through `pNext`.
    2. `pNext`:-
        - _allows to create a linked list between structures._
        - It is mostly used when dealing with extensions that expose new structures to provide additional information to the `vulkan-loader`, `debugging-validation-layers`, and `gpu-driver-implementations`.
            - _i.e. they can use the `pNext->stype` field to know what's ahead in the linked list_
    3. `.flags`:- 
        - this one goes mostly ignored / set to `0`
        </br> 

8.  `.pQueueCreateInfos`:- yes, you 'can' pass multiple 😉
    - Sometimes there will be `.zzzCreateInfoCount` & `.pZZZCreateInfos` 
        - So you could like pass in an array/vector
        - You will see this in lots of other places

-- | -- | -- | ----------------------------------------------------------------------------

9. ###### CreateInfo StartingPoint
    ```cpp
    VkRenderPassCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0
    };
    ```

```ruby
10.  Do remember to check the `Valid Usage` section within each manual-page
```

11. ###### Getting/Enumerating VkObject list 💁‍♀️
    ```cpp
    uint32_t deviceCount = 0;     
        // [implicit valid usage]:- must be 0 [if 3rd-param = nullptr]
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
            // it's kinda like the function is 'output-ing into' deviceCount

    std::vector<VkPhysicalDevice> HardwareGPU_List(gpuCount);
        // best to save this as a class member variable
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, HardwareGPU_List.data());
            // note: it does return     VkResult return_code
    ```


<div style="page-break-after: always;"></div>

-- | -- | -- | ----------------------------------------------------------------------------

12. `Symbols`:-
    - 🟪:- kinda means nothing
        - i kinda used to like make it look like a bit pattern-ish iguess 🥴🫢
        </br>
        - 🟪💁‍♀️: "Pretty Obvious"

    - 🟨:- "Yellow Card"
        - it means, you don't need to hesitate about this thingy right now 💁‍♀️ we will focus on this element later 🤭
        ```ruby 
        1. ChapterZZZ => Unknown WIP/TBD Chapter
        2. Chapter2.4 => 
            If LATER-CHAPTER => Dont hesitate right now, Do this when you each that LATER-Chapter
            If  PREV-CHAPTER => You can go back and check 😛
                🔗 `SurfCAP.currentTransform`
                🔗 Chapter2.4
        ```

    - 🟧:- "Orange Card"
        - it means, this element is probably never gonna be 'necessary' for vulkan applications 💁‍♀️
        </br>

    - 🪐: "Extensions"
        - Same as 🟨 "Yellow Card". But marks a little bit more, that, "Here goes Extension" Features
        </br> 

    - 🔠: "Options"
        - Sometimes you'd "Must Need" to choose between a few options
        </br>

    - 🏳️: "I Lose, You Win!" / General Flag Icon / Sometimes means -> "Lots of Flags" / IDK / Didn't check [IDC]
    - 🎌: "Nice/Important Flags"
    - 🚩: "One Flag" [IDC]
    - 🏴: "No Flag" [IDC]
    - ⚠️: "Deprecated Feature" / "Other Kinds of Warnings" / I will try to name when using this emoji/sign
    - 🏷️: "Type"
    - 🟨 **ChapterZZZ**
    - 🔗 **_Chapter2.1_**
    - 🔗 `GITHUB_WIP`
    - 📋🔄 **_Chapter2.1_**
        - `vkEnumeratePhysicalDevices()`
        - it means, Implement Exactly like in **_Chapter2.1_** 😉
        </br>
    
    - ℹ️: "Create Info"
    - 🌯: `amVK_Wrap`
    
    - ↩️📦: "Object Getting return by Vulkan Function"

    - `📜 REY_DOCs`
        - Actual Notes
        - Mostly, vkdoc.net documentation is good enough. But if I wanna add smth extra, it goes here
        - This section might get big & robust sometimes 🤭

    - `</> TheCode`
    - `📽️ So far, The result`
        - 📝:- "File Icon"
    - `👀 Visualization / [See it] / JSON Printing`
    </br>
    
    - `🔬🛠️ 2DriverIMPL`
        - To The People Who are gonna Implement the Driver
        - Other Keyword:- "DriverGurantee"
        </br>

-- | -- | -- | ----------------------------------------------------------------------------

1.  ##### Emojis List
    - 🟪 🟨 🟧 🪐 🔠 ➡️ 🏷️ 📝 ℹ️ 📥 🌋 🧊
    - 🟪💁‍♀️
    - ↩️📦
    - 🔗 _**SubChapter 2**_
    - 🔗 _**Next SubChapter**_
    - 🔗 **_Chapter2.1_**
    - 🟨 **ChapterZZZ**
    - 📋🔄 **_Chapter2.1_**
    - 🔗 `GITHUB_WIP`
    - ##### ↩️ Return Codes
    - ##### 📜 REY_DOCs
    - ##### `</> TheCode`
    - ##### `</> main.cpp`
    - ##### `📽️ So far, The result`
    - ##### `🔬🛠️ 2DriverIMPL`
    - ##### `👀 Visualization / [See it] / JSON Printing`

2.  ##### Templates Below 
    - https://vkdoc.net/man/VkGraphicsPipelineCreateInfo
        - `.sType` 🟪 `VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO`
        - `.pNext` 🪐 `nullptr`
        - `.flags` 🏳️ `0`
            - 🪐 https://vkdoc.net/man/VkPipelineCreateFlagBits | [ivirtex-github](https://github.com/ivirtex/vulkan-hover-docs/tree/master/vscode_ext/vulkan_man_md_pages/VkPipelineCreateFlagBits.md)
            </br>

    - https://vkdoc.net/man/VkGraphicsPipelineCreateInfo
        - `.sType` 🟪 `VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO`
        - `.pNext` 🪐 `nullptr`
        - `.flags` 🏳️ `VkBufferCreateFlagBits`
            - https://vkdoc.net/man/VkBufferCreateFlagBits | [ivirtex-github](https://github.com/ivirtex/vulkan-hover-docs/tree/master/vscode_ext/vulkan_man_md_pages/VkBufferCreateFlagBits.md)
                - `SPARSE` 🟨 **ChapterZZZ**

        - `.pSwapchains` 🟪💁‍♀️
        
        - `.pNext` 🪐 `nullptr`
            - 🪐 `VkDeviceGroupCommandBufferBeginInfo`
            - 🪐 Maybe some interesting extensions, idk

        - `.flags` 🔠 `VkCommandBufferUsageFlagBits`
            - https://vkdoc.net/man/VkCommandBufferUsageFlagBits | [ivirtex-github](https://github.com/ivirtex/vulkan-hover-docs/tree/master/vscode_ext/vulkan_man_md_pages/VkCommandBufferUsageFlagBits.md)
                - 🔠 `ONE_TIME_SUBMIT`
                - 🔠 `RENDER_PASS_CONTINUE` [secondary command buffer]
                - 🔠 `SIMULTANEOUS_USE`

3.  ##### Extra Emojis
    📟📇
    🎚️🎌🏳️
    🔌🚀
    🚫📜
    ⚠️🧓
    ☢️🧨
    ☢️💀
    ⚠️🏚️

4.  ##### Number BLocks
    1️⃣
    2️⃣
    3️⃣
    4️⃣
    5️⃣
    6️⃣
    7️⃣
    8️⃣
    9️⃣
    🔟
    1️⃣1️⃣
    1️⃣2️⃣
    1️⃣3️⃣
    1️⃣4️⃣
    1️⃣5️⃣
    1️⃣6️⃣
    1️⃣7️⃣
    1️⃣8️⃣
    1️⃣9️⃣
    2️⃣0️⃣

5.  ##### Possible Function Naming Verbs-Emojis
    ```cpp
    1. query_SurfCap 🕵️♂️
    2. update_SurfCap 🔄
    3. load_SurfCap 📥
    4. acquire_SurfCap 🔗
    5. get_SurfCap 📤
    6. grab_SurfCap	👐
    7. snag_SurfCap	🎣 (Quick pull)
    8. pluck_SurfCap	✂️ (Precision)
    9. selected_gpu_surfCap	🎯 (Targeted)	Emphasizes the GPU_Index selection.
    10. current_surfCap	⏳ (Stateful)
    11. yoink_SurfCap	🦄 (Playful)	VkSurfaceCapabilitiesKHR* cap = yoink_SurfCap();
    12. procure_SurfCap	🕴️ (Formal)	procure_SurfCap() → Sounds like a business transaction!
    13. obtain_SurfCap	🏆 (Success)
    14. collect_SurfCap	📚 (Gathering)
    15. retrieve_SurfCap	🎯 (Accuracy)
    16. sync_SurfCap	🔄 (Sync State)
    17. pull_SurfCap	🪢 (Tug-of-war)
    18. refresh_SurfCap	💫 (Update)
    19. reload_SurfCap	♻️ (Reload)
    20. populate_SurfCap	🌱 (Fill Data)
    21. enumerate_SurfCap	📇 (Listing)
    22. summon_SurfCap	🧙♂️ (Magic)
    23. harvest_SurfCap	🌾 (Farm)
    24. fish_SurfCap	🎣 (Fishing)
    25. dial in	🎛️ (Precision)
    26. shape up	🌟 (Polishing)
    27. rig	🛠️ (Hacky)
    28. tailor	👗 (Custom-fit)
    29. access_SurfCap 🔍
    30. craft	🧙♂️ (Artisan)
    31. surfCap 📋 (property-style)
    32. surfCap_ptr 🎯 (or surfCapRef)
    ```

6.  ##### Extra Emojis
    ```py
    #!/usr/bin/env python3
    # 🎮 Ultimate Vulkan Emoji Guide (1-35)

    vulkan_steps = [
        # Core Setup (Original 1-5)
        "1. 🌍 Instance Creation",
        "2. 🖥️ Physical Device Selection",
        "3. ⚙️ Logical Device Setup",
        "4. 🎨 Graphics Pipeline",
        "5. 🖼️ SwapChain Initialization",

        # Resource Management (Original 6-10)
        "6. 🗄️ Buffer Allocation",
        "7. 🧠 Memory Binding",
        "8. 🖌️ Descriptor Sets",
        "9. 📦 Image Creation",
        "10. 🎮 Command Pools",

        # Execution Flow (Original 11-12)
        "11. 📜 Command Buffers",
        "12. ⏱️ Synchronization",

        # Debugging (Original 13-14)
        "13. 🔍 Validation Layers",
        "14. 🐛 Debug Messenger",

        # Advanced Features (Original 15-17)
        "15. 🌌 Ray Tracing",
        "16. 🤖 Compute Pipeline",
        "17. 🧵 Multi-Threading",

        # Cleanup (Original 18-20)
        "18. 🧹 Resource Destruction",
        "19. 💥 Device Cleanup",
        "20. 🚀 Instance Shutdown",

        # New Additions (21-35)
        "21. 🧊 Device Memory",
        "22. 🔄 Memory Barriers",
        "23. 📊 Buffer Views",
        "24. 🎛️ Pipeline Layout",
        "25. 🔮 Shader Modules",
        "26. 🧩 Pipeline Cache",
        "27. 🎆 Render Passes",
        "28. 🖌️ Dynamic Rendering",
        "29. 🌐 Multi-View Rendering",
        "30. ⏳ Timeline Semaphores",
        "31. 🚦 Fences",
        "32. 📡 Debug Markers",
        "33. 📈 Performance Queries",
        "34. 🌀 Compute Dispatches",
        "35. 🚀 Acceleration Structures"
    ]
    ```
    ```py
    #!/usr/bin/env python3
    # 🏆 Ultimate Vulkan Emoji Cheatsheet (50+ Concepts)

    vulkan_concepts = {
        # === Core Setup ===
        "🌍": "Instance Creation (vkCreateInstance)",
        "🖥️": "Physical Device Selection (vkEnumeratePhysicalDevices)",
        "⚙️": "Logical Device (vkCreateDevice)",
        "📜": "Extensions/Layers (ppEnabledExtensionNames)",
        
        # === Resources ===
        "🗄️": "Buffers (vkCreateBuffer)",
        "🧊": "Device Memory (vkAllocateMemory)",
        "📦": "Images (vkCreateImage)",
        "🔄": "Memory Barriers (vkCmdPipelineBarrier)",
        "🧶": "Image Views (vkCreateImageView)",
        "🧩": "Sparse Resources (VkSparseImageMemoryBind)",
        
        # === Pipeline ===
        "🎨": "Graphics Pipeline (vkCreateGraphicsPipelines)",
        "🤖": "Compute Pipeline (vkCreateComputePipelines)",
        "🔮": "Shader Modules (vkCreateShaderModule)",
        "🎛️": "Pipeline Layout (vkCreatePipelineLayout)",
        "🧪": "Pipeline Cache (vkCreatePipelineCache)",
        
        # === Descriptors ===
        "🖌️": "Descriptor Sets (vkAllocateDescriptorSets)",
        "📇": "Descriptor Pool (vkCreateDescriptorPool)",
        "📊": "Descriptor Set Layout (vkCreateDescriptorSetLayout)",
        
        # === Rendering ===
        "🎆": "Render Passes (vkCreateRenderPass)",
        "🖼️": "Framebuffers (vkCreateFramebuffer)",
        "🎚️": "Dynamic Rendering (VK_KHR_dynamic_rendering)",
        "👁️": "Multi-View (VK_KHR_multiview)",
        
        # === Commands ===
        "🎮": "Command Pools (vkCreateCommandPool)",
        "📜": "Command Buffers (vkAllocateCommandBuffers)",
        "⏱️": "Queue Submission (vkQueueSubmit)",
        
        # === Synchronization ===
        "🚦": "Fences (vkCreateFence)",
        "⏳": "Timeline Semaphores (VK_KHR_timeline_semaphore)",
        "🤝": "Events (vkCreateEvent)",
        
        # === Advanced ===
        "🌌": "Ray Tracing (VK_KHR_ray_tracing_pipeline)",
        "🚀": "Acceleration Structures (vkCreateAccelerationStructureKHR)",
        "🌀": "Mesh Shading (VK_EXT_mesh_shader)",
        "💫": "Task Shaders (VK_EXT_mesh_shader)",
        
        # === Debugging ===
        "🔍": "Validation Layers (VK_LAYER_KHRONOS_validation)",
        "🐛": "Debug Utils (vkCreateDebugUtilsMessengerEXT)",
        "📡": "Debug Markers (vkCmdDebugMarkerBeginEXT)",
        "📈": "Performance Queries (VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR)",
        
        # === Cleanup ===
        "🧹": "Resource Destruction (vkDestroy*)",
        "💥": "Device Cleanup (vkDestroyDevice)",
        "🚀": "Instance Shutdown (vkDestroyInstance)",
        
        # === New Additions ===
        "🔄": "Push Constants (vkCmdPushConstants)",
        "🎚️": "Dynamic States (VkPipelineDynamicStateCreateInfo)",
        "🧠": "Pipeline Derivatives (VK_PIPELINE_CREATE_DERIVATIVE_BIT)",
        "📌": "Specialization Constants (VkSpecializationInfo)",
        "🌐": "External Memory (VK_KHR_external_memory)",
        "🔗": "Linked GPUs (VK_KHR_device_group)"
    }
    ```
    ```py
    #!/usr/bin/env python3
    # 🏆 Ultimate Vulkan Cheatsheet (70+ Concepts) 🏆

    vulkan_steps = [
        # === Core Setup (1-8) ===
        "1. 🌍 Instance Creation",
        "2. 🖥️ Physical Device Selection",
        "3. ⚙️ Logical Device Setup",
        "4. 🔌 Device Features",
        "5. 📜 Extensions/Layers",
        "6. 🖼️ SwapChain Initialization",
        "7. 🌐 Surface Creation",
        "8. 🧭 Queue Families",

        # === Resources (9-24) ===
        "9. 🗄️ Buffer Allocation",
        "10. 🧊 Device Memory",
        "11. 📦 Image Creation",
        "12. 🧶 Image Views",
        "13. 🔄 Memory Barriers",
        "14. 🧩 Sparse Resources",
        "15. 📊 Buffer Views",
        "16. 🧵 Host-Coherent Memory",
        "17. 🚚 Memory Transfers",
        "18. 🧠 Staging Buffers",
        "19. 🔗 External Memory",
        "20. 🧿 Protected Memory",
        "21. 💿 Buffer Device Address",
        "22. 🏷️ Resource Naming",
        "23. 📏 Memory Requirements",
        "24. 🧑‍🔧 Memory Budget",

        # === Pipeline (25-40) ===
        "25. 🎨 Graphics Pipeline",
        "26. 🤖 Compute Pipeline",
        "27. 🔮 Shader Modules",
        "28. 🎛️ Pipeline Layout",
        "29. 🧪 Pipeline Cache",
        "30. 🔄 Push Constants",
        "31. 🎚️ Dynamic States",
        "32. 📌 Specialization Constants",
        "33. 🧠 Pipeline Derivatives",
        "34. 💾 Pipeline Libraries",
        "35. 🌀 Tessellation",
        "36. 💫 Geometry Shaders",
        "37. 🧪 Subpasses",
        "38. ✂️ Depth/Stencil",
        "39. 🌈 Blend States",
        "40. 🧵 Multiview Rendering",

        # === Commands (41-50) ===
        "41. 🎮 Command Pools",
        "42. 📜 Command Buffers",
        "43. ⏱️ Queue Submission",
        "44. 🔁 Secondary Command Buffers",
        "45. 🧑‍🍳 Indirect Commands",
        "46. 🎛️ Device Groups",
        "47. 🤝 Queue Priorities",
        "48. ⏳ Timeline Semaphores",
        "49. 🚦 Fences",
        "50. 🤝 Events",

        # === Advanced (51-70) ===
        "51. 🌌 Ray Tracing",
        "52. 🚀 Acceleration Structures",
        "53. 🌀 Mesh Shading",
        "54. 💫 Task Shading",
        "55. 📡 Debug Markers",
        "56. 📈 Performance Queries",
        "57. 🕵️‍♀️ Object Tracking",
        "58. 🧩 Bindless Resources",
        "59. 🚧 Pipeline Barriers",
        "60. 💾 Pipeline Statistics",
        "61. 🌐 External Semaphores",
        "62. 🔄 Present Modes",
        "63. 🖌️ Dynamic Rendering",
        "64. 🧶 Fragment Density Maps",
        "65. 🌀 Variable Rate Shading",
        "66. 🧿 Protected Swapchains",
        "67. 📜 Shader Printf",
        "68. 🧪 Pipeline Robusness",
        "69. 🛡️ Validation Features",
        "70. 🧹 Resource Cleanup"
    ]
    ```

-- | -- | -- | ----------------------------------------------------------------------------