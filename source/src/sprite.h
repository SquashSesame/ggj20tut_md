#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

extern u16 palette[64];
extern s16 spriteCount;

typedef struct eSprite {
    Sprite* sprite;
    void    (*pFunc)(struct eSprite* spr);
    // option args
    void*   args;
    // work
    u8      sprno;
    u8      animno;
    u8      animno_old;
    s8      time;
    // Bits
    u8      isAlive:1;
    u8      isShow:1;
    u8      pad00:6;
    // padding
    u8      pad01[3];
    // Position
    fix32   px;
    fix32   py;
    fix32   vx;
    fix32   vy;
    fix32   ax;
    fix32   ay;
} sSprite;

typedef void (*FUNC)(struct eSprite* spr);

extern void CLearAllSprite();
extern sSprite* CreateSprite(int animno, fix32 px, fix32 py, FUNC func );
extern void UpdateSprites();

#endif // SPRITE_H_INCLUDED
