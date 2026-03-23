// ============================================================
// BP Exchange Corner shops
// ============================================================

// Paired item + BP cost entry, used by BP vendor shop tables.
struct BPShopEntry
{
    u16 item;   // ITEM_* constant (or DECOR_* for decoration shops)
    u16 bpCost; // cost in Battle Points
};

static const struct BPShopEntry sBPVitaminShopEntries[] = {
    { ITEM_PROTEIN, 1 },
    { ITEM_CALCIUM, 1 },
    { ITEM_IRON,    1 },
    { ITEM_ZINC,    1 },
    { ITEM_CARBOS,  1 },
    { ITEM_HP_UP,   1 },
    { ITEM_NONE,    0 },
};

static const struct BPShopEntry sBPHoldItemShopEntries[] = {
    { ITEM_LEFTOVERS,     48 },
    { ITEM_WHITE_HERB,    48 },
    { ITEM_QUICK_CLAW,    48 },
    { ITEM_MENTAL_HERB,   48 },
    { ITEM_BRIGHT_POWDER, 64 },
    { ITEM_CHOICE_BAND,   64 },
    { ITEM_KINGS_ROCK,    64 },
    { ITEM_FOCUS_BAND,    64 },
    { ITEM_SCOPE_LENS,    64 },
    { ITEM_NONE,           0 },
};

static const struct BPShopEntry sBPDecor1ShopEntries[] = {
    { DECOR_TREECKO_DOLL,   48 },
    { DECOR_TORCHIC_DOLL,   48 },
    { DECOR_MUDKIP_DOLL,    48 },
    { DECOR_TOGEPI_DOLL,    48 },
    { DECOR_MEOWTH_DOLL,    48 },
    { DECOR_CLEFAIRY_DOLL,  48 },
    { DECOR_DITTO_DOLL,     48 },
    { DECOR_CYNDAQUIL_DOLL, 80 },
    { DECOR_CHIKORITA_DOLL, 80 },
    { DECOR_TOTODILE_DOLL,  80 },
    { ITEM_NONE,              0 },
};

static const struct BPShopEntry sBPDecor2ShopEntries[] = {
    { DECOR_LAPRAS_DOLL,    128 },
    { DECOR_VENUSAUR_DOLL,  256 },
    { DECOR_CHARIZARD_DOLL, 256 },
    { DECOR_BLASTOISE_DOLL, 256 },
    { ITEM_NONE,              0 },
};

static const struct BPShopEntry sBPPokeBallShopEntries[] = {
    { ITEM_NET_BALL,     1 },
    { ITEM_DIVE_BALL,    1 },
    { ITEM_NEST_BALL,    1 },
    { ITEM_REPEAT_BALL,  1 },
    { ITEM_TIMER_BALL,   1 },
    { ITEM_LUXURY_BALL,  1 },
    { ITEM_NONE,         0 },
};
