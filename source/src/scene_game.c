
#include <genesis.h>

#include "gfx.h"
#include "music.h"
#include "main.h"

void initScene_Game()
{
    // start music
    SND_startPlay_XGM(bgm_game);

    u16 ind = 0;

    // load background
    ind = TILE_USERINDEX;
    VDP_drawImageEx(
        APLAN,
        &bg_a,
        TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += bg_a.tileset->numTile;
#if 1
   VDP_drawImageEx(
        BPLAN,
        &bg_b,
        TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += bg_b.tileset->numTile;
#endif

    // VDP process done, we can re enable interrupts
    SYS_enableInts();

// init scrolling
//    updateCamera(FIX32(0), FIX32(0));

    initPlayer();


    // prepare palettes
    memcpy(&palette[0], bg_a.palette->data, 16);
    memcpy(&palette[16], bg_b.palette->data, 16);
    memcpy(&palette[32], cg_sprites.palette->data, 16);
//    memcpy(&palette[48], spr_boy01.palette->data, 16);


}

void updateScene_Game()
{
    updatePlayer();

}

void exitScene_Game()
{
}

