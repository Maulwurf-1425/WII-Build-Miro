/*
 * strings.h  -  MiroTayWorkshop RPG translation table
 * =====================================================
 * Languages: English, German, Polish, Russian
 *
 * NOTE ON SPECIAL CHARACTERS:
 *   GRRLIB's default bitmap system font is ASCII-only.
 *   German umlauts (ä ö ü ß), Polish diacritics (ą ę ś ź ż ć ń ó ł),
 *   and Russian Cyrillic ALL require a TTF Unicode font.
 *
 *   TO ENABLE PROPER RENDERING:
 *     1. Download a Unicode TTF (e.g. "NotoSans-Regular.ttf") and put it in data/
 *     2. In main.c, load it:
 *          GRRLIB_ttfFont *ttfFont = GRRLIB_LoadTTF(NotoSans_Regular_ttf, NotoSans_Regular_ttf_size);
 *     3. Replace all GRRLIB_Printf(...) calls with:
 *          GRRLIB_PrintfTTF(x, y, ttfFont, size, color, "text");
 *
 *   Until then the game uses ASCII-safe fallback text for DE/PL/RU.
 *   (German: ae/oe/ue/ss for umlauts. Polish: bare letters. Russian: Latin transliteration.)
 */

#pragma once

/* ====================================================================
   LANGUAGE ENUM
   ==================================================================== */
typedef enum {
    LANG_EN = 0,
    LANG_DE,
    LANG_PL,
    LANG_RU,
    LANG_COUNT
} Language;

/* ====================================================================
   STRING ID ENUM
   ==================================================================== */
typedef enum {

    /* --- TITLE / MENU --- */
    S_TITLE_SUBTITLE,   /* "Summer. Friends. Secrets."               */
    S_TITLE_P1,         /* "P1 [Wiimote 1 sideways] = MIRO"          */
    S_TITLE_P2,         /* "P2 [Wiimote 2 sideways] = TAY"           */
    S_TITLE_CONTROLS,   /* "D-Pad = Move    A = Interact    B = Back"*/
    S_TITLE_HOME,       /* "HOME  = Quit to Homebrew Channel"        */
    S_START_GAME,       /* "Start Game"                              */
    S_SETTINGS_MENU,    /* "Settings"                                */

    /* --- SETTINGS --- */
    S_SELECT_LANGUAGE,  /* "Select Language:"                        */
    S_LANG_EN,          /* "English"                                 */
    S_LANG_DE,          /* "Deutsch"                                 */
    S_LANG_PL,          /* "Polski"                                  */
    S_LANG_RU,          /* "Russkiy"  (Cyrillic: needs TTF)          */
    S_SETTINGS_TITLE,   /* "Settings" (header)                       */
    S_SETTINGS_LANG,    /* "Language:"                               */
    S_SETTINGS_BACK,    /* "[B] Back"                                */
    S_SETTINGS_CONFIRM, /* "[A] Select"                              */

    /* --- SHARED PROMPTS --- */
    S_PRESS_A_START,    /* "Press A to Start"                        */
    S_BACK,             /* "[B] Back"                                */
    S_CONTINUE,         /* "Press A to continue"                     */
    S_ENTER,            /* "[A] Enter"                               */
    S_LEAVE_OUTSIDE,    /* "[B] Outside"                             */
    S_LEAVE_BACK,       /* "[B] Back"                                */
    S_LEAVE_PARK,       /* "[B] Leave park"                          */
    S_LEAVE,            /* "[B] Leave"                               */

    /* --- HUD --- */
    S_HUD_LINE,         /* "Tay Skate Lv:%d  Lessons:%d/%d"         */
    S_WORKSHOP_UNLOCKED,/* "Workshop Unlocked!"                      */

    /* --- ZONE NAMES --- */
    S_ZONE_OVERWORLD,
    S_ZONE_MIRO_HOUSE,
    S_ZONE_MIRO_ROOM,
    S_ZONE_TAY_HOUSE,
    S_ZONE_TAY_ROOM,
    S_ZONE_SKATEPARK,
    S_ZONE_WORKSHOP,

    /* --- OVERWORLD LABELS --- */
    S_OW_MIRO_HOUSE,    /* "Miro's House"                            */
    S_OW_TAY_HOUSE,     /* "Tay's House"                             */
    S_OW_SKATEPARK,     /* "SKATEPARK"                               */
    S_OW_SECRET,        /* "???"                                     */
    S_OW_WORKSHOP,      /* "Workshop"                                */
    S_OW_WORKSHOP_ENTER,/* "[A] Enter"                               */
    S_OW_LESSONS_HINT,  /* "Lessons: %d/%d"                          */

    /* --- ROOM LABELS --- */
    S_ROOM_SOFA,        /* "Sofa"                                    */
    S_ROOM_TV,          /* "TV"                                      */
    S_ROOM_KITCHEN,     /* "Kitchen"                                 */
    S_ROOM_STAIRS,      /* "Stairs"                                  */
    S_ROOM_STAIRS_UP,   /* "[A] Room"                                */
    S_ROOM_BED,         /* "Bed"                                     */
    S_ROOM_PC,          /* "PC Setup"                                */
    S_ROOM_RGB,         /* "RGB yes"                                 */
    S_ROOM_GUITAR,      /* "Guitar"                                  */
    S_ROOM_AMP,         /* "Amp"                                     */
    S_ROOM_DRUMS,       /* "Drum Kit"                                */
    S_ROOM_SKATE,       /* "Skate"                                   */
    S_ROOM_POSTER,      /* "Poster"                                  */
    S_ROOM_COUCH,       /* "Couch"                                   */
    S_ROOM_DINING,      /* "Dining Table"                            */
    S_ROOM_WORKBENCH,   /* "WORKBENCH"                               */
    S_ROOM_TOOLS,       /* "Saw, hammer, screws"                     */
    S_ROOM_BLUEPRINTS,  /* "Blueprints:"                             */
    S_ROOM_BP_RAMP,     /* "- Ramp v3"                               */
    S_ROOM_BP_SHELF,    /* "- Shelf unit"                            */
    S_ROOM_BP_SECRET,   /* "- ???"                                   */
    S_ROOM_PARTS,       /* "Parts & Supplies"                        */
    S_ROOM_MTB,         /* "MTB helmet"                              */
    S_ROOM_FLUTE,       /* "Flute"                                   */

    /* --- SKATEPARK LABELS --- */
    S_SK_HALFPIPE,      /* "HALF-PIPE"                               */
    S_SK_RAILS,         /* "RAILS"                                   */
    S_SK_MINIRAMP,      /* "Mini Ramp"                               */
    S_SK_BOWL,          /* "Bowl"                                    */
    S_SK_TEACH_PROMPT,  /* "[Miro A] = Teach Tay a trick!"           */
    S_SK_TEACH_HINT,    /* "Miro: move close to Tay, then press A"  */

    /* --- WORKSHOP LABELS --- */
    S_WS_DESC1,         /* "A half-built skate ramp."                */
    S_WS_DESC2,         /* "The wood grain is fresh. Tay's work."   */
    S_WS_BP_LABEL,      /* "RAMP"                                    */
    S_WS_BP_LINE,       /* "Blueprint"                               */
    S_WS_BP_FINAL,      /* "v4 - FINAL"                              */
    S_WS_TOOLS,         /* "Tools"                                   */
    S_WS_BOTH_PROMPT,   /* "Both players: walk to the center [A]"   */

    /* --- SKATE LESSON --- */
    S_LESSON_TITLE,     /* "SKATE LESSON"                            */
    S_LESSON_MIRO,      /* "Miro: "Okay Tay, watch this. It's a %s."" */
    S_LESSON_TAY,       /* "Tay: "That looks insane...""             */
    S_LESSON_HIT,       /* "TAY [A]: Hit it! (timing window)"        */
    S_LESSON_PROGRESS,  /* "Lesson %d of %d  |  Tay Skate Lv:%d"    */

    /* --- TRICK RESULT --- */
    S_TRICK_LANDED,     /* "LANDED!"                                 */
    S_TRICK_BAILED,     /* "BAILED!"                                 */
    S_TRICK_WIN_DESC,   /* "Tay stomped the %s!"                     */
    S_TRICK_WIN_TAY,    /* "Tay: "OH! I can't believe I did it!""    */
    S_TRICK_WIN_MIRO,   /* "Miro: "LETS GOOO!""                      */
    S_TRICK_UNLOCK,     /* "Something unlocked..."                   */
    S_TRICK_UNLOCK2,    /* "Check the overworld. Bottom right."      */
    S_TRICK_FAIL_DESC,  /* "Tay didn't commit to the %s..."          */
    S_TRICK_FAIL_TAY,   /* "Tay: "Ow. Okay. Again.""                 */
    S_TRICK_FAIL_MIRO,  /* "Miro: "You'll get it. Keep pushing.""    */

    /* --- NPC: JAE (overworld) --- */
    S_NPC_JAE_0, S_NPC_JAE_1,

    /* --- NPC: LEO (overworld) --- */
    S_NPC_LEO_0, S_NPC_LEO_1, S_NPC_LEO_2,

    /* --- NPC: FINN (overworld) --- */
    S_NPC_FINN_0, S_NPC_FINN_1,

    /* --- NPC: MIRO'S DAD (Miro's house) --- */
    S_NPC_DAD_0, S_NPC_DAD_1, S_NPC_DAD_2,

    /* --- NPC: MIRO'S MOM (Miro's house) --- */
    S_NPC_MMOM_0, S_NPC_MMOM_1,

    /* --- NPC: TAY'S MOM (Tay's house) --- */
    S_NPC_TMOM_0, S_NPC_TMOM_1, S_NPC_TMOM_2,

    /* --- NPC: BAND POSTER (Miro's room) --- */
    S_NPC_POSTER_0, S_NPC_POSTER_1,

    /* --- NPC: WORKBENCH (Tay's room) --- */
    S_NPC_BENCH_0, S_NPC_BENCH_1, S_NPC_BENCH_2,

    /* --- NPC: KIRA (skatepark) --- */
    S_NPC_KIRA_0, S_NPC_KIRA_1, S_NPC_KIRA_2,

    /* --- NPC: DEV (skatepark) --- */
    S_NPC_DEV_0, S_NPC_DEV_1,

    /* --- NPC: SKATEPARK DUDE (skatepark) --- */
    S_NPC_DUDE_0, S_NPC_DUDE_1, S_NPC_DUDE_2,

    /* --- ENDING PAGE 0 --- */
    S_END0_TITLE, S_END0_L0, S_END0_L1,

    /* --- ENDING PAGE 1 (the note) --- */
    S_END1_HEAD, S_END1_L0, S_END1_L1, S_END1_L2, S_END1_L3, S_END1_L4,

    /* --- ENDING PAGE 2 (Tay speaks) --- */
    S_END2_L0, S_END2_L1, S_END2_L2,

    /* --- ENDING PAGE 3 (Miro speaks) --- */
    S_END3_L0, S_END3_L1, S_END3_L2,

    /* --- ENDING PAGE 4 (Tay replies) --- */
    S_END4_L0, S_END4_L1, S_END4_DESC0, S_END4_DESC1,

    /* --- ENDING PAGE 5 (credits) --- */
    S_END5_THANKS, S_END5_CREDITS, S_END5_TITLE_SCR,

    S_COUNT
} StrID;

/* ====================================================================
   TRANSLATION TABLE
   Columns: LANG_EN, LANG_DE, LANG_PL, LANG_RU
   ==================================================================== */
static const char *STRINGS[LANG_COUNT][S_COUNT] = {

/* ---- ENGLISH ---- */
{
    /* S_TITLE_SUBTITLE   */ "Summer. Friends. Secrets.",
    /* S_TITLE_P1         */ "P1 [Wiimote 1 sideways]  =  MIRO",
    /* S_TITLE_P2         */ "P2 [Wiimote 2 sideways]  =  TAY",
    /* S_TITLE_CONTROLS   */ "D-Pad = Move    A = Interact    B = Back",
    /* S_TITLE_HOME       */ "HOME = Quit to Homebrew Channel",
    /* S_START_GAME       */ "Start Game",
    /* S_SETTINGS_MENU    */ "Settings",
    /* S_SELECT_LANGUAGE  */ "Select Language:",
    /* S_LANG_EN          */ "English",
    /* S_LANG_DE          */ "Deutsch",
    /* S_LANG_PL          */ "Polski",
    /* S_LANG_RU          */ "Russkiy",
    /* S_SETTINGS_TITLE   */ "Settings",
    /* S_SETTINGS_LANG    */ "Language:",
    /* S_SETTINGS_BACK    */ "[B] Back",
    /* S_SETTINGS_CONFIRM */ "[A] Select",
    /* S_PRESS_A_START    */ "Press A to Start",
    /* S_BACK             */ "[B] Back",
    /* S_CONTINUE         */ "Press A to continue",
    /* S_ENTER            */ "[A] Enter",
    /* S_LEAVE_OUTSIDE    */ "[B] Outside",
    /* S_LEAVE_BACK       */ "[B] Back",
    /* S_LEAVE_PARK       */ "[B] Leave park",
    /* S_LEAVE            */ "[B] Leave",
    /* S_HUD_LINE         */ "Tay Skate Lv:%d  Lessons:%d/%d",
    /* S_WORKSHOP_UNLOCKED*/ "Workshop Unlocked!",
    /* S_ZONE_OVERWORLD   */ "Overworld",
    /* S_ZONE_MIRO_HOUSE  */ "Miro's House",
    /* S_ZONE_MIRO_ROOM   */ "Miro's Room",
    /* S_ZONE_TAY_HOUSE   */ "Tay's House",
    /* S_ZONE_TAY_ROOM    */ "Tay's Room",
    /* S_ZONE_SKATEPARK   */ "Skatepark",
    /* S_ZONE_WORKSHOP    */ "The Workshop",
    /* S_OW_MIRO_HOUSE    */ "Miro's House",
    /* S_OW_TAY_HOUSE     */ "Tay's House",
    /* S_OW_SKATEPARK     */ "SKATEPARK",
    /* S_OW_SECRET        */ "???",
    /* S_OW_WORKSHOP      */ "Workshop",
    /* S_OW_WORKSHOP_ENTER*/ "[A] Enter",
    /* S_OW_LESSONS_HINT  */ "Lessons: %d/%d",
    /* S_ROOM_SOFA        */ "Sofa",
    /* S_ROOM_TV          */ "TV",
    /* S_ROOM_KITCHEN     */ "Kitchen",
    /* S_ROOM_STAIRS      */ "Stairs",
    /* S_ROOM_STAIRS_UP   */ "[A] Room",
    /* S_ROOM_BED         */ "Bed",
    /* S_ROOM_PC          */ "PC Setup",
    /* S_ROOM_RGB         */ "RGB yes",
    /* S_ROOM_GUITAR      */ "Guitar",
    /* S_ROOM_AMP         */ "Amp",
    /* S_ROOM_DRUMS       */ "Drum Kit",
    /* S_ROOM_SKATE       */ "Skate",
    /* S_ROOM_POSTER      */ "Poster",
    /* S_ROOM_COUCH       */ "Couch",
    /* S_ROOM_DINING      */ "Dining Table",
    /* S_ROOM_WORKBENCH   */ "WORKBENCH",
    /* S_ROOM_TOOLS       */ "Saw, hammer, screws",
    /* S_ROOM_BLUEPRINTS  */ "Blueprints:",
    /* S_ROOM_BP_RAMP     */ "- Ramp v3",
    /* S_ROOM_BP_SHELF    */ "- Shelf unit",
    /* S_ROOM_BP_SECRET   */ "- ???",
    /* S_ROOM_PARTS       */ "Parts & Supplies",
    /* S_ROOM_MTB         */ "MTB helmet",
    /* S_ROOM_FLUTE       */ "Flute",
    /* S_SK_HALFPIPE      */ "HALF-PIPE",
    /* S_SK_RAILS         */ "RAILS",
    /* S_SK_MINIRAMP      */ "Mini Ramp",
    /* S_SK_BOWL          */ "Bowl",
    /* S_SK_TEACH_PROMPT  */ "[Miro A] = Teach Tay a trick!",
    /* S_SK_TEACH_HINT    */ "Miro: move close to Tay, then press A to teach",
    /* S_WS_DESC1         */ "A half-built skate ramp.",
    /* S_WS_DESC2         */ "The wood grain is fresh. Tay's work.",
    /* S_WS_BP_LABEL      */ "RAMP",
    /* S_WS_BP_LINE       */ "Blueprint",
    /* S_WS_BP_FINAL      */ "v4 - FINAL",
    /* S_WS_TOOLS         */ "Tools",
    /* S_WS_BOTH_PROMPT   */ "Both players: walk to the center [A]",
    /* S_LESSON_TITLE     */ "SKATE LESSON",
    /* S_LESSON_MIRO      */ "Miro: \"Okay Tay, watch this. It's a %s.\"",
    /* S_LESSON_TAY       */ "Tay: \"That looks insane...\"",
    /* S_LESSON_HIT       */ "TAY [A]: Hit it! (timing window)",
    /* S_LESSON_PROGRESS  */ "Lesson %d of %d  |  Tay Skate Lv:%d",
    /* S_TRICK_LANDED     */ "LANDED!",
    /* S_TRICK_BAILED     */ "BAILED!",
    /* S_TRICK_WIN_DESC   */ "Tay stomped the %s!",
    /* S_TRICK_WIN_TAY    */ "Tay: \"OH! I can't believe I actually did it!\"",
    /* S_TRICK_WIN_MIRO   */ "Miro: \"LETS GOOO!\"",
    /* S_TRICK_UNLOCK     */ "Something unlocked...",
    /* S_TRICK_UNLOCK2    */ "Check the overworld. Bottom right.",
    /* S_TRICK_FAIL_DESC  */ "Tay didn't commit to the %s...",
    /* S_TRICK_FAIL_TAY   */ "Tay: \"Ow. Okay. Again.\"",
    /* S_TRICK_FAIL_MIRO  */ "Miro: \"You'll get it. Keep pushing.\"",
    /* S_NPC_JAE_0        */ "Miro! You're finally outside.",
    /* S_NPC_JAE_1        */ "You should bring Tay to the park today.",
    /* S_NPC_LEO_0        */ "Has anyone seen my kneepads?",
    /* S_NPC_LEO_1        */ "I lost them AGAIN.",
    /* S_NPC_LEO_2        */ "Don't tell my mum.",
    /* S_NPC_FINN_0       */ "Race you to the skatepark!",
    /* S_NPC_FINN_1       */ "Last one there buys snacks.",
    /* S_NPC_DAD_0        */ "Don't skate till sunset again.",
    /* S_NPC_DAD_1        */ "And wear your helmet, please.",
    /* S_NPC_DAD_2        */ "...Also can you take the bins out?",
    /* S_NPC_MMOM_0       */ "Tay! Come in, I'll make sandwiches.",
    /* S_NPC_MMOM_1       */ "You two are always hungry after skating.",
    /* S_NPC_TMOM_0       */ "Tay, did you eat breakfast?",
    /* S_NPC_TMOM_1       */ "Miro, make sure he eats something.",
    /* S_NPC_TMOM_2       */ "There's leftover pasta in the fridge!",
    /* S_NPC_POSTER_0     */ "[A battered Blink-182 poster.]",
    /* S_NPC_POSTER_1     */ "[Miro's guitar leans against the amp.]",
    /* S_NPC_BENCH_0      */ "[Half-built shelf on the desk.]",
    /* S_NPC_BENCH_1      */ "[A flute case sits on the bed.]",
    /* S_NPC_BENCH_2      */ "[Blueprints everywhere.]",
    /* S_NPC_KIRA_0       */ "You skate? Cool. Respect.",
    /* S_NPC_KIRA_1       */ "Your friend still learning?",
    /* S_NPC_KIRA_2       */ "Everyone starts somewhere.",
    /* S_NPC_DEV_0        */ "Dude I just landed a tre-flip.",
    /* S_NPC_DEV_1        */ "No I'm not lying. Jae saw it.",
    /* S_NPC_DUDE_0       */ "Kid, when you commit - you COMMIT.",
    /* S_NPC_DUDE_1       */ "Half-hearted ollies end in scraped knees.",
    /* S_NPC_DUDE_2       */ "Trust your feet.",
    /* S_END0_TITLE       */ "Miro finds a note.",
    /* S_END0_L0          */ "Tucked under the ramp plans,",
    /* S_END0_L1          */ "a crumpled piece of paper in Tay's handwriting.",
    /* S_END1_HEAD        */ "[The note reads:]",
    /* S_END1_L0          */ "\"Miro - I've been building this ramp",
    /* S_END1_L1          */ " all summer. For us. For the backyard.\"",
    /* S_END1_L2          */ "\"You taught me to skate.",
    /* S_END1_L3          */ " I built us somewhere to do it.\"",
    /* S_END1_L4          */ "\"Workshop key under the drum kit. - T\"",
    /* S_END2_L0          */ "\"I started building it that first day",
    /* S_END2_L1          */ " you let me borrow your board.\"",
    /* S_END2_L2          */ "\"Before I could even ollie.\"",
    /* S_END3_L0          */ "\"You built a whole half-pipe.\"",
    /* S_END3_L1          */ "\"For us.\"",
    /* S_END3_L2          */ "\"...when do we skate it?\"",
    /* S_END4_L0          */ "\"Last coat of varnish dries tonight.\"",
    /* S_END4_L1          */ "\"Tomorrow morning. Sunrise session.\"",
    /* S_END4_DESC0       */ "[The two stand in the workshop doorway.",
    /* S_END4_DESC1       */ " The ramp fills the whole room.]",
    /* S_END5_THANKS      */ "Thanks for playing.",
    /* S_END5_CREDITS     */ "This game was made by Miro & Tay.",
    /* S_END5_TITLE_SCR   */ "[A] Title Screen",
},

/* ---- GERMAN / DEUTSCH ---- */
/* Note: ae=ae oe=oe ue=ue ss=ss (standard ASCII fallbacks for umlauts) */
{
    /* S_TITLE_SUBTITLE   */ "Sommer. Freunde. Geheimnisse.",
    /* S_TITLE_P1         */ "Sp.1 [Wiimote 1 quer]  =  MIRO",
    /* S_TITLE_P2         */ "Sp.2 [Wiimote 2 quer]  =  TAY",
    /* S_TITLE_CONTROLS   */ "Steuerkreuz=Bewegen  A=Interagieren  B=Zurueck",
    /* S_TITLE_HOME       */ "HOME = Beenden",
    /* S_START_GAME       */ "Spiel starten",
    /* S_SETTINGS_MENU    */ "Einstellungen",
    /* S_SELECT_LANGUAGE  */ "Sprache waehlen:",
    /* S_LANG_EN          */ "English",
    /* S_LANG_DE          */ "Deutsch",
    /* S_LANG_PL          */ "Polski",
    /* S_LANG_RU          */ "Russkiy",
    /* S_SETTINGS_TITLE   */ "Einstellungen",
    /* S_SETTINGS_LANG    */ "Sprache:",
    /* S_SETTINGS_BACK    */ "[B] Zurueck",
    /* S_SETTINGS_CONFIRM */ "[A] Auswaehlen",
    /* S_PRESS_A_START    */ "A druecken zum Starten",
    /* S_BACK             */ "[B] Zurueck",
    /* S_CONTINUE         */ "A druecken zum Weiterspielen",
    /* S_ENTER            */ "[A] Eintreten",
    /* S_LEAVE_OUTSIDE    */ "[B] Nach draussen",
    /* S_LEAVE_BACK       */ "[B] Zurueck",
    /* S_LEAVE_PARK       */ "[B] Park verlassen",
    /* S_LEAVE            */ "[B] Verlassen",
    /* S_HUD_LINE         */ "Tay Skate Lv:%d  Lektionen:%d/%d",
    /* S_WORKSHOP_UNLOCKED*/ "Werkstatt freigeschaltet!",
    /* S_ZONE_OVERWORLD   */ "Stadt",
    /* S_ZONE_MIRO_HOUSE  */ "Miros Haus",
    /* S_ZONE_MIRO_ROOM   */ "Miros Zimmer",
    /* S_ZONE_TAY_HOUSE   */ "Tays Haus",
    /* S_ZONE_TAY_ROOM    */ "Tays Zimmer",
    /* S_ZONE_SKATEPARK   */ "Skatepark",
    /* S_ZONE_WORKSHOP    */ "Die Werkstatt",
    /* S_OW_MIRO_HOUSE    */ "Miros Haus",
    /* S_OW_TAY_HOUSE     */ "Tays Haus",
    /* S_OW_SKATEPARK     */ "SKATEPARK",
    /* S_OW_SECRET        */ "???",
    /* S_OW_WORKSHOP      */ "Werkstatt",
    /* S_OW_WORKSHOP_ENTER*/ "[A] Eintreten",
    /* S_OW_LESSONS_HINT  */ "Lektionen: %d/%d",
    /* S_ROOM_SOFA        */ "Sofa",
    /* S_ROOM_TV          */ "Fernseher",
    /* S_ROOM_KITCHEN     */ "Kueche",
    /* S_ROOM_STAIRS      */ "Treppe",
    /* S_ROOM_STAIRS_UP   */ "[A] Zimmer",
    /* S_ROOM_BED         */ "Bett",
    /* S_ROOM_PC          */ "PC-Setup",
    /* S_ROOM_RGB         */ "RGB natuerlich",
    /* S_ROOM_GUITAR      */ "Gitarre",
    /* S_ROOM_AMP         */ "Verstaerker",
    /* S_ROOM_DRUMS       */ "Schlagzeug",
    /* S_ROOM_SKATE       */ "Skateboard",
    /* S_ROOM_POSTER      */ "Poster",
    /* S_ROOM_COUCH       */ "Couch",
    /* S_ROOM_DINING      */ "Esstisch",
    /* S_ROOM_WORKBENCH   */ "WERKBANK",
    /* S_ROOM_TOOLS       */ "Saege, Hammer, Schrauben",
    /* S_ROOM_BLUEPRINTS  */ "Bauplaene:",
    /* S_ROOM_BP_RAMP     */ "- Rampe v3",
    /* S_ROOM_BP_SHELF    */ "- Regaleinheit",
    /* S_ROOM_BP_SECRET   */ "- ???",
    /* S_ROOM_PARTS       */ "Teile & Material",
    /* S_ROOM_MTB         */ "MTB-Helm",
    /* S_ROOM_FLUTE       */ "Floete",
    /* S_SK_HALFPIPE      */ "HALFPIPE",
    /* S_SK_RAILS         */ "RAILS",
    /* S_SK_MINIRAMP      */ "Miniramp",
    /* S_SK_BOWL          */ "Bowl",
    /* S_SK_TEACH_PROMPT  */ "[Miro A] = Tay einen Trick beibringen!",
    /* S_SK_TEACH_HINT    */ "Miro: geh nah zu Tay, dann A druecken",
    /* S_WS_DESC1         */ "Eine halb fertige Skaterampe.",
    /* S_WS_DESC2         */ "Das Holz ist frisch. Tays Arbeit.",
    /* S_WS_BP_LABEL      */ "RAMPE",
    /* S_WS_BP_LINE       */ "Bauplan",
    /* S_WS_BP_FINAL      */ "v4 - FINAL",
    /* S_WS_TOOLS         */ "Werkzeuge",
    /* S_WS_BOTH_PROMPT   */ "Beide Spieler: zur Mitte gehen [A]",
    /* S_LESSON_TITLE     */ "SKATE-LEKTION",
    /* S_LESSON_MIRO      */ "Miro: \"Okay Tay, schau. Das ist ein %s.\"",
    /* S_LESSON_TAY       */ "Tay: \"Das sieht wahnsinnig aus...\"",
    /* S_LESSON_HIT       */ "TAY [A]: Jetzt! (Timing-Fenster)",
    /* S_LESSON_PROGRESS  */ "Lektion %d von %d  |  Tay Skate Lv:%d",
    /* S_TRICK_LANDED     */ "GELANDET!",
    /* S_TRICK_BAILED     */ "GESTUERZT!",
    /* S_TRICK_WIN_DESC   */ "Tay hat den %s geschafft!",
    /* S_TRICK_WIN_TAY    */ "Tay: \"OH! Ich kanns nicht glauben!\"",
    /* S_TRICK_WIN_MIRO   */ "Miro: \"YESSS!\"",
    /* S_TRICK_UNLOCK     */ "Etwas wurde freigeschaltet...",
    /* S_TRICK_UNLOCK2    */ "Schau in der Stadt nach. Unten rechts.",
    /* S_TRICK_FAIL_DESC  */ "Tay hat den %s nicht geschafft...",
    /* S_TRICK_FAIL_TAY   */ "Tay: \"Au. Okay. Nochmal.\"",
    /* S_TRICK_FAIL_MIRO  */ "Miro: \"Du schaffst das. Weitermachen.\"",
    /* S_NPC_JAE_0        */ "Miro! Endlich bist du draussen.",
    /* S_NPC_JAE_1        */ "Du solltest Tay heute zum Park mitnehmen.",
    /* S_NPC_LEO_0        */ "Hat jemand meine Knieschoner gesehen?",
    /* S_NPC_LEO_1        */ "Ich hab sie SCHON WIEDER verloren.",
    /* S_NPC_LEO_2        */ "Sag das nicht meiner Mum.",
    /* S_NPC_FINN_0       */ "Wettrennen zum Skatepark!",
    /* S_NPC_FINN_1       */ "Wer zuletzt kommt, kauft Snacks.",
    /* S_NPC_DAD_0        */ "Fahr nicht wieder bis Sonnenuntergang.",
    /* S_NPC_DAD_1        */ "Und trag deinen Helm, bitte.",
    /* S_NPC_DAD_2        */ "...Kannst du auch den Muell rausbringen?",
    /* S_NPC_MMOM_0       */ "Tay! Komm rein, ich mach Sandwiches.",
    /* S_NPC_MMOM_1       */ "Ihr seid nach dem Skaten immer hungrig.",
    /* S_NPC_TMOM_0       */ "Tay, hast du gefruestuckt?",
    /* S_NPC_TMOM_1       */ "Miro, pass auf dass er was isst.",
    /* S_NPC_TMOM_2       */ "Im Kuehlschrank ist noch Pasta!",
    /* S_NPC_POSTER_0     */ "[Ein altes Blink-182-Poster.]",
    /* S_NPC_POSTER_1     */ "[Miros Gitarre lehnt am Verstaerker.]",
    /* S_NPC_BENCH_0      */ "[Halb fertiges Regal auf dem Schreibtisch.]",
    /* S_NPC_BENCH_1      */ "[Ein Floetenkoffer liegt auf dem Bett.]",
    /* S_NPC_BENCH_2      */ "[Ueberall Bauplae ne.]",
    /* S_NPC_KIRA_0       */ "Du skatest? Cool. Respekt.",
    /* S_NPC_KIRA_1       */ "Dein Freund lernt noch?",
    /* S_NPC_KIRA_2       */ "Jeder faengt irgendwo an.",
    /* S_NPC_DEV_0        */ "Alter, ich hab gerade einen Tre-Flip gelandet.",
    /* S_NPC_DEV_1        */ "Nein, ich luege nicht. Jae hat's gesehen.",
    /* S_NPC_DUDE_0       */ "Wenn du's machst - dann machst du's RICHTIG.",
    /* S_NPC_DUDE_1       */ "Halbherzige Ollies enden mit aufgeschuerften Knien.",
    /* S_NPC_DUDE_2       */ "Vertrau deinen Fuessen.",
    /* S_END0_TITLE       */ "Miro findet einen Zettel.",
    /* S_END0_L0          */ "Versteckt unter den Rampenplaenen,",
    /* S_END0_L1          */ "ein zerknittertes Blatt in Tays Handschrift.",
    /* S_END1_HEAD        */ "[Der Zettel lautet:]",
    /* S_END1_L0          */ "\"Miro - ich baue diese Rampe",
    /* S_END1_L1          */ " den ganzen Sommer. Fuer uns. Fuer den Garten.\"",
    /* S_END1_L2          */ "\"Du hast mir das Skaten beigebracht.",
    /* S_END1_L3          */ " Ich hab uns einen Ort gebaut, wo wir es tun koennen.\"",
    /* S_END1_L4          */ "\"Werkstattschluessel unter dem Schlagzeug. - T\"",
    /* S_END2_L0          */ "\"Ich hab angefangen, als du mir",
    /* S_END2_L1          */ " das erste Mal dein Board geliehen hast.\"",
    /* S_END2_L2          */ "\"Bevor ich auch nur einen Ollie konnte.\"",
    /* S_END3_L0          */ "\"Du hast eine ganze Halfpipe gebaut.\"",
    /* S_END3_L1          */ "\"Fuer uns.\"",
    /* S_END3_L2          */ "\"...wann fahren wir drauf?\"",
    /* S_END4_L0          */ "\"Der letzte Lackierdurchgang trocknet heute Nacht.\"",
    /* S_END4_L1          */ "\"Morgen frueh. Sonnenaufgang-Session.\"",
    /* S_END4_DESC0       */ "[Die zwei stehen in der Werkstatttuer.",
    /* S_END4_DESC1       */ " Die Rampe fuellt den ganzen Raum.]",
    /* S_END5_THANKS      */ "Danke fuers Spielen.",
    /* S_END5_CREDITS     */ "Dieses Spiel wurde von Miro & Tay gemacht.",
    /* S_END5_TITLE_SCR   */ "[A] Titelbildschirm",
},

/* ---- POLISH / POLSKI ---- */
/* Note: Polish diacritics replaced with base ASCII letters */
/* a=a c=c e=e l=l n=n o=o s=s z=z (needs TTF for proper display) */
{
    /* S_TITLE_SUBTITLE   */ "Bober kurva!",
    /* S_TITLE_P1         */ "Gr.1 [Wiimote 1 poziomo]  =  MIRO",
    /* S_TITLE_P2         */ "Gr.2 [Wiimote 2 poziomo]  =  TAY",
    /* S_TITLE_CONTROLS   */ "Kierunkowskaz=Ruch  A=Akcja  B=Wstecz",
    /* S_TITLE_HOME       */ "HOME = Wyjdz do Homebrew Channel",
    /* S_START_GAME       */ "Nowa gra",
    /* S_SETTINGS_MENU    */ "Ustawienia",
    /* S_SELECT_LANGUAGE  */ "Wybierz jezyk:",
    /* S_LANG_EN          */ "English",
    /* S_LANG_DE          */ "Deutsch",
    /* S_LANG_PL          */ "Polski",
    /* S_LANG_RU          */ "Russkiy",
    /* S_SETTINGS_TITLE   */ "Ustawienia",
    /* S_SETTINGS_LANG    */ "Jezyk:",
    /* S_SETTINGS_BACK    */ "[B] Wstecz",
    /* S_SETTINGS_CONFIRM */ "[A] Wybierz",
    /* S_PRESS_A_START    */ "Nacisnij A aby zaczac",
    /* S_BACK             */ "[B] Wstecz",
    /* S_CONTINUE         */ "Nacisnij A aby kontynuowac",
    /* S_ENTER            */ "[A] Wejdz",
    /* S_LEAVE_OUTSIDE    */ "[B] Na zewnatrz",
    /* S_LEAVE_BACK       */ "[B] Wstecz",
    /* S_LEAVE_PARK       */ "[B] Wyjdz z parku",
    /* S_LEAVE            */ "[B] Wyjdz",
    /* S_HUD_LINE         */ "Tay Skate Poz:%d  Lekcje:%d/%d",
    /* S_WORKSHOP_UNLOCKED*/ "Warsztat odblokowany!",
    /* S_ZONE_OVERWORLD   */ "Miasto",
    /* S_ZONE_MIRO_HOUSE  */ "Dom Miro",
    /* S_ZONE_MIRO_ROOM   */ "Pokoj Miro",
    /* S_ZONE_TAY_HOUSE   */ "Dom Taya",
    /* S_ZONE_TAY_ROOM    */ "Pokoj Taya",
    /* S_ZONE_SKATEPARK   */ "Skatepark",
    /* S_ZONE_WORKSHOP    */ "Warsztat",
    /* S_OW_MIRO_HOUSE    */ "Dom Miro",
    /* S_OW_TAY_HOUSE     */ "Dom Taya",
    /* S_OW_SKATEPARK     */ "SKATEPARK",
    /* S_OW_SECRET        */ "???",
    /* S_OW_WORKSHOP      */ "Warsztat kurva",
    /* S_OW_WORKSHOP_ENTER*/ "[A] Wejdz",
    /* S_OW_LESSONS_HINT  */ "Lekcje: %d/%d",
    /* S_ROOM_SOFA        */ "Sofa",
    /* S_ROOM_TV          */ "Telewizor",
    /* S_ROOM_KITCHEN     */ "Kuchnia",
    /* S_ROOM_STAIRS      */ "Schody",
    /* S_ROOM_STAIRS_UP   */ "[A] Pokoj",
    /* S_ROOM_BED         */ "Lozko",
    /* S_ROOM_PC          */ "Stanowisko PC",
    /* S_ROOM_RGB         */ "RGB oczywiscie",
    /* S_ROOM_GUITAR      */ "kurva Gitara",
    /* S_ROOM_AMP         */ "Wzmacniacz",
    /* S_ROOM_DRUMS       */ "Perkusja",
    /* S_ROOM_SKATE       */ "Deska",
    /* S_ROOM_POSTER      */ "Plakat",
    /* S_ROOM_COUCH       */ "Kanapa",
    /* S_ROOM_DINING      */ "Stol jadalny",
    /* S_ROOM_WORKBENCH   */ "STOL ROBOCZY",
    /* S_ROOM_TOOLS       */ "Pilka, mlot, sruby",
    /* S_ROOM_BLUEPRINTS  */ "Plany:",
    /* S_ROOM_BP_RAMP     */ "- Rampa v3",
    /* S_ROOM_BP_SHELF    */ "- Polka",
    /* S_ROOM_BP_SECRET   */ "- ???",
    /* S_ROOM_PARTS       */ "Czesci i materialy",
    /* S_ROOM_MTB         */ "Kask MTB",
    /* S_ROOM_FLUTE       */ "Flet kurva",
    /* S_SK_HALFPIPE      */ "HALFPIPE",
    /* S_SK_RAILS         */ "RELINGI",
    /* S_SK_MINIRAMP      */ "Mala rampa",
    /* S_SK_BOWL          */ "Bowl",
    /* S_SK_TEACH_PROMPT  */ "[Miro A] = Naucz Taya triku!",
    /* S_SK_TEACH_HINT    */ "Miro: podejdz do Taya i nacisnij A",
    /* S_WS_DESC1         */ "Pol skonczona rampa skatowa.",
    /* S_WS_DESC2         */ "Drewno jest swierze. Robota Taya.",
    /* S_WS_BP_LABEL      */ "RAMPA",
    /* S_WS_BP_LINE       */ "Plan budowy",
    /* S_WS_BP_FINAL      */ "v4 - OSTATECZNY",
    /* S_WS_TOOLS         */ "Narzedzia",
    /* S_WS_BOTH_PROMPT   */ "Obaj gracze: idz do srodka [A]",
    /* S_LESSON_TITLE     */ "LEKCJA JAZDY",
    /* S_LESSON_MIRO      */ "Miro: \"Dobra Tay, patrz. To jest %s.\"",
    /* S_LESSON_TAY       */ "Tay: \"To wyglada szalenie...\"",
    /* S_LESSON_HIT       */ "TAY [A]: Teraz! (okno czasowe)",
    /* S_LESSON_PROGRESS  */ "Lekcja %d z %d  |  Tay Skate Poz:%d",
    /* S_TRICK_LANDED     */ "UDANE!",
    /* S_TRICK_BAILED     */ "WYWROTKA!",
    /* S_TRICK_WIN_DESC   */ "Tay wyladowal %s!",
    /* S_TRICK_WIN_TAY    */ "Tay: \"O! Nie moge uwierzyc, ze to zrobilem!\"",
    /* S_TRICK_WIN_MIRO   */ "Miro: \"LECIMY!\"",
    /* S_TRICK_UNLOCK     */ "Cos zostalo odblokowane...",
    /* S_TRICK_UNLOCK2    */ "Sprawdz miasto. Prawy dolny rog.",
    /* S_TRICK_FAIL_DESC  */ "Tay nie zaryzykowal %s...",
    /* S_TRICK_FAIL_TAY   */ "Tay: \"Au. Okej. Jeszcze raz.\"",
    /* S_TRICK_FAIL_MIRO  */ "Miro: \"Dasz rade. Nie poddawaj sie.\"",
    /* S_NPC_JAE_0        */ "Miro! W koncu wyszedles na zewnatrz.",
    /* S_NPC_JAE_1        */ "Powinienes zabrac Taya do parku dzisiaj.",
    /* S_NPC_LEO_0        */ "Ktos widzial moje ochraniacze?",
    /* S_NPC_LEO_1        */ "ZNOWU je zgubilam.",
    /* S_NPC_LEO_2        */ "Nie mow mamie.",
    /* S_NPC_FINN_0       */ "Wyscig do skateparku!",
    /* S_NPC_FINN_1       */ "Kto ostatni, ten placi za jedzenie.",
    /* S_NPC_DAD_0        */ "Nie jezdz znowu do zachodu slonca.",
    /* S_NPC_DAD_1        */ "I zaloz kask, prosze.",
    /* S_NPC_DAD_2        */ "...Czy mozesz wyniesc smieci?",
    /* S_NPC_MMOM_0       */ "Tay! Wejdz, zrobie kanapki.",
    /* S_NPC_MMOM_1       */ "Wy dwaj zawsze jestescie glodni po jazdzie.",
    /* S_NPC_TMOM_0       */ "Tay, czy zjadles sniadanie?",
    /* S_NPC_TMOM_1       */ "Miro, upewnij sie, ze cos zje.",
    /* S_NPC_TMOM_2       */ "W lodowce jest makaron z wczoraj!",
    /* S_NPC_POSTER_0     */ "[Wytarty plakat Blink-182.]",
    /* S_NPC_POSTER_1     */ "[Gitara Miro opiera sie o wzmacniacz.]",
    /* S_NPC_BENCH_0      */ "[Pol skonczona polka na biurku.]",
    /* S_NPC_BENCH_1      */ "[Na lozku lezy futeral na flet.]",
    /* S_NPC_BENCH_2      */ "[Wszedzie plany budowlane.]",
    /* S_NPC_KIRA_0       */ "Jezdzisz? Super. Szacun.",
    /* S_NPC_KIRA_1       */ "Twoj kumpel jeszcze sie uczy?",
    /* S_NPC_KIRA_2       */ "Kazdy gdzies zaczyna.",
    /* S_NPC_DEV_0        */ "Stary, wlasnie wyladowalem tre-flip.",
    /* S_NPC_DEV_1        */ "Nie, nie klamie. Jae widzial.",
    /* S_NPC_DUDE_0       */ "Jak sie angazujesz - to sie ANGAZUJESZ.",
    /* S_NPC_DUDE_1       */ "Polowiczne ollies koncza sie obtartymi kolanami.",
    /* S_NPC_DUDE_2       */ "Ufaj swoim stopom.",
    /* S_END0_TITLE       */ "Miro znajduje kartke.",
    /* S_END0_L0          */ "Ukryta pod planami rampy,",
    /* S_END0_L1          */ "zmiety kawalet papieru zapisany reka Taya.",
    /* S_END1_HEAD        */ "[Kartka glosit:]",
    /* S_END1_L0          */ "\"Miro - buduje te rampe",
    /* S_END1_L1          */ " cale lato. Dla nas. Na podworko.\"",
    /* S_END1_L2          */ "\"Ty nauczyles mnie jezdzic.",
    /* S_END1_L3          */ " Ja zbudowalem nam miejsce do tego.\"",
    /* S_END1_L4          */ "\"Klucz do warsztatu pod perkusja. - T\"",
    /* S_END2_L0          */ "\"Zaczelaem budowac tego pierwszego dnia,",
    /* S_END2_L1          */ " kiedy pozyczyles mi swoja deske.\"",
    /* S_END2_L2          */ "\"Zanim jeszcze umialem zrobic olliego.\"",
    /* S_END3_L0          */ "\"Zbudowales cala halfpipe.\"",
    /* S_END3_L1          */ "\"Dla nas.\"",
    /* S_END3_L2          */ "\"...kiedy na nia wjedziemy?\"",
    /* S_END4_L0          */ "\"Ostatnia warstwa lakieru schnie dzis w nocy.\"",
    /* S_END4_L1          */ "\"Jutro rano. Sesja o wschodzie slonca.\"",
    /* S_END4_DESC0       */ "[Obaj stoja w drzwiach warsztatu.",
    /* S_END4_DESC1       */ " Rampa zajmuje caly pokoj.]",
    /* S_END5_THANKS      */ "Dziekujemy za gre.",
    /* S_END5_CREDITS     */ "Ta gra zostala zrobiona przez Miro i Taya.",
    /* S_END5_TITLE_SCR   */ "[A] Ekran tytulowy",
},

/* ---- RUSSIAN / RUSSKIY ---- */
/* Note: Latin transliteration used (Cyrillic needs TTF font, see BUILD_GUIDE.md) */
/* Scheme: a=a b=b v=v g=g d=d e=e zh=zh z=z i=i j=j k=k l=l m=m n=n */
/*         o=o p=p r=r s=s t=t u=u f=f kh=kh ts=ts ch=ch sh=sh ya=ya */
{
    /* S_TITLE_SUBTITLE   */ "igra",
    /* S_TITLE_P1         */ "Igr.1 [Wiimote 1 bochkom]  =  MIRO",
    /* S_TITLE_P2         */ "Igr.2 [Wiimote 2 bochkom]  =  TAY",
    /* S_TITLE_CONTROLS   */ "Krestovino=Dvizh  A=Dejstvie  B=Nazad",
    /* S_TITLE_HOME       */ "HOME = Vyjti v Homebrew Channel",
    /* S_START_GAME       */ "Novaya igra",
    /* S_SETTINGS_MENU    */ "Nastrojki",
    /* S_SELECT_LANGUAGE  */ "Vyberi yazyk:",
    /* S_LANG_EN          */ "English",
    /* S_LANG_DE          */ "Deutsch",
    /* S_LANG_PL          */ "Polski",
    /* S_LANG_RU          */ "Russkiy",
    /* S_SETTINGS_TITLE   */ "Nastrojki",
    /* S_SETTINGS_LANG    */ "Yazyk:",
    /* S_SETTINGS_BACK    */ "[B] Nazad",
    /* S_SETTINGS_CONFIRM */ "[A] Vybrat'",
    /* S_PRESS_A_START    */ "Nazhmi A chtoby nachat'",
    /* S_BACK             */ "[B] Nazad",
    /* S_CONTINUE         */ "Nazhmi A chtoby prodolzhat'",
    /* S_ENTER            */ "[A] Vojti",
    /* S_LEAVE_OUTSIDE    */ "[B] Na ulitsu",
    /* S_LEAVE_BACK       */ "[B] Nazad",
    /* S_LEAVE_PARK       */ "[B] Ujti iz parka",
    /* S_LEAVE            */ "[B] Ujti",
    /* S_HUD_LINE         */ "Tay Skejtovyj Ur:%d  Uroki:%d/%d",
    /* S_WORKSHOP_UNLOCKED*/ "Masterskaya otkryta!",
    /* S_ZONE_OVERWORLD   */ "Gorod",
    /* S_ZONE_MIRO_HOUSE  */ "Dom Miro",
    /* S_ZONE_MIRO_ROOM   */ "Komnata Miro",
    /* S_ZONE_TAY_HOUSE   */ "Dom Taya",
    /* S_ZONE_TAY_ROOM    */ "Komnata Taya",
    /* S_ZONE_SKATEPARK   */ "Skejt-park",
    /* S_ZONE_WORKSHOP    */ "Masterskaya",
    /* S_OW_MIRO_HOUSE    */ "Dom Miro",
    /* S_OW_TAY_HOUSE     */ "Dom Taya",
    /* S_OW_SKATEPARK     */ "SKEJT-PARK",
    /* S_OW_SECRET        */ "???",
    /* S_OW_WORKSHOP      */ "Masterskaya",
    /* S_OW_WORKSHOP_ENTER*/ "[A] Vojti",
    /* S_OW_LESSONS_HINT  */ "Uroki: %d/%d",
    /* S_ROOM_SOFA        */ "Divan",
    /* S_ROOM_TV          */ "Televizor",
    /* S_ROOM_KITCHEN     */ "Kukhnya",
    /* S_ROOM_STAIRS      */ "Lestnitsa",
    /* S_ROOM_STAIRS_UP   */ "[A] Komnata",
    /* S_ROOM_BED         */ "Krovat'",
    /* S_ROOM_PC          */ "Kompyuter",
    /* S_ROOM_RGB         */ "RGB est' konechno",
    /* S_ROOM_GUITAR      */ "Gitara",
    /* S_ROOM_AMP         */ "Usilitel'",
    /* S_ROOM_DRUMS       */ "Barabanshchina",
    /* S_ROOM_SKATE       */ "Skejtbord",
    /* S_ROOM_POSTER      */ "Poster",
    /* S_ROOM_COUCH       */ "Divan",
    /* S_ROOM_DINING      */ "Stolovyj stol",
    /* S_ROOM_WORKBENCH   */ "ВЕРСТАК",  /* intentional Cyrillic - shows as ?? without TTF */
    /* S_ROOM_TOOLS       */ "Pila, molotok, shuty",
    /* S_ROOM_BLUEPRINTS  */ "Chertezhi:",
    /* S_ROOM_BP_RAMP     */ "- Ramp v3",
    /* S_ROOM_BP_SHELF    */ "- Polka",
    /* S_ROOM_BP_SECRET   */ "- ???",
    /* S_ROOM_PARTS       */ "Zapchasti i materialy",
    /* S_ROOM_MTB         */ "Velosipednyj shljem",
    /* S_ROOM_FLUTE       */ "Flejta",
    /* S_SK_HALFPIPE      */ "KHATF-PAJP",
    /* S_SK_RAILS         */ "GRIND-RELINGI",
    /* S_SK_MINIRAMP      */ "Mini-ramp",
    /* S_SK_BOWL          */ "Bowl",
    /* S_SK_TEACH_PROMPT  */ "[Miro A] = Nauchat' Taya trjuku!",
    /* S_SK_TEACH_HINT    */ "Miro: podojdi k Tayu, potom nazhmi A",
    /* S_WS_DESC1         */ "Nedostrojennaya skatovaya ramp.",
    /* S_WS_DESC2         */ "Derevo svezhee. Rabota Taya.",
    /* S_WS_BP_LABEL      */ "RAMP",
    /* S_WS_BP_LINE       */ "Chertjozh",
    /* S_WS_BP_FINAL      */ "v4 - FINAL",
    /* S_WS_TOOLS         */ "Instrumenty",
    /* S_WS_BOTH_PROMPT   */ "Oba igroka: idite k tsentru [A]",
    /* S_LESSON_TITLE     */ "UROK SKATINGA",
    /* S_LESSON_MIRO      */ "Miro: \"Ladno Tay, smotri. Eto %s.\"",
    /* S_LESSON_TAY       */ "Tay: \"Eto vyglyadit beshumno...\"",
    /* S_LESSON_HIT       */ "TAY [A]: Davaj! (okno tajminga)",
    /* S_LESSON_PROGRESS  */ "Urok %d iz %d  |  Tay Skejtov. Ur:%d",
    /* S_TRICK_LANDED     */ "ZALANDOVAL!",
    /* S_TRICK_BAILED     */ "UPALI!",
    /* S_TRICK_WIN_DESC   */ "Tay zalandoval %s!",
    /* S_TRICK_WIN_TAY    */ "Tay: \"Neveroyatno! U menya poluchilos'!\"",
    /* S_TRICK_WIN_MIRO   */ "Miro: \"POGNAALI!\"",
    /* S_TRICK_UNLOCK     */ "Chto-to otkrylos'...",
    /* S_TRICK_UNLOCK2    */ "Posmotri v gorode. Vnizy sprava.",
    /* S_TRICK_FAIL_DESC  */ "Tay ne reshilsya na %s...",
    /* S_TRICK_FAIL_TAY   */ "Tay: \"blatj!\"",
    /* S_TRICK_FAIL_MIRO  */ "Miro: \"idi nahui i delaj suka\"",
    /* S_NPC_JAE_0        */ "Miro! Nakonets-to ty na ulitse.",
    /* S_NPC_JAE_1        */ "Vozmi Taya s soboj v park segodnya.",
    /* S_NPC_LEO_0        */ "Kto-nibud' videl moi nakolennieki?",
    /* S_NPC_LEO_1        */ "Ya SNOVA ikh poteryala.",
    /* S_NPC_LEO_2        */ "Ne govori maame.",
    /* S_NPC_FINN_0       */ "Gonki do skejt-parka!",
    /* S_NPC_FINN_1       */ "Poslednij pokupaet peregorodki.",
    /* S_NPC_DAD_0        */ "Ne katajsya do zakata snova.",
    /* S_NPC_DAD_1        */ "I nadev shljem, pozhalujsta.",
    /* S_NPC_DAD_2        */ "...I vynes musor, pozhalujsta.",
    /* S_NPC_MMOM_0       */ "Tay! Zakhodj, ya sdelaju buterbrody.",
    /* S_NPC_MMOM_1       */ "Vy vsegda golodny posle kataniya.",
    /* S_NPC_TMOM_0       */ "Tey, ty zavtrakal?",
    /* S_NPC_TMOM_1       */ "Miro, ubedjsya chto on chto-nibud' pojel.",
    /* S_NPC_TMOM_2       */ "V kholodilnike jest' vcherashniye makarony!",
    /* S_NPC_POSTER_0     */ "[Potrjopannyj poster Blink-182.]",
    /* S_NPC_POSTER_1     */ "[Gitara Miro stoit u usilitelya.]",
    /* S_NPC_BENCH_0      */ "[Nedostrojennaya polka na stole.]",
    /* S_NPC_BENCH_1      */ "[Futlyar dlya flejty lezit na krojvati.]",
    /* S_NPC_BENCH_2      */ "[Vezde chertezhi.]",
    /* S_NPC_KIRA_0       */ "Ty katajesh'sya? Klass. Uvazhuha.",
    /* S_NPC_KIRA_1       */ "Tvoj drug eshche uchitsya?",
    /* S_NPC_KIRA_2       */ "Vse s chego-to nachinayut.",
    /* S_NPC_DEV_0        */ "Brat, ya tol'ko chto zalandoval tre-flip.",
    /* S_NPC_DEV_1        */ "Net ya ne vru. Jae videl.",
    /* S_NPC_DUDE_0       */ "Paren', yesli uzh delaesh' - delaesh' KAK NADO.",
    /* S_NPC_DUDE_1       */ "Nepolnotsennye olli zakonchatsya kolenyami.",
    /* S_NPC_DUDE_2       */ "Doverqj svoim nogam.",
    /* S_END0_TITLE       */ "Miro nakhodit zapisku.",
    /* S_END0_L0          */ "Sprjatannuyu pod planami ramp,",
    /* S_END0_L1          */ "smyatyj listochek, napisannyj rukoj Taya.",
    /* S_END1_HEAD        */ "[Zapiska glasit:]",
    /* S_END1_L0          */ "\"Miro - ya stroyu etu rampu",
    /* S_END1_L1          */ " vsyo leto. Dlya nas. Dlya dvora.\"",
    /* S_END1_L2          */ "\"Ty nauchil menya katatT'sya.",
    /* S_END1_L3          */ " Ya postroil nam mesto gde eto mozhno delat'.\"",
    /* S_END1_L4          */ "\"Klyuch ot masterskoj pod barabanami. - T\"",
    /* S_END2_L0          */ "\"Ya nachal stroit' v tot pervyj den',",
    /* S_END2_L1          */ " kogda ty odolzhil mne svoju dosku.\"",
    /* S_END2_L2          */ "\"Do togo, kak ya eshche mog sdelat' olli.\"",
    /* S_END3_L0          */ "\"Ty postroil tseluyu khalf-pajp.\"",
    /* S_END3_L1          */ "\"Dlya nas.\"",
    /* S_END3_L2          */ "\"...kogda my na nejo pojdyom?\"",
    /* S_END4_L0          */ "\"Poslednij sloj laka sukhnyet segodnya noch'yu.\"",
    /* S_END4_L1          */ "\"Zavtra utrom. Sessiya na rassvete.\"",
    /* S_END4_DESC0       */ "[Dvoje stoyat v dvernom proyome masterskoj.",
    /* S_END4_DESC1       */ " Ramp zanimajet vsyu komnatu.]",
    /* S_END5_THANKS      */ "Spasibo za igru.",
    /* S_END5_CREDITS     */ "Eta igra sozdana Miro i Tayem.",
    /* S_END5_TITLE_SCR   */ "[A] Ekran nazvanya",
},

}; /* end STRINGS table */
