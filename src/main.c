#include "ParticuleEngine/ParticuleEngine.h"
#include "ParticuleEngine/Resources.h"
#include "Rpg/SpriteRpg.h"
#include "InterfaceSystem/InterfaceSystem.h"
#include "InterfaceSystem/EventDataSystem.h"

#include "Rpg/World.h"

#include "testMain.h"

int main(){//int argc, char *argv[]) {
    PC_Init();
    initEventDataSystem();
    //////////////////////////////////////////
    //LoopTest();
    //ExampleDrawRpg();
    ExampleDrawUI();
    //////////////////////////////////////////
    PC_Quit();
    return 0;
}