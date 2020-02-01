#include <genesis.h>

#include "gfx.h"
#include "music.h"
#include "scene_logo.h"
#include "scene_game.h"
#include "player.h"


// forward
static void handleInput();
static void joyEvent(u16 joy, u16 changed, u16 state);

/**
 *
 * return void
 *
 */
static void updatePhysic();
static void updateAnim();
static void updateCamera(fix32 x, fix32 y);

// sprites structure
Sprite sprites[256];
u16 palette[64];

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

    SPR_init(256);

    // set all palette to black
    VDP_setPaletteColors(0, palette_black, 64);

    JOY_setEventHandler(joyEvent);

    /*
        GGJ LOGO
    */
    initScene_Logo();

    // fade in
    VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);
    u8 isEnd = 0;
    while(isEnd ==0)
    {
        updateScene_Logo();

        u16 padinfo = JOY_readJoypad(JOY_1);
        if (padinfo & (BUTTON_A|BUTTON_B|BUTTON_C)){
            VDP_fadeOut(0, (4 * 16) - 1, 20, FALSE);
            isEnd = 1;
        }

        // update sprites (only one to update here)
        SPR_update(sprites, 1);

        VDP_waitVSync();
    }


    /*
        GAME
    */
    initScene_Game();

    // fade in
    VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);

    while(TRUE)
    {
        updateScene_Game();


        // update sprites (only one to update here)
        SPR_update(sprites, 1);

        VDP_waitVSync();
    }

    return 0;
}

