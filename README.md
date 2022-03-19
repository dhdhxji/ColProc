# ColProc
ColProc is a simple rendering library to implement declarative-style graphics. ColProc allows You to define all rendering units and bind them to achieve amazing visual interaction.

## Constructing blocks
There are two fundamental concepts for ColProc: 
- All rendering units should be as simple as possible. Every ColProc responds only for one specific thing and can be united to rendering three.
- Data provided to rendering tree nodes should be determined on the initialization step and can be retrieved anytime while rendering.

## Usage
ColProc has a native c++ interface to interact with it, but a more flexible way to deal with the library - use Lua runtime, which provides bindings to the library. Only one disadvantage of using Lua - a very large code footprint (around 8MB without optimizations and 3MB with size optimization), which is not allowed for microcontrollers (not for all). 

Bindings for Lua will be generated automatically on the project build. The Lua interpreter will be embedded in this library, so it is almost dependency-free (all other dependencies will be downloaded automatically, so there is no need to handle it).

### Installation
ColProc distributed as cmake library. You can add it to Your like a regular cmake library, but some build dependencies should be satisfied:
- Compiler with c++17 support
- libclang (installation depends on Your pkg manager, `apt install libclang` for Ubuntu)
- python3 with libclang bindings 
    ```
    pip3 install clang
    ```
### Examples
Examples can be found in [examples](examples) directory. It contains both the native c++ example and Lua-runtime example.