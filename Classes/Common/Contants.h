//
//  Contants.h
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#ifndef MyCppGame_Contants_h
#define MyCppGame_Contants_h
#include "TypeDefine.h"

const unsigned long MAX_PATH_LENGTH = 128UL;

const float MIN_ACTION_CYLE_TIME = 0.01f;
const USIZE GAME_MAP_LAYER_LEVEL = 1000;
const USIZE GAME_PLAYER_LAYER_LEVEL = 2000;
const USIZE GAME_HUD_LAYER_LEVEL = 3000;

const USIZE CONFIG_ROLEMANAGER_SIZE = 4096;

const float WIN_WIDTH = 480;
const float WIN_HEIGHT = 320;

const float VALID_MIN_MAP_X = WIN_WIDTH/4;
const float VALID_MAX_MAP_X = WIN_WIDTH*3/4;

const float MAP_POS_X = WIN_WIDTH / 2;
const float MAP_POS_Y = WIN_HEIGHT / 2;
const int MAP_Z_INDEX_GAME_LAYER = 0;

const float HERO_POS_X = WIN_WIDTH / 2;
const int HERO_Z_INDEX_GAME_LAYER = 10;

const float ENEMY_SPAWN_INTERVAL = 3.0f;
const int ENEMY_Z_INDEX_GAME_LAYER = 20;

const int GAME_LAYER_Z_INDEX = 10;
const int HUD_LAYER_Z_INDEX = 20;

const int ID_ACTION_MOVING = 1;
const int ID_ACTION_JUMPING = 2;
const int ID_ACTION_SKILLING = 2;

#endif
