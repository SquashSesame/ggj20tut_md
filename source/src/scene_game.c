#include "main.h"

#include "gfx.h"
#include "music.h"
#include "player.h"
#include "player_heri.h"

void updateBG(int x, int y);

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
        TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind),
        0, 0, FALSE, TRUE);
    ind += bg_a.tileset->numTile;
#if 1
   VDP_drawImageEx(
        BPLAN,
        &bg_b,
        TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, ind),
        0, 0, FALSE, TRUE);
    ind += bg_b.tileset->numTile;
#endif

    initPlayer_Heri(9);
    initPlayer(0);

    // prepare palettes
    memcpy(&palette[0], bg_a.palette->data, 16*2);
    memcpy(&palette[16], bg_b.palette->data, 16*2);
    memcpy(&palette[32], cg_sprites.palette->data, 16*2);
    memcpy(&palette[48], cg_sprites.palette->data, 16*2);

    // VDP process done, we can re enable interrupts
    SYS_enableInts();
}

void updateScene_Game()
{
    updateBG(0, -40);
}

void exitScene_Game()
{
}

int scrBG_X =0;
int scrBG_Y =0;

void updateBG(int addx, int addy)
{
#if 1
//s    if ((x != camposx) || (y != camposy))
    {
        scrBG_X += addx;
        scrBG_Y += addy;
        VDP_setHorizontalScroll(PLAN_A, (int)(scrBG_X>>8));
//        VDP_setHorizontalScroll(PLAN_B, fix32ToInt(-camposx) >> 3);
        VDP_setVerticalScroll(PLAN_A, (int)(scrBG_Y>>8));
//        VDP_setVerticalScroll(PLAN_B, fix32ToInt(camposy) >> 3);
    }
#endif
}

