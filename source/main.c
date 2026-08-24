/*
 * MiroTayWorkshop RPG  -  v0.3 "Sprachauswahl"
 * =============================================
 * Now with: EN / DE / PL / RU language support
 * Settings menu accessible from title screen.
 *
 * Controls: 2 Wiimotes held HORIZONTALLY
 *   D-Pad  -> move / navigate menus
 *   A      -> interact / confirm
 *   B      -> cancel / back
 *   HOME   -> exit to Homebrew Channel
 *
 * BUILD: see BUILD_GUIDE.md
 */

#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "strings.h"   /* translation table */

/* ====================================================================
   GRRLIB COMPATIBILITY SHIM
   This GRRLIB build has no texture-based system font
   (GRRLIB_GetSystemFont() does not exist here). Instead it exposes
   GRRLIB_PrintfSystemFont(x, y, string, fontSize, color) directly.
   Rather than rewrite every call site in this file, we redirect all
   existing GRRLIB_Printf(x, y, GRRLIB_GetSystemFont(), color, zoom, ...)
   calls through this shim, unchanged.
   ==================================================================== */
#include <stdarg.h>

static void* GRRLIB_GetSystemFont(void) { return NULL; }

static void MTW_PrintfCompat(f32 xpos, f32 ypos, void *unused_tex, u32 color,
                              f32 zoom, const char *text, ...) {
    (void)unused_tex;
    char tmp[1024];
    va_list argp;
    va_start(argp, text);
    vsnprintf(tmp, sizeof(tmp), text, argp);
    va_end(argp);
    unsigned int fontSize = (unsigned int)(zoom * 16.0f);
    if (fontSize < 8) fontSize = 8;
    GRRLIB_PrintfSystemFont((int)xpos, (int)ypos, tmp, fontSize, color);
}

#define GRRLIB_Printf(x, y, tex, color, zoom, ...) \
    MTW_PrintfCompat((x), (y), (tex), (color), (zoom), __VA_ARGS__)

/* ====================================================================
   LANGUAGE
   ==================================================================== */
static Language currentLang = LANG_EN;

/* T() - translate a string ID to current language */
static const char *T(StrID id) {
    return STRINGS[currentLang][id];
}

/* ====================================================================
   GAME STATES
   ==================================================================== */
typedef enum {
    STATE_LOGO,
    STATE_TITLE,
    STATE_SETTINGS,
    STATE_OVERWORLD,
    STATE_MIRO_HOUSE,
    STATE_MIRO_ROOM,
    STATE_TAY_HOUSE,
    STATE_TAY_ROOM,
    STATE_SKATEPARK,
    STATE_SKATE_LESSON,
    STATE_TRICK_ATTEMPT,
    STATE_WORKSHOP,
    STATE_DIALOGUE,
    STATE_ENDING
} GameState;

/* ====================================================================
   DIALOGUE
   ==================================================================== */
#define MAX_DIALOGUE_LINES 4
typedef struct {
    const char *speaker;
    const char *lines[MAX_DIALOGUE_LINES];
    int         num_lines;
} Dialogue;

static GameState state        = STATE_LOGO;
static GameState returnState  = STATE_OVERWORLD;
static float     logoTimer    = 0.0f;

static Dialogue  activeDialogue;
static int       dialogueLine  = 0;

/* Skate progress */
static int       workshopUnlocked      = 0;
static int       endingTriggered       = 0;
static int       tayLessonsCompleted   = 0;
static int       taySkateLevel         = 0;
static const char *TRICKS[] = {"Ollie","Manual","Kickflip",
                                "Heelflip","50-50 Grind","Noseslide"};
static int        currentTrick  = 0;
static float      trickTimer    = 0.0f;
static int        trickSuccess  = 0;

/* ====================================================================
   TITLE MENU
   ==================================================================== */
static int  titleSelection   = 0;   /* 0=Start  1=Settings */

/* ====================================================================
   SETTINGS
   ==================================================================== */
static int  settingsSelection = 0;  /* 0-3 = language index */
static int  settingsCooldown  = 0;  /* prevent rapid scrolling */

/* ====================================================================
   PLAYER
   ==================================================================== */
typedef struct {
    const char *name;
    float x, y, speed;
    int   skate, build, music, mtb, cook;
    int   wpad_chan;
    u32   color;
} Player;

static Player miro = {
    "Miro", 200,260, 2.4f, 9,4,8,8,2, WPAD_CHAN_0, 0x00AEFFFF
};
static Player tay = {
    "Tay",  240,260, 2.4f, 1,9,7,8,9, WPAD_CHAN_1, 0xFF6600FF
};

/* ====================================================================
   NPC
   ==================================================================== */
typedef struct {
    const char *name;
    float x, y;
    u32   color;
    GameState zone;
    Dialogue  dialogue;
} NPC;

#define MAX_NPCS 11
static NPC npcs[MAX_NPCS];
static int npc_count = 0;

static void AddNPC(const char *name, float x, float y, u32 col, GameState zone,
                   StrID l0, StrID l1, StrID l2, int nlines) {
    NPC *n = &npcs[npc_count++];
    n->name  = name; n->x = x; n->y = y;
    n->color = col;  n->zone = zone;
    n->dialogue.speaker    = name;
    n->dialogue.num_lines  = nlines;
    n->dialogue.lines[0]   = T(l0);
    n->dialogue.lines[1]   = (nlines>1) ? T(l1) : NULL;
    n->dialogue.lines[2]   = (nlines>2) ? T(l2) : NULL;
    n->dialogue.lines[3]   = NULL;
}

/* Re-run when language changes so dialogue text updates */
static void InitNPCs(void) {
    npc_count = 0;
    AddNPC("Jae",              370,320, 0xFFCC00FF, STATE_OVERWORLD,
           S_NPC_JAE_0,  S_NPC_JAE_1,  S_NPC_JAE_0, 2);
    AddNPC("Leo",              150,350, 0x33CC33FF, STATE_OVERWORLD,
           S_NPC_LEO_0,  S_NPC_LEO_1,  S_NPC_LEO_2, 3);
    AddNPC("Finn",             480,200, 0xFF99CCFF, STATE_OVERWORLD,
           S_NPC_FINN_0, S_NPC_FINN_1, S_NPC_FINN_0, 2);
    AddNPC("Miro's Dad",       200,300, 0x888888FF, STATE_MIRO_HOUSE,
           S_NPC_DAD_0,  S_NPC_DAD_1,  S_NPC_DAD_2,  3);
    AddNPC("Miro's Mom",       350,280, 0xFFAAAAFF, STATE_MIRO_HOUSE,
           S_NPC_MMOM_0, S_NPC_MMOM_1, S_NPC_MMOM_0, 2);
    AddNPC("Tay's Mom",        300,260, 0xAADDFFFF, STATE_TAY_HOUSE,
           S_NPC_TMOM_0, S_NPC_TMOM_1, S_NPC_TMOM_2, 3);
    AddNPC("Band Poster",      480,180, 0x444444FF, STATE_MIRO_ROOM,
           S_NPC_POSTER_0, S_NPC_POSTER_1, S_NPC_POSTER_0, 2);
    AddNPC("Workbench",        200,320, 0x7B5C3EFF, STATE_TAY_ROOM,
           S_NPC_BENCH_0, S_NPC_BENCH_1, S_NPC_BENCH_2, 3);
    AddNPC("Kira",             300,200, 0xFF66AAFF, STATE_SKATEPARK,
           S_NPC_KIRA_0, S_NPC_KIRA_1, S_NPC_KIRA_2, 3);
    AddNPC("Dev",              400,350, 0x66FFD9FF, STATE_SKATEPARK,
           S_NPC_DEV_0,  S_NPC_DEV_1,  S_NPC_DEV_0,  2);
    AddNPC("Skatepark Dude",   100,160, 0xCCCCCCFF, STATE_SKATEPARK,
           S_NPC_DUDE_0, S_NPC_DUDE_1, S_NPC_DUDE_2, 3);
}

/* ====================================================================
   UTILITY
   ==================================================================== */
#define SCREEN_W 640
#define SCREEN_H 480
#define INTERACT  36.0f
#define MAX_LES   6

static float Dist(float ax,float ay,float bx,float by) {
    float dx=ax-bx, dy=ay-by;
    return sqrtf(dx*dx+dy*dy);
}

static void StartDialogue(Dialogue *d, GameState ret) {
    activeDialogue = *d;
    dialogueLine   = 0;
    returnState    = ret;
    state          = STATE_DIALOGUE;
}

static void MovePlayer(Player *p) {
    u32 held = WPAD_ButtonsHeld(p->wpad_chan);
    float dx=0, dy=0;
    if (held & WPAD_BUTTON_RIGHT) dy -= p->speed;
    if (held & WPAD_BUTTON_LEFT)  dy += p->speed;
    if (held & WPAD_BUTTON_UP)    dx -= p->speed;
    if (held & WPAD_BUTTON_DOWN)  dx += p->speed;
    p->x += dx; p->y += dy;
    if (p->x < 16)        p->x = 16;
    if (p->x > SCREEN_W-16) p->x = SCREEN_W-16;
    if (p->y < 16)        p->y = 16;
    if (p->y > SCREEN_H-16) p->y = SCREEN_H-16;
}

static void DrawPlayer(Player *p, const char *lbl) {
    GRRLIB_Rectangle(p->x-10, p->y-10, 20, 20, p->color, 1);
    GRRLIB_Printf(p->x-16, p->y-26, GRRLIB_GetSystemFont(), 0xFFFFFFFF, 1, "%s", lbl);
}

static void DrawNPCsForZone(GameState zone) {
    for (int i=0; i<npc_count; i++) {
        if (npcs[i].zone != zone) continue;
        GRRLIB_Rectangle(npcs[i].x-8, npcs[i].y-8, 16, 16, npcs[i].color, 1);
        GRRLIB_Printf(npcs[i].x-20, npcs[i].y-22,
                      GRRLIB_GetSystemFont(), 0xFFFFFFFF, 1, "%s", npcs[i].name);
    }
}

static void CheckNPCInteract(Player *p, GameState zone, GameState ret) {
    if (!(WPAD_ButtonsDown(p->wpad_chan) & WPAD_BUTTON_A)) return;
    for (int i=0; i<npc_count; i++) {
        if (npcs[i].zone != zone) continue;
        if (Dist(p->x, p->y, npcs[i].x, npcs[i].y) < INTERACT) {
            StartDialogue(&npcs[i].dialogue, ret);
            return;
        }
    }
}

static int BothNear(float tx, float ty, float r) {
    return Dist(miro.x,miro.y,tx,ty)<r && Dist(tay.x,tay.y,tx,ty)<r;
}

/* ====================================================================
   HUD
   ==================================================================== */
static void DrawHUD(GameState zone) {
    StrID zid = S_ZONE_OVERWORLD;
    if (zone==STATE_MIRO_HOUSE) zid=S_ZONE_MIRO_HOUSE;
    if (zone==STATE_MIRO_ROOM)  zid=S_ZONE_MIRO_ROOM;
    if (zone==STATE_TAY_HOUSE)  zid=S_ZONE_TAY_HOUSE;
    if (zone==STATE_TAY_ROOM)   zid=S_ZONE_TAY_ROOM;
    if (zone==STATE_SKATEPARK)  zid=S_ZONE_SKATEPARK;
    if (zone==STATE_WORKSHOP)   zid=S_ZONE_WORKSHOP;
    GRRLIB_Printf(8, 8, GRRLIB_GetSystemFont(), 0xFFFFFFFF, 1, "%s", T(zid));

    /* HUD bottom: Tay Skate Lv / Lessons */
    char hud[64];
    snprintf(hud, sizeof(hud), T(S_HUD_LINE),
             taySkateLevel, tayLessonsCompleted, MAX_LES);
    GRRLIB_Printf(8, 460, GRRLIB_GetSystemFont(), 0xFFFFFFAA, 1, "%s", hud);

    if (workshopUnlocked)
        GRRLIB_Printf(340, 8, GRRLIB_GetSystemFont(), 0xFF66FFFF, 1,
                      "%s", T(S_WORKSHOP_UNLOCKED));
}

/* ====================================================================
   COLOURS
   ==================================================================== */
#define COL_GRASS    0x4A7C3FFF
#define COL_ROAD     0x666666FF
#define COL_HOUSE_M  0x8B5A2BFF
#define COL_HOUSE_T  0x3A6EA5FF
#define COL_SKATEPARK 0xCCCCCCFF
#define COL_WORKSHOP 0x2A2A2AFF
#define COL_FLOOR_M  0xD4A96AFF
#define COL_FLOOR_T  0xC8D8E8FF
#define COL_PURPLE   0x6A0DADFF
#define COL_WHITE    0xFFFFFFFF
#define COL_BLACK    0x000000FF

/* ====================================================================
   STATE: LOGO
   ==================================================================== */
static void UpdateLogo(void) {
    logoTimer += 1.0f/60.0f;
    if (logoTimer > 3.5f
     || (WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_A)
     || (WPAD_ButtonsDown(WPAD_CHAN_1)&WPAD_BUTTON_A))
        state = STATE_TITLE;
}
static void DrawLogo(void) {
    GRRLIB_FillScreen(COL_PURPLE);
    GRRLIB_Printf(60, 160, GRRLIB_GetSystemFont(), COL_WHITE, 3, "MiroTayWorkshop");
    GRRLIB_Printf(60, 220, GRRLIB_GetSystemFont(), COL_WHITE, 3, "RPG");
    GRRLIB_Printf(180, 380, GRRLIB_GetSystemFont(), 0xCCCCCCFF, 1,
                  "%s", T(S_PRESS_A_START));
}

/* ====================================================================
   STATE: TITLE
   ====================================================================
   Two menu items: [Start Game]  [Settings]
   D-Pad up/down to move cursor, A to confirm
   ==================================================================== */
static void UpdateTitle(void) {
    u32 downM = WPAD_ButtonsDown(WPAD_CHAN_0);
    u32 downT = WPAD_ButtonsDown(WPAD_CHAN_1);
    u32 down  = downM | downT;

    if (settingsCooldown > 0) settingsCooldown--;

    if (settingsCooldown == 0) {
        u32 heldM = WPAD_ButtonsHeld(WPAD_CHAN_0);
        u32 heldT = WPAD_ButtonsHeld(WPAD_CHAN_1);
        u32 held  = heldM | heldT;
        if (held & (WPAD_BUTTON_DOWN|WPAD_BUTTON_LEFT)) {
            titleSelection = (titleSelection+1)%2;
            settingsCooldown = 14;
        }
        if (held & (WPAD_BUTTON_UP|WPAD_BUTTON_RIGHT)) {
            titleSelection = (titleSelection+1)%2;
            settingsCooldown = 14;
        }
    }

    if (down & WPAD_BUTTON_A) {
        if (titleSelection == 0) {
            /* Start */
            miro.x=260; miro.y=300;
            tay.x =300; tay.y =300;
            state = STATE_OVERWORLD;
        } else {
            /* Settings */
            settingsSelection = (int)currentLang;
            settingsCooldown  = 0;
            state = STATE_SETTINGS;
        }
    }
}
static void DrawTitle(void) {
    GRRLIB_FillScreen(COL_PURPLE);
    GRRLIB_Printf(80, 40, GRRLIB_GetSystemFont(), COL_WHITE,   2, "MiroTayWorkshop RPG");
    GRRLIB_Printf(80, 90, GRRLIB_GetSystemFont(), 0xDDAAFFFF,  1, "%s", T(S_TITLE_SUBTITLE));

    /* Controls */
    GRRLIB_Printf(80, 150, GRRLIB_GetSystemFont(), 0x00AEFFFF, 1, "%s", T(S_TITLE_P1));
    GRRLIB_Printf(80, 172, GRRLIB_GetSystemFont(), 0xFF6600FF, 1, "%s", T(S_TITLE_P2));
    GRRLIB_Printf(80, 210, GRRLIB_GetSystemFont(), COL_WHITE,  1, "%s", T(S_TITLE_CONTROLS));
    GRRLIB_Printf(80, 230, GRRLIB_GetSystemFont(), COL_WHITE,  1, "%s", T(S_TITLE_HOME));

    /* Menu items */
    u32 colStart    = (titleSelection==0) ? 0xFFFF00FF : 0xAAAAAAFF;
    u32 colSettings = (titleSelection==1) ? 0xFFFF00FF : 0xAAAAAAFF;
    const char *arrowStart    = (titleSelection==0) ? "> " : "  ";
    const char *arrowSettings = (titleSelection==1) ? "> " : "  ";

    GRRLIB_Printf(200, 310, GRRLIB_GetSystemFont(), colStart,    2,
                  "%s%s", arrowStart, T(S_START_GAME));
    GRRLIB_Printf(200, 360, GRRLIB_GetSystemFont(), colSettings, 2,
                  "%s%s", arrowSettings, T(S_SETTINGS_MENU));

    /* Small language indicator */
    GRRLIB_Printf(480, 460, GRRLIB_GetSystemFont(), 0x888888FF, 1,
                  "Lang: %s", T(S_LANG_EN + (int)currentLang));
}

/* ====================================================================
   STATE: SETTINGS
   ====================================================================
   Language picker - D-Pad up/down, A to confirm, B to go back.
   Shows flag-coloured blocks next to each language name.
   ==================================================================== */
static u32 LANG_FLAG_COLORS[LANG_COUNT] = {
    0x003399FF,  /* EN - blue */
    0x000000FF,  /* DE - black */
    0xDC143CFF,  /* PL - red   */
    0xCC0000FF,  /* RU - red   */
};
static u32 LANG_FLAG_ACCENT[LANG_COUNT] = {
    0xCC0000FF,  /* EN - red    */
    0xDD0000FF,  /* DE - red    */
    0xFFFFFFFF,  /* PL - white  */
    0x003399FF,  /* RU - blue   */
};

static void UpdateSettings(void) {
    u32 down = WPAD_ButtonsDown(WPAD_CHAN_0) | WPAD_ButtonsDown(WPAD_CHAN_1);

    if (settingsCooldown > 0) settingsCooldown--;

    if (settingsCooldown == 0) {
        u32 held = WPAD_ButtonsHeld(WPAD_CHAN_0) | WPAD_ButtonsHeld(WPAD_CHAN_1);
        if (held & (WPAD_BUTTON_DOWN|WPAD_BUTTON_LEFT)) {
            settingsSelection = (settingsSelection+1) % LANG_COUNT;
            settingsCooldown = 14;
        }
        if (held & (WPAD_BUTTON_UP|WPAD_BUTTON_RIGHT)) {
            settingsSelection = (settingsSelection + LANG_COUNT - 1) % LANG_COUNT;
            settingsCooldown = 14;
        }
    }

    if (down & WPAD_BUTTON_A) {
        /* Apply language */
        currentLang = (Language)settingsSelection;
        InitNPCs();  /* rebuild NPC dialogue in new language */
        state = STATE_TITLE;
        titleSelection = 0;
    }
    if (down & WPAD_BUTTON_B) {
        state = STATE_TITLE;
    }
}

static void DrawSettings(void) {
    GRRLIB_FillScreen(0x1A0A2AFF);   /* dark purple background */

    /* Title */
    GRRLIB_Printf(200, 30, GRRLIB_GetSystemFont(), COL_WHITE, 2,
                  "%s", T(S_SETTINGS_TITLE));

    /* Subtitle */
    GRRLIB_Printf(180, 80, GRRLIB_GetSystemFont(), 0xDDAAFFFF, 1,
                  "%s", T(S_SELECT_LANGUAGE));

    /* Language options */
    const char *langNames[LANG_COUNT] = {
        T(S_LANG_EN), T(S_LANG_DE), T(S_LANG_PL), T(S_LANG_RU)
    };
    /* Native name display */
    const char *nativeNames[LANG_COUNT] = {
        "English", "Deutsch", "Polski", "Russkiy"
    };

    for (int i=0; i<LANG_COUNT; i++) {
        int  ypos    = 150 + i * 68;
        int  sel     = (i == settingsSelection);
        int  cur     = (i == (int)currentLang);
        u32  bgCol   = sel ? 0x6A0DADFF : 0x2A1A3AFF;
        u32  txtCol  = sel ? 0xFFFF00FF : (cur ? 0xAAFFAAFF : 0xCCCCCCFF);

        /* Selection box */
        GRRLIB_Rectangle(80, ypos-4, 480, 52, bgCol, 1);

        /* Flag colour blocks (left side) */
        GRRLIB_Rectangle(88, ypos+2, 28, 20, LANG_FLAG_COLORS[i], 1);
        GRRLIB_Rectangle(88, ypos+22,28, 20, LANG_FLAG_ACCENT[i], 1);

        /* Arrow */
        if (sel)
            GRRLIB_Printf(126, ypos+14, GRRLIB_GetSystemFont(), 0xFFFF00FF, 2, ">");

        /* Language name */
        GRRLIB_Printf(148, ypos+6,  GRRLIB_GetSystemFont(), txtCol, 2,
                      "%s", nativeNames[i]);

        /* Current language marker */
        if (cur)
            GRRLIB_Printf(430, ypos+14, GRRLIB_GetSystemFont(), 0x00FF88FF, 1,
                          "<< active");
    }

    /* Instructions */
    GRRLIB_Printf(100, 430, GRRLIB_GetSystemFont(), 0xFFCC66FF, 1,
                  "%s     %s",
                  T(S_SETTINGS_CONFIRM), T(S_SETTINGS_BACK));

    /* D-pad hint */
    GRRLIB_Printf(100, 450, GRRLIB_GetSystemFont(), 0x888888FF, 1,
                  "D-Pad Up/Down = navigate");
}

/* ====================================================================
   STATE: OVERWORLD
   ==================================================================== */
static void UpdateOverworld(void) {
    MovePlayer(&miro);
    MovePlayer(&tay);
    CheckNPCInteract(&miro, STATE_OVERWORLD, STATE_OVERWORLD);
    CheckNPCInteract(&tay,  STATE_OVERWORLD, STATE_OVERWORLD);

    u32 dM = WPAD_ButtonsDown(WPAD_CHAN_0);
    u32 dT = WPAD_ButtonsDown(WPAD_CHAN_1);

    if (Dist(miro.x,miro.y,120,200)<28 && (dM&WPAD_BUTTON_A)) {
        miro.x=200; miro.y=400; tay.x=240; tay.y=400;
        state=STATE_MIRO_HOUSE; }
    if (Dist(tay.x,tay.y,100,380)<28 && (dT&WPAD_BUTTON_A)) {
        miro.x=200; miro.y=400; tay.x=240; tay.y=400;
        state=STATE_TAY_HOUSE; }
    if ((Dist(miro.x,miro.y,530,120)<32||Dist(tay.x,tay.y,530,120)<32)
      && ((dM|dT)&WPAD_BUTTON_A)) {
        miro.x=200; miro.y=300; tay.x=250; tay.y=300;
        state=STATE_SKATEPARK; }
    if (workshopUnlocked
      && (Dist(miro.x,miro.y,540,400)<32||Dist(tay.x,tay.y,540,400)<32)
      && ((dM|dT)&WPAD_BUTTON_A)) {
        miro.x=300; miro.y=300; tay.x=340; tay.y=300;
        state=STATE_WORKSHOP; }
}
static void DrawOverworld(void) {
    GRRLIB_FillScreen(COL_GRASS);
    GRRLIB_Rectangle(0,290, SCREEN_W,60, COL_ROAD, 1);
    GRRLIB_Rectangle(310,0, 60,SCREEN_H, COL_ROAD, 1);

    /* Miro's House */
    GRRLIB_Rectangle(30,100, 160,130, COL_HOUSE_M, 1);
    GRRLIB_Printf(45,110, GRRLIB_GetSystemFont(), COL_WHITE, 1,
                  "%s", T(S_OW_MIRO_HOUSE));
    GRRLIB_Rectangle(100,215, 24,16, 0x442200FF, 1);
    GRRLIB_Printf(70,238, GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_ENTER));

    /* Tay's House */
    GRRLIB_Rectangle(20,360, 160,110, COL_HOUSE_T, 1);
    GRRLIB_Printf(35,370, GRRLIB_GetSystemFont(), COL_WHITE, 1,
                  "%s", T(S_OW_TAY_HOUSE));
    GRRLIB_Rectangle(82,460, 24,16, 0x1A3A6AFF, 1);
    GRRLIB_Printf(50,450, GRRLIB_GetSystemFont(), 0xAADDFFFF, 1, "%s", T(S_ENTER));

    /* Skatepark */
    GRRLIB_Rectangle(420,30, 200,180, COL_SKATEPARK, 1);
    GRRLIB_Printf(440,40, GRRLIB_GetSystemFont(), 0x333333FF, 1,
                  "%s", T(S_OW_SKATEPARK));
    GRRLIB_Rectangle(430,130, 60,50, 0xAAAAAA88, 1);
    GRRLIB_Rectangle(520,120, 80,60, 0xAAAAAA88, 1);
    GRRLIB_Rectangle(500,195, 24,16, 0x555555FF, 1);
    GRRLIB_Printf(468,214, GRRLIB_GetSystemFont(), 0x333333FF, 1, "%s", T(S_ENTER));

    /* Workshop / secret */
    if (workshopUnlocked) {
        GRRLIB_Rectangle(450,360, 150,100, COL_WORKSHOP, 1);
        GRRLIB_Printf(462,370, GRRLIB_GetSystemFont(), 0xFF66FFFF, 1,
                      "%s", T(S_OW_WORKSHOP));
        GRRLIB_Printf(458,430, GRRLIB_GetSystemFont(), 0xFF66FFFF, 1,
                      "%s", T(S_OW_WORKSHOP_ENTER));
    } else {
        GRRLIB_Rectangle(450,360, 150,100, 0x222222FF, 1);
        GRRLIB_Printf(462,370, GRRLIB_GetSystemFont(), 0x555555FF, 1,
                      "%s", T(S_OW_SECRET));
        if (tayLessonsCompleted>0) {
            char buf[32];
            snprintf(buf, sizeof(buf), T(S_OW_LESSONS_HINT),
                     tayLessonsCompleted, MAX_LES);
            GRRLIB_Printf(455,400, GRRLIB_GetSystemFont(), 0x555555FF, 1, "%s", buf);
        }
    }

    DrawNPCsForZone(STATE_OVERWORLD);
    DrawPlayer(&miro, "Miro");
    DrawPlayer(&tay,  "Tay");
    DrawHUD(STATE_OVERWORLD);
}

/* ====================================================================
   STATE: MIRO'S HOUSE
   ==================================================================== */
static void UpdateMiroHouse(void) {
    MovePlayer(&miro); MovePlayer(&tay);
    CheckNPCInteract(&miro, STATE_MIRO_HOUSE, STATE_MIRO_HOUSE);
    CheckNPCInteract(&tay,  STATE_MIRO_HOUSE, STATE_MIRO_HOUSE);
    u32 d = WPAD_ButtonsDown(WPAD_CHAN_0)|WPAD_ButtonsDown(WPAD_CHAN_1);
    if ((Dist(miro.x,miro.y,500,100)<30||Dist(tay.x,tay.y,500,100)<30)&&(d&WPAD_BUTTON_A)) {
        miro.x=300; miro.y=300; tay.x=340; tay.y=300; state=STATE_MIRO_ROOM; }
    if (d&WPAD_BUTTON_B) { miro.x=200; miro.y=300; tay.x=240; tay.y=300;
                            state=STATE_OVERWORLD; }
}
static void DrawMiroHouse(void) {
    GRRLIB_FillScreen(COL_FLOOR_M);
    GRRLIB_Printf(200,20, GRRLIB_GetSystemFont(), 0x442200FF, 2,
                  "%s", T(S_ZONE_MIRO_HOUSE));
    GRRLIB_Rectangle(20,80,  120,60, 0x6B3A1FFF, 1);
    GRRLIB_Printf(30,110, GRRLIB_GetSystemFont(), COL_WHITE, 1, "%s", T(S_ROOM_SOFA));
    GRRLIB_Rectangle(460,80, 80,80,  0x555533FF, 1);
    GRRLIB_Printf(464,90, GRRLIB_GetSystemFont(), COL_WHITE, 1, "%s", T(S_ROOM_TV));
    GRRLIB_Rectangle(200,280,140,80, 0xBB8855FF, 1);
    GRRLIB_Printf(215,310, GRRLIB_GetSystemFont(), COL_WHITE, 1, "%s", T(S_ROOM_KITCHEN));
    GRRLIB_Rectangle(470,60, 80,60,  0xAA7744FF, 1);
    GRRLIB_Printf(472,65, GRRLIB_GetSystemFont(), 0x333333FF, 1, "%s", T(S_ROOM_STAIRS));
    GRRLIB_Printf(458,114, GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_ROOM_STAIRS_UP));
    DrawNPCsForZone(STATE_MIRO_HOUSE);
    DrawPlayer(&miro,"Miro"); DrawPlayer(&tay,"Tay");
    DrawHUD(STATE_MIRO_HOUSE);
    GRRLIB_Printf(8,24, GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_LEAVE_OUTSIDE));
}

/* ====================================================================
   STATE: MIRO'S ROOM
   ==================================================================== */
static void UpdateMiroRoom(void) {
    MovePlayer(&miro); MovePlayer(&tay);
    CheckNPCInteract(&miro, STATE_MIRO_ROOM, STATE_MIRO_ROOM);
    CheckNPCInteract(&tay,  STATE_MIRO_ROOM, STATE_MIRO_ROOM);
    u32 d=WPAD_ButtonsDown(WPAD_CHAN_0)|WPAD_ButtonsDown(WPAD_CHAN_1);
    if (d&WPAD_BUTTON_B) state=STATE_MIRO_HOUSE;
}
static void DrawMiroRoom(void) {
    GRRLIB_FillScreen(0x2B2B4AFF);
    GRRLIB_Printf(200,14, GRRLIB_GetSystemFont(), COL_WHITE, 2,
                  "%s", T(S_ZONE_MIRO_ROOM));
    GRRLIB_Rectangle(20,60,  130,70, 0x336699FF, 1);
    GRRLIB_Printf(30,90,  GRRLIB_GetSystemFont(), COL_WHITE,    1, "%s", T(S_ROOM_BED));
    GRRLIB_Rectangle(400,60, 120,90, 0x111111FF, 1);
    GRRLIB_Printf(410,70, GRRLIB_GetSystemFont(), 0x00FF99FF,   1, "%s", T(S_ROOM_PC));
    GRRLIB_Printf(408,88, GRRLIB_GetSystemFont(), 0x00FF99FF,   1, "%s", T(S_ROOM_RGB));
    GRRLIB_Rectangle(20,300, 50,120, 0xAA2222FF, 1);
    GRRLIB_Printf(12,310, GRRLIB_GetSystemFont(), COL_WHITE,    1, "%s", T(S_ROOM_GUITAR));
    GRRLIB_Rectangle(80,340, 60,80,  0x333333FF, 1);
    GRRLIB_Printf(82,360, GRRLIB_GetSystemFont(), 0xFFFF00FF,   1, "%s", T(S_ROOM_AMP));
    GRRLIB_Rectangle(350,320,200,120,0x8B5A2BFF, 1);
    GRRLIB_Printf(380,360, GRRLIB_GetSystemFont(), COL_WHITE,   1, "%s", T(S_ROOM_DRUMS));
    GRRLIB_Rectangle(200,80, 14,120, 0xFF6600FF, 1);
    GRRLIB_Printf(170,90, GRRLIB_GetSystemFont(), 0xFF6600FF,   1, "%s", T(S_ROOM_SKATE));
    GRRLIB_Rectangle(460,170,60,80,  0x111111FF, 1);
    GRRLIB_Printf(462,175, GRRLIB_GetSystemFont(), 0xFFFFFFAA,  1, "%s", T(S_ROOM_POSTER));
    DrawNPCsForZone(STATE_MIRO_ROOM);
    DrawPlayer(&miro,"Miro"); DrawPlayer(&tay,"Tay");
    DrawHUD(STATE_MIRO_ROOM);
    GRRLIB_Printf(8,24, GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_LEAVE_BACK));
}

/* ====================================================================
   STATE: TAY'S HOUSE
   ==================================================================== */
static void UpdateTayHouse(void) {
    MovePlayer(&miro); MovePlayer(&tay);
    CheckNPCInteract(&miro, STATE_TAY_HOUSE, STATE_TAY_HOUSE);
    CheckNPCInteract(&tay,  STATE_TAY_HOUSE, STATE_TAY_HOUSE);
    u32 d=WPAD_ButtonsDown(WPAD_CHAN_0)|WPAD_ButtonsDown(WPAD_CHAN_1);
    if ((Dist(tay.x,tay.y,500,100)<30||Dist(miro.x,miro.y,500,100)<30)&&(d&WPAD_BUTTON_A)) {
        miro.x=300; miro.y=300; tay.x=340; tay.y=300; state=STATE_TAY_ROOM; }
    if (d&WPAD_BUTTON_B) { miro.x=240; miro.y=300; tay.x=280; tay.y=300;
                            state=STATE_OVERWORLD; }
}
static void DrawTayHouse(void) {
    GRRLIB_FillScreen(COL_FLOOR_T);
    GRRLIB_Printf(200,14, GRRLIB_GetSystemFont(), 0x1A3A6AFF, 2,
                  "%s", T(S_ZONE_TAY_HOUSE));
    GRRLIB_Rectangle(20,100,  140,60, 0x3A6EA5FF, 1);
    GRRLIB_Printf(40,120, GRRLIB_GetSystemFont(), COL_WHITE,   1, "%s", T(S_ROOM_COUCH));
    GRRLIB_Rectangle(380,80,  220,100,0xEEEECCFF, 1);
    GRRLIB_Printf(400,90, GRRLIB_GetSystemFont(), 0x333300FF,  1, "%s", T(S_ROOM_KITCHEN));
    GRRLIB_Rectangle(160,280, 200,100,0xD2B48CFF, 1);
    GRRLIB_Printf(180,320, GRRLIB_GetSystemFont(), 0x333333FF, 1, "%s", T(S_ROOM_DINING));
    GRRLIB_Rectangle(470,60,  80,60,  0xAA7744FF, 1);
    GRRLIB_Printf(472,65, GRRLIB_GetSystemFont(), 0x333333FF,  1, "%s", T(S_ROOM_STAIRS));
    GRRLIB_Printf(458,114, GRRLIB_GetSystemFont(),0x1A3A6AFF, 1, "%s", T(S_ROOM_STAIRS_UP));
    DrawNPCsForZone(STATE_TAY_HOUSE);
    DrawPlayer(&miro,"Miro"); DrawPlayer(&tay,"Tay");
    DrawHUD(STATE_TAY_HOUSE);
    GRRLIB_Printf(8,24, GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_LEAVE_OUTSIDE));
}

/* ====================================================================
   STATE: TAY'S ROOM
   ==================================================================== */
static void UpdateTayRoom(void) {
    MovePlayer(&miro); MovePlayer(&tay);
    CheckNPCInteract(&miro, STATE_TAY_ROOM, STATE_TAY_ROOM);
    CheckNPCInteract(&tay,  STATE_TAY_ROOM, STATE_TAY_ROOM);
    u32 d=WPAD_ButtonsDown(WPAD_CHAN_0)|WPAD_ButtonsDown(WPAD_CHAN_1);
    if (d&WPAD_BUTTON_B) state=STATE_TAY_HOUSE;
}
static void DrawTayRoom(void) {
    GRRLIB_FillScreen(0x1A3A1AFF);
    GRRLIB_Printf(200,14, GRRLIB_GetSystemFont(), COL_WHITE, 2,
                  "%s", T(S_ZONE_TAY_ROOM));
    GRRLIB_Rectangle(20,60,  130,70, 0x5577AAFF, 1);
    GRRLIB_Printf(30,90,  GRRLIB_GetSystemFont(), COL_WHITE,   1, "%s", T(S_ROOM_BED));
    GRRLIB_Rectangle(90,70, 80,10,   0xCCAAAAFF, 1);
    GRRLIB_Printf(94,54,  GRRLIB_GetSystemFont(), 0xCCAAAAFF,  1, "%s", T(S_ROOM_FLUTE));
    GRRLIB_Rectangle(350,60,  240,100,0x7B5C3EFF, 1);
    GRRLIB_Printf(370,70, GRRLIB_GetSystemFont(), COL_WHITE,   1, "%s", T(S_ROOM_WORKBENCH));
    GRRLIB_Printf(360,88, GRRLIB_GetSystemFont(), 0xFFCC66FF,  1, "%s", T(S_ROOM_TOOLS));
    GRRLIB_Rectangle(350,200, 180,120,0x002244FF, 1);
    GRRLIB_Printf(358,208, GRRLIB_GetSystemFont(),0x88CCFFFF,  1, "%s", T(S_ROOM_BLUEPRINTS));
    GRRLIB_Printf(358,224, GRRLIB_GetSystemFont(),0x88CCFFFF,  1, "%s", T(S_ROOM_BP_RAMP));
    GRRLIB_Printf(358,240, GRRLIB_GetSystemFont(),0x88CCFFFF,  1, "%s", T(S_ROOM_BP_SHELF));
    GRRLIB_Printf(358,256, GRRLIB_GetSystemFont(),0x88CCFFFF,  1, "%s", T(S_ROOM_BP_SECRET));
    GRRLIB_Rectangle(20,220,  220,60, 0x4A3728FF, 1);
    GRRLIB_Printf(26,232, GRRLIB_GetSystemFont(), COL_WHITE,   1, "%s", T(S_ROOM_PARTS));
    GRRLIB_Rectangle(20,380,  60,50,  0xFF3300FF, 1);
    GRRLIB_Printf(14,360, GRRLIB_GetSystemFont(), 0xFF3300FF,  1, "%s", T(S_ROOM_MTB));
    DrawNPCsForZone(STATE_TAY_ROOM);
    DrawPlayer(&miro,"Miro"); DrawPlayer(&tay,"Tay");
    DrawHUD(STATE_TAY_ROOM);
    GRRLIB_Printf(8,24, GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_LEAVE_BACK));
}

/* ====================================================================
   STATE: SKATEPARK
   ==================================================================== */
static void UpdateSkatepark(void) {
    MovePlayer(&miro); MovePlayer(&tay);
    CheckNPCInteract(&miro, STATE_SKATEPARK, STATE_SKATEPARK);
    CheckNPCInteract(&tay,  STATE_SKATEPARK, STATE_SKATEPARK);

    if (Dist(miro.x,miro.y,tay.x,tay.y) < 40.0f
     && (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_A)) {
        currentTrick = (tayLessonsCompleted < (int)(sizeof(TRICKS)/sizeof(TRICKS[0])))
                       ? tayLessonsCompleted
                       : (int)(sizeof(TRICKS)/sizeof(TRICKS[0]))-1;
        trickTimer=0; trickSuccess=0;
        state = STATE_SKATE_LESSON;
    }
    u32 d=WPAD_ButtonsDown(WPAD_CHAN_0)|WPAD_ButtonsDown(WPAD_CHAN_1);
    if (d&WPAD_BUTTON_B) { miro.x=260; miro.y=300; tay.x=300; tay.y=300;
                            state=STATE_OVERWORLD; }
}
static void DrawSkatepark(void) {
    GRRLIB_FillScreen(COL_SKATEPARK);

    /* Half-pipe */
    GRRLIB_Rectangle(80,30, 480,100, 0xAAAAAACC, 1);
    GRRLIB_Printf(240,70, GRRLIB_GetSystemFont(), 0x333333FF, 2,
                  "%s", T(S_SK_HALFPIPE));

    /* Rail section */
    GRRLIB_Rectangle(530,150, 80,200, 0x888888FF, 1);
    GRRLIB_Printf(532,190, GRRLIB_GetSystemFont(), 0x333333FF, 1, "%s", T(S_SK_RAILS));
    GRRLIB_Rectangle(545,160, 8,180, 0x444444FF, 1);
    GRRLIB_Rectangle(575,160, 8,180, 0x444444FF, 1);

    /* Mini ramp */
    GRRLIB_Rectangle(20,350, 200,110, 0x999999FF, 1);
    GRRLIB_Printf(40,395, GRRLIB_GetSystemFont(), 0x333333FF, 1,
                  "%s", T(S_SK_MINIRAMP));

    /* Bowl */
    GRRLIB_Rectangle(380,360, 220,100, 0x777777FF, 1);
    GRRLIB_Printf(420,400, GRRLIB_GetSystemFont(), 0x333333FF, 1, "%s", T(S_SK_BOWL));

    /* Main flat */
    GRRLIB_Rectangle(80,150, 430,180, 0xBBBBBBFF, 1);

    /* Teach prompt */
    if (Dist(miro.x,miro.y,tay.x,tay.y) < 60.0f)
        GRRLIB_Printf(130,340, GRRLIB_GetSystemFont(), COL_PURPLE, 1,
                      "%s", T(S_SK_TEACH_PROMPT));
    else
        GRRLIB_Printf(80,340, GRRLIB_GetSystemFont(), 0x555555FF, 1,
                      "%s", T(S_SK_TEACH_HINT));

    DrawNPCsForZone(STATE_SKATEPARK);
    DrawPlayer(&miro,"Miro"); DrawPlayer(&tay,"Tay");
    DrawHUD(STATE_SKATEPARK);
    GRRLIB_Printf(8,24, GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_LEAVE_PARK));
}

/* ====================================================================
   STATE: SKATE LESSON
   ==================================================================== */
static void UpdateSkateLesson(void) {
    trickTimer += 1.0f/60.0f;
    if (trickTimer > 4.0f) {
        trickSuccess=0; state=STATE_TRICK_ATTEMPT; trickTimer=0; return; }
    if ((WPAD_ButtonsDown(WPAD_CHAN_1)&WPAD_BUTTON_A) && trickTimer > 0.5f) {
        trickSuccess=1;
        tayLessonsCompleted++;
        taySkateLevel = (tayLessonsCompleted*10)/MAX_LES;
        if (taySkateLevel>10) taySkateLevel=10;
        if (tayLessonsCompleted>=MAX_LES) workshopUnlocked=1;
        state=STATE_TRICK_ATTEMPT; trickTimer=0;
    }
}
static void DrawSkateLesson(void) {
    GRRLIB_FillScreen(0x2B3B5BFF);
    GRRLIB_Printf(140,30, GRRLIB_GetSystemFont(), COL_WHITE, 2,
                  "%s", T(S_LESSON_TITLE));

    char buf[96];
    snprintf(buf,sizeof(buf), T(S_LESSON_MIRO), TRICKS[currentTrick]);
    GRRLIB_Printf(80,90, GRRLIB_GetSystemFont(), 0x00AEFFFF, 1, "%s", buf);
    GRRLIB_Printf(80,115, GRRLIB_GetSystemFont(), 0xFF6600FF, 1,
                  "%s", T(S_LESSON_TAY));

    /* Timing bar */
    float bar = 1.0f - (trickTimer/3.5f);
    if (bar<0) bar=0;
    GRRLIB_Rectangle(80,280, 480,30, 0x444444FF, 1);
    GRRLIB_Rectangle(80,280, (int)(480*bar),30, 0x00FF66FF, 1);
    GRRLIB_Printf(80,258, GRRLIB_GetSystemFont(), COL_WHITE, 1,
                  "%s", T(S_LESSON_HIT));

    /* Miro skater silhouette */
    GRRLIB_Rectangle(280,180, 30,40, 0x00AEFFFF, 1);
    GRRLIB_Rectangle(282,168, 26,18, 0xFFD700FF, 1);
    GRRLIB_Rectangle(270,212,  70,6, 0x333333FF, 1);

    snprintf(buf,sizeof(buf), T(S_LESSON_PROGRESS),
             tayLessonsCompleted+1, MAX_LES, taySkateLevel);
    GRRLIB_Printf(80,380, GRRLIB_GetSystemFont(), 0xFFCC66FF, 1, "%s", buf);
}

/* ====================================================================
   STATE: TRICK ATTEMPT (result)
   ==================================================================== */
static void UpdateTrickAttempt(void) {
    u32 d=WPAD_ButtonsDown(WPAD_CHAN_0)|WPAD_ButtonsDown(WPAD_CHAN_1);
    if (d&WPAD_BUTTON_A) state=STATE_SKATEPARK;
}
static void DrawTrickAttempt(void) {
    GRRLIB_FillScreen(0x1A2A1AFF);
    char buf[96];
    if (trickSuccess) {
        GRRLIB_Printf(100,120, GRRLIB_GetSystemFont(), 0x00FF66FF, 3,
                      "%s", T(S_TRICK_LANDED));
        snprintf(buf,sizeof(buf), T(S_TRICK_WIN_DESC), TRICKS[currentTrick]);
        GRRLIB_Printf(100,210, GRRLIB_GetSystemFont(), COL_WHITE,   1, "%s", buf);
        GRRLIB_Printf(100,240, GRRLIB_GetSystemFont(), 0xFF6600FF,  1,
                      "%s", T(S_TRICK_WIN_TAY));
        GRRLIB_Printf(100,270, GRRLIB_GetSystemFont(), 0x00AEFFFF,  1,
                      "%s", T(S_TRICK_WIN_MIRO));
        if (workshopUnlocked) {
            GRRLIB_Printf(60,320, GRRLIB_GetSystemFont(), 0xFF66FFFF, 2,
                          "%s", T(S_TRICK_UNLOCK));
            GRRLIB_Printf(60,380, GRRLIB_GetSystemFont(), 0xFF66FFFF, 1,
                          "%s", T(S_TRICK_UNLOCK2));
        }
    } else {
        GRRLIB_Printf(100,120, GRRLIB_GetSystemFont(), 0xFF3300FF, 3,
                      "%s", T(S_TRICK_BAILED));
        snprintf(buf,sizeof(buf), T(S_TRICK_FAIL_DESC), TRICKS[currentTrick]);
        GRRLIB_Printf(100,210, GRRLIB_GetSystemFont(), COL_WHITE,  1, "%s", buf);
        GRRLIB_Printf(100,240, GRRLIB_GetSystemFont(), 0xFF6600FF, 1,
                      "%s", T(S_TRICK_FAIL_TAY));
        GRRLIB_Printf(100,270, GRRLIB_GetSystemFont(), 0x00AEFFFF, 1,
                      "%s", T(S_TRICK_FAIL_MIRO));
    }
    GRRLIB_Printf(140,430, GRRLIB_GetSystemFont(), 0xFFCC66FF, 1,
                  "%s", T(S_CONTINUE));
}

/* ====================================================================
   STATE: WORKSHOP (plot twist)
   ==================================================================== */
static void UpdateWorkshop(void) {
    MovePlayer(&miro); MovePlayer(&tay);
    if (BothNear(320,240,60) && !endingTriggered
     && ((WPAD_ButtonsDown(WPAD_CHAN_0)|WPAD_ButtonsDown(WPAD_CHAN_1))&WPAD_BUTTON_A)) {
        endingTriggered=1; state=STATE_ENDING; }
    u32 d=WPAD_ButtonsDown(WPAD_CHAN_0)|WPAD_ButtonsDown(WPAD_CHAN_1);
    if (d&WPAD_BUTTON_B) { miro.x=260; miro.y=300; tay.x=300; tay.y=300;
                            state=STATE_OVERWORLD; }
}
static void DrawWorkshop(void) {
    GRRLIB_FillScreen(COL_WORKSHOP);
    GRRLIB_Printf(200,14, GRRLIB_GetSystemFont(), 0xFF66FFFF, 2,
                  "%s", T(S_ZONE_WORKSHOP));
    GRRLIB_Rectangle(80,120, 480,200, 0x3A2A1AFF, 1);
    GRRLIB_Printf(180,160, GRRLIB_GetSystemFont(), 0xFF66FFFF, 1, "%s", T(S_WS_DESC1));
    GRRLIB_Printf(140,180, GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_WS_DESC2));
    GRRLIB_Rectangle(30,60,  120,100, 0x001A44FF, 1);
    GRRLIB_Printf(34,66,  GRRLIB_GetSystemFont(), 0x88CCFFFF, 1, "%s", T(S_WS_BP_LABEL));
    GRRLIB_Printf(34,80,  GRRLIB_GetSystemFont(), 0x88CCFFFF, 1, "%s", T(S_WS_BP_LINE));
    GRRLIB_Printf(34,94,  GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_WS_BP_FINAL));
    GRRLIB_Rectangle(500,60, 100,240, 0x4A3728FF, 1);
    GRRLIB_Printf(504,66, GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_WS_TOOLS));
    GRRLIB_Rectangle(270,220,80,40, 0xFF66FF33, 1);
    GRRLIB_Printf(140,340, GRRLIB_GetSystemFont(), 0xFF66FFFF, 1,
                  "%s", T(S_WS_BOTH_PROMPT));
    DrawPlayer(&miro,"Miro"); DrawPlayer(&tay,"Tay");
    DrawHUD(STATE_WORKSHOP);
    GRRLIB_Printf(8,24, GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_LEAVE));
}

/* ====================================================================
   STATE: DIALOGUE
   ==================================================================== */
static void UpdateDialogue(void) {
    u32 d=WPAD_ButtonsDown(WPAD_CHAN_0)|WPAD_ButtonsDown(WPAD_CHAN_1);
    if (d&(WPAD_BUTTON_A|WPAD_BUTTON_B)) {
        dialogueLine++;
        if (dialogueLine >= activeDialogue.num_lines) {
            dialogueLine=0; state=returnState; }
    }
}
static void DrawDialogue(void) {
    switch(returnState) {
        case STATE_MIRO_HOUSE: DrawMiroHouse(); break;
        case STATE_MIRO_ROOM:  DrawMiroRoom();  break;
        case STATE_TAY_HOUSE:  DrawTayHouse();  break;
        case STATE_TAY_ROOM:   DrawTayRoom();   break;
        case STATE_SKATEPARK:  DrawSkatepark(); break;
        default:               DrawOverworld(); break;
    }
    GRRLIB_Rectangle(30,360, 580,100, 0x000000CCFF, 1);
    GRRLIB_Rectangle(30,360, 580,100, COL_PURPLE,   0);
    GRRLIB_Printf(46,370, GRRLIB_GetSystemFont(), 0xFFCC66FF, 1,
                  "%s:", activeDialogue.speaker);
    if (dialogueLine < activeDialogue.num_lines && activeDialogue.lines[dialogueLine])
        GRRLIB_Printf(46,394, GRRLIB_GetSystemFont(), COL_WHITE, 1,
                      "%s", activeDialogue.lines[dialogueLine]);
    GRRLIB_Printf(380,438, GRRLIB_GetSystemFont(), 0xAAAAFFFF, 1,
                  "[A] Next  [B] Skip");
}

/* ====================================================================
   STATE: ENDING (plot twist payoff)
   ==================================================================== */
static int endPage=0;
static void UpdateEnding(void) {
    u32 d=WPAD_ButtonsDown(WPAD_CHAN_0)|WPAD_ButtonsDown(WPAD_CHAN_1);
    if (d&WPAD_BUTTON_A) endPage++;
    if (endPage>5) {
        state=STATE_TITLE; endPage=0; endingTriggered=0;
        workshopUnlocked=0; tayLessonsCompleted=0; taySkateLevel=0;
        titleSelection=0;
    }
}
static void DrawEnding(void) {
    GRRLIB_FillScreen(0x0A0A1AFF);
    switch(endPage) {
        case 0:
            GRRLIB_Printf(60,120, GRRLIB_GetSystemFont(), 0xFF66FFFF, 2, "%s", T(S_END0_TITLE));
            GRRLIB_Printf(60,200, GRRLIB_GetSystemFont(), COL_WHITE,  1, "%s", T(S_END0_L0));
            GRRLIB_Printf(60,220, GRRLIB_GetSystemFont(), COL_WHITE,  1, "%s", T(S_END0_L1));
            break;
        case 1:
            GRRLIB_Printf(60,80,  GRRLIB_GetSystemFont(), 0xFFCC88FF, 1, "%s", T(S_END1_HEAD));
            GRRLIB_Printf(60,120, GRRLIB_GetSystemFont(), 0x88CCFFFF, 1, "%s", T(S_END1_L0));
            GRRLIB_Printf(60,145, GRRLIB_GetSystemFont(), 0x88CCFFFF, 1, "%s", T(S_END1_L1));
            GRRLIB_Printf(60,175, GRRLIB_GetSystemFont(), 0x88CCFFFF, 1, "%s", T(S_END1_L2));
            GRRLIB_Printf(60,200, GRRLIB_GetSystemFont(), 0x88CCFFFF, 1, "%s", T(S_END1_L3));
            GRRLIB_Printf(60,230, GRRLIB_GetSystemFont(), 0x88CCFFFF, 1, "%s", T(S_END1_L4));
            break;
        case 2:
            GRRLIB_Printf(60,120, GRRLIB_GetSystemFont(), 0xFF6600FF, 2, "Tay:");
            GRRLIB_Printf(60,180, GRRLIB_GetSystemFont(), 0xFF6600FF, 1, "%s", T(S_END2_L0));
            GRRLIB_Printf(60,204, GRRLIB_GetSystemFont(), 0xFF6600FF, 1, "%s", T(S_END2_L1));
            GRRLIB_Printf(60,240, GRRLIB_GetSystemFont(), 0xFF6600FF, 1, "%s", T(S_END2_L2));
            break;
        case 3:
            GRRLIB_Printf(60,120, GRRLIB_GetSystemFont(), 0x00AEFFFF, 2, "Miro:");
            GRRLIB_Printf(60,180, GRRLIB_GetSystemFont(), 0x00AEFFFF, 1, "%s", T(S_END3_L0));
            GRRLIB_Printf(60,210, GRRLIB_GetSystemFont(), 0x00AEFFFF, 1, "%s", T(S_END3_L1));
            GRRLIB_Printf(60,250, GRRLIB_GetSystemFont(), 0x00AEFFFF, 1, "%s", T(S_END3_L2));
            break;
        case 4:
            GRRLIB_Printf(60,120, GRRLIB_GetSystemFont(), 0xFF6600FF, 2, "Tay:");
            GRRLIB_Printf(60,180, GRRLIB_GetSystemFont(), 0xFF6600FF, 1, "%s", T(S_END4_L0));
            GRRLIB_Printf(60,210, GRRLIB_GetSystemFont(), 0xFF6600FF, 1, "%s", T(S_END4_L1));
            GRRLIB_Printf(60,250, GRRLIB_GetSystemFont(), COL_WHITE,  1, "%s", T(S_END4_DESC0));
            GRRLIB_Printf(60,270, GRRLIB_GetSystemFont(), COL_WHITE,  1, "%s", T(S_END4_DESC1));
            break;
        case 5:
            GRRLIB_FillScreen(COL_PURPLE);
            GRRLIB_Printf(80,140, GRRLIB_GetSystemFont(), COL_WHITE,  2, "MiroTayWorkshop RPG");
            GRRLIB_Printf(80,300, GRRLIB_GetSystemFont(), 0xFFCC66FF, 1, "%s", T(S_END5_THANKS));
            GRRLIB_Printf(80,330, GRRLIB_GetSystemFont(), 0xDDAAFFFF, 1, "%s", T(S_END5_CREDITS));
            GRRLIB_Printf(80,400, GRRLIB_GetSystemFont(), 0xAAAAFFFF, 1, "%s", T(S_END5_TITLE_SCR));
            break;
    }
    if (endPage<5)
        GRRLIB_Printf(460,450, GRRLIB_GetSystemFont(), 0xAAAAFFFF, 1,
                      "%s", T(S_CONTINUE));
}

/* ====================================================================
   MAIN
   ==================================================================== */
int main(int argc, char **argv) {
    GRRLIB_Init();
    WPAD_Init();

    InitNPCs();

    while (1) {
        WPAD_ScanPads();

        if ((WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_HOME)
         || (WPAD_ButtonsDown(WPAD_CHAN_1)&WPAD_BUTTON_HOME))
            break;

        switch(state) {
            case STATE_LOGO:          UpdateLogo();          break;
            case STATE_TITLE:         UpdateTitle();         break;
            case STATE_SETTINGS:      UpdateSettings();      break;
            case STATE_OVERWORLD:     UpdateOverworld();     break;
            case STATE_MIRO_HOUSE:    UpdateMiroHouse();     break;
            case STATE_MIRO_ROOM:     UpdateMiroRoom();      break;
            case STATE_TAY_HOUSE:     UpdateTayHouse();      break;
            case STATE_TAY_ROOM:      UpdateTayRoom();       break;
            case STATE_SKATEPARK:     UpdateSkatepark();     break;
            case STATE_SKATE_LESSON:  UpdateSkateLesson();   break;
            case STATE_TRICK_ATTEMPT: UpdateTrickAttempt();  break;
            case STATE_WORKSHOP:      UpdateWorkshop();      break;
            case STATE_DIALOGUE:      UpdateDialogue();      break;
            case STATE_ENDING:        UpdateEnding();        break;
        }

        switch(state) {
            case STATE_LOGO:          DrawLogo();            break;
            case STATE_TITLE:         DrawTitle();           break;
            case STATE_SETTINGS:      DrawSettings();        break;
            case STATE_OVERWORLD:     DrawOverworld();       break;
            case STATE_MIRO_HOUSE:    DrawMiroHouse();       break;
            case STATE_MIRO_ROOM:     DrawMiroRoom();        break;
            case STATE_TAY_HOUSE:     DrawTayHouse();        break;
            case STATE_TAY_ROOM:      DrawTayRoom();         break;
            case STATE_SKATEPARK:     DrawSkatepark();       break;
            case STATE_SKATE_LESSON:  DrawSkateLesson();     break;
            case STATE_TRICK_ATTEMPT: DrawTrickAttempt();    break;
            case STATE_WORKSHOP:      DrawWorkshop();        break;
            case STATE_DIALOGUE:      DrawDialogue();        break;
            case STATE_ENDING:        DrawEnding();          break;
        }

        GRRLIB_Render();
    }

    GRRLIB_Exit();
    exit(0);
    return 0;
}
