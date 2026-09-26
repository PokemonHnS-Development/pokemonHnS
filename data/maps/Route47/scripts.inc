Route47_MapScripts::
	.byte 0


Route47_EventScript_Hiker::
	trainerbattle_single TRAINER_DEVIN, Route47_Text_HikerSeen, Route47_Text_HikerBeaten
	msgbox Route47_Text_HikerAfter, MSGBOX_AUTOCLOSE
	end

Route47_Text_HikerSeen::
	.string "Extrañar a otros es...\n"
	.string "así es. \p"
	.string "Pero las batallas son batallas,\n"
	.string "¡así que vamos!$"

Route47_Text_HikerBeaten::
	.string "¡Jajaja!$"

Route47_Text_HikerAfter::
	.string "¡Tras una batalla siempre debes irte\n"
	.string "con una risa de despedida!$"

Route47_EventScript_Camper::
	trainerbattle_single TRAINER_GRANT, Route47_Text_CamperSeen, Route47_Text_CamperBeaten
	msgbox Route47_Text_CamperAfter, MSGBOX_AUTOCLOSE
	end

Route47_Text_CamperSeen::
	.string "No me gustan las multitudes, así que\n"
	.string "acampo aquí con mis\l"
	.string "POKéMON!$"

Route47_Text_CamperBeaten::
	.string "Supongo que debería ir más profundo\n"
	.string "en la montaña...$"

Route47_Text_CamperAfter::
	.string "¡Nos vemos!$"

Route47_EventScript_Thom::
	trainerbattle_double TRAINER_THOM_AND_KAE, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple1After1, MSGBOX_AUTOCLOSE
	end

Route47_EventScript_Kae::
	trainerbattle_double TRAINER_THOM_AND_KAE, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple1After2, MSGBOX_AUTOCLOSE
	end

Route47_Text_Couple1Seen::
	.string "THOM: Uno más uno son dos. ¡Pero los\n"
	.string "dos juntos somos mucho\l"
	.string "más fuertes!\p"
	.string "KAE: ¡Nosotros no somos una pareja\n"
	.string "aburrida!$"

Route47_Text_Couple1Beaten::
	.string "THOM: No era lo que esperaba.\l"
	.string "KAE: ¡Tú también eres inusual!$"

Route47_Text_Couple1After1::
	.string "THOM: ¡Parece que tu poder es\n"
	.string "imposible de predecir!$"

Route47_Text_Couple1After2::
	.string "KAE: Creí que eras un entrenador\n"
	.string "solitario común. ¡Qué error!$"

Route47_EventScript_Duff::
	trainerbattle_double TRAINER_DUFF_AND_EDA, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple2After1, MSGBOX_AUTOCLOSE
	end

Route47_EventScript_Eda::
	trainerbattle_double TRAINER_DUFF_AND_EDA, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, Route104_Text_GinaNotEnoughMons
	msgbox Route47_Text_Couple2After2, MSGBOX_AUTOCLOSE
	end

Route47_Text_Couple2Seen::
	.string "DUFF: ¡Cuidar a mi novia hace que\n"
	.string "mi corazón vuele!\p"
	.string "EDA: ¡Lo que siento por mi novio\n"
	.string "es tan amplio y profundo como\l"
	.string "el océano!$"

Route47_Text_Couple2Beaten::
	.string "DUFF: No fui rival para ti...\l"
	.string "EDA: Realmente eres increíble...$"

Route47_Text_Couple2After1::
	.string "DUFF: ¡Gracias por esta batalla\n"
	.string "tan inspiradora! ¡Adiós!$"

Route47_Text_Couple2After2::
	.string "EDA: ¡Tú también deberías buscar\n"
	.string "una pareja maravillosa!$"

Route47_EventScript_Sage::
	lock
	faceplayer
	msgbox EmbeddedTower_Text_OldManIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

EmbeddedTower_Text_OldManIntro:
	.string "¡Hola, qué tal!\p"
	.string "Dicen que tras este hueco solía\n"
	.string "haber una torre enorme que llegaba\l"
	.string "al cielo.\p"
	.string "Dicen que era una torre muy rara\n"
	.string "con la mitad incrustada en el\l"
	.string "acantilado.\p"
	.string "¡No solo era una torre altísima,\n"
	.string "sino que también bajaba mucho\l"
	.string "bajo tierra!\p"
	.string "¡Se rumorea que llegaba hasta\n"
	.string "el fondo del océano!\p"
	.string "En resumen, las ruinas conectaban\n"
	.string "el cielo, la tierra y el mar\l"
	.string "entre sí...\p"
	.string "Casi toda la torre cayó,\n"
	.string "y solo quedan la entrada y el\l"
	.string "interior, donde verás patrones\l"
	.string "extraños.$"

Route47_EventScript_Item_Pearl::
    finditem ITEM_PEARL
    end

Route47_EventScript_Item_Revive::
    finditem ITEM_REVIVE
    end

Route47_EventScript_Item_WhiteFlute::
    finditem ITEM_WHITE_FLUTE
    end

Route47_EventScript_Item_Stardust::
	finditem ITEM_STARDUST
	end

Route47_EventScript_Item_LuckyPunch::
	finditem ITEM_LUCKY_PUNCH
	end

Route47_EventScript_Chinchou::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHINCHOU, CRY_MODE_NORMAL
	msgbox Route47_Text_Chinchou, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route47_Text_Chinchou:
	.string "CHINCHOU: ¡Chou!$"
