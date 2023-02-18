# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.15)
project(MyAddin)

include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.1 REQUIRED)

set(SOURCES
  ModeraWorldRPG/Sources/main.cpp
  ModeraWorldRPG/Sources/List.hpp
  ModeraWorldRPG/Sources/ParticuleBase.cpp
  ModeraWorldRPG/Sources/ParticuleBase.hpp
  ModeraWorldRPG/Sources/Ressources.cpp
  ModeraWorldRPG/Sources/Ressources.hpp
  ModeraWorldRPG/Sources/Tilesets.cpp
  ModeraWorldRPG/Sources/Tilesets.hpp
  ModeraWorldRPG/Sources/Map.cpp
  ModeraWorldRPG/Sources/Map.hpp
  ModeraWorldRPG/Sources/GameManager.cpp
  ModeraWorldRPG/Sources/GameManager.hpp
  # ...
)
# Shared assets, fx-9860G-only assets and fx-CG-50-only assets
set(ASSETS
  # ...
)
set(ASSETS_fx
  assets-fx/font.png
  # ...
)
set(ASSETS_cg
  #/*<IMG_CASIO>*/
assets-cg/Tilesets/Dungeon_A1.png
assets-cg/Tilesets/Dungeon_A2.png
assets-cg/Tilesets/Dungeon_A4.png
assets-cg/Tilesets/Dungeon_A5.png
assets-cg/Tilesets/Dungeon_B.png
assets-cg/Tilesets/Dungeon_C.png
assets-cg/Tilesets/Inside_A1.png
assets-cg/Tilesets/Inside_A2.png
assets-cg/Tilesets/Inside_A4.png
assets-cg/Tilesets/Inside_A5.png
assets-cg/Tilesets/Inside_B.png
assets-cg/Tilesets/Inside_C.png
assets-cg/Tilesets/Outside_A1.png
assets-cg/Tilesets/Outside_A2.png
assets-cg/Tilesets/Outside_A3.png
assets-cg/Tilesets/Outside_A4.png
assets-cg/Tilesets/Outside_A5.png
assets-cg/Tilesets/Outside_B.png
assets-cg/Tilesets/Outside_C.png
assets-cg/Tilesets/World_A1.png
assets-cg/Tilesets/World_A2.png
assets-cg/Tilesets/World_B.png
assets-cg/Tilesets/World_C.png
#/*</IMG_CASIO>*/
  # ...
)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

add_executable(myaddin ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(myaddin PRIVATE -Wall -Wextra -Os)
target_link_libraries(myaddin Gint::Gint "${CMAKE_CURRENT_SOURCE_DIR}/libsupc++.a")

if("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G)
  generate_g1a(TARGET myaddin OUTPUT "ModeraW.g1a"
    NAME "ModeraWorld" ICON assets-fx/icon.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCG50)
  generate_g3a(TARGET myaddin OUTPUT "ModeraW.g3a"
    NAME "ModeraWorld" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
endif()
