#include "main.h"

#include "gfx.h"
#include "music.h"
#include "player.h"

#define LIMIT_LEFT      FIX32(32)
#define LIMIT_RIGHT     FIX32(320-32)
#define LIMIT_UP        FIX32(32)
#define LIMIT_BOTTOM    FIX32(200)

#define ACCELL          FIX32(0.01f)
#define LIMIT_SPEED     FIX32(4.0f)

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
        if (spr->vx < -LIMIT_SPEED) spr->vx = -LIMIT_SPEED;
    }
    else if (padinfo & BUTTON_RIGHT){
        spr->vx += ACCELL;
        if (spr->vx > LIMIT_SPEED) spr->vx = LIMIT_SPEED;
    }

    if (padinfo & BUTTON_UP){
        spr->vy -= ACCELL;
        if (spr->vy < -LIMIT_SPEED) spr->vy = -LIMIT_SPEED;
    }
    else if (padinfo & BUTTON_DOWN){
        spr->vy += ACCELL;
        if (spr->vy > LIMIT_SPEED) spr->vy = LIMIT_SPEED;
    }


    if (padinfo & BUTTON_A){
//        VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);
    }

    if (padinfo & BUTTON_B){
//        VDP_fadeOut(0, (4 * 16) - 1, 20, FALSE);
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





