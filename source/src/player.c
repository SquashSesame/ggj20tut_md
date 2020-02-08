#include "main.h"

#include "gfx.h"
#include "music.h"
#include "player.h"


int     dirMissile = 2;
int     flgPad =0;
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

    if (flgPad == 0 && (padinfo & BUTTON_LEFT) && dirMissile > 0){
        flgPad = 1;
        dirMissile--;
        spr->animno = missileTbl[dirMissile].animno;
//        SPR_setAnimAndFrame(spr->sprite, spr->animno, dirMissile);
    }
    else if (flgPad == 0 && (padinfo & BUTTON_RIGHT) && dirMissile < (MAX_MISSLE-1)){
        flgPad = 1;
        dirMissile++;
        spr->animno = missileTbl[dirMissile].animno;
//        SPR_setAnimAndFrame(spr->sprite, spr->animno, dirMissile);
    }
    else if ((padinfo & (BUTTON_LEFT|BUTTON_RIGHT)) == 0){
        flgPad = 0;
    }


    if (padinfo & BUTTON_A){
//        SND_startPlay_XGM(bgm_game);
    }

    if (padinfo & BUTTON_B){
//        SND_playSfx_VGM(se_bullet, sizeof(se_bullet));
    }

}

#define TANK_POS_X  FIX32(144)
#define TANK_POS_Y  FIX32(156)

void initPlayer(int animno)
{
    dirMissile = 2;
    sprTankHoh = CreateSprite(
            missileTbl[dirMissile].animno,
            (TANK_POS_X), (TANK_POS_Y), funcTankHou);

    sprTank = CreateSprite(
            0, (TANK_POS_X), (TANK_POS_Y), NULL);
}


void updatePlayer()
{
}






