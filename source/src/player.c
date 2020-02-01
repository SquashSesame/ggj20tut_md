#include <genesis.h>

#include "gfx.h"
#include "music.h"
#include "player.h"
#include "main.h"


/*
    ワーク
*/
fix32 camposx;
fix32 camposy;
fix32 posx;
fix32 posy;
fix32 movx;
fix32 movy;
s16 xorder;
s16 yorder;


void handleInput();
void updatePhysic();
void updateCamera(fix32 x, fix32 y);
void updateAnim();
void updateCamera(fix32 x, fix32 y);
Sprite* sprPlayer = NULL;

/*
    初期化
*/
void initPlayer()
{
    camposx = -1;
    camposy = -1;
    posx = FIX32(48);
    posy = MAX_POSY;
    movx = FIX32(0);
    movy = FIX32(0);
    xorder = 0;
    yorder = 0;

    // init sonic sprite
    SPR_initSprite(
                    &sprites[0],
                    &cg_sprites,
                    fix32ToInt(posx - camposx),
                    fix32ToInt(posy - camposy),
                    TILE_ATTR(PAL2, TRUE, FALSE, FALSE));

    SPR_setAnim(&sprites[0], 0);
    SPR_update(sprites, 0);
}
/*
    プレイヤー移動
*/
void updatePlayer()
{
    handleInput();



    // set sprite position
    SPR_setPosition(
        &sprites[0],
        fix32ToInt(posx - camposx),
        fix32ToInt(posy - camposy)
    );
}

void handleInput()
{
    u16 padinfo = JOY_readJoypad(JOY_1);

    if (padinfo & BUTTON_UP)
        yorder = -1;
    else if (padinfo & BUTTON_DOWN)
        yorder = +1;
    else
        yorder = 0;

    if (padinfo & BUTTON_LEFT)
        xorder = -1;
    else if (padinfo & BUTTON_RIGHT)
        xorder = +1;
    else
        xorder = 0;


    if (padinfo & BUTTON_A){
        SND_startPlay_XGM(bgm_game);
    }

    if (padinfo & BUTTON_B){
        SND_playSfx_VGM(se_bullet, sizeof(se_bullet));
    }
}

void updateCamera(fix32 x, fix32 y)
{
#if 1
    if ((x != camposx) || (y != camposy))
    {
        camposx = x;
        camposy = y;
        VDP_setHorizontalScroll(PLAN_A, fix32ToInt(-camposx));
        VDP_setHorizontalScroll(PLAN_B, fix32ToInt(-camposx) >> 3);
        VDP_setVerticalScroll(PLAN_A, fix32ToInt(camposy));
        VDP_setVerticalScroll(PLAN_B, fix32ToInt(camposy) >> 3);
    }
#endif
}






