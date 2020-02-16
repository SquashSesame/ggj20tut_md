#include "main.h"

#include "gfx.h"
#include "music.h"
#include "player.h"

#define TANK_POS_X  FIX32(144)
#define TANK_POS_Y  FIX32(156)

int     dirMissile = 2;
int     flgPad =0;
int     flgBlt =0;
sSprite* sprTank;
sSprite* sprTankHoh;

typedef struct {
    int     animno;
    fix32   vx;
    fix32   vy;
} sMissile;

#define MAX_MISSLETBL  5
sMissile missileTbl[6] =
{
    { /*anim*/1, /*vx*/FIX32(-1.0f), /*vy*/FIX32(0.0f) },
    { /*anim*/2, /*vx*/FIX32(-0.5f), /*vy*/FIX32(-0.5f) },
    { /*anim*/3, /*vx*/FIX32(0.0f), /*vy*/FIX32(-1.0f) },
    { /*anim*/4, /*vx*/FIX32(0.5f), /*vy*/FIX32(-0.5f) },
    { /*anim*/5, /*vx*/FIX32(1.0f), /*vy*/FIX32(0.0f) },
};

#define INTERPAL_BULLET 16
#define POWER_BULLET    100
#define LIFE_BULLET     10
#define SPNO_BULLET     6
#define MAX_BULLET      16
sSprite* sprBullet[MAX_BULLET];
int     interpalBullet =0;

sSprite* FindBlankBullet(){
    int i;
    for (i=0 ;i<MAX_BULLET ; ++i){
        if (sprBullet[i]->isAlive == FALSE){
            return sprBullet[i];
        }
    }
    return NULL;
}

void funcBullet(sSprite* spr)
{
    if (spr->isAlive == TRUE)
    {
        spr->time--;
        if (spr->time<=0){
            spr->isAlive = FALSE;
            spr->isShow = FALSE;
            return;
        } else {
            spr->isShow = TRUE;
        }

        spr->vx += spr->ax;
        spr->vy += spr->ay;
        spr->px += spr->vx;
        spr->py += spr->vy;
    }
}

void funcTank(sSprite* spr)
{


}

void funcTankHou(sSprite* spr)
{
    u16 padinfo = JOY_readJoypad(JOY_1);

    /*
        –C‘ä‚ð‰ñ“]
    */
    if (flgPad == 0 && (padinfo & BUTTON_LEFT) && dirMissile > 0){
        flgPad = 1;
        dirMissile--;
        spr->animno = missileTbl[dirMissile].animno;
    }
    else if (flgPad == 0 && (padinfo & BUTTON_RIGHT) && dirMissile < (MAX_MISSLETBL-1)){
        flgPad = 1;
        dirMissile++;
        spr->animno = missileTbl[dirMissile].animno;
    }
    else if ((padinfo & (BUTTON_LEFT|BUTTON_RIGHT)) == 0){
        flgPad = 0;
    }


    if (interpalBullet <=0 && (padinfo & BUTTON_A)){
        // ‹ó‚«‚ð’T‚·
        sSprite* bullet = FindBlankBullet();
        if (bullet != NULL){
            interpalBullet = INTERPAL_BULLET;
            bullet->isAlive = TRUE;
            bullet->isShow = TRUE;
            bullet->px = spr->px;
            bullet->py = spr->py;
            bullet->vx = missileTbl[dirMissile].vx * 2;
            bullet->vy = missileTbl[dirMissile].vy * 2;
            bullet->ax = -missileTbl[dirMissile].vx / 64;
            bullet->ay = -missileTbl[dirMissile].vy / 64;
            bullet->time = POWER_BULLET;
        }
    }
    else {
        if ( --interpalBullet <= 0) interpalBullet = 0;
    }

    if (padinfo & BUTTON_B){
//        SND_playSfx_VGM(se_bullet, sizeof(se_bullet));
    }

}

void initPlayer(int animno)
{
    dirMissile = 2;
    sprTankHoh = CreateSprite(
            missileTbl[dirMissile].animno,
            (TANK_POS_X), (TANK_POS_Y), funcTankHou);

    sprTank = CreateSprite(
            0, (TANK_POS_X), (TANK_POS_Y), NULL);

    //@‚½‚Ü
    int i;
    for (i=0 ; i<MAX_BULLET ; ++i){
        sprBullet[i] = CreateSprite(
                SPNO_BULLET, 0, 0, funcBullet);
        sprBullet[i]->isAlive = FALSE;
        sprBullet[i]->isShow = FALSE;
    }
}


void updatePlayer()
{
}






