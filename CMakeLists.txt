# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.15)
project(MyAddin)

include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.1 REQUIRED)

set(SOURCES
  #/*<SRC>*/
    src/main.c
    src/ParticuleEngine/ParticuleEngine.c
    src/ParticuleEngine/ParticuleEngine.h
    src/ParticuleEngine/ParticuleEngineDraw.c
    src/ParticuleEngine/ParticuleEngineDraw.h
    src/ParticuleEngine/ParticuleEngineFont.c
    src/ParticuleEngine/ParticuleEngineFont.h
    src/ParticuleEngine/ParticuleEngineInput.c
    src/ParticuleEngine/ParticuleEngineInput.h
    src/ParticuleEngine/ParticuleEngineTexture.c
    src/ParticuleEngine/ParticuleEngineTexture.h
    src/ParticuleEngine/Resources.c
    src/ParticuleEngine/Resources.h
    Libs/List/List.c
    Libs/List/List.h
#/*</SRC>*/
  # ...
)
# Shared assets, fx-9860G-only assets and fx-CG-50-only assets
set(ASSETS
  # ...
)
set(ASSETS_fx
  #/*<IMG_FX>*/

#/*</IMG_FX>*/
)
set(ASSETS_cg
  #/*<IMG_CG>*/
assets/assets-cg/Images/test.png
#/*</IMG_CG>*/
  # ...
)

include_directories(Libs/List)
link_directories(Libs/List)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

add_executable(myaddin ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(myaddin PRIVATE -Wall -Wextra -Os)
target_link_libraries(myaddin Gint::Gint "${CMAKE_CURRENT_SOURCE_DIR}/libsupc++.a")

#/*<NAME_APP_FIELD>*/
set(NAME_APP "Engine")
#/*</NAME_APP_FIELD>*/

#/*<DIR_OUT_FIELD>*/
set(DIR_OUT "bin")
#/*</DIR_OUT_FIELD>*/

if("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G)
  generate_g1a(TARGET myaddin OUTPUT "${DIR_OUT}/${NAME_APP}.g1a"
    NAME "${NAME_APP}" ICON assets/assets-fx/icon.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCG50)
  generate_g3a(TARGET myaddin OUTPUT "${DIR_OUT}/${NAME_APP}.g3a"
    NAME "${NAME_APP}" ICONS assets/assets-cg/icon-uns.png assets/assets-cg/icon-sel.png)
endif()
