#include "main.h"

#include "gfx.h"
#include "music.h"
#include "scene_logo.h"
#include "scene_title.h"
#include "scene_game.h"

#define LOGO_TIMER  (30 * 4)
// forward
static void handleInput();
static void joyEvent(u16 joy, u16 changed, u16 state);

static void updatePhysic();
static void updateAnim();
static void updateCamera(fix32 x, fix32 y);

void joyEvent(u16 joy, u16 changed, u16 state)
{
    // START button state changed
    if (changed & BUTTON_START)
    {
    }

    if (changed & state & (BUTTON_A | BUTTON_B | BUTTON_C))
    {

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
    SPR_init();
    SPR_reset();

    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);

    // speed up controller checking
    JOY_setSupport(PORT_1, JOY_SUPPORT_6BTN);
    JOY_setSupport(PORT_2, JOY_SUPPORT_6BTN);


    while(TRUE)
    {
        CLearAllSprite();


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
            // タイマー
            timer--;
            // キーに反応
            u16 padinfo = JOY_readJoypad(JOY_1);
            if (timer <= 0 || (padinfo & (BUTTON_A|BUTTON_B|BUTTON_C))){
                VDP_fadeOut(0, (4 * 16) - 1, 20, FALSE);
                isEnd = 1;
            }

            VDP_waitVSync();
        }


        SYS_disableInts();
        CLearAllSprite();


        /*
            TITLE
        */
        initScene_Title();

        // fade in
        VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);
        SYS_enableInts();

        isEnd = 0;
        while(isEnd ==0)
        {
            // キーに反応
            u16 padinfo = JOY_readJoypad(JOY_1);
            if (padinfo & (BUTTON_START|BUTTON_A|BUTTON_B|BUTTON_C)){
                VDP_fadeOut(0, (4 * 16) - 1, 20, FALSE);
                isEnd = 1;
            }

            VDP_waitVSync();
        }


        SYS_disableInts();
        CLearAllSprite();

        /*
            GAME
        */
        initScene_Game();

        SYS_enableInts();
        // fade in
        VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);

        while(TRUE)
        {
            updateScene_Game();

            UpdateSprites();

            VDP_waitVSync();
        }


        VDP_fadeOut(0, (4 * 16) - 1, 20, FALSE);
        SYS_disableInts();
        // -> LOGO
    }

    return 0;
}

