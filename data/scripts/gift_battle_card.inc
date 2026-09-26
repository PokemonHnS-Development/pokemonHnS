MysteryGiftScript_BattleCard::
	setvaddress MysteryGiftScript_BattleCard
	vgoto_if_set FLAG_MYSTERY_GIFT_DONE, MysteryGiftScript_BattleCardInfo
	setorcopyvar VAR_RESULT, GET_CARD_BATTLES_WON
	specialvar VAR_0x8008, GetMysteryGiftCardStat
	vgoto_if_ne VAR_0x8008, REQUIRED_CARD_BATTLES, MysteryGiftScript_BattleCardInfo
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard_WonPrize
	waitmessage
	waitbuttonpress
	giveitem ITEM_POTION
	release
	setflag FLAG_MYSTERY_GIFT_DONE
	end

MysteryGiftScript_BattleCardInfo:
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftBattleCountCard:
	.string "Gracias por usar el sistema de\n"
	.string "REGALOS MISTERIOSOS.\p"
	.string "Tu TARJETA DE BATALLAS guarda\n"
	.string "tu récord contra otros\l"
	.string "ENTRENADORES con la misma TARJETA.\p"
	.string "Busca y lucha contra ENTRENADORES\n"
	.string "que tengan tu misma TARJETA.\p"
	.string "Mira el ranking general leyendo\n"
	.string "las NOTICIAS.\p"
	.string "¡Por favor, pruébalo!$"

sText_MysteryGiftBattleCountCard_WonPrize:
	.string "Gracias por usar el sistema de\n"
	.string "REGALOS MISTERIOSOS.\p"
	.string "¡Felicidades!\p"
	.string "¡Ganaste un premio por ganar\n"
	.string "tres batallas!\p"
	.string "Esperamos que esto te inspire a\n"
	.string "luchar más.$"
