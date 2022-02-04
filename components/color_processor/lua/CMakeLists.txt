# Download sources
ExternalProject_Add(lua
   URL "https://www.lua.org/ftp/lua-5.3.5.tar.gz"
   CONFIGURE_COMMAND ""
   BUILD_COMMAND ""
   BUILD_ALWAYS true
   BUILD_IN_SOURCE true
   INSTALL_COMMAND ""
)

ExternalProject_Get_property(lua SOURCE_DIR)

add_library(liblua STATIC)

target_sources( liblua PUBLIC
   ${SOURCE_DIR}/src/lapi.c
   ${SOURCE_DIR}/src/lauxlib.c
   ${SOURCE_DIR}/src/lbaselib.c
   ${SOURCE_DIR}/src/lbitlib.c
   ${SOURCE_DIR}/src/lcode.c
   ${SOURCE_DIR}/src/lcorolib.c
   ${SOURCE_DIR}/src/lctype.c
   ${SOURCE_DIR}/src/ldblib.c
   ${SOURCE_DIR}/src/ldebug.c
   ${SOURCE_DIR}/src/ldo.c
   ${SOURCE_DIR}/src/ldump.c
   ${SOURCE_DIR}/src/lfunc.c
   ${SOURCE_DIR}/src/lgc.c
   ${SOURCE_DIR}/src/linit.c
   ${SOURCE_DIR}/src/liolib.c
   ${SOURCE_DIR}/src/llex.c
   ${SOURCE_DIR}/src/lmathlib.c
   ${SOURCE_DIR}/src/lmem.c
   ${SOURCE_DIR}/src/loadlib.c
   ${SOURCE_DIR}/src/lobject.c
   ${SOURCE_DIR}/src/lopcodes.c
   ${SOURCE_DIR}/src/loslib.c
   ${SOURCE_DIR}/src/lparser.c
   ${SOURCE_DIR}/src/lstate.c
   ${SOURCE_DIR}/src/lstring.c
   ${SOURCE_DIR}/src/lstrlib.c
   ${SOURCE_DIR}/src/ltable.c
   ${SOURCE_DIR}/src/ltablib.c
   ${SOURCE_DIR}/src/ltm.c
   #${SOURCE_DIR}/src/lua.c
   #${SOURCE_DIR}/src/luac.c
   ${SOURCE_DIR}/src/lundump.c
   ${SOURCE_DIR}/src/lutf8lib.c
   ${SOURCE_DIR}/src/lvm.c
   ${SOURCE_DIR}/src/lzio.c
)

target_include_directories(liblua PUBLIC "${SOURCE_DIR}/src")