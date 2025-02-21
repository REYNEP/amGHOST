## Structure
```ruby
    |- .forge = for now it is quite empty
    |- .install = `cmake install`
    |- CMakeFiles
        |- REY_FetchV4 from REY_LoggerNUtils
    |- intern
    |- REY_LoggerNUtils:- [GIT-SUBMODULE] /see ## libraries section in this doc
```


## Libraries / Modules / External Stuffs [.forge]
1. `REY_LoggerNUtils`:- [GIT-SUBMODULE]
    - even tho it's a git-submodule. we fetch/grab/do-shits using CMAKE Scripts like `.forge/CMakeFiles/REY_FetchV4_REY_LoggerNUtils.cmake` instead of `git submodule --update --init`

## Common Principles I Followed
1. Logs are better than RETURN VALUES. 
    - The way that we need to check RETURN VALUES of every single VULKAN FUNCTION. Wrapping every vulkan function call around with a RESULT/VK_CHECK wrapper.... is exactly what led me to take this decision.