#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


#define ANIM_STAND      0
#define ANIM_WAIT       1
#define ANIM_WALK       2
#define ANIM_RUN        3
#define ANIM_BRAKE      4
#define ANIM_UP         5
#define ANIM_CROUNCH    6
#define ANIM_ROLL       7

#define MAX_SPEED       FIX32(8)
#define RUN_SPEED       FIX32(6)
#define BRAKE_SPEED     FIX32(2)

#define JUMP_SPEED      FIX32(-8)
#define GRAVITY         FIX32(0.4)
#define ACCEL           FIX32(0.1)
#define DE_ACCEL        FIX32(0.15)

#define MIN_POSX        FIX32(10)
#define MAX_POSX        FIX32(400)
#define MAX_POSY        FIX32(156)

#define MAX_SPRITE      80

extern Sprite sprites[MAX_SPRITE];
extern u16 palette[64];
extern s16 spriteCount;

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

#endif // MAIN_H_INCLUDED
