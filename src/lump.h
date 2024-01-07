#pragma once

#include "wad.h"

#include <stdint.h>

struct Thing {        // THINGS
    int16_t x;
    int16_t y;
    int16_t face_angle;   // EAST = 0, NORTH = 90, WEST = 180, SOUTH = 270
    int16_t type;
    int16_t flags;
};

enum THING_TYPE {
    UNUSED1                 = 0xFFFF,
    UNUSED2                 = 0x0000,

    P1_START                = 0x0001,
    P2_START                = 0x0002,
    P3_START                = 0x0003,
    P4_START                = 0x0004,

    DEATHMATCH_START        = 0x000B,
    TELEPORT_LANDING        = 0x000E,

    FORMER_HUMAN            = 0x0BBC,
    WOLF_SS                 = 0x0054,
    FORMER_HUMAN_SERGEANT   = 0x0009,
    HEAVY_WEAPON_DUDE       = 0x0041,
    IMP                     = 0x0BB9,
    DEMON                   = 0x0BBA,
    SPECTRE                 = 0x003A,
    LOST_SOUL               = 0x0BBE,
    CACODEMON               = 0x0BBD,
    HELL_KNIGHT             = 0x0045,
    BARON_OF_HELL           = 0x0BBB,
    ARACHNOTRON             = 0x0044,
    PAIN_ELEMENTAL          = 0x0047,
    REVENANT                = 0x0042,
    MANCUBUS                = 0x0043,
    ARCH_VILE               = 0x0040,
    SPIDER_MASTERMIND       = 0x0007,
    CYBER_DEMON             = 0x0010,

    BOSS_BRAIN              = 0x0058,
    BOSS_SHOOTER            = 0x0059,
    SPAWN_SHOT              = 0x0057,

    CHAINSAW                = 0x07D5,
    SHOTGUN                 = 0x07D1,
    SUPER_SHOTGUN           = 0x0052,
    CHAINGUN                = 0x07D2,
    ROCKET_LAUNCHER         = 0x07D3,
    PLASMA_GUN              = 0x07D4,
    BFG                     = 0x07D6,
    AMMO_CLIP               = 0x07D7,
    SHOTGUN_SHELLS          = 0x07D8,
    ROCKET                  = 0x07DA,
    CELL_CHARGE             = 0x07FF,
    AMMO_BOX                = 0x0800,
    SHELLS_BOX              = 0x0801,
    ROCKET_BOX              = 0x07FE,
    CELL_CHARGE_PACK        = 0x0011,
    BACKPACK                = 0x0008,

    STIMPAK                 = 0x07DB,
    MEDIKIT                 = 0x07DC,
    HEALTH_POTION           = 0x07DE,
    SPIRIT_ARMOR            = 0x07DF,
    GREEN_ARMOR             = 0x07E2,
    BLUE_ARMOR              = 0x07E3,
    MEGASPHERE              = 0x0053,
    SOULSPHERE              = 0x07DD,
    INVULNERABILITY         = 0x07E6,
    BERSERK                 = 0x07E7,
    INVISIBILITY            = 0x07E8,
    RADIATION_SUIT          = 0x07E9,
    COMPUTER_MAP            = 0x07EA,
    LITE_AMP_GOGGLES        = 0x07FD,

    BLUE_KEYCARD            = 0x0005,
    RED_KEYCARD             = 0x000D,
    YELLOW_KEYCARD          = 0x0006,
    BLUE_SKULLKEY           = 0x0028,
    RED_SKULLKEY            = 0x0026,
    YELLOW_SKULLKEY         = 0x0027,

    BARREL                  = 0x07F3,
    BILLY                   = 0x0048,
    TALL_TECHNO_PILLAR      = 0x0030,
    TALL_GREEN_PILLAR       = 0x001E,
    TALL_RED_PILLAR         = 0x0020,
    SHORT_GREEN_PILLAR      = 0x001F,
    SHORT_GREEN_PILLAR_H    = 0x0024,
    SHORT_RED_PILLAR        = 0x0021,
    SHORT_RED_PILLAR_SKULL  = 0x0025,
    STALAGMITE              = 0x002F,
    BURNT_TREE              = 0x002B,
    LARGE_BROWN_TREE        = 0x0036,

    FLOOR_LAMP              = 0x07EC,
    TALL_TECHNO_FLOOR_LAMP  = 0x0055,
    SHORT_TECHNO_FLOOR_LAMP = 0x0056,
    CANDLE                  = 0x0022,
    CANDELABRA              = 0x0023,
    TALL_BLUE_FIRESTICK     = 0x002C,
    TALL_GREEN_FIRESTICK    = 0x002D,
    TALL_RED_FIRESTICK      = 0x0039,
    BURNING_BARREL          = 0x0046,

    EVIL_EYE                = 0x0029,
    FLOATING_SKULL          = 0x002A,
    HANGING_VICTIM_T1       = 0x0031,
    HANGING_VICTIM_T2       = 0x003F,
    HANGING_VICTIM_A1       = 0x0032,
    HANGING_VICTIM_A2       = 0x003B,
    HANGING_LEGS_1          = 0x0034,
    HANGING_LEGS_2          = 0x003C,
    HANGING_VICTIM_1_LEG_1  = 0x0033,
    HANGING_VICTIM_1_LEG_2  = 0x003D,
    HANGING_LEG_1           = 0x0035,
    HANGING_LEG_2           = 0x003E,
    HANGING_VICTIM_GUTS     = 0x0049,
    HANGING_VICTIM_BRAIN    = 0x004A,
    HANGING_TORSO_DOWN      = 0x004B,
    HANGING_TORSO_SKULL     = 0x004C,
    HANGING_TORSO_UP        = 0x004D,
    HANGING_TORSO_BRAIN     = 0x004E,

    IMPALED_HUMAN           = 0x0019,
    TWITCHING_IMPALED_HUMAN = 0x001A,
    SKULL_POLE              = 0x001B,
    SKULL_SHISH_KEBAB       = 0x001C,
    SKULLS_PILE             = 0x001D,
    BLOODY_MESS_1           = 0x000A,
    BLOODY_MESS_2           = 0x000C,
    BLOOD_POOL_FLESH        = 0x0018,
    BLOOD_POOL_1            = 0x004F,
    BLOOD_POOL_2            = 0x0050,
    BRAIN_POOL              = 0x0051,
    DEAD_PLAYER             = 0x000F,
    DEAD_FORMER_HUMAN       = 0x0012,
    DEAD_FORMER_SERGEANT    = 0x0013,
    DEAD_IMP                = 0x0014,
    DEAD_DEMON              = 0x0015,
    DEAD_CACODEMON          = 0x0016,
    DEAD_LOST_SOUL          = 0x0017,
};

enum THING_FLAG {
    EASY        = 1 << 0,   // THING appears in skill 1, 2
    MEDIUM      = 1 << 1,   // THING appears in skill 3
    HARD        = 1 << 2,   // THING appears in skill 4, 5
    DEAF_GUARD  = 1 << 3,   // indicates a deaf guard
    MP_ONLY     = 1 << 4,   // THING only appears in multiplayer
};

struct Linedef {      // LINEDEFS
    uint16_t start_vertex;
    uint16_t end_vertex;
    uint16_t flags;
    uint16_t line_type;
    uint16_t sector_tag;
    uint16_t right_sidedef;
    uint16_t left_sidedef;
};

enum LINEDEF_FLAG {
    BLOCKING                    = 1 << 0,
    BLOCKS_MONSTERS             = 1 << 1,
    TWO_SIDED                   = 1 << 2,
    UPPER_TEXTURE_UNPEGGED      = 1 << 3,
    LOWER_TEXTURE_UNPEGGED      = 1 << 4,
    SECRET                      = 1 << 5,
    SOUNDBLOCK                  = 1 << 6,
    DONT_DRAW                   = 1 << 7,
    MAPPED                      = 1 << 8,
};

struct Sidedef {      // SIDEDEFS

};

struct Vertex {       // VERTEXES
    int16_t x;
    int16_t y;
};

struct Segment {      // SEGS

};

struct SubSector {    // SSECTORS

};

struct Node {         // NODES

};

struct Sector {       // SECTORS

};

struct Reject {       // REJECT

};

struct Blockmap {     // BLOCKMAP

};
