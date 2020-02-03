#include <genesis.h>

#include "gfx.h"
#include "music.h"
#include "scene_logo.h"
#include "scene_game.h"
#include "player.h"
#include "player_heri.h"

#define LOGO_TIMER  (30 * 2)
// forward
static void handleInput();
static void joyEvent(u16 joy, u16 changed, u16 state);

static void updatePhysic();
static void updateAnim();
static void updateCamera(fix32 x, fix32 y);

// sprites structure
Sprite sprites[MAX_SPRITE];
u16 palette[64];
s16 spriteCount;

void joyEvent(u16 joy, u16 changed, u16 state)
{
    // START button state changed
    if (changed & BUTTON_START)
    {
    }

    if (changed & state & (BUTTON_A | BUTTON_B | BUTTON_C))
    {
//        if (movy == 0)
//            movy = JUMP_SPEED;
    }
}


int main()
{
    // disable interrupt when accessing VDP
    SYS_disableInts();
    // initialization
    VDP_setScreenWidth320();
//    VDP_setScreenWidth256();

    // set all palette to black
    VDP_setPaletteColors(0, palette_black, 64);
    JOY_setEventHandler(joyEvent);


 // Init sprites position
    VDP_resetSprites();
    spriteCount = 0;

    SPR_init(MAX_SPRITE);

    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);

    // speed up controller checking
    JOY_setSupport(PORT_1, JOY_SUPPORT_6BTN);
    JOY_setSupport(PORT_2, JOY_SUPPORT_6BTN);

    /*
        GGJ LOGO
    */
    initScene_Logo();

    // fade in
    VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);
    SYS_enableInts();

    int timer = LOGO_TIMER;
    u8 isEnd = 0;
    while(isEnd ==0)
    {
        updateScene_Logo();

        // タイマー
        timer--;
        // キーに反応
        u16 padinfo = JOY_readJoypad(JOY_1);
        if (timer <= 0 || (padinfo & (BUTTON_A|BUTTON_B|BUTTON_C)){
            VDP_fadeOut(0, (4 * 16) - 1, 20, FALSE);
            isEnd = 1;
        }

        // update sprites (only one to update here)
//        SPR_update(sprites, 1);

        VDP_waitVSync();
    }


    SYS_disableInts();
    // initialization
    VDP_setScreenWidth320();
//    VDP_setScreenWidth256();

    // set all palette to black
    VDP_setPaletteColors(0, palette_black, 64);

    JOY_setEventHandler(joyEvent);

    SPR_init(MAX_SPRITE);

    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);

    // speed up controller checking
    JOY_setSupport(PORT_1, JOY_SUPPORT_6BTN);
    JOY_setSupport(PORT_2, JOY_SUPPORT_6BTN);


    /*
        GAME
    */
    initScene_Game();

    // fade in
    VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);
    SYS_enableInts();

    while(TRUE)
    {
        updateScene_Game();


        // update sprites (only one to update here)
        if (spriteCount > 0){
            SPR_update(sprites, spriteCount);
        }

        VDP_waitVSync();
    }

    return 0;
}

