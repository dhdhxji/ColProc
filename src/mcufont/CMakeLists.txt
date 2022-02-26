include("../../CPM.cmake")

CPMAddPackage("gh:mcufont/mcufont#master")

add_library(mcufont)
target_sources(
    mcufont PUBLIC
    "${mcufont_SOURCE_DIR}/decoder/mf_encoding.c"
    "${mcufont_SOURCE_DIR}/decoder/mf_font.c"
    "${mcufont_SOURCE_DIR}/decoder/mf_justify.c"
    "${mcufont_SOURCE_DIR}/decoder/mf_kerning.c"
    "${mcufont_SOURCE_DIR}/decoder/mf_rlefont.c"
    "${mcufont_SOURCE_DIR}/decoder/mf_bwfont.c"
    "${mcufont_SOURCE_DIR}/decoder/mf_scaledfont.c"
    "${mcufont_SOURCE_DIR}/decoder/mf_wordwrap.c"
)

target_include_directories(
    mcufont PUBLIC
    "fonts"
    "${mcufont_SOURCE_DIR}/decoder/"
)