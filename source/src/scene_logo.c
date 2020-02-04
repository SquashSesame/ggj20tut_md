#include "main.h"

#include "gfx.h"
#include "music.h"

void initScene_Logo()
{
    u16 ind = 0;

    // load background
    ind = TILE_USERINDEX;
    VDP_drawImageEx(
        BPLAN,
        &ggj_logo,
        TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += ggj_logo.tileset->numTile;


    // VDP process done, we can re enable interrupts
    SYS_enableInts();


    // prepare palettes
    memcpy(&palette[0], ggj_logo.palette->data, 32);
}

void updateScene_Logo()
{

}

void exitScene_Logo()
{

}

