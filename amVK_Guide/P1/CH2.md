---
export_on_save:
  prince: false
---
<div class="REY_TITLE" align=center>

# Chapter 2: `VkDevice`

<div class="REY_IMG_CONTAINER" align=center style="text-align: center !important; font-align: center !important;">

![img1](./images/CH2.Vulkanised-2023-Tutorial-PART1_Page12_REY.png)
Take a look into this awesome [slide](./../V3.EverythingEverywhereAllAtOnce/P1_Vulkanised-2023-Tutorial/Vulkanised-2023-Tutorial-PART1.pdf) from slide-26 onwards
...to understand what each of these steps above _"feel like"/mean/"how to imagine them"_.
*slide = [Vulkanised 2023 Tutorial Part 1](https://www.khronos.org/assets/uploads/developers/presentations/Vulkanised-2023-Tutorial-PART1.pdf)

</div>
</div>
</br>
</br>
</br>



## 0. `amVK` wrap 🌯
```cpp
    #include "amVK_Instance.hh"
    #include "amVK_DeviceQueues.hh"
    #include "amVK_Device.hh"

        // TwT
        REY_LOG("");
    amVK_Instance::EnumeratePhysicalDevices();
    amVK_GPUProps  *GPUProps = amVK_InstanceProps::GetARandom_GPU();
                    GPUProps->GetPhysicalDeviceQueueFamilyProperties();
                    GPUProps->REY_CategorizeQueueFamilies();

    amVK_Device* D = new amVK_Device(GPUProps);
        D->CI                           // VkDeviceCreateInfo       [public]
        D->Queues                       // amVK_DeviceQueues        [public] [take a look inside 😜]
        D->add_1D_QFAMs_QCount_USER()   // amVK_DeviceQueues
        D->CreateDevice(1);             // param1 = GraphicsQueueCount = 
        D->GetDeviceQueues();           //     see:- Queues.TheArrays 😜
        D->Queues.GraphicsQ(0)          // returns   Queues.TheArrays.Graphics[0]
```

















<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
<div align=center style="font-size: 50px; font-family: 'Iosevka Curly'; ">Page-Break</div>
</div>
<div class="REY_PAGEBREAK     REY_PAGE_STARTS_WITH_H2"></div>
<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
</div>



















## 1. 📦 `vkCreateDevice()`
- https://vkdoc.net/man/vkCreateDevice
    - `physicalDevice` 🟪 `HardwareGPU_List[0]` / `amVK_InstanceProps::GetARandom_GPU()`
        - Enumerate 🟨 **_Chapter2.3_**
        - How to _'choose'_? 🟨 **_Chapter2.End_**
    - `pCreateInfo` 🟪💁‍♀️
        - 🔗 _**SubChapter 2**_
    - `pAllocator` 🟨 **ChapterZZZ**
    - `pDevice` ↩️📦 `&m_Device`
        - ↩️📦: "Returned by vkFunc()"

> ![image4](./images/CH2.image4.png)

- ##### `📽️ So far, The result`:- 
    - [4.guide.chapter2.2.midway.hh](./examples/4.guide.chapter2.2.midway.hh)


## 2. 🛠️ `VkDeviceCreateInfo`
- https://vkdoc.net/man/VkDeviceCreateInfo
    - `.sType` 🟪 `VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO`
    - `.pNext` 🪐 `nullptr`
        - 🪐 almost any EXT that you are gonna enable.... is prolly gonna end up being passed on here.... tied to `VkDeviceCI` 💁‍♀️
    - `.flags` 🏴 `0`
        - 🏴: "No Flag" 
        - `VkSpecs` Says:- `reserved for future use`
        </br>

    - `.pQueueCreateInfos` 🔗 _**SubChapter 5**_
        - Multiple Queue Create Infos:- 🟨 **_Chapter2.8_**
    - `.ppEnabledLayerNames` ⚠️ _deprecated [by Vulkan]_
    - `.ppEnabledExtensionNames` 🟨 **_Chapter4.2_**
    - `.pEnabledFeatures` 🟨 **ChapterZZZ**
        - This should be really interesting

- ##### 📜 REY_DOCs
    - `.pQueueCreateInfos` -> yes, you 'can' pass multiple 😉
    - Sometimes there will be `.zzzCreateInfoCount` & `.pZZZCreateInfos` 
        - So you could like pass in an array/vector
        - You will see this in lots of other places

- ##### `📽️ So far, The result`:- 
    - [4.guide.chapter2.3.midway.hh](./examples/4.guide.chapter2.3.midway.hh)






















<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
<div align=center style="font-size: 50px; font-family: 'Iosevka Curly'; ">Page-Break</div>
</div>
<div class="REY_PAGEBREAK"></div>
<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
</div>

















</br>

## 3. 📜 `vkEnumeratePhysicalDevices()`
- https://vkdoc.net/man/vkEnumeratePhysicalDevices
- ##### `</> TheCode`
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
    - `👀 Visualization / [See it] / JSON Printing`:- [4.guide.chapter2.1.json.hh](./examples/4.guide.chapter2.1.json.hh)
    - `📽️ So far, The result`:- [4.guide.chapter2.1.midway.hh](./examples/4.guide.chapter2.1.midway.hh)
    - `🔗 GitHub`:- [amVK_GPUProps.hh](https://github.com/REYNEP/amGHOST/blob/74cf5c96a9b12db4896f2f4c592cfd72923d6231/amVK/utils/amVK_GPUProps.cpp#L5-L17)
</br>




<div align=center>

## 4. 🧊 `amVK_InstanceProps::GetARandom_GPU()`

`</> TheCode` 🔗 `GITHUB` [amVK_InstanceProps.hh#L39](https://github.com/REYNEP/amGHOST/blob/74cf5c96a9b12db4896f2f4c592cfd72923d6231/amVK/utils/amVK_InstanceProps.hh#L39)

</div>
</br>





## 5. 🛠️ `VkDeviceQueueCreateInfo` - *'The Real Deal'*
- https://vkdoc.net/man/VkDeviceQueueCreateInfo
    - `.sType` 🟪 `VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO`
    - `.pNext` 🪐 `nullptr`
        - 🪐 2 Extensions 😉 (will talk about them later)
    - `.flags` 🏳️ `0`
        - 🪐 https://vkdoc.net/man/VkDeviceQueueCreateFlagBits | [ivirtex-github](https://github.com/ivirtex/vulkan-hover-docs/tree/master/vscode_ext/vulkan_man_md_pages/VkDeviceQueueCreateFlagBits.md)
        - 🚩: "Only Option" 
            - `VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT` [Protected Queue]
        </br>
        
    - `.queueFamilyIndex` 🔗 _**Next 3 SubChapters**_
        - `vkGetPhysicalDeviceQueueFamilyProperties()` --> look for a QueueFamily that supports `VK_QUEUE_GRAPHICS_BIT`
        </br>
 
    - `.queueCount` 🟪 `1` [Specify, how many you need 💁‍♀️]
    </br>
 
    - `.pQueuePriorities` --> yes, this can be multiple "Priorities" 🥴 [idk yet why tho]
        - Range = (0.0 -> 1.0) [inclusive]
        - Within the same device, queues with higher priority may be allotted more processing time than queues with lower priority.
        </br>

- ##### `📽️ So far, The result`:-
    - We are gonna take a Big Leap & Start connecting to 🔗 `GITHUB`
    - [amVK_DeviceQCI.hh](https://github.com/REYNEP/amGHOST/blob/1f6bfe014c42962f935a546c39ddb237ff99d002/amVK/core/amVK_DeviceQCI.hh#L9-L15)

</br>
</br>

















<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
<div align=center style="font-size: 50px; font-family: 'Iosevka Curly'; ">Page-Break</div>
</div>
<div class="REY_PAGEBREAK"></div>
<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
</div>



















</br>
</br>

## 6. 📜 `vkGetPhysicalDeviceQueueFamilyProperties()`
</br>

- https://vkdoc.net/man/vkGetPhysicalDeviceQueueFamilyProperties
- ##### 📜 REY_DOCs
    - a GPU can have _"multiple QueueFamilies"_
        - a `QueueFamily` might support `VK_QUEUE_GRAPHICS_BIT`
        - another `QueueFamily` might support `VK_QUEUE_COMPUTE_BIT`
        - another `QueueFamily` might support `VK_QUEUE_TRANSFER_BIT`
        - another `QueueFamily` might support `VK_QUEUE_VIDEO_ENCODE_BIT_KHR`
        - another `QueueFamily` might support a-mixture of multiple
        - talking about this in -> 🔗 _Next SubChapter_
        </br>

- ##### `</> TheCode` [OldWay]
    ```cpp
    #define GPUs                                amVK_InstanceProps::s_HardwareGPU_List
    #define amVK_2D_GPUs_QFAMs                     amVK_Instance::s_HardwareGPU_QFamProps_List2D
    static inline REY_Array<REY_Array<VkQueueFamilyProperties>>   s_HardwareGPU_QFamProps_List2D;
        // REY_Array --> "REY_LoggerNUtils/REY_Utils.hh" 😄
        // 1 System/PC
            // multiple GPU
                // multiple QFamProps
    ```
    ```cpp
    static inline void GetPhysicalDeviceQueueFamilyProperties(void) {
        amVK_2D_GPUs_QFAMs.reserve(GPUs.n);            // malloc using "new" keyword
        for ( uint32_t k = 0;  k < GPUs.n; k++ )       // for each GPU
        {
            REY_Array<VkQueueFamilyProperties> *k_QFamProps = &amVK_2D_GPUs_QFAMs.data[k];

            uint32_t QFamCount = 0;
                vkGetPhysicalDeviceQueueFamilyProperties(GPUs[k], &QFamCount, nullptr);

            k_QFamProps->n = QFamCount;
            k_QFamProps->data = new VkQueueFamilyProperties[QFamCount];
                vkGetPhysicalDeviceQueueFamilyProperties(GPUs[k], &k_QFamProps->n, k_QFamProps->data);
        }
        #undef GPUs
    }
    ```
    - `👀 Visualization / [See it] / JSON Printing`:- [4.guide.chapter2.5.json.hh](./examples/4.guide.chapter2.5.json.hh)
        - Check the [3070 JSON by REY](./examples/4.guide.chapter2.5.data.json)
    - `📽️ So far, The result`:- **_[OldWay]_** [4.guide.chapter2.5.amVK_Instance.hh](./examples/4.guide.chapter2.5.amVK_Instance.hh)
        - Compare to -> [4.guide.chapter2.1.midway.hh](./examples/4.guide.chapter2.1.midway.hh)
            - `2DArray_QFAM_Props` part & below were added only compared to `Chapter2.1.`
            </br>
            </br>

- ##### `📽️ So far, The result`:- 🔗 `GITHUB` [NewWay]
    - [amVK_GPUProps.hh](https://github.com/REYNEP/amGHOST/blob/1f6bfe014c42962f935a546c39ddb237ff99d002/amVK/utils/amVK_GPUProps.hh)
    - [amVK_GPUProps.cpp#L5-L17](https://github.com/REYNEP/amGHOST/blob/1f6bfe014c42962f935a546c39ddb237ff99d002/amVK/utils/amVK_GPUProps.cpp#L5-L17)




















<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
<div align=center style="font-size: 50px; font-family: 'Iosevka Curly'; ">Page-Break</div>
</div>
<div class="REY_PAGEBREAK"></div>
<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
</div>





















## 7. 🏷️ `VkQueueFamilyProperties`
- https://vkdoc.net/man/VkQueueFamilyProperties
- ##### 📜 REY_DOCs
    - `.queueFlags` 
        - we are gonna choose a `QCI.queueFamilyIndex` based on these flags
        - primarily, for the least, we wanna choose a `QueueFamily` that supports `VK_QUEUE_GRAPHICS_BIT`
        - all kinds of amazing things can be done using 
            - `VK_QUEUE_COMPUTE_BIT`
            - `VK_QUEUE_TRANSFER_BIT`
            - `VK_QUEUE_VIDEO_ENCODE_BIT_KHR`
    - `.queueCount` 
        - yes there is a limit to 'how many `Queues` we are allowed to work with' 🥴
    - `.timestampValidBits`
    - `.minImageTransferGranularity`
</br>



## 8. `VkDeviceQCI.queueFamilyIndex` [OldWay]
- `🎯 Task` 
    - is to choose a `QueueFamily` that supports `VK_QUEUE_GRAPHICS_BIT` 😉
    - (if you've followed on so far -> this should be easy 😉) 
- ##### `</> amVK_Device.hh`
    ```cpp
    void amVK_Device::Select_QFAM_GRAPHICS(void) {
        if (!amVK_Instance::called_GetPhysicalDeviceQueueFamilyProperties) {
            amVK_Instance::EnumeratePhysicalDevices();
        }

        if (!amVK_Instance::called_GetPhysicalDeviceQueueFamilyProperties) {
            amVK_Instance::GetPhysicalDeviceQueueFamilyProperties();
        }

        amVK_Instance::amVK_PhysicalDevice_Index index = amVK_HEART->GetARandom_PhysicalDevice_amVK_Index();
        this->QCI.Default.queueFamilyIndex = amVK_Instance::ChooseAQueueFamily(VK_QUEUE_GRAPHICS_BIT, index); 
            // If you wanna see the implementation for this function
    }
    ```
    - `📽️ So far, The result`:- _**OldWay**_ (Don't spend time inside this, more than 1 minute)
        - [4.guide.chapter2.9.Props.hh](./examples/4.guide.chapter2.9.Props.hh)
        - [4.guide.chapter2.9.amVK.cpp](./examples/4.guide.chapter2.9.amVK.cpp)
        </br> 
    - `📽️ So far, The result`:- _**NewWay**_ 🔗 `GITHUB` (NewWay is like 10x more organized and easier to understand)
        - [amVK_GPUProps.hh](https://github.com/REYNEP/amGHOST/blob/1f6bfe014c42962f935a546c39ddb237ff99d002/amVK/utils/amVK_GPUProps.hh)
        - [amVK_GPUProps.cpp#L266-L286](https://github.com/REYNEP/amGHOST/blob/1f6bfe014c42962f935a546c39ddb237ff99d002/amVK/utils/amVK_GPUProps.cpp#L266-L286)
        </br> 



<div align=center>

## 9. 🧊 `REY_CategorizeQueueFamilies()` [NewWay]

`</> TheCode` 🔗 `GITHUB` 
[amVK_GPUProps.hh#L50](https://github.com/REYNEP/amGHOST/blob/74cf5c96a9b12db4896f2f4c592cfd72923d6231/amVK/utils/amVK_GPUProps.hh#L50)
[amVK_GPUProps.cpp#L260](https://github.com/REYNEP/amGHOST/blob/main/amVK/utils/amVK_GPUProps.cpp#L260)

</div>




















<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
<div align=center style="font-size: 50px; font-family: 'Iosevka Curly'; ">Page-Break</div>
</div>
<div class="REY_PAGEBREAK"></div>
<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
</div>



















</br>
</br>
</br>
</br>
</br>
</br>
</br>
</br>
</br>
</br>
</br>
</br>
</br>


## 10. back to 📦 `vkCreateDevice()` finally calling it 😊
- https://vkdoc.net/man/VkDeviceCreateInfo
- ##### `</> main.cpp`
    ```cpp
    amVK_Device* D = new amVK_Device(GPUProps);
        D->CI                           // VkDeviceCreateInfo       [public]
        D->Queues                       // amVK_DeviceQueues        [public] [take a look inside 😜]
        D->add_1D_QFAMs_QCount_USER()   // amVK_DeviceQueues
        D->CreateDevice(1);             // param1 = GraphicsQueueCount = 1
        D->GetDeviceQueues();           //     see:- Queues.TheArrays 😜
        D->Queues.GraphicsQ(0)          // returns   Queues.TheArrays.Graphics[0]
    ```
    - Think of this as a PSeudoCode / or / check out my code if you wanna
    - `CreateInfo` => By default has initial values inside `amVK_Device`
    </br>


<div align=center>

## 11. 🧊 `amVK_DeviceQueues`
🔗 [amVK_DeviceQueues.hh](https://github.com/REYNEP/amGHOST/blob/74cf5c96a9b12db4896f2f4c592cfd72923d6231/amVK/core/amVK_DeviceQueues.hh)

</div>






















<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
<div align=center style="font-size: 50px; font-family: 'Iosevka Curly'; ">Page-Break</div>
</div>
<div class="REY_PAGEBREAK"></div>
<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
</div>



















</br>
</br>
</br>
</br>

## 🟪 eXtras / TheEnd
#### 11. multiple `VkDeviceCreateInfo.pQueueCreateInfos`
- [VUID-VkDeviceCreateInfo-queueFamilyIndex-02802](https://vkdoc.net/man/VkDeviceCreateInfo#VUID-VkDeviceCreateInfo-queueFamilyIndex-02802)
    - The `.queueFamilyIndex` member of each element of `.pQueueCreateInfos` must be unique 💁‍♀️
    </br>
 
    - So, randomly `push_back()`ing without any kinda safety ➡️ kinda feels absurd. 💁‍♀️ doesn't it? .... e.g.
        ```cpp
        /* ============ REY_LoggerNUtils::REY_Utils.hh ============ */
        REY_ArrayDYN<VkDeviceQueueCreateInfo> Array = REY_ArrayDYN<VkDeviceQueueCreateInfo>(2);
            REY_ARRAY_PUSH_BACK(Array) = this->Default_QCI;
            REY_ARRAY_PUSH_BACK(Array) =          Your_QCI;
        ```
        - ##### [OldWay]:- [amVK_DeviceQCI.hh](https://github.com/REYNEP/amGHOST/blob/1f6bfe014c42962f935a546c39ddb237ff99d002/amVK/core/amVK_DeviceQCI.hh#L19) 
  
    - So what i did is:- to introduce a `QCount` array as per `QFamily` 💁‍♀️
        - ##### [NewWay]:- [amVK_DeviceQueues.hh#L56](https://github.com/REYNEP/amGHOST/blob/74cf5c96a9b12db4896f2f4c592cfd72923d6231/amVK/core/amVK_DeviceQueues.hh#L56)

    - & then have a function for the user to increase the `QCount`
        - ##### [NewWay]:- 🔗 `GITHUB_WIP` --> `amVK_Device::add_1D_QFAMs_QCount_USER()`

12. #### OldWay 📆 `March, 2025`
    1. `class amVK_InstanceProps`
        - `EnumeratePhysicalDevices()`
        - `GetPhysicalDeviceQueueFamilyProperties()`

    - (Don't spend time inside this, more than 1 minute)
        - 📝 [4.guide.chapter2.9.Props.hh](./examples/4.guide.chapter2.9.Props.hh)
        - 📝 [4.guide.chapter2.9.amVK.cpp](./examples/4.guide.chapter2.9.amVK.cpp)

    - https://github.com/REYNEP/amGHOST/tree/3e44b982902a3f3fa4ac584aefb19da3d4cdfcc6

13. #### NewWay 📆 `May, 2025`
    - 🔗 `GITHUB` (**NewWay** is like 10x more organized and easier to understand)
        - 📝 [amVK_GPUProps.hh](https://github.com/REYNEP/amGHOST/blob/1f6bfe014c42962f935a546c39ddb237ff99d002/amVK/utils/amVK_GPUProps.hh)
        - 📝 [amVK_GPUProps.cpp#L266-L286](https://github.com/REYNEP/amGHOST/blob/1f6bfe014c42962f935a546c39ddb237ff99d002/amVK/utils/amVK_GPUProps.cpp#L266-L286)
        </br> 

14. `vkGetPhysicalDeviceProperties()` 🟨 **Chapter11**
15. GetFeatures 🟨 **Chapter11**
16. MemoryTypes 🟨 **Chapter11**
17. Guide on `amVK_Array` 🟨 ***Chapter6.6***