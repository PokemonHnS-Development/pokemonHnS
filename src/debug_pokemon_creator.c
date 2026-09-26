// Port of Watanabe Debug Menu -> Create Pokémon Menu
/* TODO Known Bugs and Todo List:
    * Nickname length can't be changed
Things that are not implemented yet, or bugs that are caused by unimplemented features:
    * PP are not recalculated when editing PP Up count or moves.
    * Only one of the sleep and toxic counter should be visible and editable at one time, but only if the status is sleep or toxic respectively. (This does not take the separate indexes for these two values into consideration.)
    * Language, Origin Game, Met Location, Ball, and Nature (the unused separate index) should be drawn with their names next to them.
    * If the Pokérus Strain is 0, the Days indexes should not be accessible.
    * Setting "Egg" from Off to On should also update "Egg2", but setting "Egg2" to Off should NOT update "Egg". Also, setting "Egg" to Off should NOT update "Egg2".
    * Add a "Bad Egg" index as an alternate value for "Present".
    * In edit mode, pressing Select should reset that value; in mode 0, to default; else to that of the mon being edited.
    * If the mon being created would be Shiny, draw a star next to the nickname.
    * Dynamic max values:
        * PP (With max PP for that move including PP Up boosts)
        * Current HP (with max HP)
        * EXP (with EXP at level 100 for that species)
    * Binary and octal display modes
    * Draw the mon's icon next to the species
    * An actual cursor (instead of just highlighting the selected option)
*/
#include "global.h"
#include "battle_main.h"
#include "data.h"
#include "debug.h"
#include "item.h"
#include "list_menu.h"
#include "main.h"
#include "menu.h"
#include "pokemon.h"
#include "pokemon_summary_screen.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "region_map.h"
#include "script.h"
#include "sound.h"
#include "strings.h"
#include "string_util.h"
#include "mini_printf.h"
#include "gba/isagbprint.h"
#include "constants/songs.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/battle.h"
#include "constants/region_map_sections.h"

#if TX_DEBUG_SYSTEM_ENABLE == TRUE

static void DebugPkmCreator_Init_SetDefaults(void);
static void DebugPkmCreator_Init_SetDefaults(void);
static void DebugPkmCreator_Init_SetNewMonData(bool8 setMoves);
static void DebugPkmCreator_PopulateDataStruct(void);
static void DebugPkmCreator_Redraw(void);
static void DebugPkmCreator_EditModeRedraw(u32, u8);
static void DebugPkmCreator_ProcessInput(u8);
static void DebugPkmCreator_EditModeProcessInput(u8);
static u8 DebugPkmCreator_GiveToPlayer(void);

static const u8 Str_Species[] = _("Especie");
static const u8 Str_Personality[] = _("PID/Naturaleza/Género");
static const u8 Str_TrainerID[] = _("TID/SID/Género OT");
static const u8 Str_SecretID[] = _("SID");
static const u8 Str_OT[] = _("Nombre OT");
static const u8 Str_Nick[] = _("Apodo");
static const u8 Str_Gender[] = _("Género");
static const u8 Str_Nature[] = _("Naturaleza");
static const u8 Str_Egg[] = _("Huevo");
static const u8 Str_Egg2[] = _("Huevo2");
static const u8 Str_HasSpecies[] = _("Regalo");
static const u8 Str_Language[] = _("Idioma");
static const u8 Str_Game[] = _("Juego Origen");
static const u8 Str_Item[] = _("Objeto Llevado");
static const u8 Str_Level[] = _("Nivel");
static const u8 Str_EXP[] = _("Experiencia/Nivel");
static const u8 Str_Ability[] = _("Habilidad");
static const u8 Str_Friendship[] = _("Amistad");
static const u8 Str_MetLevel[] = _("Nivel Encuentro");
static const u8 Str_MetLocation[] = _("Lugar Encuentro");
static const u8 Str_Ball[] = _("BALL");
static const u8 Str_PKrus[] = _("{PK}Rus Id/Dura/Izq");
static const u8 Str_HP[] = _("PS");
static const u8 Str_Atk[] = _("Atq");
static const u8 Str_Def[] = _("Def");
static const u8 Str_Spe[] = _("Vel");
static const u8 Str_SpA[] = _("AtqE");
static const u8 Str_SpD[] = _("DefE");
static const u8 Str_HP_IV_EV[] = _("PS IV/EV/Act/Máx");
static const u8 Str_Atk_IV_EV[] = _("Atq IV/EV/Res");
static const u8 Str_Def_IV_EV[] = _("Def IV/EV/Res");
static const u8 Str_Spe_IV_EV[] = _("Vel IV/EV/Res");
static const u8 Str_SpA_IV_EV[] = _("Atq. Esp. IV/EV/Res");
static const u8 Str_SpD_IV_EV[] = _("Def. Esp. IV/EV/Res");
static const u8 Str_EV[] = _("EV");
static const u8 Str_IV[] = _("IV");
static const u8 Str_Current[] = _("Actual");
static const u8 Str_Status[] = _("Estado");
static const u8 Str_Cool[] = _("Genial");
static const u8 Str_Cute[] = _("Lindo");
static const u8 Str_Tough[] = _("Duro");
static const u8 Str_Beauty[] = _("Bello");
static const u8 Str_Smart[] = _("Listo");
static const u8 Str_Sheen[] = _("Brillante");
static const u8 Str_Fateful[] = _("Destino");
static const u8 Str_Fateful2[] = _("Cintas sin usar");
static const u8 Str_CoolRibbon[] = _("Cintas Geniales");
static const u8 Str_CuteRibbon[] = _("Cintas Lindas");
static const u8 Str_ToughRibbon[] = _("Cintas Duras");
static const u8 Str_BeautyRibbon[] = _("Cintas Belleza");
static const u8 Str_SmartRibbon[] = _("Cintas Inteligencia");
static const u8 Str_ChampRibbon[] = _("Cinta Campeón");
static const u8 Str_WinRibbon[] = _("Cinta Ganador");
static const u8 Str_VictoryRibbon[] = _("Cinta Victoria");
static const u8 Str_ArtistRibbon[] = _("Cinta Artista");
static const u8 Str_EffortRibbon[] = _("Cinta Esfuerzo");
static const u8 Str_GiftRibbon[] = _("Cintas de regalo");
static const u8 Str_Move[] = _("Movimiento");
static const u8 Str_PP[] = _("PP");
static const u8 Str_PPUp[] = _("PP Max");

static const u8 Str_On[] = _("Sí");
static const u8 Str_Off[] = _("No");
static const u8 Str_HexPrefix[] = _("0x");

static const u8 Str_Header_Create[] = _("{COLOR GREEN}Crear Pokémon");
static const u8 Str_Header_Edit[] = _("{COLOR GREEN}Editar Pokémon");
static const u8 Str_Header2[] = _("{START_BUTTON} Guardar y salir {DPAD_LEFTRIGHT} Pág.");

static const u8 Str_DefaultOTName[8] = _("Debug-E");

static const u8 Str_Page[] = _("Pág.: {STR_VAR_1}");
static const u8 Str_Slot[] = _("Espacio: {STR_VAR_1}");

static const u8 Str_StringVars[] = _("{STR_VAR_1}{STR_VAR_3}");
static const u8 Str_Spacer1[] = _(": {CLEAR_TO 100}");
static const u8 Str_CursorColor[] = _("{COLOR GREEN}");
static const u8 Str_Cursor2Color[] = _("{COLOR DARK_GRAY}{HIGHLIGHT LIGHT_BLUE}");
static const u8 Str_CursorColorOff[] = _("{HIGHLIGHT WHITE}{COLOR GREEN}");
static const u8 Str_JpnCharset[] = _("{JPN}");

static const u8 Str_Genderless[] = _("-");
static const u8 Str_Male[] = _("♂");
static const u8 Str_Female[] = _("♀");
static const u8 *const GenderIndexes[3] = {
    Str_Male,
    Str_Female,
    Str_Genderless
};

static const u8 Str_Empty[] = _("");
static const u8 Str_isShiny[] = _("{TRIANGLE}");
static const u8 *const IsShinyIndex[2] = {
    Str_Empty,
    Str_isShiny
};

static const u8 Str_None[] = _("---");
static const u8 Str_Psn[] = _("VNE");
static const u8 Str_Par[] = _("PAR");
static const u8 Str_Brn[] = _("QUE");
static const u8 Str_Slp[] = _("SUE");
static const u8 Str_Frz[] = _("CON");
static const u8 Str_Psn2[] = _("PSN2");

static const u8 *const StatusIndexes[7] = {
    Str_None,
    Str_Psn,
    Str_Par,
    Str_Brn,
    Str_Slp,
    Str_Frz,
    Str_Psn2
};

struct EditPokemonStruct {
    const u8* text;
    u32 mode;
    u32 min;
    u32 max;
    u32 initial;
    u16 SetMonDataParam;
    u16 digitCount;
};

enum {
    EDIT_NULL,
    EDIT_NORMAL,
    EDIT_READONLY,
    EDIT_STRING,
    EDIT_BOOL,
    EDIT_HEX,
};

enum {
    VAL_SPECIES,
    VAL_PID,
    VAL_TID,
    VAL_SID,
    VAL_OT,
    VAL_OT_GENDER,
    VAL_NICK,
    VAL_PKM_GENDER,
    VAL_NATURE,
    VAL_EGG,
    VAL_EGG2,
    VAL_HASSPECIES,
    VAL_LANGUAGE,
    VAL_GAME,
    VAL_ITEM,
    VAL_LEVEL,
    VAL_EXP,
    VAL_ABILITY,
    VAL_FRIENDSHIP,
    VAL_METLVL,
    VAL_METLOCATATION,
    VAL_BALL,
    VAL_PKRUS_STRAIN,
    VAL_PKRUS_DAYS_DEF,
    VAL_PKRUS_DAYS_LEFT,
    VAL_HP_CURRENT,
    VAL_HP_MAX,
    VAL_ATK,
    VAL_DEF,
    VAL_SPEED,
    VAL_SPATK,
    VAL_SPDEF,
    VAL_HP_IV,
    VAL_ATK_IV,
    VAL_DEF_IV,
    VAL_SPEED_IV,
    VAL_SPATK_IV,
    VAL_SPDEF_IV,
    VAL_HP_EV,
    VAL_ATK_EV,
    VAL_DEF_EV,
    VAL_SPEED_EV,
    VAL_SPATK_EV,
    VAL_SPDEF_EV,
    VAL_COOL,
    VAL_CUTE,
    VAL_BEAUTY,
    VAL_SMART,
    VAL_TOUGH,
    VAL_SHEEN,
    VAL_STATUS,
    VAL_SLEEP_TIMER,
    VAL_PSN2_TIMER,
    VAL_RIBBON_CHAMPRIBBON,
    VAL_RIBBON_WINRIBBON,
    VAL_RIBBON_VICTORYRIBBON,
    VAL_RIBBON_ARTISTRIBBON,
    VAL_RIBBON_EFFORTRIBBON,
    VAL_RIBBON_COOLRIBBON,
    VAL_RIBBON_CUTERIBBON,
    VAL_RIBBON_BEAUTYRIBBON,
    VAL_RIBBON_SMARTRIBBON,
    VAL_RIBBON_TOUGHRIBBON,
    VAL_RIBBON_GIFTRIBBON,
    VAL_RIBBON_FATEFUL,
    VAL_RIBBON_FATEFUL2,
    VAL_MOVE_1,
    VAL_MOVE_2,
    VAL_MOVE_3,
    VAL_MOVE_4,
    VAL_MOVE_1_PP,
    VAL_MOVE_2_PP,
    VAL_MOVE_3_PP,
    VAL_MOVE_4_PP,
    VAL_MOVE_1_PPUP,
    VAL_MOVE_2_PPUP,
    VAL_MOVE_3_PPUP,
    VAL_MOVE_4_PPUP,
    VAL_IS_SHINY,
};

#define PAGE_COUNT 7

// text, mode, min value, max value, initial value, SetMonDataParam, digitCount
static const struct EditPokemonStruct DebugPkmCreator_Options[] =
{
        [VAL_SPECIES]              = {Str_Species, EDIT_NORMAL, 1, NUM_SPECIES-1, SPECIES_BULBASAUR, MON_DATA_SPECIES, 4},
        [VAL_PID]                  = {Str_Personality, EDIT_HEX, 0, 0xffffffff, 0, MON_DATA_PERSONALITY, 8},
        [VAL_TID]                  = {Str_TrainerID, EDIT_NORMAL, 0, 0xffff, 0, MON_DATA_OT_ID, 5},
        [VAL_SID]                  = {Str_SecretID, EDIT_NORMAL, 0, 0xffff, 0, MON_DATA_OT_ID, 5}, // SID
        [VAL_OT]                   = {Str_OT, EDIT_STRING, 0, 0, 0, MON_DATA_OT_NAME, PLAYER_NAME_LENGTH}, // We can't set a default here because the saveblock pointer can change.
        [VAL_OT_GENDER]            = {Str_Gender, EDIT_NORMAL, 0, 1, 0, MON_DATA_OT_GENDER, 1},
        [VAL_NICK]                 = {Str_Nick, EDIT_STRING, 0, 0, 0, MON_DATA_NICKNAME, POKEMON_NAME_LENGTH},
        [VAL_PKM_GENDER]           = {Str_Gender, EDIT_READONLY, 0, 2, 0, MON_DATA_PERSONALITY, 1},
        [VAL_NATURE]               = {Str_Nature, EDIT_READONLY, 0, 24, 0, MON_DATA_PERSONALITY, 2},
        [VAL_EGG]                  = {Str_Egg, EDIT_BOOL, 0, 1, 0, MON_DATA_IS_EGG, 1},
        [VAL_EGG2]                 = {Str_Egg2, EDIT_BOOL, 0, 1, 0, MON_DATA_SANITY_IS_EGG, 1},
        [VAL_HASSPECIES]           = {Str_HasSpecies, EDIT_BOOL, 0, 1, 1, MON_DATA_SANITY_HAS_SPECIES, 1},
        [VAL_LANGUAGE]             = {Str_Language, EDIT_NORMAL, 0, NUM_LANGUAGES - 1, GAME_LANGUAGE, MON_DATA_LANGUAGE, 2},
        [VAL_GAME]                 = {Str_Game, EDIT_NORMAL, 0, 49, GAME_VERSION, MON_DATA_MET_GAME, 2}, // 45 = Shield
        [VAL_ITEM]                 = {Str_Item, EDIT_NORMAL, 0, ITEMS_COUNT - 1, 0, MON_DATA_HELD_ITEM, 3},
        [VAL_LEVEL]                = {Str_Level, EDIT_NORMAL, 0, 100, 10, MON_DATA_LEVEL, 3},
        [VAL_EXP]                  = {Str_EXP, EDIT_NORMAL, 0, 1640000, 1000, MON_DATA_EXP, 7},
        [VAL_ABILITY]              = {Str_Ability, EDIT_NORMAL, 0, 2, 0, MON_DATA_ABILITY_NUM, 1},
        [VAL_FRIENDSHIP]           = {Str_Friendship, EDIT_NORMAL, 0, 255, 0, MON_DATA_FRIENDSHIP, 3},
        [VAL_METLVL]               = {Str_MetLevel, EDIT_NORMAL, 0, 100, 10, MON_DATA_MET_LEVEL, 3}, // 0 instead of 1 because 0 means hatched from an Egg
        [VAL_METLOCATATION]        = {Str_MetLocation, EDIT_NORMAL, 0, 65535, MAPSEC_NEW_BARK_TOWN, MON_DATA_MET_LOCATION, 5},
        [VAL_BALL]                 = {Str_Ball, EDIT_NORMAL, 0, LAST_BALL, ITEM_POKE_BALL, MON_DATA_POKEBALL, 2},
        [VAL_PKRUS_STRAIN]         = {Str_PKrus, EDIT_NORMAL, 0, 3, 0, MON_DATA_POKERUS, 1}, // 4 different "strains"
        [VAL_PKRUS_DAYS_DEF]       = {Str_PKrus, EDIT_NORMAL, 1, 4, 1, MON_DATA_POKERUS, 1}, // "default" days until cured
        [VAL_PKRUS_DAYS_LEFT]      = {Str_PKrus, EDIT_NORMAL, 0, 7, 0, MON_DATA_POKERUS, 1}, // Days until cured
        // Current stats
        [VAL_HP_CURRENT]           = {Str_HP, EDIT_NORMAL, 0, 999, 0, MON_DATA_HP, 3},
        [VAL_HP_MAX]               = {Str_HP, EDIT_READONLY, 0, 999, 0, MON_DATA_MAX_HP, 3},
        [VAL_ATK]                  = {Str_Atk, EDIT_READONLY, 0, 999, 0, MON_DATA_ATK, 3},
        [VAL_DEF]                  = {Str_Def, EDIT_READONLY, 0, 999, 0, MON_DATA_DEF, 3},
        [VAL_SPEED]                = {Str_Spe, EDIT_READONLY, 0, 999, 0, MON_DATA_SPEED, 3},
        [VAL_SPATK]                = {Str_SpA, EDIT_READONLY, 0, 999, 0, MON_DATA_SPATK, 3},
        [VAL_SPDEF]                = {Str_SpD, EDIT_READONLY, 0, 999, 0, MON_DATA_SPDEF, 3},
        // IVs
        [VAL_HP_IV]                = {Str_HP_IV_EV, EDIT_NORMAL, 0, 31, 0, MON_DATA_HP_IV, 2},
        [VAL_ATK_IV]               = {Str_Atk_IV_EV, EDIT_NORMAL, 0, 31, 0, MON_DATA_ATK_IV, 2},
        [VAL_DEF_IV]               = {Str_Def_IV_EV, EDIT_NORMAL, 0, 31, 0, MON_DATA_DEF_IV, 2},
        [VAL_SPEED_IV]             = {Str_Spe_IV_EV, EDIT_NORMAL, 0, 31, 0, MON_DATA_SPEED_IV, 2},
        [VAL_SPATK_IV]             = {Str_SpA_IV_EV, EDIT_NORMAL, 0, 31, 0, MON_DATA_SPATK_IV, 2},
        [VAL_SPDEF_IV]             = {Str_SpD_IV_EV, EDIT_NORMAL, 0, 31, 0, MON_DATA_SPDEF_IV, 2},
        // EVs
        [VAL_HP_EV]                = {Str_HP_IV_EV, EDIT_NORMAL, 0, 255, 0, MON_DATA_HP_EV, 3},
        [VAL_ATK_EV]               = {Str_Atk_IV_EV, EDIT_NORMAL, 0, 255, 0, MON_DATA_ATK_EV, 3},
        [VAL_DEF_EV]               = {Str_Def_IV_EV, EDIT_NORMAL, 0, 255, 0, MON_DATA_DEF_EV, 3},
        [VAL_SPEED_EV]             = {Str_Spe_IV_EV, EDIT_NORMAL, 0, 255, 0, MON_DATA_SPEED_EV, 3},
        [VAL_SPATK_EV]             = {Str_SpA_IV_EV, EDIT_NORMAL, 0, 255, 0, MON_DATA_SPATK_EV, 3},
        [VAL_SPDEF_EV]             = {Str_SpD_IV_EV, EDIT_NORMAL, 0, 255, 0, MON_DATA_SPDEF_EV, 3},
        // Contest Stats
        [VAL_COOL]                 = {Str_Cool, EDIT_NORMAL, 0, 255, 0, MON_DATA_COOL, 3},
        [VAL_CUTE]                 = {Str_Cute, EDIT_NORMAL, 0, 255, 0, MON_DATA_CUTE, 3},
        [VAL_BEAUTY]               = {Str_Beauty, EDIT_NORMAL, 0, 255, 0, MON_DATA_BEAUTY, 3},
        [VAL_SMART]                = {Str_Smart, EDIT_NORMAL, 0, 255, 0, MON_DATA_SMART, 3},
        [VAL_TOUGH]                = {Str_Tough, EDIT_NORMAL, 0, 255, 0, MON_DATA_TOUGH, 3},
        [VAL_SHEEN]                = {Str_Sheen, EDIT_NORMAL, 0, 255, 0, MON_DATA_SHEEN, 3},
        [VAL_STATUS]               = {Str_Status, EDIT_NORMAL, 0, 6, 0, MON_DATA_STATUS, 1},
        [VAL_SLEEP_TIMER]          = {Str_Slp, EDIT_NORMAL, 0, 7, 0, MON_DATA_STATUS, 1}, // sleep timer
        [VAL_PSN2_TIMER]           = {Str_Psn2, EDIT_NORMAL, 0, 15, 0, MON_DATA_STATUS, 2}, // badly poisoned timer
        // Ribbons
        [VAL_RIBBON_CHAMPRIBBON]   = {Str_ChampRibbon, EDIT_BOOL, 0, 1, 0, MON_DATA_CHAMPION_RIBBON, 1},
        [VAL_RIBBON_WINRIBBON]     = {Str_WinRibbon, EDIT_BOOL, 0, 1, 0, MON_DATA_WINNING_RIBBON, 1},
        [VAL_RIBBON_VICTORYRIBBON] = {Str_VictoryRibbon, EDIT_BOOL, 0, 1, 0, MON_DATA_VICTORY_RIBBON, 1},
        [VAL_RIBBON_ARTISTRIBBON]  = {Str_ArtistRibbon, EDIT_BOOL, 0, 1, 0, MON_DATA_ARTIST_RIBBON, 1},
        [VAL_RIBBON_EFFORTRIBBON]  = {Str_EffortRibbon, EDIT_BOOL, 0, 1, 0, MON_DATA_EFFORT_RIBBON, 1},
        [VAL_RIBBON_COOLRIBBON]    = {Str_CoolRibbon, EDIT_NORMAL, 0, 3, 0, MON_DATA_COOL_RIBBON, 1},
        [VAL_RIBBON_CUTERIBBON]    = {Str_CuteRibbon, EDIT_NORMAL, 0, 3, 0, MON_DATA_CUTE_RIBBON, 1},
        [VAL_RIBBON_BEAUTYRIBBON]  = {Str_BeautyRibbon, EDIT_NORMAL, 0, 3, 0, MON_DATA_BEAUTY_RIBBON, 1},
        [VAL_RIBBON_SMARTRIBBON]   = {Str_SmartRibbon, EDIT_NORMAL, 0, 3, 0, MON_DATA_SMART_RIBBON, 1},
        [VAL_RIBBON_TOUGHRIBBON]   = {Str_ToughRibbon, EDIT_NORMAL, 0, 3, 0, MON_DATA_TOUGH_RIBBON, 1},
        [VAL_RIBBON_GIFTRIBBON]    = {Str_GiftRibbon, EDIT_HEX, 0, 127, 0, MON_DATA_MARINE_RIBBON, 2},
        [VAL_RIBBON_FATEFUL]       = {Str_Fateful, EDIT_BOOL, 0, 1, 0, MON_DATA_MODERN_FATEFUL_ENCOUNTER, 1},
        [VAL_RIBBON_FATEFUL2]      = {Str_Fateful2, EDIT_NORMAL, 0, 3, 0, MON_DATA_UNUSED_RIBBONS, 1},
        // Move data
        [VAL_MOVE_1]               = {Str_Move, EDIT_NORMAL, 0, MOVES_COUNT - 1, MOVE_POUND, MON_DATA_MOVE1, 3},
        [VAL_MOVE_2]               = {Str_Move, EDIT_NORMAL, 0, MOVES_COUNT - 1, 0, MON_DATA_MOVE2, 3},
        [VAL_MOVE_3]               = {Str_Move, EDIT_NORMAL, 0, MOVES_COUNT - 1, 0, MON_DATA_MOVE3, 3},
        [VAL_MOVE_4]               = {Str_Move, EDIT_NORMAL, 0, MOVES_COUNT - 1, 0, MON_DATA_MOVE4, 3},
        [VAL_MOVE_1_PP]            = {Str_PP, EDIT_NORMAL, 0, 99, 40, MON_DATA_PP1, 2},
        [VAL_MOVE_2_PP]            = {Str_PP, EDIT_NORMAL, 0, 99, 40, MON_DATA_PP2, 2},
        [VAL_MOVE_3_PP]            = {Str_PP, EDIT_NORMAL, 0, 99, 40, MON_DATA_PP3, 2},
        [VAL_MOVE_4_PP]            = {Str_PP, EDIT_NORMAL, 0, 99, 40, MON_DATA_PP4, 2},
        [VAL_MOVE_1_PPUP]          = {Str_PPUp, EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
        [VAL_MOVE_2_PPUP]          = {Str_PPUp, EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
        [VAL_MOVE_3_PPUP]          = {Str_PPUp, EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
        [VAL_MOVE_4_PPUP]          = {Str_PPUp, EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
        [VAL_IS_SHINY]             = {Str_Nature, EDIT_READONLY, 0, 1, 0, MON_DATA_PERSONALITY, 1},
};

#define EDIT_OPTION_COUNT ARRAY_COUNT(DebugPkmCreator_Options)

static const u8 DebugPkmCreator_Pages[PAGE_COUNT + 1][7] =
{
    {VAL_SPECIES, VAL_LEVEL, VAL_TID, VAL_PID, VAL_NICK, VAL_OT, 0xFF},
    {VAL_STATUS, VAL_FRIENDSHIP, VAL_PKRUS_STRAIN, VAL_EGG, VAL_EGG2, VAL_HASSPECIES, 0xFF},
    {VAL_MOVE_1, VAL_MOVE_2, VAL_MOVE_3, VAL_MOVE_4, VAL_ITEM, VAL_ABILITY, 0xFF},
    {VAL_HP_IV, VAL_ATK_IV, VAL_DEF_IV, VAL_SPEED_IV, VAL_SPATK_IV, VAL_SPDEF_IV, 0xFF},
    {VAL_COOL, VAL_CUTE, VAL_BEAUTY, VAL_SMART, VAL_TOUGH, VAL_SHEEN, 0xFF},
    {VAL_RIBBON_COOLRIBBON, VAL_RIBBON_CUTERIBBON, VAL_RIBBON_BEAUTYRIBBON, VAL_RIBBON_SMARTRIBBON, VAL_RIBBON_TOUGHRIBBON, VAL_RIBBON_ARTISTRIBBON, 0xFF},
    {VAL_RIBBON_CHAMPRIBBON, VAL_RIBBON_WINRIBBON, VAL_RIBBON_VICTORYRIBBON, VAL_RIBBON_EFFORTRIBBON, VAL_RIBBON_GIFTRIBBON, VAL_RIBBON_FATEFUL, 0xFF},
    {VAL_LANGUAGE, VAL_GAME, VAL_METLVL, VAL_METLOCATATION, VAL_BALL, VAL_RIBBON_FATEFUL2, 0xFF},
};

static const u8 DebugPkmCreator_AltIndexes[PAGE_COUNT + 1][6][3] =
{
    {
        {VAL_PKM_GENDER, 0xFF, 0xFF},
        {VAL_EXP, 0xFF, 0xFF},
        {VAL_SID, VAL_OT_GENDER, 0xFF},
        {VAL_NATURE, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
    },
    {
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {VAL_PKRUS_DAYS_DEF, VAL_PKRUS_DAYS_LEFT, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
    },
    {
        {VAL_MOVE_1_PP, VAL_MOVE_1_PPUP, 0xFF},
        {VAL_MOVE_2_PP, VAL_MOVE_2_PPUP, 0xFF},
        {VAL_MOVE_3_PP, VAL_MOVE_3_PPUP, 0xFF},
        {VAL_MOVE_4_PP, VAL_MOVE_4_PPUP, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
    },
    {
        {VAL_HP_EV, VAL_HP_CURRENT, VAL_HP_MAX},
        {VAL_ATK_EV, VAL_ATK, 0xFF},
        {VAL_DEF_EV, VAL_DEF, 0xFF},
        {VAL_SPEED_EV, VAL_SPEED, 0xFF},
        {VAL_SPATK_EV, VAL_SPATK, 0xFF},
        {VAL_SPDEF_EV, VAL_SPDEF, 0xFF},
    },
    {
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
    },
    {
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
    },
    {
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
    },
    {
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
    },
};

struct PokemonCreator
{
    struct Pokemon mon;
    struct Pokemon* monBeingEdited;
    u16 index;
    u16 mode;
    u32 data[EDIT_OPTION_COUNT];
    u8 currentPage;
    u8 selectedOption;
    u8 headerWindowId;
    u8 menuWindowId;
};

static EWRAM_DATA struct PokemonCreator sDebugPkmCreatorData = {0};
static EWRAM_DATA u8 DebugPkmCreator_NameBuffer[16] = {0};
static EWRAM_DATA u32 DebugPkmCreator_editingVal[4] = {0};

static const struct WindowTemplate DebugPkmCreator_HeaderWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 28,
    .height = 2,
    .baseBlock = 1,
    .paletteNum = 15
};

static const struct WindowTemplate DebugPkmCreator_FullScreenWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 5,
    .width = 28,
    .height = 14,
    .baseBlock = 57,
    .paletteNum = 15
};


/*
    Mode List:
    *  0 - Add to party
    *  1 - Edit party
    *  2 - Edit PC Box
    *  3 - Edit enemy party (usable as a sandbox)
    *  4 - Edit enemy party for debug battle
    *  5 - Edit party for debug battle
    *  6 - Add to enemy party (Unused)
    *  7 - Testing mode (Don't alter parties)
    *  8 - Testing mode (use first mon as template)
    *  9 - For battle debug menu: Edit enemy party
    * 10 - For battle debug menu: Edit enemy party as specified index
*/
void DebugPkmCreator_Init(u8 mode, u8 index)
{
    struct Pokemon* mons;
    u32 i;
    sDebugPkmCreatorData.mode = mode;
    switch (mode) {
    case 0:
    case 6:
        mons = &gEnemyParty[0];
        ZeroMonData(mons); // Is this really necessary?
        ZeroMonData(&sDebugPkmCreatorData.mon);
        sDebugPkmCreatorData.monBeingEdited = mons;
        sDebugPkmCreatorData.index = 0;
        break;
    case 1:
    case 5: // used in Debug Battle
        mons = &gPlayerParty[sDebugPkmCreatorData.index];
        if (mode == 1) 
            CopyMon(&sDebugPkmCreatorData.mon, mons, sizeof(struct Pokemon));
        sDebugPkmCreatorData.monBeingEdited = mons;
        break;
    case 2:
        mons = (struct Pokemon*) &gPokemonStoragePtr->boxes[0][sDebugPkmCreatorData.index];
        CopyMon(&sDebugPkmCreatorData.mon, mons, sizeof(struct BoxPokemon));
        CalculateMonStats(&sDebugPkmCreatorData.mon);
        sDebugPkmCreatorData.monBeingEdited = mons;
        break;
    case 3:
    case 4: // used in Debug Battle
        mons = &gEnemyParty[sDebugPkmCreatorData.index];
        if (mode == 3)
            CopyMon(&sDebugPkmCreatorData.mon, mons, sizeof(struct Pokemon));
        sDebugPkmCreatorData.monBeingEdited = mons;
        break;
    case 7:
    case 8:
    default:
        if (mode == 8)
            CopyMon(&sDebugPkmCreatorData.mon, &gPlayerParty[0], sizeof(struct Pokemon));
        else
            ZeroMonData(&sDebugPkmCreatorData.mon);
        sDebugPkmCreatorData.monBeingEdited = &sDebugPkmCreatorData.mon;
        sDebugPkmCreatorData.index = 0;
        break;
    case 9: // Add to enemy party
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetMonData(&gEnemyParty[i], MON_DATA_SANITY_HAS_SPECIES))
                continue;
            else
                break;
        }
        if (i >= PARTY_SIZE)
            return;
        mons = &gEnemyParty[i];
        ZeroMonData(mons); // Is this really necessary?
        ZeroMonData(&sDebugPkmCreatorData.mon);
        sDebugPkmCreatorData.monBeingEdited = mons;
        sDebugPkmCreatorData.index = i;
        break;
    case 10: // Edit enemy party at index
        sDebugPkmCreatorData.index = index;
        mons = &gEnemyParty[sDebugPkmCreatorData.index];
        CopyMon(&sDebugPkmCreatorData.mon, mons, sizeof(struct Pokemon));
        sDebugPkmCreatorData.monBeingEdited = mons;
        break;
    }
    // Set default data
    if (mode == 0 || mode == 6 || mode == 7 || mode == 9)
    {
        SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_OT_NAME, Str_DefaultOTName);
        DebugPkmCreator_Init_SetDefaults();
    }
    // Populate the editor data
    DebugPkmCreator_PopulateDataStruct();
    // Draw the editor menu
    LoadMessageBoxAndBorderGfx();
    sDebugPkmCreatorData.headerWindowId = AddWindow(&DebugPkmCreator_HeaderWindowTemplate);
    DrawStdWindowFrame(sDebugPkmCreatorData.headerWindowId, FALSE);
    CopyWindowToVram(sDebugPkmCreatorData.headerWindowId, 3);
    AddTextPrinterParameterized(sDebugPkmCreatorData.headerWindowId, 1, mode == 0 ? Str_Header_Create : Str_Header_Edit, 0, 0, 0, NULL);
    AddTextPrinterParameterized(sDebugPkmCreatorData.headerWindowId, 0, Str_Header2, 105, 0, 0, NULL);
    sDebugPkmCreatorData.menuWindowId = AddWindow(&DebugPkmCreator_FullScreenWindowTemplate);
    DrawStdWindowFrame(sDebugPkmCreatorData.menuWindowId, FALSE);
    CopyWindowToVram(sDebugPkmCreatorData.menuWindowId, 3);
    DebugPkmCreator_Redraw();
    CreateTask(DebugPkmCreator_ProcessInput, 10);
}

static void DebugPkmCreator_Init_SetDefaults(void)
{
    u32 i;
    for (i = 0; i < EDIT_OPTION_COUNT; i++)
    {
        switch (i)
        {
        default:
            sDebugPkmCreatorData.data[i] = DebugPkmCreator_Options[i].initial;
            break;
        case VAL_PID:
            sDebugPkmCreatorData.data[i] = Random32();
            break;
        case VAL_TID:
            sDebugPkmCreatorData.data[i] = (*(u32*) &gSaveBlock2Ptr->playerTrainerId) & 0xffff;
            break;
        case VAL_SID:
            sDebugPkmCreatorData.data[i] = (*(u32*) &gSaveBlock2Ptr->playerTrainerId) >> 16;
            break;
        case VAL_EXP:
            sDebugPkmCreatorData.data[i] = gExperienceTables[gSpeciesInfo[DebugPkmCreator_Options[0].initial].growthRate][DebugPkmCreator_Options[15].initial];
            break;
        }
    }
    DebugPkmCreator_Init_SetNewMonData(TRUE);
}

static void DebugPkmCreator_Init_SetNewMonData(bool8 setMoves)
{
    struct Pokemon* mons = &sDebugPkmCreatorData.mon;
    u32 data, i, j, k;
    // Buffer the OT name
    StringCopyN(DebugPkmCreator_NameBuffer, mons->box.otName, PLAYER_NAME_LENGTH);
    data = (sDebugPkmCreatorData.data[3] << 16) | sDebugPkmCreatorData.data[2];
    CreateMon(mons, sDebugPkmCreatorData.data[0], sDebugPkmCreatorData.data[15], 32, 1, sDebugPkmCreatorData.data[1], OT_ID_PRESET, data);
    SetMonData(mons, MON_DATA_OT_NAME, DebugPkmCreator_NameBuffer);
    data = ((sDebugPkmCreatorData.data[23] - 1) & 3) << 6;
    data |= (sDebugPkmCreatorData.data[22] & 3) << 4;
    data |= (sDebugPkmCreatorData.data[24] & 0xf);
    SetMonData(mons, MON_DATA_POKERUS, &data);
    for (i = 0; i < EDIT_OPTION_COUNT; i++)
    {
        switch (i)
        {
        default:
            SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &sDebugPkmCreatorData.data[i]);
            break;
        // All these should already be set (or will be set later)
        case VAL_SPECIES ... VAL_OT: // PID, TID, OT
        case VAL_NICK ... VAL_NATURE: // Nickname, gender, nature
        case VAL_LEVEL:
        case VAL_PKRUS_STRAIN ... VAL_PKRUS_DAYS_LEFT: // Pokérus
        case VAL_HP_MAX ... VAL_SPDEF: // Current stats
        case VAL_MOVE_1_PPUP ... VAL_MOVE_3_PPUP:
        case VAL_IS_SHINY:
            break;
        // Only set after initial generation
        case VAL_OT_GENDER:
        case VAL_FRIENDSHIP: // Friendship (will always default to the base friendship of the default species)
        case VAL_METLOCATATION:
        case VAL_HP_CURRENT:
            if (!setMoves)
                SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &sDebugPkmCreatorData.data[i]);
            break;
        case VAL_ABILITY:
            if (setMoves)
            {
                if (gSpeciesInfo[sDebugPkmCreatorData.data[0]].abilities[1])
                {
                    data = sDebugPkmCreatorData.data[1] & 1;
                    SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &data);
                }
                break;
            }
            SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &sDebugPkmCreatorData.data[i]);
            break;
        case VAL_SPDEF_IV: // IVs
            if (setMoves)
            {
                data = Random32();
                SetMonData(mons, MON_DATA_IVS, &data);
                break;
            }
            SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &sDebugPkmCreatorData.data[i]);
            break;
        case VAL_STATUS:
            j = sDebugPkmCreatorData.data[i];
            switch (j)
            {
            case 0:
            default:
                data = 0;
                break;
            case 1:
                data = STATUS1_POISON;
                break;
            case 2:
                data = STATUS1_PARALYSIS;
                break;
            case 3:
                data = STATUS1_BURN;
                break;
            case 4:
                data = 3;
                break;
            case 5:
                data = STATUS1_FREEZE;
                break;
            case 6:
                data = STATUS1_TOXIC_POISON;
                break;
            }
            SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &data);
            break;
        case VAL_SLEEP_TIMER:
            if (sDebugPkmCreatorData.data[50] == 4)
            {
                data = sDebugPkmCreatorData.data[i];
                SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &data);
            }
            break;
        case VAL_PSN2_TIMER:
            if (sDebugPkmCreatorData.data[i] == 6)
            {
                data = sDebugPkmCreatorData.data[i] << 8 | STATUS1_TOXIC_POISON;
                SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &data);
            }
            break;
        case VAL_RIBBON_GIFTRIBBON:
            data = sDebugPkmCreatorData.data[i];
            for (j = 0; j < 7; j++)
            {
                k = data & 1;
                SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam + j, &k);
                data >>= 1;
            }
            break;
        case VAL_MOVE_4: // Moves
            if (setMoves)
            {
                GiveMonInitialMoveset(mons);
                break;
            }
            SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &sDebugPkmCreatorData.data[i]);
            break;
        case VAL_MOVE_4_PPUP: // PP Up count (74 through 76 are set too)
            data = 0;
            for (j = 0; j < 4; j++)
            {
                data <<= 2;
                data |= (sDebugPkmCreatorData.data[74 + j] & 3);
            }
            SetMonData(mons, DebugPkmCreator_Options[74].SetMonDataParam, &data);
            break;
        }
    }
    if (setMoves) MonRestorePP(mons);
    CalculateMonStats(mons);
}

static void DebugPkmCreator_SetMonData(void)
{
    struct Pokemon* mons = &sDebugPkmCreatorData.mon;
    u32 data, i, j, k;
    data = ((sDebugPkmCreatorData.data[23] - 1) & 3) << 6;
    data |= (sDebugPkmCreatorData.data[22] & 3) << 4;
    data |= (sDebugPkmCreatorData.data[24] & 0xf);
    SetMonData(mons, MON_DATA_POKERUS, &data);
    for (i = 0; i < EDIT_OPTION_COUNT; i++)
    {
        switch (i)
        {
        default:
            SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &sDebugPkmCreatorData.data[i]);
            break;
        case VAL_SPECIES ... VAL_OT: // PID and TID, leave alone. 0 is species, which we handle in a different function
        case VAL_NICK ... VAL_NATURE: // Nickname (4) and OT name, set by the actual editor; 7-8 are gender and nature (readonly)
        case VAL_LEVEL: // Level (set by CalculateMonStats)
        case VAL_PKRUS_STRAIN ... VAL_PKRUS_DAYS_LEFT: // Pokérus (set above)
        case VAL_HP_MAX ... VAL_SPATK: // Current stats (readonly). 31 calls CalculateMonStats
        case VAL_MOVE_1_PPUP ... VAL_MOVE_3_PPUP: // PP Up counts (77 sets all at once)
        case VAL_IS_SHINY:
            break;
        case 31: // Stats (and level)
            CalculateMonStats(mons);
            break;
        case 50: // Status
            j = sDebugPkmCreatorData.data[i];
            switch (j)
            {
            case 0:
            default:
                data = 0;
                break;
            case 1:
                data = STATUS1_POISON;
                break;
            case 2:
                data = STATUS1_PARALYSIS;
                break;
            case 3:
                data = STATUS1_BURN;
                break;
            case 4:
                data = 3;
                break;
            case 5:
                data = STATUS1_FREEZE;
                break;
            case 6:
                data = STATUS1_TOXIC_POISON;
                break;
            }
            SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &data);
            break;
        case 51: // Sleep counter
            if (sDebugPkmCreatorData.data[50] == 4)
            {
                data = sDebugPkmCreatorData.data[i];
                SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &data);
            }
            break;
        case 52: // Toxic counter
            if (sDebugPkmCreatorData.data[i] == 6)
            {
                data = sDebugPkmCreatorData.data[i] << 8 | STATUS1_TOXIC_POISON;
                SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, &data);
            }
            break;
        case 63: // Gift ribbons
            data = sDebugPkmCreatorData.data[i];
            for (j = 0; j < 7; j++)
            {
                k = data & 1;
                SetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam + j, &k);
                data >>= 1;
            }
            break;
        case 77: // PP Up count (74 through 76 are set too)
            data = 0;
            for (j = 0; j < 4; j++)
            {
                data <<= 2;
                data |= (sDebugPkmCreatorData.data[77 - j] & 3);
            }
            SetMonData(mons, DebugPkmCreator_Options[74].SetMonDataParam, &data);
            break;
        }
    }
}

static void DebugPkmCreator_PopulateDataStruct(void)
{
    struct Pokemon* mons = &sDebugPkmCreatorData.mon;
    u32 data, i, j;
    for (i = 0; i < EDIT_OPTION_COUNT; i++)
    {
        switch (i)
        {
        default:
            sDebugPkmCreatorData.data[i] = GetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, NULL);
            break;
        case VAL_TID:
            data = GetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, NULL);
            sDebugPkmCreatorData.data[i] = data & 0xffff;
            break;
        case VAL_SID:
            data = GetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, NULL);
            sDebugPkmCreatorData.data[i] = data >> 16;
            break;
        case VAL_OT:
            sDebugPkmCreatorData.data[i] = (u32) &mons->box.otName;
            break;
        case VAL_NICK:
            sDebugPkmCreatorData.data[i] = (u32) &mons->box.nickname;
            break;
        case VAL_PKM_GENDER:
            data = GetMonGender(mons);
            if (data == MON_FEMALE)
                data = 1;
            else if (data == MON_GENDERLESS)
                data = 2;
            sDebugPkmCreatorData.data[i] = data;
            break;
        case VAL_NATURE:
            sDebugPkmCreatorData.data[i] = GetNature(mons, FALSE);
            break;
        case VAL_PKRUS_STRAIN:
            data = GetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, NULL);
            data &= 0x30;
            data >>= 4;
            sDebugPkmCreatorData.data[i] = data;
            break;
        case VAL_PKRUS_DAYS_DEF:
            data = GetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, NULL);
            data &= 0xc0;
            data >>= 6;
            sDebugPkmCreatorData.data[i] = data + 1;
            break;
        case VAL_PKRUS_DAYS_LEFT:
            data = GetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, NULL);
            data &= 0xf;
            sDebugPkmCreatorData.data[i] = data;
            break;
        case VAL_STATUS:
            data = GetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, NULL);
            if (data & STATUS1_SLEEP)
                data = 4;
            else if (data & STATUS1_POISON)
                data = 1;
            else if (data & STATUS1_BURN)
                data = 3;
            else if (data & STATUS1_FREEZE)
                data = 5;
            else if (data & STATUS1_PARALYSIS)
                data = 2;
            else if (data & STATUS1_TOXIC_POISON)
                data = 6;
            else data = 0;
            sDebugPkmCreatorData.data[i] = data;
            break;
        case VAL_SLEEP_TIMER:
            data = GetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, NULL);
            data &= STATUS1_SLEEP;
            sDebugPkmCreatorData.data[i] = data;
            break;
        case VAL_PSN2_TIMER:
            data = GetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, NULL);
            data >>= 8;
            sDebugPkmCreatorData.data[i] = data;
            break;
        case VAL_RIBBON_GIFTRIBBON:
            data = 0;
            for (j = 0; j < 7; j++)
            {
                data <<= 1;
                data |= GetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam - 1 + (7 - j), NULL);
            }
            sDebugPkmCreatorData.data[i] = data;
            break;
        case VAL_MOVE_1_PPUP ... VAL_MOVE_4_PPUP:
            data = GetMonData(mons, DebugPkmCreator_Options[i].SetMonDataParam, NULL);
            j = (i - 74) * 2;
            data >>= j;
            sDebugPkmCreatorData.data[i] = data & 3;
            break;
        case VAL_IS_SHINY:
            //GetMonData(&sDebugPkmCreatorData.mon, MON_DATA_PERSONALITY)
            sDebugPkmCreatorData.data[i] = IsShinyOtIdPersonality(sDebugPkmCreatorData.data[VAL_OT], sDebugPkmCreatorData.data[VAL_PID]);
            break;
        }
    }
}

// Draw Functions
static void DebugPkmCreator_Redraw(void)
{
    u32 i;
    u32 x = 0;
    u32 y = 0;
    u8* bufferPosition;
    const u8* page = DebugPkmCreator_Pages[sDebugPkmCreatorData.currentPage];
    const struct EditPokemonStruct* data;
    u8 index;
    ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.currentPage + 1, STR_CONV_MODE_LEFT_ALIGN, 2);
    StringExpandPlaceholders(gStringVar2, Str_Page);
    AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 0, gStringVar2, x, y, 0, NULL);
    if ((sDebugPkmCreatorData.mode >= 1 && sDebugPkmCreatorData.mode <= 5) || sDebugPkmCreatorData.mode == 10) {
        x = 100;
        ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.index + 1, STR_CONV_MODE_LEFT_ALIGN, 2);
        StringExpandPlaceholders(gStringVar2, Str_Slot);
        AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 0, gStringVar2, x, y, 0, NULL);
        x = 0;
    }
    y += 16;
    for (i = 0; i < 6; i++)
    {
        bufferPosition = gStringVar2;
        index = page[i];
        if (index == 0xFF) break;
        if (i == sDebugPkmCreatorData.selectedOption)
        {
            // Color the currently selected option green
            bufferPosition = StringCopy(bufferPosition, Str_CursorColor);
        }
        data = &DebugPkmCreator_Options[index];
        switch (index)
        {
        default:
            switch (data->mode)
            {
            case EDIT_NORMAL:
            case EDIT_READONLY:
            default:
                ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
                break;
            case EDIT_HEX:
                ConvertUIntToHexStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
                break;
            case EDIT_NULL:
                break;
            case EDIT_BOOL:
                StringCopy(gStringVar1, sDebugPkmCreatorData.data[index] ? Str_On : Str_Off);
                break;
            case EDIT_STRING:
                StringCopyN(gStringVar1, (u8*) sDebugPkmCreatorData.data[index], data->digitCount);
                // Pokémon names can sometimes be unterminated, so add an extra terminator here
                gStringVar1[data->digitCount] = EOS;
                break;
            }
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            if (data->mode == EDIT_HEX)
            {
                bufferPosition = StringCopy(bufferPosition, Str_HexPrefix);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            break;
        case VAL_SPECIES:
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 140;
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gSpeciesNames[sDebugPkmCreatorData.data[index]], x, y, 0, NULL);
            break;
        case VAL_LEVEL:
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 140;
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[VAL_EXP], STR_CONV_MODE_LEADING_ZEROS, DebugPkmCreator_Options[VAL_EXP].digitCount);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar1, x, y, 0, NULL);
            break;
        case VAL_TID:
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 140;
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[VAL_SID], STR_CONV_MODE_LEADING_ZEROS, DebugPkmCreator_Options[VAL_SID].digitCount);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar1, x, y, 0, NULL);
            x = 180;
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, GenderIndexes[sDebugPkmCreatorData.data[VAL_OT_GENDER]], x, y, 0, NULL);
            break;
        case VAL_PID:
            ConvertUIntToHexStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            bufferPosition = StringCopy(bufferPosition, Str_HexPrefix);
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 160;
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gNatureNamePointers[sDebugPkmCreatorData.data[8]], x, y, 0, NULL);
            x = 208;
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, GenderIndexes[sDebugPkmCreatorData.data[VAL_PKM_GENDER]], x, y, 0, NULL);
            x = 214;
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, IsShinyIndex[sDebugPkmCreatorData.data[VAL_IS_SHINY]], x, y, 0, NULL);
            break;
        case VAL_OT_GENDER:
        case VAL_PKM_GENDER:
            StringCopy(gStringVar1, GenderIndexes[sDebugPkmCreatorData.data[index]]);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            break;
        case VAL_GAME:
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 130;
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gText_ThreeDashes, x, y, 0, NULL);
            break;
        case VAL_ITEM:
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 145;
            CopyItemName(sDebugPkmCreatorData.data[index], gStringVar1);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gStringVar1, x, y, 0, NULL);
            break;
        case VAL_ABILITY:
            StringCopy(gStringVar1, gAbilityNames[GetAbilityBySpecies(sDebugPkmCreatorData.data[0], sDebugPkmCreatorData.data[index])]);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            break;
        case VAL_METLOCATATION:
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 130;
            GetMapName_HandleVersion(gStringVar1, sDebugPkmCreatorData.data[index], sDebugPkmCreatorData.data[13]);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gStringVar1, x, y, 0, NULL);
            break;
        case VAL_BALL:
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 130;
            CopyItemName(sDebugPkmCreatorData.data[index], gStringVar1);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gStringVar1, x, y, 0, NULL);
            break;
        case VAL_STATUS:
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 130;
            StringCopy(gStringVar1, StatusIndexes[sDebugPkmCreatorData.data[index]]);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gStringVar1, x, y, 0, NULL);
            break;			
        case VAL_MOVE_1 ... VAL_MOVE_4:
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                *bufferPosition = CHAR_SPACE;
                bufferPosition++;
                *bufferPosition = CHAR_1 + (index - 66);
                bufferPosition++;
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 120;
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[70 + (index - 66)], STR_CONV_MODE_LEADING_ZEROS, 2);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar1, x, y, 0, NULL);
            x = 136;
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[74 + (index - 66)], STR_CONV_MODE_LEADING_ZEROS, 1);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar1, x, y, 0, NULL);
            x = 144;
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gMoveNames[sDebugPkmCreatorData.data[index]], x, y, 0, NULL);
            break;
        case VAL_PKRUS_STRAIN:
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 140;
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[VAL_PKRUS_DAYS_DEF], STR_CONV_MODE_LEADING_ZEROS, DebugPkmCreator_Options[VAL_PKRUS_DAYS_DEF].digitCount);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar1, x, y, 0, NULL);
            x = 180;
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[VAL_PKRUS_DAYS_LEFT], STR_CONV_MODE_LEADING_ZEROS, DebugPkmCreator_Options[VAL_PKRUS_DAYS_LEFT].digitCount);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar1, x, y, 0, NULL);
            break;
        case VAL_HP_IV ... VAL_SPDEF_IV:
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            if (data->text != NULL)
            {
                bufferPosition = StringCopy(bufferPosition, data->text);
                bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
            }
            *gStringVar3 = EOS;
            StringExpandPlaceholders(bufferPosition, Str_StringVars);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);

            x = 136;
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index + 6], STR_CONV_MODE_LEADING_ZEROS, DebugPkmCreator_Options[VAL_HP_MAX].digitCount);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar1, x, y, 0, NULL);
            x = 172;
            ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[index - 6], STR_CONV_MODE_LEADING_ZEROS, DebugPkmCreator_Options[VAL_HP_MAX].digitCount);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar1, x, y, 0, NULL);
            if (index == VAL_HP_IV)
            {
                x = 172;
                ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[VAL_HP_CURRENT], STR_CONV_MODE_LEADING_ZEROS, DebugPkmCreator_Options[VAL_HP_MAX].digitCount);
                AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar1, x, y, 0, NULL);
                x = 208;
                ConvertIntToDecimalStringN(gStringVar1, sDebugPkmCreatorData.data[VAL_HP_MAX], STR_CONV_MODE_LEADING_ZEROS, DebugPkmCreator_Options[VAL_HP_MAX].digitCount);
                AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar1, x, y, 0, NULL);
            }
            break;
        }
        x = 0;
        y+= 16;
        /* TODO: Add non-default cases:
            * PID (is shiny)
            * Status (sleep/toxic counter)
            * Language (language name)
        */
    }
}

static void DebugPkmCreator_EditModeRedraw(u32 digit, u8 editIndex)
{
    u32 x = 100;
    u32 y = sDebugPkmCreatorData.selectedOption * 2 * 8 + 16;
    u32 i = 0;
    u8* bufferPosition = gStringVar2;
    const u8* page = DebugPkmCreator_Pages[sDebugPkmCreatorData.currentPage];
    const struct EditPokemonStruct* data;
    u8 index;
    u32 digitToHighlight;

    if (editIndex != 0 && DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][editIndex - 1] != 0xFF)
    {
        index = DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][editIndex - 1];
        x += 5 * 8 * editIndex;
    }
    else
        index = page[sDebugPkmCreatorData.selectedOption];

    data = &DebugPkmCreator_Options[index];

    switch (index)
    {
    default:
        switch (data->mode)
        {
        case EDIT_NORMAL:
        default:
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
            ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            break;
        case EDIT_HEX:
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
            ConvertUIntToHexStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
            bufferPosition = StringCopy(bufferPosition, Str_CursorColor);
            bufferPosition = StringCopy(bufferPosition, Str_HexPrefix);
            break;
        case EDIT_NULL:
            return; // Haha, don't even make the effort...
        case EDIT_BOOL:
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 24, 16);
            bufferPosition = StringCopy(bufferPosition, Str_Cursor2Color);
            bufferPosition = StringCopy(bufferPosition, DebugPkmCreator_editingVal[editIndex] ? Str_On : Str_Off);
            *bufferPosition = EOS;
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            return;
        case EDIT_STRING:
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
            StringCopyN(gStringVar1, DebugPkmCreator_NameBuffer, data->digitCount);
            break;
        }
        break;
    case VAL_SPECIES:
        // Same as the default case, except we draw more data here
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        if (editIndex == 0)
        {
            x = 140;
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 72, 16);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gSpeciesNames[DebugPkmCreator_editingVal[editIndex]], x, y, 0, NULL);
            x = 100; // Reset for the actual species number
        }
        break;
    case VAL_LEVEL:
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        if (editIndex == 0)
        {
            //u32 newExp = gExperienceTables[gSpeciesInfo[sDebugPkmCreatorData.data[VAL_SPECIES]].growthRate][DebugPkmCreator_editingVal[editIndex]];
            x = 140;
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 120, 16);
            ConvertIntToDecimalStringN(gStringVar2, sDebugPkmCreatorData.data[VAL_EXP], STR_CONV_MODE_LEADING_ZEROS, DebugPkmCreator_Options[VAL_EXP].digitCount);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 100;
        }
        break;
    case VAL_TID:
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        if (editIndex == 0)
        {
            x = 140;
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 120, 16);
            ConvertIntToDecimalStringN(gStringVar2, sDebugPkmCreatorData.data[VAL_SID], STR_CONV_MODE_LEADING_ZEROS, DebugPkmCreator_Options[VAL_SID].digitCount);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 180;
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, GenderIndexes[sDebugPkmCreatorData.data[VAL_OT_GENDER]], x, y, 0, NULL);
            x = 100;
        }
        break;
    case VAL_PID:
        if (editIndex == 0) {
            u32 pid = DebugPkmCreator_editingVal[editIndex];
            u16 nature = GetNatureFromPersonality(pid);
            u8 gender = GetGenderFromSpeciesAndPersonality(sDebugPkmCreatorData.data[VAL_SPECIES], pid);
            u8 isSihny = IsShinyOtIdPersonality(sDebugPkmCreatorData.data[VAL_OT], pid);
            if (gender == MON_FEMALE) 
                gender = 1;
            else if (gender == MON_GENDERLESS) 
                gender = 2;
            x = 160;
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 120, 16);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gNatureNamePointers[nature], x, y, 0, NULL);
            x = 208;
            StringCopy(gStringVar2, GenderIndexes[gender]);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
            x = 214;
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, IsShinyIndex[isSihny], x, y, 0, NULL);
            x = 100;
        }
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 60, 16);
        ConvertUIntToHexStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        bufferPosition = StringCopy(bufferPosition, Str_CursorColor);
        bufferPosition = StringCopy(bufferPosition, Str_HexPrefix);
        break;
    case VAL_OT_GENDER:
    case VAL_PKM_GENDER:
        if (editIndex != 0 && page[sDebugPkmCreatorData.selectedOption] == 0)
            x = 204;
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 8, 16);
        bufferPosition = StringCopy(bufferPosition, Str_Cursor2Color);
        bufferPosition = StringCopy(bufferPosition, GenderIndexes[DebugPkmCreator_editingVal[editIndex]]);
        *bufferPosition = EOS;
        AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
        return;
    case VAL_GAME:
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        if (editIndex == 0)
        {
            x = 130;
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 120, 16);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gText_ThreeDashes, x, y, 0, NULL);
            x = 100;
        }
        break;
    case VAL_ITEM:
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        if (editIndex == 0)
        {
            x = 145;
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 120, 16);
            CopyItemName(DebugPkmCreator_editingVal[editIndex], gStringVar2);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gStringVar2, x, y, 0, NULL);
            x = 100;
        }
        break;
    case VAL_ABILITY:
        if (editIndex != 0 && page[sDebugPkmCreatorData.selectedOption] == 0)
            x = 204;
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 120, 16);
        bufferPosition = StringCopy(bufferPosition, Str_Cursor2Color);
        bufferPosition = StringCopy(bufferPosition, gAbilityNames[GetAbilityBySpecies(sDebugPkmCreatorData.data[0], DebugPkmCreator_editingVal[editIndex])]);
        *bufferPosition = EOS;
        AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
        return;
    case VAL_METLOCATATION:
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        if (editIndex == 0)
        {
            x = 130;
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 120, 16);
            GetMapName_HandleVersion(gStringVar2, DebugPkmCreator_editingVal[editIndex], sDebugPkmCreatorData.data[13]);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gStringVar2, x, y, 0, NULL);
            x = 100;
        }
        break;
    case VAL_BALL:
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        if (editIndex == 0)
        {
            x = 130;
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 120, 16);
            CopyItemName(DebugPkmCreator_editingVal[editIndex], gStringVar2);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gStringVar2, x, y, 0, NULL);
            x = 100;
        }
        break;
    case VAL_STATUS:
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        if (editIndex == 0)
        {
            x = 130;
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 120, 16);
            CopyItemName(DebugPkmCreator_editingVal[editIndex], gStringVar2);
            StringCopy(gStringVar2, StatusIndexes[DebugPkmCreator_editingVal[editIndex]]);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gStringVar2, x, y, 0, NULL);
            x = 100;
        }
        break;
    case VAL_HP_EV ... VAL_SPDEF_EV:
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        x = 136;
        break;
    case VAL_HP_CURRENT:
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        x = 172;
        break;
    case VAL_MOVE_1 ... VAL_MOVE_4:
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6 - 4, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        if (editIndex == 0)
        {
            x = 144;
            // TODO: Fill all the way to the end?
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 120, 16);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, 1, gMoveNames[DebugPkmCreator_editingVal[editIndex]], x, y, 0, NULL);
            x = 100;
        }
        break;
    case VAL_MOVE_1_PP ... VAL_MOVE_4_PP:
        x = 120;
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        break;
    case VAL_MOVE_1_PPUP ... VAL_MOVE_4_PPUP:
        if (TRUE)
        {
            u16 move = sDebugPkmCreatorData.data[index - 8];
            u8 basePP = gBattleMoves[move].pp;
            basePP = basePP + ((basePP * 20 * DebugPkmCreator_editingVal[editIndex]) / 100);

            x = 120;
            FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, DebugPkmCreator_Options[VAL_MOVE_1_PP].digitCount * 6, 16);
            ConvertIntToDecimalStringN(gStringVar2, basePP, STR_CONV_MODE_LEADING_ZEROS, DebugPkmCreator_Options[VAL_MOVE_1_PP].digitCount);
            AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
        }
        x = 136;
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        ConvertIntToDecimalStringN(gStringVar1, DebugPkmCreator_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
        break;
    }

    bufferPosition = StringCopy(bufferPosition, Str_CursorColor);
    digitToHighlight = data->mode == EDIT_STRING ? digit : data->digitCount - digit - 1;
    for (i = 0; i < data->digitCount; i++)
    {
        if (i == digitToHighlight)
            bufferPosition = StringCopy(bufferPosition, Str_Cursor2Color);
        *bufferPosition = gStringVar1[i];
        bufferPosition++;
        if (i == digitToHighlight)
            bufferPosition = StringCopy(bufferPosition, Str_CursorColorOff);
    }
    *bufferPosition = EOS;
    AddTextPrinterParameterized(sDebugPkmCreatorData.menuWindowId, FONT_NARROW, gStringVar2, x, y, 0, NULL);
    /* TODO Re-print the following data once edited:
        * PID (is shiny)
        * Status (sleep/toxic counter)
        * Language (language name)
    */
}



static void DebugPkmCreator_ProcessInput(u8 taskid)
{
    u16 keys = gMain.newKeys;
    struct Task* task = &gTasks[taskid];
    struct Pokemon* mons;

    if (keys & DPAD_LEFT) // Switch Pages
    {
        if (sDebugPkmCreatorData.currentPage > 0)
            sDebugPkmCreatorData.currentPage--;
        else
            sDebugPkmCreatorData.currentPage = PAGE_COUNT;
        FillWindowPixelBuffer(sDebugPkmCreatorData.menuWindowId, 0x11);
        DebugPkmCreator_Redraw();
        PlaySE(SE_SELECT);
        return;
    }
    if (keys & DPAD_RIGHT) // Switch Pages
    {
        if (sDebugPkmCreatorData.currentPage < PAGE_COUNT)
            sDebugPkmCreatorData.currentPage++;
        else
            sDebugPkmCreatorData.currentPage = 0;
        FillWindowPixelBuffer(sDebugPkmCreatorData.menuWindowId, 0x11);
        DebugPkmCreator_Redraw();
        PlaySE(SE_SELECT);
        return;
    }
    if (keys & DPAD_UP) // Switch Entry
    {
        if (sDebugPkmCreatorData.selectedOption > 0)
            sDebugPkmCreatorData.selectedOption--;
        else
            sDebugPkmCreatorData.selectedOption = 5;
        DebugPkmCreator_Redraw();
        PlaySE(SE_SELECT);
        return;
    }
    if (keys & DPAD_DOWN) // Switch Entry
    {
        if (sDebugPkmCreatorData.selectedOption < 5)
            sDebugPkmCreatorData.selectedOption++;
        else
            sDebugPkmCreatorData.selectedOption = 0;
        DebugPkmCreator_Redraw();
        PlaySE(SE_SELECT);
        return;
    }
    if (keys & L_BUTTON) // Switch Pokemon e.g. in Box or Party (not used on ADD)
    {
        // This check is much simpler than the one below it...
        if (sDebugPkmCreatorData.index <= 0) return;
        sDebugPkmCreatorData.index--;
        switch (sDebugPkmCreatorData.mode)
        {
        case 2:
            // We can technically select slot 404 of box 1 (actually box 13 slot 14) but it's still valid behavior provided the max index was set properly above.
            mons = (struct Pokemon*) &gPokemonStoragePtr->boxes[0][sDebugPkmCreatorData.index];
            sDebugPkmCreatorData.monBeingEdited = mons;
            CopyMon(&sDebugPkmCreatorData.mon, mons, sizeof(struct BoxPokemon));
            CalculateMonStats(&sDebugPkmCreatorData.mon);
            break;
        case 1:
        case 5:
            mons = &gPlayerParty[sDebugPkmCreatorData.index];
            sDebugPkmCreatorData.monBeingEdited = mons;
            CopyMon(&sDebugPkmCreatorData.mon, mons, sizeof(struct Pokemon));
            break;
        case 3:
        case 4:
        case 10:
            mons = &gEnemyParty[sDebugPkmCreatorData.index];
            sDebugPkmCreatorData.monBeingEdited = mons;
            CopyMon(&sDebugPkmCreatorData.mon, mons, sizeof(struct Pokemon));
            break;
        default:
            break;
        }
        DebugPkmCreator_PopulateDataStruct();
        FillWindowPixelBuffer(sDebugPkmCreatorData.menuWindowId, 0x11);
        DebugPkmCreator_Redraw();
        PlaySE(SE_SELECT);
        return;
    }
    if (keys & R_BUTTON) // Switch Pokemon e.g. in Box or Party (not used on ADD)
    {
        u32 max_index;
        switch (sDebugPkmCreatorData.mode)
        {
        case 0:
        case 6 ... 8:
        default:
            return;
        case 1:
        case 3 ... 5:
        case 10:
            max_index = PARTY_SIZE;
            break;
        case 2:
            max_index = TOTAL_BOXES_COUNT * IN_BOX_COUNT;
            break;
        }
        if (sDebugPkmCreatorData.index >= max_index - 1) return;
        sDebugPkmCreatorData.index++;
        switch (sDebugPkmCreatorData.mode)
        {
        case 2:
            mons = (struct Pokemon*) &gPokemonStoragePtr->boxes[0][sDebugPkmCreatorData.index];
            sDebugPkmCreatorData.monBeingEdited = mons;
            CopyMon(&sDebugPkmCreatorData.mon, mons, sizeof(struct BoxPokemon));
            CalculateMonStats(&sDebugPkmCreatorData.mon);
            break;
        case 1:
        case 5:
            mons = &gPlayerParty[sDebugPkmCreatorData.index];
            sDebugPkmCreatorData.monBeingEdited = mons;
            CopyMon(&sDebugPkmCreatorData.mon, mons, sizeof(struct Pokemon));
            break;
        case 3:
        case 4:
        case 10:
            mons = &gEnemyParty[sDebugPkmCreatorData.index];
            sDebugPkmCreatorData.monBeingEdited = mons;
            CopyMon(&sDebugPkmCreatorData.mon, mons, sizeof(struct Pokemon));
            break;
        }
        DebugPkmCreator_PopulateDataStruct();
        FillWindowPixelBuffer(sDebugPkmCreatorData.menuWindowId, 0x11);
        DebugPkmCreator_Redraw();
        PlaySE(SE_SELECT);
        return;
    }
    if (keys & B_BUTTON) // Close window
    {
        ClearStdWindowAndFrame(sDebugPkmCreatorData.headerWindowId, TRUE);
        RemoveWindow(sDebugPkmCreatorData.headerWindowId);
        ClearStdWindowAndFrame(sDebugPkmCreatorData.menuWindowId, TRUE);
        RemoveWindow(sDebugPkmCreatorData.menuWindowId);
        DestroyTask(taskid);
        
        if (sDebugPkmCreatorData.mode == 9 || sDebugPkmCreatorData.mode == 10)
            Debug_ReShowBattleDebugMenu();
        else
        {
            ScriptContext_Enable();
            PlaySE(SE_SELECT);
        }
        return;
    }
    if (keys & SELECT_BUTTON) // TODO: Re-randomize the PID and IVs, or if OT is selected, toggle OT gender
    {
        return;
    }
    if (keys & A_BUTTON) // Enter Edit Mode
    {
        u32 i;
        u8 index = DebugPkmCreator_Pages[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption];
        if (DebugPkmCreator_Options[index].mode != EDIT_NULL && DebugPkmCreator_Options[index].mode != EDIT_READONLY)
        {
            DebugPkmCreator_editingVal[0] = sDebugPkmCreatorData.data[index];
            if (DebugPkmCreator_Options[index].mode == EDIT_STRING)
            {
                StringCopyN(DebugPkmCreator_NameBuffer, (u8*) DebugPkmCreator_editingVal[0], 16);
                DebugPkmCreator_NameBuffer[DebugPkmCreator_Options[index].digitCount] = EOS;
            }
            else
            {
                for (i = 1; i < 4; i++)
                {
                    if (DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][i - 1] == 0xFF) 
                        break;
                    DebugPkmCreator_editingVal[i] = sDebugPkmCreatorData.data[DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][i - 1]];
                }
            }
            task->data[0] = 0;
            task->data[1] = 0;
            DebugPkmCreator_EditModeRedraw(task->data[0], task->data[1]);
            task->func = DebugPkmCreator_EditModeProcessInput;
            PlaySE(SE_SELECT);
        }
        return;
    }
    if (keys & START_BUTTON) // Confirm changes and add/edit Pokemon
    {
        DebugPkmCreator_SetMonData();
        // TODO: Add a confirmation prompt
        if (DebugPkmCreator_GiveToPlayer() != MON_CANT_GIVE)
            PlaySE(SE_EXP_MAX);
        else
            PlaySE(SE_BOO);

        ClearStdWindowAndFrame(sDebugPkmCreatorData.headerWindowId, TRUE);
        RemoveWindow(sDebugPkmCreatorData.headerWindowId);
        ClearStdWindowAndFrame(sDebugPkmCreatorData.menuWindowId, TRUE);
        RemoveWindow(sDebugPkmCreatorData.menuWindowId);
        DestroyTask(taskid);
        if (sDebugPkmCreatorData.mode == 9 || sDebugPkmCreatorData.mode == 10)
            Debug_ReShowBattleDebugMenu();
        else
            ScriptContext_Enable();
        return;
    }
}

static const u32 powersOf10[10] = {
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
};

static void DebugPkmCreator_EditModeProcessInput(u8 taskid)
{
    u16 keys = gMain.newKeys;
    u16 heldKeys = gMain.newAndRepeatedKeys;
    struct Task* task = &gTasks[taskid];
    u32 i, j, min, max, index, indexBeingEdited;
    u32 z = 0;

    u16 digit = task->data[0];
    u16 editIndex = task->data[1];

    u32 x = 100;
    u32 y = sDebugPkmCreatorData.selectedOption * 2 * 8 + 16;

    const struct EditPokemonStruct* data;
    const u8* page = DebugPkmCreator_Pages[sDebugPkmCreatorData.currentPage];

    if (editIndex != 0 && DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][editIndex - 1] != 0xFF) 
        index = DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][editIndex - 1];
    else
        index = page[sDebugPkmCreatorData.selectedOption];

    data = &DebugPkmCreator_Options[index];

    switch (index)
    {
    default:
        min = data->min;
        max = data->max;
        break;
    }

    if (keys & B_BUTTON) // Leave Edit Mode
    {
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, 124, 16);
        DebugPkmCreator_Redraw();
        task->func = DebugPkmCreator_ProcessInput;
        PlaySE(SE_SELECT);
        return;
    }

    if (keys & (A_BUTTON | START_BUTTON)) // Confirm current changes
    {
        if (data->mode == EDIT_STRING)
            StringCopyN((u8*) sDebugPkmCreatorData.data[index], DebugPkmCreator_NameBuffer, data->digitCount);
        else
        {
            for (i = 0; i < 4; i++)
            {
                if (i != 0)
                    indexBeingEdited = DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][i - 1];
                else 
                    indexBeingEdited = index;
                
                // Skip if: no entry, no value change or readonly value
                if (indexBeingEdited == 0xFF)
                    continue;
                if (sDebugPkmCreatorData.data[indexBeingEdited] == DebugPkmCreator_editingVal[i])
                    continue;
                data = &DebugPkmCreator_Options[indexBeingEdited];
                if (data->mode == EDIT_READONLY)
                    continue;

                sDebugPkmCreatorData.data[indexBeingEdited] = DebugPkmCreator_editingVal[i];
                switch (indexBeingEdited)
                {
                default:
                    DebugPkmCreator_SetMonData();
                    DebugPkmCreator_PopulateDataStruct();
                    break;
                case VAL_SPECIES:
                    DebugPkmCreator_SetMonData();
                    SetMonData(&sDebugPkmCreatorData.mon, data->SetMonDataParam, &DebugPkmCreator_editingVal[i]);
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_NICKNAME, gSpeciesNames[DebugPkmCreator_editingVal[i]]);
                    // Clear moves
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_MOVE1, &z);
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_MOVE2, &z);
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_MOVE3, &z);
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_MOVE4, &z);
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_PP1, &z);
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_PP2, &z);
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_PP3, &z);
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_PP4, &z);
                    GiveMonInitialMoveset(&sDebugPkmCreatorData.mon);
                    // preserve level
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_EXP, &gExperienceTables[gSpeciesInfo[DebugPkmCreator_editingVal[i]].growthRate][sDebugPkmCreatorData.data[15]]);
                    CalculateMonStats(&sDebugPkmCreatorData.mon);
                    // preserve sanity bit
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_SANITY_HAS_SPECIES, &sDebugPkmCreatorData.data[11]);
                    DebugPkmCreator_PopulateDataStruct();
                    break;
                case VAL_PID ... VAL_SID:
                    DebugPkmCreator_Init_SetNewMonData(FALSE);
                    DebugPkmCreator_PopulateDataStruct();
                    break;
                case VAL_LEVEL:
                    SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_EXP, &gExperienceTables[gSpeciesInfo[sDebugPkmCreatorData.data[VAL_SPECIES]].growthRate][sDebugPkmCreatorData.data[VAL_LEVEL]]);
                    CalculateMonStats(&sDebugPkmCreatorData.mon);
                    DebugPkmCreator_PopulateDataStruct();
                    DebugPkmCreator_editingVal[0] = sDebugPkmCreatorData.data[VAL_LEVEL];
                    DebugPkmCreator_editingVal[1] = sDebugPkmCreatorData.data[VAL_EXP];
                    break;
                case VAL_EXP:
                    SetMonData(&sDebugPkmCreatorData.mon, data->SetMonDataParam, &DebugPkmCreator_editingVal[i]);
                    CalculateMonStats(&sDebugPkmCreatorData.mon);
                    DebugPkmCreator_PopulateDataStruct();
                    break;
                case VAL_HP_IV ... VAL_SPDEF_EV:
                    if (indexBeingEdited == VAL_HP_IV || indexBeingEdited == VAL_HP_EV)
                    {
                        u16 maxHp;
                        SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_HP_IV, &DebugPkmCreator_editingVal[0]);
                        SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_HP_EV, &DebugPkmCreator_editingVal[1]);
                        CalculateMonStats(&sDebugPkmCreatorData.mon);
                        maxHp = GetMonData(&sDebugPkmCreatorData.mon, MON_DATA_MAX_HP, NULL);
                        sDebugPkmCreatorData.data[VAL_HP_CURRENT] = maxHp;
                        SetMonData(&sDebugPkmCreatorData.mon, MON_DATA_HP, &maxHp);
                        DebugPkmCreator_editingVal[2] = maxHp;
                        DebugPkmCreator_PopulateDataStruct();
                        i = 4;
                        break;
                    }
                    
                    SetMonData(&sDebugPkmCreatorData.mon, data->SetMonDataParam, &DebugPkmCreator_editingVal[i]);
                    CalculateMonStats(&sDebugPkmCreatorData.mon);
                    DebugPkmCreator_PopulateDataStruct();
                    break;
                }
            }
        }
        FillWindowPixelRect(sDebugPkmCreatorData.menuWindowId, 0x11, x, y, data->digitCount * 6, 16);
        DebugPkmCreator_Redraw();
        task->func = DebugPkmCreator_ProcessInput;
        PlaySE(SE_SELECT);
        return;
    }
    if (heldKeys & DPAD_UP) // Change selected value
    {
        if (index == 1) // PID does have a min/max, but they cover the entire 32-bit value range.
        {
            DebugPkmCreator_editingVal[editIndex] += (1 << (4 * digit));
            DebugPkmCreator_EditModeRedraw(digit, editIndex);
            PlaySE(SE_SELECT);
            return;
        }
        switch (data->mode)
        {
        case EDIT_NORMAL:
        default:
            if (DebugPkmCreator_editingVal[editIndex] + powersOf10[digit] > max)
                DebugPkmCreator_editingVal[editIndex] = data->min;
            else
                DebugPkmCreator_editingVal[editIndex] += powersOf10[digit];
            break;
        case EDIT_NULL:
        case EDIT_READONLY:
            return;
        case EDIT_BOOL:
            if (DebugPkmCreator_editingVal[editIndex]) return;
            DebugPkmCreator_editingVal[editIndex] = TRUE;
            break;
        case EDIT_HEX:
            if (DebugPkmCreator_editingVal[editIndex] + (1 << (4 * digit)) > max)
                DebugPkmCreator_editingVal[editIndex] = data->min;
            else
                DebugPkmCreator_editingVal[editIndex] += (1 << (4 * digit));
            break;
        case EDIT_STRING:
            DebugPkmCreator_NameBuffer[digit]++;
            DebugPkmCreator_NameBuffer[digit] &= 0xFF;
            if (DebugPkmCreator_NameBuffer[digit] >= CHAR_DYNAMIC)
                DebugPkmCreator_NameBuffer[digit] = EOS;
            else if (DebugPkmCreator_NameBuffer[digit] >= CHAR_DYNAMIC && DebugPkmCreator_NameBuffer[digit] < EOS)
                DebugPkmCreator_NameBuffer[digit] = 0;
            break;
        }
        DebugPkmCreator_EditModeRedraw(digit, editIndex);
        PlaySE(SE_SELECT);
        return;
    }
    if (heldKeys & DPAD_DOWN) // Change selected value
    {
        if (index == 1)
        {
            DebugPkmCreator_editingVal[editIndex] -= (1 << (4 * digit));
            DebugPkmCreator_EditModeRedraw(digit, editIndex);
            PlaySE(SE_SELECT);
            return;
        }
        switch (data->mode)
        {
        case EDIT_NORMAL:
        default:
            if ((s32) (DebugPkmCreator_editingVal[editIndex] - powersOf10[digit]) < (s32) min)
                DebugPkmCreator_editingVal[editIndex] = data->max;
            else
                DebugPkmCreator_editingVal[editIndex] -= powersOf10[digit];
            break;
        case EDIT_NULL:
        case EDIT_READONLY:
            return;
        case EDIT_BOOL:
            if (!DebugPkmCreator_editingVal[editIndex]) return;
            DebugPkmCreator_editingVal[editIndex] = FALSE;
            break;
        case EDIT_HEX:
            if ((s32) (DebugPkmCreator_editingVal[editIndex] - (1 << (4 * digit))) < (s32) min)
                DebugPkmCreator_editingVal[editIndex] = data->max;
            else
                DebugPkmCreator_editingVal[editIndex] -= (1 << (4 * digit));
            break;
        case EDIT_STRING:
            DebugPkmCreator_NameBuffer[digit]--;
            DebugPkmCreator_NameBuffer[digit] &= 0xFF;
            if (DebugPkmCreator_NameBuffer[digit] >= CHAR_DYNAMIC && DebugPkmCreator_NameBuffer[digit] < EOS)
                DebugPkmCreator_NameBuffer[digit] = CHAR_DYNAMIC - 1;
            break;
        }
        DebugPkmCreator_EditModeRedraw(digit, editIndex);
        PlaySE(SE_SELECT);
        return;
    }
    if (keys & DPAD_LEFT) // Change selected digit
    {
        if (data->mode == EDIT_STRING)
        {
            if ((s16) (digit - 1) < 0)
            {
                if ((editIndex != 0 && DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][editIndex - 2] != 0xFF) || editIndex == 1)
                {
                    DebugPkmCreator_EditModeRedraw(data->digitCount, editIndex);
                    digit = DebugPkmCreator_Options[DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][editIndex]].digitCount - 1;
                    editIndex--;
                }
                else
                    return;
            }
            else 
                digit--;
        }
        else
        {
            if (digit >= data->digitCount - 1)
            {
                if ((editIndex != 0 && DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][editIndex - 2] != 0xFF) || editIndex == 1)
                {
                    DebugPkmCreator_EditModeRedraw(data->digitCount, editIndex);
                    digit = 0;
                    editIndex--;
                }
                else 
                    return;
            }
            else 
                digit++;
        }
        DebugPkmCreator_EditModeRedraw(digit, editIndex);
        task->data[0] = digit;
        task->data[1] = editIndex;
        PlaySE(SE_SELECT);
        return;
    }
    if (keys & DPAD_RIGHT) // Change selected digit
    {
        if (data->mode == EDIT_STRING)
        {
            if (digit >= data->digitCount - 1)
            {
                if (editIndex + 1 < 4 && DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][editIndex] != 0xFF)
                {
                    DebugPkmCreator_EditModeRedraw(data->digitCount, editIndex);
                    digit = 0;
                    editIndex++;
                }
                else
                    return;
            }
            else
                digit++;
        }
        else 
        {
            if ((s16) (digit - 1) < 0) 
            {
                if (editIndex + 1 < 4 && DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][editIndex] != 0xFF && DebugPkmCreator_Options[DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][editIndex]].mode != EDIT_READONLY)
                {
                    DebugPkmCreator_EditModeRedraw(data->digitCount, editIndex);
                    digit = DebugPkmCreator_Options[DebugPkmCreator_AltIndexes[sDebugPkmCreatorData.currentPage][sDebugPkmCreatorData.selectedOption][editIndex]].digitCount - 1;
                    editIndex++;
                }
                else
                    return;
            }
            else
                digit--;
        }
        DebugPkmCreator_EditModeRedraw(digit, editIndex);
        task->data[0] = digit;
        task->data[1] = editIndex;
        PlaySE(SE_SELECT);
        return;
    }
    // TODO: Select resets the value to default
}

// This is basically a copy of GiveMonToPlayer, except without setting the OT details to the player's.
static u8 DebugPkmCreator_GiveToPlayer(void)
{
    u32 i;
    struct Pokemon* mon = &sDebugPkmCreatorData.mon;
    switch (sDebugPkmCreatorData.mode)
    {
    case 0:
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) == 0)
                break;
        }

        if (i >= PARTY_SIZE)
            return CopyMonToPC(mon);

        CopyMon(&gPlayerParty[i], mon, sizeof(*mon));
        gPlayerPartyCount = i + 1;
        return MON_GIVEN_TO_PARTY;
    case 1:
    case 3 ... 5:
    case 10:
        CopyMon(sDebugPkmCreatorData.monBeingEdited, mon, sizeof(struct Pokemon));
        return MON_GIVEN_TO_PARTY;
    case 2:
        CopyMon(sDebugPkmCreatorData.monBeingEdited, mon, sizeof(struct BoxPokemon));
        return MON_GIVEN_TO_PC;
    case 6:
    case 9:
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
                break;
        }

        if (i >= PARTY_SIZE)
            return MON_CANT_GIVE;

        CopyMon(&gEnemyParty[i], mon, sizeof(*mon));
        gEnemyPartyCount = i + 1;
        return MON_GIVEN_TO_PARTY;
    case 7:
    case 8:
    default:
        return MON_CANT_GIVE;
    }
}
#endif
