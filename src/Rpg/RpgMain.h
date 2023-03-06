#ifndef RPG_MAIN_H
#define RPG_MAIN_H
#include "RpgResources.h"
#include "World.h"
#include "Chunk.h"
#include "SpriteRpg.h"
#include "Camera.h"

#include "../ParticuleEngine/ParticuleEngine.h"
#include "../ParticuleEngine/Resources.h"
#include "../InterfaceSystem/InterfaceSystem.h"
#include "../InterfaceSystem/EventDataSystem.h"

void RpgInit();

void RpgLoop();

void RpgExit();

#endif