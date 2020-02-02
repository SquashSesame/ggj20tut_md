#include <genesis.h>

#include "gfx.h"
#include "music.h"
#include "player.h"
#include "main.h"


/*
    ワーク
*/
fix32 posx;
fix32 posy;
int   dirMissile = 2;

typedef struct {
    int     animno;
    fix32   vx;
    fix32   vy;
} sMissile;

#define MAX_MISSLE  5
sMissile missileTbl[6] =
{
    { /*anim*/1, /*vx*/-1.0f, /*vy*/0.0f },
    { /*anim*/2, /*vx*/-0.5f, /*vy*/-0.5f },
    { /*anim*/3, /*vx*/0.0f, /*vy*/-1.0f },
    { /*anim*/4, /*vx*/0.5f, /*vy*/-0.5f },
    { /*anim*/5, /*vx*/1.0f, /*vy*/0.0f },
    //　END
    { 0, 0,0   }
};


void handleInput();
#define REVSERV_SPNO 4
#define MAX_BULLET  20
typedef struct {
    u8      isAlive;
    u8      spno;
    s8      time;
    u8      p2;
    fix32   px;
    fix32   py;
    fix32   vx;
    fix32   vy;
} sBullet;
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

void updateBullet()
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

/*
    初期化
*/
void initPlayer()
{
    posx = FIX32(100);
    posy = MAX_POSY;

    // init sonic sprite
    SPR_initSprite(
        &sprites[0],
        &cg_sprites,
        fix32ToInt(posx),
        fix32ToInt(posy),
        TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    SPR_setAnim(&sprites[0], 0);

    // init sonic sprite
    SPR_initSprite(
        &sprites[1],
        &cg_sprites,
        fix32ToInt(posx),
        fix32ToInt(posy),
        TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    SPR_setAnim(&sprites[1], missileTbl[dirMissile].animno);
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
        fix32ToInt(posx),
        fix32ToInt(posy)
    );
    SPR_setPosition(
        &sprites[1],
        fix32ToInt(posx),
        fix32ToInt(posy)
    );

    updateBullet();
}

void handleInput()
{
    u16 padinfo = JOY_readJoypad(JOY_1);

    if (padinfo & BUTTON_LEFT && dirMissile > 0){
        dirMissile--;
        SPR_setAnim(&sprites[1], missileTbl[dirMissile].animno);
    } else if (padinfo & BUTTON_RIGHT && dirMissile < MAX_MISSLE){
        dirMissile++;
        SPR_setAnim(&sprites[1], missileTbl[dirMissile].animno);
    }


    if (padinfo & BUTTON_A){
//        SND_startPlay_XGM(bgm_game);
    }

    if (padinfo & BUTTON_B){
//        SND_playSfx_VGM(se_bullet, sizeof(se_bullet));
    }
}






