#include <genesis.h>

#include "gfx.h"
#include "music.h"
#include "player.h"
#include "main.h"


#define ACCELL  0.01f

fix32   posx;
fix32   posy;
fix32   add_vx = 0;
fix32   add_vy = 0;
int     heri_sprno;
int     heri_animno;


void handleInput();
#define REVSERV_SPNO 24
#define MAX_BULLET  10
sBullet bulletList_Heri[MAX_BULLET];

sBullet* FindBlankBullet_Heri(){
    s16 i;
    for (i=0 ;i<MAX_BULLET ; i++){
        sBullet* item = &bulletList_Heri[i];
        if (item->isAlive == FALSE){
            return item;
        }
    }
    return NULL;
}

static void updateBullet()
{
    s16 i;
    for (i=0 ;i<MAX_BULLET ; ++i)
    {
        sBullet* item = &bulletList_Heri[i];
        if (item->isAlive == TRUE){

            item->px += item->vx;
            item->py += item->vy;

            SPR_setPosition(
                &sprites[REVSERV_SPNO + item->spno],
                fix32ToInt(item->px),
                fix32ToInt(item->py)
            );

            item->time--;
            if (item->time<=0){
                item->isAlive = FALSE;
            }
        }
    }
}

void initPlayer_Heri(int sprno, int animno)
{
    heri_sprno = sprno;
    heri_animno = animno;

    posx = FIX32(120);
    posy = FIX32(80);

    // init sonic sprite
    SPR_initSprite(
        &sprites[heri_sprno],
        (SpriteDefinition*)&cg_sprites,
        fix32ToInt(posx),
        fix32ToInt(posy),
        TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
//        TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 2));
    SPR_setAnim(&sprites[heri_sprno], heri_animno);
}

void updatePlayer_Heri()
{
    handleInput();

    posx += add_vx;
    posy += add_vy;

    if (posx < 32) posx = 32;
    if (posx > 260) posx = 260;
    if (posy < 32) posy = 32;
    if (posy > 200) posy = 200;

    // set sprite position
    (
        &sprites[heri_sprno],
        fix32ToInt(posx),
        fix32ToInt(posy)
    );

//    updateBullet();
}

static  void handleInput()
{
    u16 padinfo = JOY_readJoypad(JOY_2);

    if (padinfo & BUTTON_LEFT){
        add_vx -= ACCELL;
    } else if (padinfo & BUTTON_RIGHT){
        add_vx += ACCELL;
    }

    if (padinfo & BUTTON_UP){
        add_vy -= ACCELL;
    } else if (padinfo & BUTTON_DOWN){
        add_vy += ACCELL;
    }


    if (padinfo & BUTTON_A){
//        SND_startPlay_XGM(bgm_game);
    }

    if (padinfo & BUTTON_B){
//        SND_playSfx_VGM(se_bullet, sizeof(se_bullet));
    }
}






