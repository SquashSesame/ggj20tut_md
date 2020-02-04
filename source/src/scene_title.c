#include "main.h"

#include "gfx.h"
#include "music.h"

void initScene_Title()
{
    u16 ind = 0;

    // load background
    ind = TILE_USERINDEX;
    VDP_drawImageEx(
        BPLAN,
        &title,
        TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += title.tileset->numTile;


    // VDP process done, we can re enable interrupts
    SYS_enableInts();


    // prepare palettes
    memcpy(&palette[0], title.palette->data, 32);
}

