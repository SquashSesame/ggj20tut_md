
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
        BPLAN,
        &cg_bgcg,
        TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += cg_bgcg.tileset->numTile;

#if 0
    VDP_drawImageEx(
        APLAN,
        &bga_image,
        TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += bga_image.tileset->numTile;
#endif


    // VDP process done, we can re enable interrupts
    SYS_enableInts();

// init scrolling
//    updateCamera(FIX32(0), FIX32(0));

    initPlayer();


    // prepare palettes
    memcpy(&palette[0], cg_bgcg.palette->data, 16);
//    memcpy(&palette[16], bgb_image.palette->data, 16);
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

