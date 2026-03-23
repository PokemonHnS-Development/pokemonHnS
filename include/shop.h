#ifndef GUARD_SHOP_H
#define GUARD_SHOP_H

extern struct ItemSlot gMartPurchaseHistory[3];

void CreatePokemartMenu(const u16 *);
void CreateDecorationShop1Menu(const u16 *);
void CreateDecorationShop2Menu(const u16 *);
void CreateKurtBallShop(const u16 *);
void CB2_ExitSellMenu(void);

// BP vendor shops (Battle Frontier Exchange Service Corner)
void CreateBPVitaminShop(void);   // multi-buy vitamins
void CreateBPHoldItemShop(void);  // single-buy held items
void CreateBPDecorShop1(void);    // single-buy small dolls
void CreateBPDecorShop2(void);    // single-buy large dolls
void CreateBPPokeBallShop(void);  // multi-buy Poké Balls

#endif // GUARD_SHOP_H
