#include <genesis.h>

#include "gfx.h"
#include "music.h"
#include "player.h"
#include "main.h"


fix32   posx;
fix32   posy;
int     dirMissile = 2;
int     tank_sprno;
int     tank_animno;

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
    //�@END
    { 0, 0,0   }
};


static void handleInput();
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

void initPlayer(int sprno, int animno)
{
    tank_sprno = sprno;
    tank_animno = animno;

    posx = FIX32(100);
    posy = MAX_POSY;
#if 1
    // init sonic sprite
    SPR_initSprite(
        &sprites[tank_sprno],
        &cg_sprites,
        fix32ToInt(posx),
        fix32ToInt(posy),
        TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
//        TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
    SPR_setAnim(&sprites[tank_sprno], tank_animno);
//    SPR_setAlwaysVisible(&sprites[tank_sprno+1], TRUE);
#endif
#if 1
    // init sonic sprite
    SPR_initSprite(
        &sprites[tank_sprno+1],
        &cg_sprites,
        fix32ToInt(posx),
        fix32ToInt(posy),
        TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
//        TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
//    SPR_setAlwaysVisible(&sprites[tank_sprno], TRUE);
    SPR_setAnim(
        &sprites[tank_sprno+1],
        missileTbl[dirMissile].animno);
#endif
}


void updatePlayer()
{
//    handleInput();
#if 1
    // set sprite position
    SPR_setPosition(
        &sprites[tank_sprno],
        fix32ToInt(posx),
        fix32ToInt(posy)
    );
#endif
#if 1
    SPR_setPosition(
        &sprites[tank_sprno+1],
        fix32ToInt(posx),
        fix32ToInt(posy)
    );
#endif
//    updateBullet();
}

static void handleInput()
{
    u16 padinfo = JOY_readJoypad(JOY_1);

    if ((padinfo & BUTTON_LEFT) && dirMissile > 0){
        dirMissile--;
        SPR_setAnim(&sprites[tank_sprno+1], missileTbl[dirMissile].animno);
    } else if ((padinfo & BUTTON_RIGHT) && dirMissile < MAX_MISSLE){
        dirMissile++;
        SPR_setAnim(&sprites[tank_sprno+1], missileTbl[dirMissile].animno);
    }


    if (padinfo & BUTTON_A){
//        SND_startPlay_XGM(bgm_game);
    }

    if (padinfo & BUTTON_B){
//        SND_playSfx_VGM(se_bullet, sizeof(se_bullet));
    }
}






