#include "global.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "decoration.h"
#include "decoration_inventory.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "item_icon.h"
#include "item_menu.h"
#include "list_menu.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "money.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "scanline_effect.h"
#include "script.h"
#include "shop.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "text_window.h"
#include "tv.h"
#include "constants/decorations.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/metatile_behaviors.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "data/battle_frontier/battle_frontier_exchange_corner.h"

#define TAG_SCROLL_ARROW   2100
#define TAG_ITEM_ICON_BASE 9110 // immune to time blending
#define TAG_BERRY_ICON     9150 // berry icon for Kurt shop
#define TAG_QUANTITY_BERRY 9151 // scaled berry icon for quantity window

#define MAX_ITEMS_SHOWN 8

enum {
    WIN_BUY_SELL_QUIT,
    WIN_BUY_QUIT,
};

enum {
    WIN_MONEY,
    WIN_BERRIES,
    WIN_ITEM_LIST,
    WIN_ITEM_DESCRIPTION,
    WIN_QUANTITY_IN_BAG,
    WIN_QUANTITY_PRICE,
    WIN_MESSAGE,
};

enum {
    COLORID_NORMAL,      // Item descriptions, quantity in bag, and quantity/price
    COLORID_ITEM_LIST,   // The text in the item list, and the cursor normally
    COLORID_GRAY_CURSOR, // When the cursor has selected an item to purchase
};

enum {
    MART_TYPE_NORMAL,
    MART_TYPE_DECOR,
    MART_TYPE_DECOR2,
    MART_TYPE_KURT,
    MART_TYPE_BP,       // BP currency, multi-buy (Vitamin clerk)
    MART_TYPE_BP_ITEM,  // BP currency, single-buy regular items (Hold Item clerk)
    MART_TYPE_BP_DECOR, // BP currency, single-buy decorations (Decor clerks)
};

// shop view window NPC info enum
enum
{
    OBJ_EVENT_ID,
    X_COORD,
    Y_COORD,
    ANIM_NUM,
    LAYER_TYPE
};

struct MartInfo
{
    void (*callback)(void);
    const struct MenuAction *menuActions;
    const u16 *itemList;
    u16 itemCount;
    u8 windowId;
    u8 martType;
};

struct ShopData
{
    u16 tilemapBuffers[4][0x400];
    u32 totalCost;
    u16 itemsShowed;
    u16 selectedRow;
    u16 scrollOffset;
    u16 maxQuantity;
    u8 scrollIndicatorsTaskId;
    u8 iconSlot;
    u8 itemSpriteIds[2];
    s16 viewportObjects[OBJECT_EVENTS_COUNT][5];
};

// Kurt's berry-to-ball mapping
struct KurtBallMapping
{
    u16 berry;
    u16 ball;
};

static const struct KurtBallMapping sKurtBallMappings[] =
{
    {ITEM_PECHA_BERRY,  ITEM_LOVE_BALL},
    {ITEM_RAWST_BERRY,  ITEM_LURE_BALL},
    {ITEM_CHERI_BERRY,  ITEM_FRIEND_BALL},
    {ITEM_ORAN_BERRY,   ITEM_HEAVY_BALL},
    {ITEM_CHESTO_BERRY, ITEM_MOON_BALL},
    {ITEM_ASPEAR_BERRY, ITEM_FAST_BALL},
    {ITEM_PERSIM_BERRY, ITEM_LEVEL_BALL},
};

static EWRAM_DATA struct MartInfo sMartInfo = {0};
static EWRAM_DATA struct ShopData *sShopData = NULL;
static EWRAM_DATA struct ListMenuItem *sListMenuItems = NULL;
static EWRAM_DATA u8 (*sItemNames)[ITEM_NAME_LENGTH + 2] = {0};
static EWRAM_DATA u8 sPurchaseHistoryId = 0;
static EWRAM_DATA u16 sKurtCurrentBerry = ITEM_NONE;
static EWRAM_DATA u8 sBerryIconSpriteId = SPRITE_NONE;
static EWRAM_DATA u8 sQuantityBerryIconSpriteId = SPRITE_NONE;
static EWRAM_DATA const struct BPShopEntry *sBPShopEntries = NULL;
EWRAM_DATA struct ItemSlot gMartPurchaseHistory[SMARTSHOPPER_NUM_ITEMS] = {0};

static void Task_ShopMenu(u8 taskId);
static void Task_HandleShopMenuQuit(u8 taskId);
static void CB2_InitBuyMenu(void);
static void Task_GoToBuyOrSellMenu(u8 taskId);
static void MapPostLoadHook_ReturnToShopMenu(void);
static void Task_ReturnToShopMenu(u8 taskId);
static void ShowShopMenuAfterExitingBuyOrSellMenu(u8 taskId);
static void BuyMenuDrawGraphics(void);
static void BuyMenuAddScrollIndicatorArrows(void);
static void Task_BuyMenu(u8 taskId);
static void BuyMenuBuildListMenuTemplate(void);
static void BuyMenuInitBgs(void);
static void BuyMenuInitWindows(void);
static void BuyMenuDecompressBgGraphics(void);
static void BuyMenuSetListEntry(struct ListMenuItem *, u16, u8 *);
static void BuyMenuAddItemIcon(u16, u8);
static void BuyMenuRemoveItemIcon(u16, u8);
static void BuyMenuPrint(u8 windowId, const u8 *text, u8 x, u8 y, s8 speed, u8 colorSet);
static void BuyMenuDrawMapGraphics(void);
static void BuyMenuCopyMenuBgToBg1TilemapBuffer(void);
static void BuyMenuCollectObjectEventData(void);
static void BuyMenuDrawObjectEvents(void);
static void BuyMenuDrawMapBg(void);
static bool8 BuyMenuCheckForOverlapWithMenuBg(int, int);
static void BuyMenuDrawMapMetatile(s16, s16, const u16 *, u8);
static void BuyMenuDrawMapMetatileLayer(u16 *dest, s16 offset1, s16 offset2, const u16 *src);
static bool8 BuyMenuCheckIfObjectEventOverlapsMenuBg(s16 *);
static void ExitBuyMenu(u8 taskId);
static void Task_ExitBuyMenu(u8 taskId);
static void BuyMenuTryMakePurchase(u8 taskId);
static void BuyMenuReturnToItemList(u8 taskId);
static void Task_BuyHowManyDialogueInit(u8 taskId);
static void BuyMenuConfirmPurchase(u8 taskId);
static void BuyMenuPrintItemQuantityAndPrice(u8 taskId);
static void Task_BuyHowManyDialogueHandleInput(u8 taskId);
static void BuyMenuSubtractMoney(u8 taskId);
static void RecordItemPurchase(u8 taskId);
static void Task_ReturnToItemListAfterItemPurchase(u8 taskId);
static void Task_ReturnToItemListAfterDecorationPurchase(u8 taskId);
static void Task_ExitKurtShopAfterPurchase(u8 taskId);
static void Task_HandleShopMenuBuy(u8 taskId);
static void Task_HandleShopMenuSell(u8 taskId);
static void BuyMenuPrintItemDescriptionAndShowItemIcon(s32 item, bool8 onInit, struct ListMenu *list);
static void BuyMenuPrintPriceInList(u8 windowId, u32 itemId, u8 y);

// Kurt shop helper functions
static u16 GetBerryFromBall(u16 ballItem)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sKurtBallMappings); i++)
    {
        if (sKurtBallMappings[i].ball == ballItem)
            return sKurtBallMappings[i].berry;
    }
    return ITEM_NONE;
}

static const struct OamData sOamData_QuantityBerryIcon =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_DOUBLE,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 2,
    .affineParam = 0
};

static const union AnimCmd sSpriteAnim_QuantityBerryIcon[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_QuantityBerryIcon[] =
{
    sSpriteAnim_QuantityBerryIcon
};

static const struct SpriteTemplate sSpriteTemplate_QuantityBerryIcon =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &sOamData_QuantityBerryIcon,
    .anims = sSpriteAnimTable_QuantityBerryIcon,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

// Get total quantity of an item in the bag
static u16 GetItemQuantityInBag(u16 itemId)
{
    u8 i;
    u8 pocket;
    u16 totalQuantity = 0;
    
    if (ItemId_GetPocket(itemId) == 0)
        return 0;
    
    pocket = ItemId_GetPocket(itemId) - 1;
    
    // Sum up quantities across all slots that contain this item
    for (i = 0; i < gBagPockets[pocket].capacity; i++)
    {
        if (gBagPockets[pocket].itemSlots[i].itemId == itemId)
        {
            totalQuantity += GetBagItemQuantity(&gBagPockets[pocket].itemSlots[i].quantity);
        }
    }
    
    return totalQuantity;
}

static void AddBerryIcon(u16 berryItem)
{
    u8 spriteId;
    
    // Remove old icon if it exists
    if (sBerryIconSpriteId != SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_BERRY_ICON);
        FreeSpritePaletteByTag(TAG_BERRY_ICON);
        DestroySprite(&gSprites[sBerryIconSpriteId]);
        sBerryIconSpriteId = SPRITE_NONE;
    }
    
    if (berryItem == ITEM_NONE)
        return;
    
    // Create berry icon using standard item icon function
    spriteId = AddItemIconSprite(TAG_BERRY_ICON, TAG_BERRY_ICON, berryItem);
    if (spriteId != MAX_SPRITES)
    {
        sBerryIconSpriteId = spriteId;
        // Position at left side of berry window
        // WIN_BERRIES is at screen position (8,8), size 80x24
        gSprites[spriteId].x = 22;  // 8 + 13 (left padding + half icon width)
        gSprites[spriteId].y = 24;  // 8 + 12 (center vertically in window)
        gSprites[spriteId].oam.priority = 0;
    }
}

static void RemoveBerryIcon(void)
{
    if (sBerryIconSpriteId != SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_BERRY_ICON);
        FreeSpritePaletteByTag(TAG_BERRY_ICON);
        DestroySprite(&gSprites[sBerryIconSpriteId]);
        sBerryIconSpriteId = SPRITE_NONE;
    }
}

static void AddQuantityBerryIcon(u16 berryItem)
{
    u8 spriteId;
    
    // Remove old icon if it exists
    if (sQuantityBerryIconSpriteId != SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_QUANTITY_BERRY);
        FreeSpritePaletteByTag(TAG_QUANTITY_BERRY);
        DestroySprite(&gSprites[sQuantityBerryIconSpriteId]);
        sQuantityBerryIconSpriteId = SPRITE_NONE;
    }
    
    if (berryItem == ITEM_NONE)
        return;
    
    // Create scaled berry icon using custom template
    spriteId = AddCustomItemIconSprite(&sSpriteTemplate_QuantityBerryIcon, TAG_QUANTITY_BERRY, TAG_QUANTITY_BERRY, berryItem);
    if (spriteId != MAX_SPRITES)
    {
        sQuantityBerryIconSpriteId = spriteId;
        // WIN_QUANTITY_PRICE is at tilemap (18,11) = screen position (144, 88), size 80x16
        gSprites[spriteId].x = 219;
        gSprites[spriteId].y = 99;
        gSprites[spriteId].oam.priority = 0;
        
        SetOamMatrixRotationScaling(gSprites[spriteId].oam.matrixNum, 192, 192, 0);
    }
}

static void RemoveQuantityBerryIcon(void)
{
    if (sQuantityBerryIconSpriteId != SPRITE_NONE)
    {
        FreeSpriteTilesByTag(TAG_QUANTITY_BERRY);
        FreeSpritePaletteByTag(TAG_QUANTITY_BERRY);
        DestroySprite(&gSprites[sQuantityBerryIconSpriteId]);
        sQuantityBerryIconSpriteId = SPRITE_NONE;
    }
}

static void PrintBerryCount(u8 windowId, u16 berryItem)
{
    u16 berryCount;
    
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    
    if (berryItem == ITEM_NONE)
    {
        RemoveBerryIcon();
        return;
    }
    
    // Get actual berry count from bag
    berryCount = GetItemQuantityInBag(berryItem);
    
    // Add/update berry icon sprite
    AddBerryIcon(berryItem);
    
    // Format string: "COUNT: ###"
    ConvertIntToDecimalStringN(gStringVar1, berryCount, STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar4, gText_InBagVar1);
    
    // Print text after the icon
    AddTextPrinterParameterized(windowId, FONT_NORMAL, gStringVar4, 23, 5, 0, NULL);
}

// Look up the BP cost for an item in the active BP shop entry table.
static u16 GetBPCostForItem(u16 itemId)
{
    u16 i = 0;
    if (sBPShopEntries == NULL)
        return 0;
    while (sBPShopEntries[i].item != ITEM_NONE)
    {
        if (sBPShopEntries[i].item == itemId)
            return sBPShopEntries[i].bpCost;
        i++;
    }
    return 0;
}

// Draw the border and print the current BP amount in the WIN_MONEY window.
static void PrintBPAmountInMoneyBox(u8 windowId, u32 bp, u8 speed)
{
    u8 *ptr = ConvertIntToDecimalStringN(gStringVar1, bp, STR_CONV_MODE_RIGHT_ALIGN, 4);
    u8 x;
    StringCopy(ptr, gText_BP);
    x = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar1, 80);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    AddTextPrinterParameterized(windowId, FONT_NORMAL, gStringVar1, x, 1, speed, NULL);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static const u16 sShopInventory_ZeroBadges[] = {
    ITEM_POKE_BALL,
    ITEM_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_OneBadge[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_TwoBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_ThreeBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_FourBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_FiveBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_SixBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_SevenBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_MAX_POTION,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_MAX_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_EightBadges[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_MAX_POTION,
    ITEM_FULL_RESTORE,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_MAX_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 *const sShopInventories[] = 
{
    sShopInventory_ZeroBadges, 
    sShopInventory_OneBadge,
    sShopInventory_TwoBadges,
    sShopInventory_ThreeBadges,
    sShopInventory_FourBadges,
    sShopInventory_FiveBadges,
    sShopInventory_SixBadges,
    sShopInventory_SevenBadges,
    sShopInventory_EightBadges
};

static const u16 sShopInventory_ZeroBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_POTION,
    ITEM_ETHER,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_OneBadge_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ETHER,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_TwoBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ETHER,
    ITEM_ELIXIR,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_ThreeBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ETHER,
    ITEM_ELIXIR,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_FourBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_ETHER,
    ITEM_ELIXIR,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_FiveBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_ETHER,
    ITEM_MAX_ETHER,
    ITEM_ELIXIR,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_SixBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_ETHER,
    ITEM_MAX_ETHER,
    ITEM_ELIXIR,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_SevenBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_MAX_POTION,
    ITEM_ETHER,
    ITEM_MAX_ETHER,
    ITEM_ELIXIR,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_MAX_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 sShopInventory_EightBadges_PC[] = {
    ITEM_POKE_BALL,
    ITEM_GREAT_BALL,
    ITEM_ULTRA_BALL,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_MAX_POTION,
    ITEM_FULL_RESTORE,
    ITEM_ETHER,
    ITEM_MAX_ETHER,
    ITEM_ELIXIR,
    ITEM_MAX_ELIXIR,
    ITEM_FULL_HEAL,
    ITEM_ANTIDOTE,
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_AWAKENING,
    ITEM_PARALYZE_HEAL,
    ITEM_REVIVE,
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_MAX_REPEL,
    ITEM_POKE_DOLL,
    ITEM_ESCAPE_ROPE,
    ITEM_NONE
};

static const u16 *const sShopInventories_PC[] = 
{
    sShopInventory_ZeroBadges_PC, 
    sShopInventory_OneBadge_PC,
    sShopInventory_TwoBadges_PC,
    sShopInventory_ThreeBadges_PC,
    sShopInventory_FourBadges_PC,
    sShopInventory_FiveBadges_PC,
    sShopInventory_SixBadges_PC,
    sShopInventory_SevenBadges_PC,
    sShopInventory_EightBadges_PC
};

static const struct YesNoFuncTable sShopPurchaseYesNoFuncs =
{
    BuyMenuTryMakePurchase,
    BuyMenuReturnToItemList
};

static const struct MenuAction sShopMenuActions_BuySellQuit[] =
{
    { gText_ShopBuy, {.void_u8=Task_HandleShopMenuBuy} },
    { gText_ShopSell, {.void_u8=Task_HandleShopMenuSell} },
    { gText_ShopQuit, {.void_u8=Task_HandleShopMenuQuit} }
};

static const struct MenuAction sShopMenuActions_BuyQuit[] =
{
    { gText_ShopBuy, {.void_u8=Task_HandleShopMenuBuy} },
    { gText_ShopQuit, {.void_u8=Task_HandleShopMenuQuit} }
};

static const struct WindowTemplate sShopMenuWindowTemplates[] =
{
    [WIN_BUY_SELL_QUIT] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 9,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x0008,
    },
    // Separate shop menu window for decorations, which can't be sold
    [WIN_BUY_QUIT] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 9,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x0008,
    }
};

static const struct ListMenuTemplate sShopBuyMenuListTemplate =
{
    .items = NULL,
    .moveCursorFunc = BuyMenuPrintItemDescriptionAndShowItemIcon,
    .itemPrintFunc = BuyMenuPrintPriceInList,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = WIN_ITEM_LIST,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_NARROW,
    .cursorKind = CURSOR_BLACK_ARROW
};

static const struct BgTemplate sShopBuyMenuBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    }
};

static const struct WindowTemplate sShopBuyMenuWindowTemplates[] =
{
    [WIN_MONEY] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x001E,
    },
    [WIN_BERRIES] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 10,
        .height = 3,
        .paletteNum = 15,
        .baseBlock = 0x001E,
    },
    [WIN_ITEM_LIST] = {
        .bg = 0,
        .tilemapLeft = 14,
        .tilemapTop = 2,
        .width = 15,
        .height = 16,
        .paletteNum = 15,
        .baseBlock = 0x003C,  // Adjusted: was 0x0032, +10 blocks for WIN_BERRIES
    },
    [WIN_ITEM_DESCRIPTION] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 13,
        .width = 14,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x012C,  // Adjusted: was 0x0122, +10 blocks
    },
    [WIN_QUANTITY_IN_BAG] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 11,
        .width = 12,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x0180,  // Adjusted: was 0x0176, +10 blocks
    },
    [WIN_QUANTITY_PRICE] = {
        .bg = 0,
        .tilemapLeft = 18,
        .tilemapTop = 11,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x0198,  // Adjusted: was 0x018E, +10 blocks
    },
    [WIN_MESSAGE] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x01AC,  // Adjusted: was 0x01A2, +10 blocks
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sShopBuyMenuYesNoWindowTemplates =
{
    .bg = 0,
    .tilemapLeft = 21,
    .tilemapTop = 9,
    .width = 5,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 0x0218,  // Adjusted: was 0x020E, +10 blocks
};

static const u8 sShopBuyMenuTextColors[][3] =
{
    [COLORID_NORMAL]      = {1, 2, 3},
    [COLORID_ITEM_LIST]   = {0, 2, 3},
    [COLORID_GRAY_CURSOR] = {0, 3, 2},
};

static u8 CreateShopMenu(u8 martType)
{
    int numMenuItems;

    LockPlayerFieldControls();
    sMartInfo.martType = martType;

    if (martType == MART_TYPE_NORMAL)
    {
        struct WindowTemplate winTemplate = sShopMenuWindowTemplates[WIN_BUY_SELL_QUIT];
        winTemplate.width = GetMaxWidthInMenuTable(sShopMenuActions_BuySellQuit, ARRAY_COUNT(sShopMenuActions_BuySellQuit));
        sMartInfo.windowId = AddWindow(&winTemplate);
        sMartInfo.menuActions = sShopMenuActions_BuySellQuit;
        numMenuItems = ARRAY_COUNT(sShopMenuActions_BuySellQuit);
    }
    else
    {
        struct WindowTemplate winTemplate = sShopMenuWindowTemplates[WIN_BUY_QUIT];
        winTemplate.width = GetMaxWidthInMenuTable(sShopMenuActions_BuyQuit, ARRAY_COUNT(sShopMenuActions_BuyQuit));
        sMartInfo.windowId = AddWindow(&winTemplate);
        sMartInfo.menuActions = sShopMenuActions_BuyQuit;
        numMenuItems = ARRAY_COUNT(sShopMenuActions_BuyQuit);
    }

    SetStandardWindowBorderStyle(sMartInfo.windowId, FALSE);
    PrintMenuTable(sMartInfo.windowId, numMenuItems, sMartInfo.menuActions);
    InitMenuInUpperLeftCornerNormal(sMartInfo.windowId, numMenuItems, 0);
    PutWindowTilemap(sMartInfo.windowId);
    CopyWindowToVram(sMartInfo.windowId, COPYWIN_MAP);

    return CreateTask(Task_ShopMenu, 8);
}

static void SetShopMenuCallback(void (* callback)(void))
{
    sMartInfo.callback = callback;
}

static u8 GetNumberOfBadges(void)
{
    u16 badgeFlag;
    u8 count = 0;
    
    for (badgeFlag = FLAG_BADGE01_GET; badgeFlag < FLAG_BADGE01_GET + NUM_BADGES; badgeFlag++)
    {
        if (FlagGet(badgeFlag))
            count++;
    }
    
    return count;
}

static void SetShopItemsForSale(const u16 *items)
{
    u16 i = 0;
    u8 badgeCount = GetNumberOfBadges();

    if ((items == NULL) && (!gSaveBlock1Ptr->tx_Challenges_PkmnCenter))
        sMartInfo.itemList = sShopInventories[badgeCount];
    else if ((items == NULL) && (gSaveBlock1Ptr->tx_Challenges_PkmnCenter))
        sMartInfo.itemList = sShopInventories_PC[badgeCount];
    else
        sMartInfo.itemList = items;

    sMartInfo.itemCount = 0;
    while (sMartInfo.itemList[i])
    {
        sMartInfo.itemCount++;
        i++;
    }
}

static void Task_ShopMenu(u8 taskId)
{
    s8 inputCode = Menu_ProcessInputNoWrap();
    switch (inputCode)
    {
    case MENU_NOTHING_CHOSEN:
        break;
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        Task_HandleShopMenuQuit(taskId);
        break;
    default:
        sMartInfo.menuActions[inputCode].func.void_u8(taskId);
        break;
    }
}

#define tItemCount  data[1]
#define tItemId     data[5]
#define tListTaskId data[7]
#define tCallbackHi data[8]
#define tCallbackLo data[9]

static void Task_HandleShopMenuBuy(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    tCallbackHi = (u32)CB2_InitBuyMenu >> 16;
    tCallbackLo = (u32)CB2_InitBuyMenu;
    gTasks[taskId].func = Task_GoToBuyOrSellMenu;
    FadeScreen(FADE_TO_BLACK, 0);
}

static void Task_HandleShopMenuSell(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    tCallbackHi = (u32)CB2_GoToSellMenu >> 16;
    tCallbackLo = (u32)CB2_GoToSellMenu;
    gTasks[taskId].func = Task_GoToBuyOrSellMenu;
    FadeScreen(FADE_TO_BLACK, 0);
}

void CB2_ExitSellMenu(void)
{
    gFieldCallback = MapPostLoadHook_ReturnToShopMenu;
    SetMainCallback2(CB2_ReturnToField);
}

static void Task_HandleShopMenuQuit(u8 taskId)
{
    ClearStdWindowAndFrameToTransparent(sMartInfo.windowId, 2); // Incorrect use, making it not copy it to vram.
    RemoveWindow(sMartInfo.windowId);
    TryPutSmartShopperOnAir();
    UnlockPlayerFieldControls();
    DestroyTask(taskId);

    if (sMartInfo.callback)
        sMartInfo.callback();
}

static void Task_GoToBuyOrSellMenu(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        SetMainCallback2((void *)((u16)tCallbackHi << 16 | (u16)tCallbackLo));
    }
}

static void MapPostLoadHook_ReturnToShopMenu(void)
{
    FadeInFromBlack();
    CreateTask(Task_ReturnToShopMenu, 8);
}

static void Task_ReturnToShopMenu(u8 taskId)
{
    if (IsWeatherNotFadingIn() == TRUE)
    {
        if (sMartInfo.martType == MART_TYPE_DECOR2)
            DisplayItemMessageOnField(taskId, gText_CanIHelpWithAnythingElse, ShowShopMenuAfterExitingBuyOrSellMenu);
        else
            DisplayItemMessageOnField(taskId, gText_AnythingElseICanHelp, ShowShopMenuAfterExitingBuyOrSellMenu);
    }
}

static void ShowShopMenuAfterExitingBuyOrSellMenu(u8 taskId)
{
    CreateShopMenu(sMartInfo.martType);
    DestroyTask(taskId);
}

static void CB2_BuyMenu(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_BuyMenu(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_InitBuyMenu(void)
{
    u8 taskId;

    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        CpuFastFill(0, (void *)OAM, OAM_SIZE);
        ScanlineEffect_Stop();
        ResetTempTileDataBuffers();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        ClearScheduledBgCopiesToVram();
        sShopData = AllocZeroed(sizeof(struct ShopData));
        sShopData->scrollIndicatorsTaskId = TASK_NONE;
        sShopData->itemSpriteIds[0] = SPRITE_NONE;
        sShopData->itemSpriteIds[1] = SPRITE_NONE;
        sBerryIconSpriteId = SPRITE_NONE;
        sQuantityBerryIconSpriteId = SPRITE_NONE;
        BuyMenuBuildListMenuTemplate();
        BuyMenuInitBgs();
        FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 0x20, 0x20);
        FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 0x20, 0x20);
        FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 0x20, 0x20);
        FillBgTilemapBufferRect_Palette0(3, 0, 0, 0, 0x20, 0x20);
        BuyMenuInitWindows();
        BuyMenuDecompressBgGraphics();
        gMain.state++;
        break;
    case 1:
        if (!FreeTempTileDataBuffersIfPossible())
            gMain.state++;
        break;
    default:
        BuyMenuDrawGraphics();
        BuyMenuAddScrollIndicatorArrows();
        taskId = CreateTask(Task_BuyMenu, 8);
        gTasks[taskId].tListTaskId = ListMenuInit(&gMultiuseListMenuTemplate, 0, 0);
        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB_BuyMenu);
        SetMainCallback2(CB2_BuyMenu);
        break;
    }
}

static void BuyMenuFreeMemory(void)
{
    RemoveBerryIcon();
    RemoveQuantityBerryIcon();
    Free(sShopData);
    Free(sListMenuItems);
    Free(sItemNames);
    FreeAllWindowBuffers();
}

static void BuyMenuBuildListMenuTemplate(void)
{
    u16 i;

    sListMenuItems = Alloc((sMartInfo.itemCount + 1) * sizeof(*sListMenuItems));
    sItemNames = Alloc((sMartInfo.itemCount + 1) * sizeof(*sItemNames));
    for (i = 0; i < sMartInfo.itemCount; i++)
        BuyMenuSetListEntry(&sListMenuItems[i], sMartInfo.itemList[i], sItemNames[i]);

    StringCopy(sItemNames[i], gText_Cancel2);
    sListMenuItems[i].name = sItemNames[i];
    sListMenuItems[i].id = LIST_CANCEL;

    gMultiuseListMenuTemplate = sShopBuyMenuListTemplate;
    gMultiuseListMenuTemplate.items = sListMenuItems;
    gMultiuseListMenuTemplate.totalItems = sMartInfo.itemCount + 1;
    if (gMultiuseListMenuTemplate.totalItems > MAX_ITEMS_SHOWN)
        gMultiuseListMenuTemplate.maxShowed = MAX_ITEMS_SHOWN;
    else
        gMultiuseListMenuTemplate.maxShowed = gMultiuseListMenuTemplate.totalItems;

    sShopData->itemsShowed = gMultiuseListMenuTemplate.maxShowed;
}

static void BuyMenuSetListEntry(struct ListMenuItem *menuItem, u16 item, u8 *name)
{
    if (sMartInfo.martType == MART_TYPE_NORMAL
        || sMartInfo.martType == MART_TYPE_KURT
        || sMartInfo.martType == MART_TYPE_BP
        || sMartInfo.martType == MART_TYPE_BP_ITEM)
        CopyItemName(item, name);
    else  // DECOR, DECOR2, BP_DECOR
        StringCopy(name, gDecorations[item].name);

    menuItem->name = name;
    menuItem->id = item;
}

static void BuyMenuPrintItemDescriptionAndShowItemIcon(s32 item, bool8 onInit, struct ListMenu *list)
{
    const u8 *description;
    if (onInit != TRUE)
        PlaySE(SE_SELECT);

    if (item != LIST_CANCEL)
        BuyMenuAddItemIcon(item, sShopData->iconSlot);
    else
        BuyMenuAddItemIcon(ITEM_LIST_END, sShopData->iconSlot);

    BuyMenuRemoveItemIcon(item, sShopData->iconSlot ^ 1);
    sShopData->iconSlot ^= 1;
    if (item != LIST_CANCEL)
    {
        if (sMartInfo.martType == MART_TYPE_NORMAL
            || sMartInfo.martType == MART_TYPE_BP
            || sMartInfo.martType == MART_TYPE_BP_ITEM)
            description = ItemId_GetDescription(item);
        else if (sMartInfo.martType == MART_TYPE_KURT)
        {
            description = ItemId_GetDescription(item);
            // Update berry count for Kurt shop
            sKurtCurrentBerry = GetBerryFromBall(item);
            PrintBerryCount(WIN_BERRIES, sKurtCurrentBerry);
            CopyWindowToVram(WIN_BERRIES, COPYWIN_FULL);
        }
        else
            description = gDecorations[item].description;
    }
    else
    {
        description = gText_QuitShopping;
        
        // For Kurt shop, update berry display to show exit
        if (sMartInfo.martType == MART_TYPE_KURT)
        {
            FillWindowPixelBuffer(WIN_BERRIES, PIXEL_FILL(1));
            AddBerryIcon(ITEM_LIST_END);
            AddTextPrinterParameterized(WIN_BERRIES, FONT_NORMAL, gText_ExitMenu, 28, 5, 0, NULL);
            CopyWindowToVram(WIN_BERRIES, COPYWIN_FULL);
        }
    }

    FillWindowPixelBuffer(WIN_ITEM_DESCRIPTION, PIXEL_FILL(0));
    BuyMenuPrint(WIN_ITEM_DESCRIPTION, description, 3, 1, 0, COLORID_NORMAL);
}

static void BuyMenuPrintPriceInList(u8 windowId, u32 itemId, u8 y)
{
    u8 x;

    if (itemId != LIST_CANCEL)
    {
        if (sMartInfo.martType == MART_TYPE_BP
            || sMartInfo.martType == MART_TYPE_BP_ITEM
            || sMartInfo.martType == MART_TYPE_BP_DECOR)
        {
            // Show "##BP" right-aligned in the list
            u8 *ptr = ConvertIntToDecimalStringN(gStringVar4, GetBPCostForItem((u16)itemId), STR_CONV_MODE_LEFT_ALIGN, 4);
            StringCopy(ptr, gText_BP);
            x = GetStringRightAlignXOffset(FONT_NARROW, gStringVar4, 120);
            AddTextPrinterParameterized4(windowId, FONT_NARROW, x, y, 0, 0, sShopBuyMenuTextColors[COLORID_ITEM_LIST], TEXT_SKIP_DRAW, gStringVar4);
            return;
        }
        else if (sMartInfo.martType == MART_TYPE_KURT)
        {
            // For Kurt shop, show "1 BerryName" instead of price (removing " Berry" suffix)
            u16 berryId = ITEM_NONE;
            u32 i;
            
            berryId = GetBerryFromBall(itemId);
            
            if (berryId != ITEM_NONE)
            {
                CopyItemName(berryId, gStringVar4);
                // Remove last 6 characters (" Berry")
                gStringVar4[StringLength(gStringVar4) - 6] = EOS;
                StringAppend(gStringVar4, gText_Space);
                StringAppend(gStringVar4, gText_xOne);
                x = GetStringRightAlignXOffset(FONT_NARROW, gStringVar4, 120);
                AddTextPrinterParameterized4(windowId, FONT_NARROW, x, y, 0, 0, sShopBuyMenuTextColors[COLORID_ITEM_LIST], TEXT_SKIP_DRAW, gStringVar4);
            }
            return;
        }
        else if (sMartInfo.martType == MART_TYPE_NORMAL)
        {
            ConvertIntToDecimalStringN(
                gStringVar1,
                ItemId_GetPrice(itemId) >> IsPokeNewsActive(POKENEWS_SLATEPORT),
                STR_CONV_MODE_LEFT_ALIGN,
                5);
        }
        else
        {
            ConvertIntToDecimalStringN(
                gStringVar1,
                gDecorations[itemId].price,
                STR_CONV_MODE_LEFT_ALIGN,
                5);
        }

        if (FlagGet(FLAG_FINITE_TMS) == TRUE)
            StringExpandPlaceholders(gStringVar4, gText_PokedollarVar1);
        else if (ItemId_GetPocket(itemId) == POCKET_TM_HM && (CheckBagHasItem(itemId, 1) || CheckPCHasItem(itemId, 1)) && (FlagGet(FLAG_FINITE_TMS) == FALSE))
            StringCopy(gStringVar4, gText_SoldOut2);
        else
            StringExpandPlaceholders(gStringVar4, gText_PokedollarVar1);
        x = GetStringRightAlignXOffset(FONT_NARROW, gStringVar4, 120);
        AddTextPrinterParameterized4(windowId, FONT_NARROW, x, y, 0, 0, sShopBuyMenuTextColors[COLORID_ITEM_LIST], TEXT_SKIP_DRAW, gStringVar4);
    }
}

static void BuyMenuAddScrollIndicatorArrows(void)
{
    if (sShopData->scrollIndicatorsTaskId == TASK_NONE && sMartInfo.itemCount + 1 > MAX_ITEMS_SHOWN)
    {
        sShopData->scrollIndicatorsTaskId = AddScrollIndicatorArrowPairParameterized(
            SCROLL_ARROW_UP,
            172,
            12,
            148,
            sMartInfo.itemCount - (MAX_ITEMS_SHOWN - 1),
            TAG_SCROLL_ARROW,
            TAG_SCROLL_ARROW,
            &sShopData->scrollOffset);
    }
}

static void BuyMenuRemoveScrollIndicatorArrows(void)
{
    if (sShopData->scrollIndicatorsTaskId != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(sShopData->scrollIndicatorsTaskId);
        sShopData->scrollIndicatorsTaskId = TASK_NONE;
    }
}

static void BuyMenuPrintCursor(u8 scrollIndicatorsTaskId, u8 colorSet)
{
    u8 y = ListMenuGetYCoordForPrintingArrowCursor(scrollIndicatorsTaskId);
    BuyMenuPrint(WIN_ITEM_LIST, gText_SelectorArrow2, 0, y, 0, colorSet);
}

static void BuyMenuAddItemIcon(u16 item, u8 iconSlot)
{
    u8 spriteId;
    u8 *spriteIdPtr = &sShopData->itemSpriteIds[iconSlot];
    if (*spriteIdPtr != SPRITE_NONE)
        return;

    if (sMartInfo.martType == MART_TYPE_NORMAL
        || sMartInfo.martType == MART_TYPE_KURT
        || sMartInfo.martType == MART_TYPE_BP
        || sMartInfo.martType == MART_TYPE_BP_ITEM
        || item == ITEM_LIST_END)
    {
        spriteId = AddItemIconSprite(iconSlot + TAG_ITEM_ICON_BASE, iconSlot + TAG_ITEM_ICON_BASE, item);
        if (spriteId != MAX_SPRITES)
        {
            *spriteIdPtr = spriteId;
            gSprites[spriteId].x2 = 24;
            gSprites[spriteId].y2 = 88;
        }
    }
    else
    {
        spriteId = AddDecorationIconObject(item, 20, 84, 1, iconSlot + TAG_ITEM_ICON_BASE, iconSlot + TAG_ITEM_ICON_BASE);
        if (spriteId != MAX_SPRITES)
            *spriteIdPtr = spriteId;
    }
}

static void BuyMenuRemoveItemIcon(u16 item, u8 iconSlot)
{
    u8 *spriteIdPtr = &sShopData->itemSpriteIds[iconSlot];
    if (*spriteIdPtr == SPRITE_NONE)
        return;

    FreeSpriteTilesByTag(iconSlot + TAG_ITEM_ICON_BASE);
    FreeSpritePaletteByTag(iconSlot + TAG_ITEM_ICON_BASE);
    DestroySprite(&gSprites[*spriteIdPtr]);
    *spriteIdPtr = SPRITE_NONE;
}

static void BuyMenuInitBgs(void)
{
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sShopBuyMenuBgTemplates, ARRAY_COUNT(sShopBuyMenuBgTemplates));
    SetBgTilemapBuffer(1, sShopData->tilemapBuffers[1]);
    SetBgTilemapBuffer(2, sShopData->tilemapBuffers[3]);
    SetBgTilemapBuffer(3, sShopData->tilemapBuffers[2]);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    ShowBg(3);
}

static void BuyMenuDecompressBgGraphics(void)
{
    int i;
    u16 *map;

    // Decompress graphics
    DecompressAndCopyTileDataToVram(1, gShopMenu_Gfx, 0x3A0, 0x3E3, 0);

    // Decompress tilemap to WRAM
    LZDecompressWram(gShopMenu_Tilemap, sShopData->tilemapBuffers[0]);

    // Patch palette index in each entry (change 12 → 6)
    map = (u16 *)sShopData->tilemapBuffers[0];
    // size = width * height of the tilemap. Shop menu is 32x32 tiles → 1024 entries.
    for (i = 0; i < 32 * 32; i++)
        map[i] = (map[i] & 0x0FFF) | (10 << 12);

    // Load palette into slot 6
    LoadCompressedPalette(gShopMenu_Pal, BG_PLTT_ID(6), PLTT_SIZE_4BPP);
}

static void BuyMenuInitWindows(void)
{
    u8 moneyWindowId;
    
    InitWindows(sShopBuyMenuWindowTemplates);
    DeactivateAllTextPrinters();
    
    // Use WIN_BERRIES for Kurt shop (taller window), WIN_MONEY for others
    moneyWindowId = (sMartInfo.martType == MART_TYPE_KURT) ? WIN_BERRIES : WIN_MONEY;
    
    LoadUserWindowBorderGfx(moneyWindowId, 1, BG_PLTT_ID(13));
    LoadMessageBoxGfx(moneyWindowId, 0xA, BG_PLTT_ID(14));
    PutWindowTilemap(moneyWindowId);
    PutWindowTilemap(WIN_ITEM_LIST);
    PutWindowTilemap(WIN_ITEM_DESCRIPTION);
}

static void BuyMenuPrint(u8 windowId, const u8 *text, u8 x, u8 y, s8 speed, u8 colorSet)
{
    AddTextPrinterParameterized4(windowId, FONT_NORMAL, x, y, 0, 0, sShopBuyMenuTextColors[colorSet], speed, text);
}

static void BuyMenuDisplayMessage(u8 taskId, const u8 *text, TaskFunc callback)
{
    DisplayMessageAndContinueTask(taskId, WIN_MESSAGE, 10, 14, FONT_NORMAL, GetPlayerTextSpeedDelay(), text, callback);
    ScheduleBgCopyTilemapToVram(0);
}

static void BuyMenuDrawGraphics(void)
{
    BuyMenuDrawMapGraphics();
    BuyMenuCopyMenuBgToBg1TilemapBuffer();
    
    if (sMartInfo.martType == MART_TYPE_KURT)
    {
        // For Kurt shop, draw berry count window instead of money
        // Fill window buffer first to clear any garbage graphics
        // FillWindowPixelBuffer(WIN_BERRIES, PIXEL_FILL(1));
        DrawStdFrameWithCustomTileAndPalette(WIN_BERRIES, FALSE, 1, 13);
        // Initialize with first item's berry
        if (sMartInfo.itemCount > 0)
        {
            u16 firstBall = sMartInfo.itemList[0];
            sKurtCurrentBerry = GetBerryFromBall(firstBall);
            PrintBerryCount(WIN_BERRIES, sKurtCurrentBerry);
        }
        
    }
    else if (sMartInfo.martType == MART_TYPE_BP
             || sMartInfo.martType == MART_TYPE_BP_ITEM
             || sMartInfo.martType == MART_TYPE_BP_DECOR)
    {
        // For BP shops: draw WIN_MONEY border, show current BP, and add BP label sprite
        DrawStdFrameWithCustomTileAndPalette(WIN_MONEY, FALSE, 1, 13);
        PrintBPAmountInMoneyBox(WIN_MONEY, gSaveBlock2Ptr->frontier.battlePoints, 0);
        AddBPLabelObject(19, 11);
    }
    else
    {
        AddMoneyLabelObject(19, 11);
        PrintMoneyAmountInMoneyBoxWithBorder(WIN_MONEY, 1, 13, GetMoney(&gSaveBlock1Ptr->money));
    }
    
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);
    ScheduleBgCopyTilemapToVram(2);
    ScheduleBgCopyTilemapToVram(3);
}

static void BuyMenuDrawMapGraphics(void)
{
    BuyMenuCollectObjectEventData();
    BuyMenuDrawObjectEvents();
    BuyMenuDrawMapBg();
}

static void BuyMenuDrawMapBg(void)
{
    s16 i, j;
    s16 x, y;
    const struct MapLayout *mapLayout;
    u16 metatile;
    u8 metatileLayerType;

    mapLayout = gMapHeader.mapLayout;
    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    x -= 4;
    y -= 4;

    for (j = 0; j < 10; j++)
    {
        for (i = 0; i < 15; i++)
        {
            metatile = MapGridGetMetatileIdAt(x + i, y + j);
            if (BuyMenuCheckForOverlapWithMenuBg(i, j) == TRUE)
                metatileLayerType = MapGridGetMetatileLayerTypeAt(x + i, y + j);
            else
                metatileLayerType = METATILE_LAYER_TYPE_COVERED;

            if (metatile < NUM_METATILES_IN_PRIMARY)
                BuyMenuDrawMapMetatile(i, j, mapLayout->primaryTileset->metatiles + metatile * NUM_TILES_PER_METATILE, metatileLayerType);
            else
                BuyMenuDrawMapMetatile(i, j, mapLayout->secondaryTileset->metatiles + ((metatile - NUM_METATILES_IN_PRIMARY) * NUM_TILES_PER_METATILE), metatileLayerType);
        }
    }
}

static void BuyMenuDrawMapMetatile(s16 x, s16 y, const u16 *src, u8 metatileLayerType)
{
    u16 offset1 = x * 2;
    u16 offset2 = y * 64;

    switch (metatileLayerType)
    {
    case METATILE_LAYER_TYPE_NORMAL:
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[3], offset1, offset2, src);
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[1], offset1, offset2, src + 4);
        break;
    case METATILE_LAYER_TYPE_COVERED:
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[2], offset1, offset2, src);
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[3], offset1, offset2, src + 4);
        break;
    case METATILE_LAYER_TYPE_SPLIT:
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[2], offset1, offset2, src);
        BuyMenuDrawMapMetatileLayer(sShopData->tilemapBuffers[1], offset1, offset2, src + 4);
        break;
    }
}

static void BuyMenuDrawMapMetatileLayer(u16 *dest, s16 offset1, s16 offset2, const u16 *src)
{
    // This function draws a whole 2x2 metatile.
    dest[offset1 + offset2] = src[0]; // top left
    dest[offset1 + offset2 + 1] = src[1]; // top right
    dest[offset1 + offset2 + 32] = src[2]; // bottom left
    dest[offset1 + offset2 + 33] = src[3]; // bottom right
}

static void BuyMenuCollectObjectEventData(void)
{
    s16 facingX;
    s16 facingY;
    u8 y;
    u8 x;
    u8 numObjects = 0;

    GetXYCoordsOneStepInFrontOfPlayer(&facingX, &facingY);

    for (y = 0; y < OBJECT_EVENTS_COUNT; y++)
        sShopData->viewportObjects[y][OBJ_EVENT_ID] = OBJECT_EVENTS_COUNT;

    for (y = 0; y < 5; y++)
    {
        for (x = 0; x < 7; x++)
        {
            u8 objEventId = GetObjectEventIdByXY(facingX - 4 + x, facingY - 2 + y);

            // skip if invalid or an overworld pokemon that is not following the player
            if (objEventId != OBJECT_EVENTS_COUNT && !(gObjectEvents[objEventId].active && gObjectEvents[objEventId].graphicsId >= OBJ_EVENT_GFX_MON_BASE && gObjectEvents[objEventId].localId != OBJ_EVENT_ID_FOLLOWER))
            {
                sShopData->viewportObjects[numObjects][OBJ_EVENT_ID] = objEventId;
                sShopData->viewportObjects[numObjects][X_COORD] = x;
                sShopData->viewportObjects[numObjects][Y_COORD] = y;
                sShopData->viewportObjects[numObjects][LAYER_TYPE] = MapGridGetMetatileLayerTypeAt(facingX - 4 + x, facingY - 2 + y);

                switch (gObjectEvents[objEventId].facingDirection)
                {
                case DIR_SOUTH:
                    sShopData->viewportObjects[numObjects][ANIM_NUM] = ANIM_STD_FACE_SOUTH;
                    break;
                case DIR_NORTH:
                    sShopData->viewportObjects[numObjects][ANIM_NUM] = ANIM_STD_FACE_NORTH;
                    break;
                case DIR_WEST:
                    sShopData->viewportObjects[numObjects][ANIM_NUM] = ANIM_STD_FACE_WEST;
                    break;
                case DIR_EAST:
                default:
                    sShopData->viewportObjects[numObjects][ANIM_NUM] = ANIM_STD_FACE_EAST;
                    break;
                }
                numObjects++;
            }
        }
    }
}

static void BuyMenuDrawObjectEvents(void)
{
    u8 i;
    u8 spriteId;
    const struct ObjectEventGraphicsInfo *graphicsInfo;
    u8 weatherTemp = gWeatherPtr->palProcessingState;

    // This function runs during fadeout, so the weather palette processing state must be temporarily changed,
    // so that time-blending will work properly
    if (weatherTemp == WEATHER_PAL_STATE_SCREEN_FADING_OUT)
        gWeatherPtr->palProcessingState = WEATHER_PAL_STATE_IDLE;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (sShopData->viewportObjects[i][OBJ_EVENT_ID] == OBJECT_EVENTS_COUNT)
            continue;

        graphicsInfo = GetObjectEventGraphicsInfo(gObjectEvents[sShopData->viewportObjects[i][OBJ_EVENT_ID]].graphicsId);

        spriteId = CreateObjectGraphicsSprite(
            gObjectEvents[sShopData->viewportObjects[i][OBJ_EVENT_ID]].graphicsId,
            SpriteCallbackDummy,
            (u16)sShopData->viewportObjects[i][X_COORD] * 16 + 8,
            (u16)sShopData->viewportObjects[i][Y_COORD] * 16 + 48 - graphicsInfo->height / 2,
            2);

        if (BuyMenuCheckIfObjectEventOverlapsMenuBg(sShopData->viewportObjects[i]) == TRUE)
        {
            gSprites[spriteId].subspriteTableNum = 4;
            gSprites[spriteId].subspriteMode = SUBSPRITES_ON;
        }

        StartSpriteAnim(&gSprites[spriteId], sShopData->viewportObjects[i][ANIM_NUM]);
    }

    gWeatherPtr->palProcessingState = weatherTemp; // restore weather state
    CpuFastCopy(gPlttBufferFaded + 16*16, gPlttBufferUnfaded + 16*16, PLTT_BUFFER_SIZE);
}

static bool8 BuyMenuCheckIfObjectEventOverlapsMenuBg(s16 *object)
{
    if (!BuyMenuCheckForOverlapWithMenuBg(object[X_COORD], object[Y_COORD] + 2) && object[LAYER_TYPE] != METATILE_LAYER_TYPE_COVERED)
        return TRUE;
    else
        return FALSE;
}

static void BuyMenuCopyMenuBgToBg1TilemapBuffer(void)
{
    s16 i;
    u16 *dest = sShopData->tilemapBuffers[1];
    const u16 *src = sShopData->tilemapBuffers[0];

    for (i = 0; i < 1024; i++)
    {
        if (src[i] != 0)
            dest[i] = src[i] + 0xC3E3;
    }
}

static bool8 BuyMenuCheckForOverlapWithMenuBg(int x, int y)
{
    const u16 *metatile = sShopData->tilemapBuffers[0];
    int offset1 = x * 2;
    int offset2 = y * 64;

    if (metatile[offset2 + offset1] == 0 &&
        metatile[offset2 + offset1 + 32] == 0 &&
        metatile[offset2 + offset1 + 1] == 0 &&
        metatile[offset2 + offset1 + 33] == 0)
        return TRUE;

    return FALSE;
}

static void Task_BuyMenu(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        s32 itemId = ListMenu_ProcessInput(tListTaskId);
        ListMenuGetScrollAndRow(tListTaskId, &sShopData->scrollOffset, &sShopData->selectedRow);

        switch (itemId)
        {
        case LIST_NOTHING_CHOSEN:
            break;
        case LIST_CANCEL:
            PlaySE(SE_SELECT);
            // Set VAR_RESULT to indicate no purchase was made
            if (sMartInfo.martType == MART_TYPE_KURT)
                gSpecialVar_Result = FALSE;
            ExitBuyMenu(taskId);
            break;
        default:
            PlaySE(SE_SELECT);
            tItemId = itemId;
            ClearWindowTilemap(WIN_ITEM_DESCRIPTION);
            BuyMenuRemoveScrollIndicatorArrows();
            BuyMenuPrintCursor(tListTaskId, COLORID_GRAY_CURSOR);

            if (sMartInfo.martType == MART_TYPE_NORMAL)
                sShopData->totalCost = (ItemId_GetPrice(itemId) >> IsPokeNewsActive(POKENEWS_SLATEPORT));
            else if (sMartInfo.martType == MART_TYPE_KURT)
                sShopData->totalCost = 1; // 1 berry per ball
            else if (sMartInfo.martType == MART_TYPE_BP
                     || sMartInfo.martType == MART_TYPE_BP_ITEM
                     || sMartInfo.martType == MART_TYPE_BP_DECOR)
                sShopData->totalCost = GetBPCostForItem(itemId); // BP cost per item
            else
                sShopData->totalCost = gDecorations[itemId].price;

            if (sMartInfo.martType == MART_TYPE_KURT)
            {
                // For Kurt shop, check berry availability
                u16 berryItem = GetBerryFromBall(itemId);
                u16 berryCount = GetItemQuantityInBag(berryItem);
                
                if (berryCount < 1)
                {
                    // Not enough berries
                    CopyItemName(berryItem, gStringVar1);
                    BuyMenuDisplayMessage(taskId, gText_DontHaveEnoughVar1, BuyMenuReturnToItemList);
                }
                else
                {
                    // Proceed to quantity selection
                    CopyItemName(itemId, gStringVar1);
                    BuyMenuDisplayMessage(taskId, gText_Var1SureHowMany, Task_BuyHowManyDialogueInit);
                }
            }
            else if (sMartInfo.martType == MART_TYPE_BP)
            {
                // Multi-buy vitamin shop: check BP then go to quantity selection
                if (gSaveBlock2Ptr->frontier.battlePoints < sShopData->totalCost)
                {
                    BuyMenuDisplayMessage(taskId, gText_YouDontHaveEnoughBP, BuyMenuReturnToItemList);
                }
                else
                {
                    CopyItemName(itemId, gStringVar1);
                    BuyMenuDisplayMessage(taskId, gText_Var1CertainlyHowMany, Task_BuyHowManyDialogueInit);
                }
            }
            else if (sMartInfo.martType == MART_TYPE_BP_ITEM)
            {
                // Single-buy held item shop: check BP then confirm directly
                if (gSaveBlock2Ptr->frontier.battlePoints < sShopData->totalCost)
                {
                    BuyMenuDisplayMessage(taskId, gText_YouDontHaveEnoughBP, BuyMenuReturnToItemList);
                }
                else
                {
                    u8 *ptr;
                    tItemCount = 1;
                    CopyItemName(itemId, gStringVar1);
                    ptr = ConvertIntToDecimalStringN(gStringVar2, sShopData->totalCost, STR_CONV_MODE_LEFT_ALIGN, 4);
                    StringExpandPlaceholders(gStringVar4, gText_YouWantedVar1ThatllBeVar2BP);
                    BuyMenuDisplayMessage(taskId, gStringVar4, BuyMenuConfirmPurchase);
                }
            }
            else if (sMartInfo.martType == MART_TYPE_BP_DECOR)
            {
                // Single-buy decoration shop: check BP then confirm directly
                if (gSaveBlock2Ptr->frontier.battlePoints < sShopData->totalCost)
                {
                    BuyMenuDisplayMessage(taskId, gText_YouDontHaveEnoughBP, BuyMenuReturnToItemList);
                }
                else
                {
                    u8 *ptr;
                    tItemCount = 1;
                    StringCopy(gStringVar1, gDecorations[itemId].name);
                    ptr = ConvertIntToDecimalStringN(gStringVar2, sShopData->totalCost, STR_CONV_MODE_LEFT_ALIGN, 4);
                    StringExpandPlaceholders(gStringVar4, gText_YouWantedVar1ThatllBeVar2BP);
                    BuyMenuDisplayMessage(taskId, gStringVar4, BuyMenuConfirmPurchase);
                }
            }
            else if (!IsEnoughMoney(&gSaveBlock1Ptr->money, sShopData->totalCost))
            {
                BuyMenuDisplayMessage(taskId, gText_YouDontHaveMoney, BuyMenuReturnToItemList);
            }
            else if (ItemId_GetPocket(itemId) == POCKET_TM_HM && (CheckBagHasItem(itemId, 1) || CheckPCHasItem(itemId, 1)) && (FlagGet(FLAG_FINITE_TMS) == FALSE))
            {
                BuyMenuDisplayMessage(taskId, gText_YouAlreadyHaveThis, BuyMenuReturnToItemList);
            }
            else
            {
                if (sMartInfo.martType == MART_TYPE_NORMAL)
                {
                    CopyItemName(itemId, gStringVar1);
                    if (ItemId_GetPocket(itemId) == POCKET_TM_HM)
                    {
                        if (FlagGet(FLAG_FINITE_TMS) == TRUE)
                        { 
                            StringCopy(gStringVar2, gMoveNames[ItemIdToBattleMoveId(itemId)]);
                            BuyMenuDisplayMessage(taskId, gText_Var1CertainlyHowMany2, Task_BuyHowManyDialogueInit);
                        }
                        else
                        {
                            ConvertIntToDecimalStringN(gStringVar2, sShopData->totalCost, STR_CONV_MODE_LEFT_ALIGN, 6);
                            StringExpandPlaceholders(gStringVar4, gText_YouWantedVar1ThatllBeVar2);
                            tItemCount = 1;
                            sShopData->totalCost = (ItemId_GetPrice(tItemId) >> IsPokeNewsActive(POKENEWS_SLATEPORT)) * tItemCount;
                            BuyMenuDisplayMessage(taskId, gStringVar4, BuyMenuConfirmPurchase);
                        }
                    }
                    else
                    {
                        BuyMenuDisplayMessage(taskId, gText_Var1CertainlyHowMany, Task_BuyHowManyDialogueInit);
                    }
                }
                else
                {
                    StringCopy(gStringVar1, gDecorations[itemId].name);
                    ConvertIntToDecimalStringN(gStringVar2, sShopData->totalCost, STR_CONV_MODE_LEFT_ALIGN, 6);

                    if (sMartInfo.martType == MART_TYPE_DECOR)
                        StringExpandPlaceholders(gStringVar4, gText_Var1IsItThatllBeVar2);
                    else // MART_TYPE_DECOR2
                        StringExpandPlaceholders(gStringVar4, gText_YouWantedVar1ThatllBeVar2);

                    BuyMenuDisplayMessage(taskId, gStringVar4, BuyMenuConfirmPurchase);
                }
            }
            break;
        }
    }
}

static void Task_BuyHowManyDialogueInit(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    u16 quantityInBag = CountTotalItemQuantityInBag(tItemId);
    u16 maxQuantity;

    DrawStdFrameWithCustomTileAndPalette(WIN_QUANTITY_IN_BAG, FALSE, 1, 13);
    ConvertIntToDecimalStringN(gStringVar1, quantityInBag, STR_CONV_MODE_RIGHT_ALIGN, MAX_ITEM_DIGITS + 1);
    StringExpandPlaceholders(gStringVar4, gText_InBagVar1);
    BuyMenuPrint(WIN_QUANTITY_IN_BAG, gStringVar4, 0, 1, 0, COLORID_NORMAL);
    tItemCount = 1;
    DrawStdFrameWithCustomTileAndPalette(WIN_QUANTITY_PRICE, FALSE, 1, 13);
    BuyMenuPrintItemQuantityAndPrice(taskId);
    ScheduleBgCopyTilemapToVram(0);

    if (sMartInfo.martType == MART_TYPE_KURT)
    {
        // For Kurt shop, max quantity is berry_count
        u16 berryItem = GetBerryFromBall(tItemId);
        u16 berryCount = GetItemQuantityInBag(berryItem);
        maxQuantity = berryCount;
        
        if (maxQuantity > MAX_BAG_ITEM_CAPACITY)
            sShopData->maxQuantity = MAX_BAG_ITEM_CAPACITY;
        else
            sShopData->maxQuantity = maxQuantity;
    }
    else if (sMartInfo.martType == MART_TYPE_BP)
    {
        // For BP vitamin shop, max quantity is affordable with current BP
        maxQuantity = gSaveBlock2Ptr->frontier.battlePoints / sShopData->totalCost;
        if (maxQuantity > MAX_BAG_ITEM_CAPACITY)
            sShopData->maxQuantity = MAX_BAG_ITEM_CAPACITY;
        else
            sShopData->maxQuantity = maxQuantity;
    }
    else
    {
        maxQuantity = GetMoney(&gSaveBlock1Ptr->money) / sShopData->totalCost;

        if (maxQuantity > MAX_BAG_ITEM_CAPACITY)
            sShopData->maxQuantity = MAX_BAG_ITEM_CAPACITY;
        else
            sShopData->maxQuantity = maxQuantity;
    }

    gTasks[taskId].func = Task_BuyHowManyDialogueHandleInput;
}

static void Task_BuyHowManyDialogueHandleInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&tItemCount, sShopData->maxQuantity) == TRUE)
    {
        if (sMartInfo.martType == MART_TYPE_KURT)
        {
            // For Kurt shop, total cost is 1:1 ratio
            sShopData->totalCost = tItemCount;
        }
        else if (sMartInfo.martType == MART_TYPE_BP)
        {
            // For BP vitamin shop, re-derive total cost from per-item cost
            sShopData->totalCost = GetBPCostForItem(tItemId) * tItemCount;
        }
        else
        {
            sShopData->totalCost = (ItemId_GetPrice(tItemId) >> IsPokeNewsActive(POKENEWS_SLATEPORT)) * tItemCount;
        }
        BuyMenuPrintItemQuantityAndPrice(taskId);
    }
    else
    {
        if (JOY_NEW(A_BUTTON))
        {
            PlaySE(SE_SELECT);
            RemoveQuantityBerryIcon();
            ClearStdWindowAndFrameToTransparent(WIN_QUANTITY_PRICE, FALSE);
            ClearStdWindowAndFrameToTransparent(WIN_QUANTITY_IN_BAG, FALSE);
            ClearWindowTilemap(WIN_QUANTITY_PRICE);
            ClearWindowTilemap(WIN_QUANTITY_IN_BAG);
            PutWindowTilemap(WIN_ITEM_LIST);
            CopyItemName(tItemId, gStringVar1);
            ConvertIntToDecimalStringN(gStringVar2, tItemCount, STR_CONV_MODE_LEFT_ALIGN, BAG_ITEM_CAPACITY_DIGITS);
            ConvertIntToDecimalStringN(gStringVar3, sShopData->totalCost, STR_CONV_MODE_LEFT_ALIGN, 6);

            if (sMartInfo.martType == MART_TYPE_KURT)
            {
                u16 berryId = GetBerryFromBall(tItemId);
                CopyItemName(berryId, gStringVar4);
                // Remove " BERRY" suffix (last 6 characters)
                gStringVar4[StringLength(gStringVar4) - 6] = EOS;
                StringAppend(gStringVar3, gText_Space);
                StringAppend(gStringVar3, gStringVar4);
                
                if (tItemCount == 1)
                    BuyMenuDisplayMessage(taskId, gText_KurtVar1AndYouWantedVar2Singular, BuyMenuConfirmPurchase);
                else
                    BuyMenuDisplayMessage(taskId, gText_KurtVar1AndYouWantedVar2Plural, BuyMenuConfirmPurchase);
            }
            else if (sMartInfo.martType == MART_TYPE_BP)
            {
                BuyMenuDisplayMessage(taskId, gText_Var1AndYouWantedVar2BP, BuyMenuConfirmPurchase);
            }
            else
                BuyMenuDisplayMessage(taskId, gText_Var1AndYouWantedVar2, BuyMenuConfirmPurchase);
            
        }
        else if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_SELECT);
            RemoveQuantityBerryIcon();
            ClearStdWindowAndFrameToTransparent(WIN_QUANTITY_PRICE, FALSE);
            ClearStdWindowAndFrameToTransparent(WIN_QUANTITY_IN_BAG, FALSE);
            ClearWindowTilemap(WIN_QUANTITY_PRICE);
            ClearWindowTilemap(WIN_QUANTITY_IN_BAG);
            BuyMenuReturnToItemList(taskId);
        }
    }
}

static void BuyMenuConfirmPurchase(u8 taskId)
{
    CreateYesNoMenuWithCallbacks(taskId, &sShopBuyMenuYesNoWindowTemplates, 1, 0, 0, 1, 13, &sShopPurchaseYesNoFuncs);
}

static void BuyMenuTryMakePurchase(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    PutWindowTilemap(WIN_ITEM_LIST);

    if (sMartInfo.martType == MART_TYPE_KURT)
    {
        // For Kurt: check if there's space, but don't give items yet
        u16 totalBalls = tItemCount;
        if (CheckBagHasSpace(tItemId, totalBalls) == TRUE)
        {
            // Store item info in special vars for script to use later
            gSpecialVar_0x8004 = tItemId;
            gSpecialVar_0x8005 = totalBalls;
            BuyMenuDisplayMessage(taskId, gText_KurtGettingStarted, BuyMenuSubtractMoney);
            RecordItemPurchase(taskId);
        }
        else
        {
            BuyMenuDisplayMessage(taskId, gText_NoMoreRoomForThis, BuyMenuReturnToItemList);
        }
    }
    else if (sMartInfo.martType == MART_TYPE_NORMAL)
    {
        if (AddBagItem(tItemId, tItemCount) == TRUE)
        {
            if (FlagGet(FLAG_FINITE_TMS) == TRUE)
            {
                BuyMenuDisplayMessage(taskId, gText_HereYouGoThankYou, BuyMenuSubtractMoney);
                RecordItemPurchase(taskId);
            }
            else
            {
                RedrawListMenu(tListTaskId);
                RecordItemPurchase(taskId);
                BuyMenuDisplayMessage(taskId, gText_HereYouGoThankYou, BuyMenuSubtractMoney);
            }
        }
        else
        {
            BuyMenuDisplayMessage(taskId, gText_NoMoreRoomForThis, BuyMenuReturnToItemList);
        }
    }
    else if (sMartInfo.martType == MART_TYPE_BP || sMartInfo.martType == MART_TYPE_BP_ITEM)
    {
        // BP item shops: give item, then deduct BP
        if (AddBagItem(tItemId, tItemCount) == TRUE)
        {
            BuyMenuDisplayMessage(taskId, gText_HereYouGoThankYou, BuyMenuSubtractMoney);
        }
        else
        {
            BuyMenuDisplayMessage(taskId, gText_NoMoreRoomForThis, BuyMenuReturnToItemList);
        }
    }
    else if (sMartInfo.martType == MART_TYPE_BP_DECOR)
    {
        // BP decoration shop: send to PC, then deduct BP
        if (DecorationAdd(tItemId))
        {
            BuyMenuDisplayMessage(taskId, gText_ThankYouIllSendItHome, BuyMenuSubtractMoney);
        }
        else
        {
            BuyMenuDisplayMessage(taskId, gText_SpaceForVar1Full, BuyMenuReturnToItemList);
        }
    }
    else
    {
        if (DecorationAdd(tItemId))
        {
            if (sMartInfo.martType == MART_TYPE_DECOR)
                BuyMenuDisplayMessage(taskId, gText_ThankYouIllSendItHome, BuyMenuSubtractMoney);
            else // MART_TYPE_DECOR2
                BuyMenuDisplayMessage(taskId, gText_ThanksIllSendItHome, BuyMenuSubtractMoney);
        }
        else
        {
            BuyMenuDisplayMessage(taskId, gText_SpaceForVar1Full, BuyMenuReturnToItemList);
        }
    }
}

static void BuyMenuSubtractMoney(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    
    IncrementGameStat(GAME_STAT_SHOPPED);
    
    if (sMartInfo.martType == MART_TYPE_KURT)
    {   
        // For Kurt: remove berries and wait for button press before exiting
        u16 berryItem = GetBerryFromBall(tItemId);
        u16 totalBerries = tItemCount;
        RemoveBagItem(berryItem, totalBerries);
        PlaySE(SE_BANG);
        // Set VAR_RESULT to indicate purchase was made
        gSpecialVar_Result = TRUE;
        // Wait for button press before exiting
        gTasks[taskId].func = Task_ExitKurtShopAfterPurchase;
    }
    else if (sMartInfo.martType == MART_TYPE_BP
             || sMartInfo.martType == MART_TYPE_BP_ITEM
             || sMartInfo.martType == MART_TYPE_BP_DECOR)
    {
        // Deduct BP and refresh the BP window
        gSaveBlock2Ptr->frontier.battlePoints -= (u16)sShopData->totalCost;
        PlaySE(SE_SHOP);
        PrintBPAmountInMoneyBox(WIN_MONEY, gSaveBlock2Ptr->frontier.battlePoints, 0);

        if (sMartInfo.martType == MART_TYPE_BP_DECOR)
            gTasks[taskId].func = Task_ReturnToItemListAfterDecorationPurchase;
        else
            gTasks[taskId].func = Task_ReturnToItemListAfterItemPurchase;
    }
    else
    {
        RemoveMoney(&gSaveBlock1Ptr->money, sShopData->totalCost);
        PlaySE(SE_SHOP);
        PrintMoneyAmountInMoneyBox(WIN_MONEY, GetMoney(&gSaveBlock1Ptr->money), 0);

        if (sMartInfo.martType == MART_TYPE_NORMAL)
            gTasks[taskId].func = Task_ReturnToItemListAfterItemPurchase;
        else
            gTasks[taskId].func = Task_ReturnToItemListAfterDecorationPurchase;
    }
}

static void Task_ReturnToItemListAfterItemPurchase(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);

        // Purchasing 10+ Poke Balls gets the player a Premier Ball
        if ((ItemId_GetPocket(tItemId) == POCKET_POKE_BALLS) && tItemCount > 9 && AddBagItem(ITEM_PREMIER_BALL, tItemCount / 10) == TRUE)
            if (tItemCount > 19)
           {
               BuyMenuDisplayMessage(taskId, gText_ThrowInPremierBalls, BuyMenuReturnToItemList);
           }
           else
           {
               BuyMenuDisplayMessage(taskId, gText_ThrowInPremierBall, BuyMenuReturnToItemList);
           }
        else
            BuyMenuReturnToItemList(taskId);
    }
}

static void Task_ReturnToItemListAfterDecorationPurchase(u8 taskId)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BuyMenuReturnToItemList(taskId);
    }
}

static void Task_ExitKurtShopAfterPurchase(u8 taskId)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        ClearDialogWindowAndFrameToTransparent(WIN_MESSAGE, FALSE);
        ClearWindowTilemap(WIN_MESSAGE);
        ScheduleBgCopyTilemapToVram(0);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_ExitBuyMenu;
    }
}

static void BuyMenuReturnToItemList(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    ClearDialogWindowAndFrameToTransparent(WIN_MESSAGE, FALSE);
    BuyMenuPrintCursor(tListTaskId, COLORID_ITEM_LIST);
    PutWindowTilemap(WIN_ITEM_LIST);
    PutWindowTilemap(WIN_ITEM_DESCRIPTION);
    ScheduleBgCopyTilemapToVram(0);
    BuyMenuAddScrollIndicatorArrows();
    gTasks[taskId].func = Task_BuyMenu;
}

static void BuyMenuPrintItemQuantityAndPrice(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    FillWindowPixelBuffer(WIN_QUANTITY_PRICE, PIXEL_FILL(1));
    
    if (sMartInfo.martType == MART_TYPE_KURT)
    {
        // For Kurt shop: "×001  ###" with berry sprite
        u16 totalBalls = tItemCount;
        u16 berryItem;
        u8 x;
        
        // Print quantity (left side)
        ConvertIntToDecimalStringN(gStringVar1, tItemCount, STR_CONV_MODE_LEADING_ZEROS, BAG_ITEM_CAPACITY_DIGITS);
        StringExpandPlaceholders(gStringVar4, gText_xVar1);
        BuyMenuPrint(WIN_QUANTITY_PRICE, gStringVar4, 0, 1, 0, COLORID_NORMAL);
        
        // Print total ball count (right side, leaving space for berry icon)
        ConvertIntToDecimalStringN(gStringVar1, totalBalls, STR_CONV_MODE_LEFT_ALIGN, BAG_ITEM_CAPACITY_DIGITS);
        x = GetStringRightAlignXOffset(FONT_NORMAL, gStringVar1, 62); // Reduced from 80 to leave space for icon
        BuyMenuPrint(WIN_QUANTITY_PRICE, gStringVar1, x, 1, 0, COLORID_NORMAL);
        
        // Add scaled berry icon
        berryItem = GetBerryFromBall(tItemId);
        AddQuantityBerryIcon(berryItem);
    }
    else if (sMartInfo.martType == MART_TYPE_BP)
    {
        // For BP vitamin shop: "×001  ##BP"
        u8 x;
        u8 bp_text[16];
        ConvertIntToDecimalStringN(gStringVar1, tItemCount, STR_CONV_MODE_LEADING_ZEROS, BAG_ITEM_CAPACITY_DIGITS);
        StringExpandPlaceholders(gStringVar4, gText_xVar1);
        BuyMenuPrint(WIN_QUANTITY_PRICE, gStringVar4, 0, 1, 0, COLORID_NORMAL);
        // Print "##BP" right-aligned on the price side
        ConvertIntToDecimalStringN(bp_text, sShopData->totalCost, STR_CONV_MODE_LEFT_ALIGN, 4);
        StringAppend(bp_text, gText_BP);
        x = GetStringRightAlignXOffset(FONT_NORMAL, bp_text, 80);
        BuyMenuPrint(WIN_QUANTITY_PRICE, bp_text, x, 1, 0, COLORID_NORMAL);
    }
    else
    {
        PrintMoneyAmount(WIN_QUANTITY_PRICE, 32, 1, sShopData->totalCost, TEXT_SKIP_DRAW);
        ConvertIntToDecimalStringN(gStringVar1, tItemCount, STR_CONV_MODE_LEADING_ZEROS, BAG_ITEM_CAPACITY_DIGITS);
        StringExpandPlaceholders(gStringVar4, gText_xVar1);
        BuyMenuPrint(WIN_QUANTITY_PRICE, gStringVar4, 0, 1, 0, COLORID_NORMAL);
    }
}

static void ExitBuyMenu(u8 taskId)
{
    // Don't set field callback for Kurt or BP shops (they re-enable script directly)
    if (sMartInfo.martType != MART_TYPE_KURT
        && sMartInfo.martType != MART_TYPE_BP
        && sMartInfo.martType != MART_TYPE_BP_ITEM
        && sMartInfo.martType != MART_TYPE_BP_DECOR)
        gFieldCallback = MapPostLoadHook_ReturnToShopMenu;
    
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_ExitBuyMenu;
}

static void Task_ExitBuyMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if (sMartInfo.martType == MART_TYPE_BP
            || sMartInfo.martType == MART_TYPE_BP_ITEM
            || sMartInfo.martType == MART_TYPE_BP_DECOR)
            RemoveBPLabelObject();
        else
            RemoveMoneyLabelObject();
        BuyMenuFreeMemory();
        SetMainCallback2(CB2_ReturnToField);
        
        // For Kurt and BP shops: unlock controls and continue script directly
        if (sMartInfo.martType == MART_TYPE_KURT
            || sMartInfo.martType == MART_TYPE_BP
            || sMartInfo.martType == MART_TYPE_BP_ITEM
            || sMartInfo.martType == MART_TYPE_BP_DECOR)
        {
            UnlockPlayerFieldControls();
            if (sMartInfo.callback)
                sMartInfo.callback();
        }
        
        DestroyTask(taskId);
    }
}

static void ClearItemPurchases(void)
{
    sPurchaseHistoryId = 0;
    memset(gMartPurchaseHistory, 0, sizeof(gMartPurchaseHistory));
}

static void RecordItemPurchase(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    u16 i;

    for (i = 0; i < ARRAY_COUNT(gMartPurchaseHistory); i++)
    {
        if (gMartPurchaseHistory[i].itemId == tItemId && gMartPurchaseHistory[i].quantity != 0)
        {
            if (gMartPurchaseHistory[i].quantity + tItemCount > 255)
                gMartPurchaseHistory[i].quantity = 255;
            else
                gMartPurchaseHistory[i].quantity += tItemCount;
            return;
        }
    }

    if (sPurchaseHistoryId < ARRAY_COUNT(gMartPurchaseHistory))
    {
        gMartPurchaseHistory[sPurchaseHistoryId].itemId = tItemId;
        gMartPurchaseHistory[sPurchaseHistoryId].quantity = tItemCount;
        sPurchaseHistoryId++;
    }
}

#undef tItemCount
#undef tItemId
#undef tListTaskId
#undef tCallbackHi
#undef tCallbackLo

void CreatePokemartMenu(const u16 *itemsForSale)
{
    CreateShopMenu(MART_TYPE_NORMAL);
    SetShopItemsForSale(itemsForSale);
    ClearItemPurchases();
    SetShopMenuCallback(ScriptContext_Enable);
}

void CreateDecorationShop1Menu(const u16 *itemsForSale)
{
    CreateShopMenu(MART_TYPE_DECOR);
    SetShopItemsForSale(itemsForSale);
    SetShopMenuCallback(ScriptContext_Enable);
}

void CreateDecorationShop2Menu(const u16 *itemsForSale)
{
    CreateShopMenu(MART_TYPE_DECOR2);
    SetShopItemsForSale(itemsForSale);
    SetShopMenuCallback(ScriptContext_Enable);
}

void CreateKurtBallShop(const u16 *itemsForSale)
{
    u8 taskId;
    s16 *data;
    
    // Skip BUY/QUIT menu, go straight to buy menu for Kurt    LockPlayerFieldControls();
    sMartInfo.martType = MART_TYPE_KURT;
    SetShopItemsForSale(itemsForSale);
    ClearItemPurchases();
    SetShopMenuCallback(ScriptContext_Enable);
    
    // Go directly to buy menu
    taskId = CreateTask(Task_ShopMenu, 8);
    data = gTasks[taskId].data;
    data[8] = (u32)CB2_InitBuyMenu >> 16;  // tCallbackHi
    data[9] = (u32)CB2_InitBuyMenu;        // tCallbackLo
    gTasks[taskId].func = Task_GoToBuyOrSellMenu;
    FadeScreen(FADE_TO_BLACK, 0);
}

// ============================================================
// BP Exchange Corner shops
// ============================================================

// Scratch buffer: item IDs only, for SetShopItemsForSale
static EWRAM_DATA u16 sBPItemList[16];

static void SetBPShopItems(const struct BPShopEntry *entries)
{
    u16 i = 0;
    sBPShopEntries = entries;
    while (entries[i].item != ITEM_NONE && i < ARRAY_COUNT(sBPItemList) - 1)
    {
        sBPItemList[i] = entries[i].item;
        i++;
    }
    sBPItemList[i] = ITEM_NONE;
    SetShopItemsForSale(sBPItemList);
}

static void CreateBPShopCommon(u8 martType, const struct BPShopEntry *entries)
{
    u8 taskId;
    s16 *data;

    // Skip BUY/QUIT menu, go straight to buy menu (same pattern as Kurt)
    LockPlayerFieldControls();
    sMartInfo.martType = martType;
    SetBPShopItems(entries);
    SetShopMenuCallback(ScriptContext_Enable);

    taskId = CreateTask(Task_ShopMenu, 8);
    data = gTasks[taskId].data;
    data[8] = (u32)CB2_InitBuyMenu >> 16;  // tCallbackHi
    data[9] = (u32)CB2_InitBuyMenu;        // tCallbackLo
    gTasks[taskId].func = Task_GoToBuyOrSellMenu;
    FadeScreen(FADE_TO_BLACK, 0);
}

void CreateBPVitaminShop(void)      { CreateBPShopCommon(MART_TYPE_BP,      sBPVitaminShopEntries);  }
void CreateBPHoldItemShop(void)     { CreateBPShopCommon(MART_TYPE_BP_ITEM,  sBPHoldItemShopEntries); }
void CreateBPDecorShop1(void)       { CreateBPShopCommon(MART_TYPE_BP_DECOR, sBPDecor1ShopEntries);   }
void CreateBPDecorShop2(void)       { CreateBPShopCommon(MART_TYPE_BP_DECOR, sBPDecor2ShopEntries);   }
void CreateBPPokeBallShop(void)     { CreateBPShopCommon(MART_TYPE_BP,      sBPPokeBallShopEntries); }
