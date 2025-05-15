---
export_on_save:
  prince: false
---
<div align=center>

![svg1](./CH0.TITLE.svg)
## Chapter 0: Prerequisites 📹

</div>


#### 📖 Suggested Reading (before embarking on this journey)
1. Brendan Galea's Vulkan C++ [Youtube Series]
    - 🔗 https://www.youtube.com/watch?v=Y9U9IE0gVHA&list=PL8327DO66nu9qYVKLDmdLW_84-yE4auCR
    - For now, just watch the first `3:40minute` video 💁‍♀️
        - I don't recommend going down the playlist, right now, tho.
 
2. Alternatively:- https://paminerva.github.io/docs/LearnVulkan/01.A-Hello-Window
    - Read the `1 - Introduction` part from here only 😊 [untill `1.2. Why Vulkan?` end]
    - 😉 [P1_P.A.Minerva_LearnVulkan_PDF/00-Introduction-and-prerequisites.pdf](./../V3.EverythingEverywhereAllAtOnce/P1_P.A.Minerva_LearnVulkan_PDF/00-Introduction-and-prerequisites.pdf)
    - 😜 [P1_P.A.Minerva_LearnVulkan_PDF/01.A-Hello-Window.pdf](./../V3.EverythingEverywhereAllAtOnce/P1_P.A.Minerva_LearnVulkan_PDF/01.A-Hello-Window.pdf)

3. Alternatively:- you can give this page a try too:- 
    - https://vkdoc.net/chapters/fundamentals
    - that is, if you are into _"official formal-documentation"_ [i sure am not....]
    </br> 


#### 🙋🏻‍♀️ The 5 Questions
- 1️⃣ What is `Vulkan`? ....🤔.... Why `Vulkan`?
    - 🔗 _Suggested Reading 2_:- `p.a.minerva`
- 2️⃣ Why should **_'you'_** learn/use `Vulkan`?
    1. _**5-10% Faster**_
    2. _**More Control**_
    3. _**Lower Level API**_
    4. You can ask and know _**'what actuaaallyyy happens under the hood of the gpu?'**_
 
- 3️⃣ Why is this Important?
    - _Well if you are planning on becoming a game dev, then yeah, this kinda is important!_
    - _**otherwise**_, if you are just here for **CreatingShaders**:- `OpenGL` is fine enough
        1. `Shader Enthusiast:- `https://www.shadertoy.com/
            1. https://www.youtube.com/playlist?list=PL9Zb80ovNLWGRFZVL4LcckTWnEGN73dFS
            2. https://www.youtube.com/playlist?list=PLGmrMu-IwbguU_nY2egTFmlg691DN7uE5
            3. https://www.youtube.com/playlist?list=PLCAFZV4XJzP-jGbTke6Bd3PNDpP1AbIKo
            4. https://www.youtube.com/playlist?list=PLGmrMu-IwbgtMxMiV3x4IrHPlPmg7FD-P
            5. https://www.youtube.com/watch?v=5J-0sy2pu_8&t=357s&pp=ygUVc2hhZGVyVG95IHJheW1hcmNoaW5n
            6. https://www.youtube.com/watch?v=khblXafu7iA&pp=ygUJc2hhZGVyVG95
        2. `Making an App/UI :-` doing everything with `OpenGL` -> would be just fine
            1. [TheCherno OpenGL Playlist [YT]](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)
            2. [TheCherno Game Engine Playlist [YT]](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)
            </br> 

- 4️⃣ When will **_'you'_** need `vulkan`?
    - kinda never  ->  unless you have grown tired of OpenGL
    - kinda   yes  ->  when you wanna understand "How the heck does the GPU Work?"
        - but yes, Big AAA games would need `vulkan` for even that last 5-10% performance

- 5️⃣ How does `vulkan` work?
    - Rest of this entire guide is dedicated to answer this question 😊

<!-- ---------------------------------- OLD VERSION ----------------------------------
#### 🙋🏻‍♀️ `The 5 Questions`
1. What is `Vulkan`? ....🤔.... Why `Vulkan`?
    - `Suggested Reading 1:- p.a.minerva`
2. Why should **_'you'_** learn/use `Vulkan`?
    1. _**5-10% Faster**_
    2. _**More Control**_
    3. _**Lower Level API**_
    4. You can ask and know _**'what actuaaallyyy happens under the hood of the gpu'**_
    </br>
 
3. Why is this Important?
    - _Well if you are planning on becoming a game dev, then yeah, this kinda is important!_
    - _**otherwise**_, if you are just here for **CreatingShaders**:- `OpenGL` is fine enough
        1. `Shader Enthusiast:- `https://www.shadertoy.com/
            1. https://www.youtube.com/playlist?list=PL9Zb80ovNLWGRFZVL4LcckTWnEGN73dFS
            2. https://www.youtube.com/playlist?list=PLGmrMu-IwbguU_nY2egTFmlg691DN7uE5
            3. https://www.youtube.com/playlist?list=PLCAFZV4XJzP-jGbTke6Bd3PNDpP1AbIKo
            4. https://www.youtube.com/playlist?list=PLGmrMu-IwbgtMxMiV3x4IrHPlPmg7FD-P
            5. https://www.youtube.com/watch?v=5J-0sy2pu_8&t=357s&pp=ygUVc2hhZGVyVG95IHJheW1hcmNoaW5n
            6. https://www.youtube.com/watch?v=khblXafu7iA&pp=ygUJc2hhZGVyVG95
        2. `Making an App/UI :-` doing everything with `OpenGL` -> would be just fine
            1. [TheCherno OpenGL Playlist [YT]](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)
            2. [TheCherno Game Engine Playlist [YT]](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)
            </br> 

4. When will "You" need `vulkan`?
    - kinda never  ->  unless you have grown tired of OpenGL
    - kinda   yes  ->  when you wanna understand "How the heck does the GPU Work?"
        - but yes, Big AAA games would need `vulkan` for even that last 5-10% performance
        </br>

5. How does `vulkan` work?
    - Rest of this entire guide is dedicated to answer this question 😊
---------------------------------- OLD VERSION ---------------------------------- -->




















<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
<div align=center style="font-size: 50px; font-family: 'Iosevka Curly'; ">Page-Break</div>
</div>
<div class="REY_PAGEBREAK"></div>
<div class="REY_NOSHOW_PDF">

-------------------------------------------------------------------
</div>


















#### 1. 🫳 grab `vulkan-sdk`, `cmake`, `amGHOST`
1. if you don't have `vscode` & `C++ Compiler` 
    - ➡️🔗 [4.guide.CH0.vscode.md](./4.guide.CH0.vscode.md)  
   </br>

2. 📥 https://vulkan.lunarg.com/sdk/home
    - make sure `VULKAN_SDK` & `VK_SDK_PATH` environment variables are set
    - restart vscode after installing
    </br>
 
3. 📥 https://cmake.org/download/
    - 🎓 `Intro/Tutorials`
        - https://enccs.github.io/intro-cmake/hello-cmake/
        - `OR`: Watch 6/7 videos from this playlist:- 
            - https://www.youtube.com/playlist?list=PLK6MXr8gasrGmIiSuVQXpfFuE1uPT615s
            </br>
 
    - restart vscode after installing
    - ##### `📜 REY_DOCs`
        - This is how it usually looks. Read through it 💁‍♀️. 
        - The app that we will make using `amGHOST`, will need to have these commands
        ```cmake
        cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

        project("idk_PROJECT" VERSION 0.1)

            set(CMAKE_CXX_STANDARD 23)
            set(CMAKE_CXX_STANDARD_REQUIRED ON)

        # --------------------
            set(SRC
                "main.cpp"
            )

            set(INC
                ${CMAKE_CURRENT_SOURCE_DIR}
            )
        # --------------------

        # --------------------
        # set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS "/P /C")     
        # Output Preprocessed File
                    add_executable (idk ${SRC})
        target_include_directories (idk PUBLIC ${INC})

        # ------amGHOST-------
                 add_subdirectory  (amGHOST)
            target_link_libraries  (idk PUBLIC amGHOST)

        # ------install-------
            install(TARGETS idk
                DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
        ``` 
        </br>
        

4. `amGHOST`
    - _amateur's Generic Handy Operating System Toolkit_
        - [secretly inspired by `blender's GHOST` xP 😜] 
    - `git clone -b win32-intro https://github.com/REYNEP/amGHOST`
    - Open it with VSCode
    - `F1` --> `CMake: Configure`
    - `F1` --> `CMake: Build`
    - `F1` --> `CMake: Install` --> `.insall` dir
    - check's _**amGHOST's Usage Example**_ inside `amGHOST/README.md`
        - `Option 1`:- use `cmake` for your project too.... using `add_subdirectory(amGHOST)`
        - `Option 2`:- use `libamGHOST.lib` after installing & `#include amGHOST/<header>`
    - just copy paste _**amGHOST's Usage Example**_ into a `main.cpp` for your program
        ```cpp
        #include "amGHOST/amGHOST_System.hh"

        int main(int argumentCount, char* argumentVector[]) 
        {
            amGHOST_System::create_system();    // initializes amG_HEART
            
            amGHOST_Window* W = amG_HEART->new_window_interface();
            W->create(L"Whatever", 0, 0, 500, 600);

            REY::cin.get();     // wait for terminal input
            W->destroy();
        }
        ``` 
        - [shorter than `readme ex. 1`]
        - now you shall have a OS-Window 😊
        </br>
        </br>

5. Viewing these readmes in a Nice Way
    - https://github.com/REYNEP/amGHOST/blob/main/amVK_Guide/P1/bkup/style-bkup.less
    - `vscode extension`:- shd101wyy.markdown-preview-enhanced
    - `scoop install princexml`
    - `vscode F1`:- Markdown Preview Enhanced:- Customize CSS (Global)
    - Paste my `style-bkup.less`
    - `vscode F1`:- Markdown Preview Enhanced:- Open Preview 💁‍♀️