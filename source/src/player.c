#include "main.h"

#include "gfx.h"
#include "music.h"
#include "player.h"


int     dirMissile = 2;
sSprite* sprTank;
sSprite* sprTankHoh;

typedef struct {
    int     animno;
    fix32   vx;
    fix32   vy;
} sMissile;

#define MAX_MISSLE  5
sMissile missileTbl[6] =
{
    { /*anim*/1, /*vx*/FIX32(-1.0f), /*vy*/FIX32(0.0f) },
    { /*anim*/2, /*vx*/FIX32(-0.5f), /*vy*/FIX32(-0.5f) },
    { /*anim*/3, /*vx*/FIX32(0.0f), /*vy*/FIX32(-1.0f) },
    { /*anim*/4, /*vx*/FIX32(0.5f), /*vy*/FIX32(-0.5f) },
    { /*anim*/5, /*vx*/FIX32(1.0f), /*vy*/FIX32(0.0f) },
};


#if 0
#define REVSERV_SPNO 4
#define MAX_BULLET  20
sBullet bulletList[MAX_BULLET];

sBullet* FindBlankBullet(){
    s16 i;
    for (i=0 ;i<MAX_BULLET ; i++){
        sBullet* item = &bulletList[i];
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
        sBullet* item = &bulletList[i];
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


void funcTank(sSprite* spr)
{


}

void funcTankHou(sSprite* spr)
{
    u16 padinfo = JOY_readJoypad(JOY_1);

    if ((padinfo & BUTTON_LEFT) && dirMissile > 0){
        dirMissile--;
        spr->animno = missileTbl[dirMissile].animno;
    } else if ((padinfo & BUTTON_RIGHT) && dirMissile < MAX_MISSLE){
        dirMissile++;
        spr->animno = missileTbl[dirMissile].animno;
    }


    if (padinfo & BUTTON_A){
//        SND_startPlay_XGM(bgm_game);
    }

    if (padinfo & BUTTON_B){
//        SND_playSfx_VGM(se_bullet, sizeof(se_bullet));
    }

}


void initPlayer(int animno)
{
    sprTank = CreateSprite(animno, FIX32(100), FIX32(156), funcTank);
    sprTankHoh = CreateSprite(animno, FIX32(100), FIX32(156), funcTankHou);
    dirMissile = 2;
}


void updatePlayer()
{
}






