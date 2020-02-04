#include    "main.h"
#include    "../res/gfx.h"

// sprites structure
Sprite sprites[MAX_SPRITE];
u16 palette[64];
s16 spriteCount;

// extern
sSprite spriteBuf[MAX_SPRITE];

void CLearAllSprite()
{
    SPR_clear();
    memset(&sprites, 0, sizeof(Sprite)* MAX_SPRITE);
    memset(&spriteBuf, 0, sizeof(sSprite) * MAX_SPRITE);
    spriteCount = 0;
}

sSprite* CreateSprite(int animno, fix32 px, fix32 py, FUNC func)
{
    sSprite* spr = &spriteBuf[spriteCount];
    memset(spr, 0, sizeof(sSprite));

    spr->sprite = &sprites[spriteCount];
    spr->pFunc = func;
    spr->isAlive = TRUE;
    spr->isShow = TRUE;
    spr->sprno = spriteCount;
    spr->animno = spr->animno_old = animno;
    spr->px = px;
    spr->py = py;

    SPR_initSprite(
        spr->sprite,
        &cg_sprites,
        fix32ToInt(px),
        fix32ToInt(py),
        TILE_ATTR(PAL2, FALSE, FALSE, FALSE));

    SPR_setAnim(spr->sprite, animno);
    spriteCount++;

    return spr;
}

void UpdateSprites()
{
    if (spriteCount <= 0){
        return;
    }

    int i=0;
    for (i=0 ; i<spriteCount; ++i)
    {
        sSprite* spr = &spriteBuf[i];

        if (spr->isAlive == FALSE){
            continue;
        }

        if (spr->pFunc != NULL){
            spr->pFunc(spr);
        }

        SPR_setAlwaysVisible(spr->sprite,
            (spr->isShow == TRUE)? TRUE : FALSE);

        if (spr->animno != spr->animno_old)
        {
            spr->animno_old = spr->animno;
            SPR_setAnim(spr->sprite, spr->animno);
        }

        SPR_setPosition(
            spr->sprite,
            fix32ToInt(spr->px),
            fix32ToInt(spr->py)
        );
    }

    SPR_update(sprites, spriteCount);
}



