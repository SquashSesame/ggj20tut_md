#include "main.h"

#include "gfx.h"
#include "music.h"
#include "player.h"

#define LIMIT_LEFT      32
#define LIMIT_RIGHT     260
#define LIMIT_UP        32
#define LIMIT_BOTTOM    200

#define ACCELL  0.05f

fix32   posx;
fix32   posy;
fix32   add_vx = 0.1f;
fix32   add_vy = 0;
int     heri_sprno;
int     heri_animno;

#if 0
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
#endif

sSprite* sprHeri;

void FuncHeri(sSprite* spr)
{
    u16 padinfo = JOY_readJoypad(JOY_2);

    if (padinfo & BUTTON_LEFT){
        spr->vx -= ACCELL;
    } else if (padinfo & BUTTON_RIGHT){
        spr->vx += ACCELL;
    }

    if (padinfo & BUTTON_UP){
        spr->vy -= ACCELL;
    } else if (padinfo & BUTTON_DOWN){
        spr->vy += ACCELL;
    }


    if (padinfo & BUTTON_A){
//        SND_startPlay_XGM(bgm_game);
    }

    if (padinfo & BUTTON_B){
//        SND_playSfx_VGM(se_bullet, sizeof(se_bullet));
    }

    spr->px += spr->vx;
    spr->py += spr->vy;

    if (spr->px < LIMIT_LEFT)   spr->px = LIMIT_LEFT;
    if (spr->px > LIMIT_RIGHT)  spr->px = LIMIT_RIGHT;
    if (spr->py < LIMIT_UP)     spr->py = LIMIT_UP;
    if (spr->py > LIMIT_BOTTOM) spr->py = LIMIT_BOTTOM;

}

void initPlayer_Heri(int animno)
{
    sprHeri = CreateSprite(animno, FIX32(120),FIX32(80), FuncHeri);
}





