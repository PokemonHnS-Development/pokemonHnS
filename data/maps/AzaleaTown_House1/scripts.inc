AzaleaTown_House1_MapScripts::
	.byte 0

AzaleaTown_House1_EventScript_Boss::
	lock
	faceplayer
	goto_if_eq VAR_AZALEA_TOWN_STATE, 5, AzaleaTown_House1_EventScript_Boss3
	goto_if_eq VAR_AZALEA_TOWN_STATE, 6, AzaleaTown_House1_EventScript_Boss3
	goto_if_eq VAR_AZALEA_TOWN_STATE, 7, AzaleaTown_House1_EventScript_Boss4
	goto_if_set FLAG_HIDE_AZALEA_TOWN_ROCKETS, AzaleaTown_House1_EventScript_Boss2
	msgbox CharcoalKiln_Text_Boss1, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Boss2::
	msgbox CharcoalKiln_Text_Boss2, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Boss3::
	msgbox CharcoalKiln_Text_Boss3, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Boss4::
	msgbox CharcoalKiln_Text_Boss4, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice::
	lock
	faceplayer
	goto_if_ge VAR_AZALEA_TOWN_STATE, 7, AzaleaTown_House1_EventScript_Apprentice3
	goto_if_set FLAG_HIDE_AZALEA_TOWN_ROCKETS, AzaleaTown_House1_EventScript_Apprentice2
	msgbox CharcoalKiln_Text_Apprentice1, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice2::
	msgbox CharcoalKiln_Text_Apprentice2, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice3::
	goto_if_set FLAG_GOT_CHARCOAL, AzaleaTown_House1_EventScript_Apprentice4
	msgbox CharcoalKiln_Text_Apprentice3, MSGBOX_DEFAULT
	giveitem ITEM_CHARCOAL 
	setflag FLAG_GOT_CHARCOAL
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice4::
	msgbox CharcoalKiln_Text_Apprentice4, MSGBOX_DEFAULT
	closemessage
	release
	end


AzaleaTown_House1_EventScript_Farfetchd::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox CharcoalKiln_Text_Farfetchd, MSGBOX_DEFAULT
	waitmoncry
	release
	end
	


CharcoalKiln_Text_Boss1:
	.string "Todos los SLOWPOKE han\n"
	.string "desaparecido del pueblo.\p"
	.string "El protector del bosque puede\n"
	.string "estar enojado con nosotros...\p"
	.string "Es un mal presagio. Mejor\n"
	.string "quedémonos dentro.$"

CharcoalKiln_Text_Boss2:
	.string "Los SLOWPOKE han vuelto...$"

CharcoalKiln_Text_Boss3:
	.string "Los SLOWPOKE han vuelto...\p"
	.string "Pero mi APRENDIZ no ha vuelto\n"
	.string "del BOSQUE VERDE.\p"
	.string "¿Dónde estará ese flojo?$"

CharcoalKiln_Text_Boss4:
	.string "¿Ahuyentaste al TEAM ROCKET y\n"
	.string "fuiste solo al BOSQUE VERDE?\p"
	.string "¡Qué valor! Me gusta eso.\n"
	.string "Ven a entrenar con nosotros.$"

CharcoalKiln_Text_Apprentice1:
	.string "¿A dónde se fueron los SLOWPOKE?\p"
	.string "¿Estarán jugando por ahí?$"

CharcoalKiln_Text_Apprentice2:
	.string "¡Los SLOWPOKE regresaron!$"

CharcoalKiln_Text_Apprentice3:
	.string "Lo siento, olvidé agradecerte.\p"
	.string "Hice este CARBÓN.\p"
	.string "A los POKéMON tipo FUEGO les\n"
	.string "gustaría llevarlo.$"

CharcoalKiln_Text_Apprentice4:
	.string "El SLOWPOKE volvió, e incluso\n"
	.string "hallaste a FARFETCH'D.\p"
	.string "¡Eres el mejor, amigo!$"

CharcoalKiln_Text_Farfetchd:
	.string "FARFETCH'D: ¡Kwaa!$"
