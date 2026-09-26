CeladonCity_Apartments_RoofHouse_MapScripts::
	.byte 0

CeladonCity_Apartments_RoofHouse_EventScript_BlackBelt::
	lock 
	faceplayer
	goto_if_set FLAG_GOT_TM_REST, CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltAfter
	msgbox CeladonMansionRoofHouse_Text_PharmacistIntro, MSGBOX_DEFAULT	
	goto_if_set FLAG_NIGHT_POKEMON, CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltRefused
	msgbox CeladonMansionRoofHouse_Text_PharmacistStory, MSGBOX_NPC
	giveitem ITEM_TM_REST
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_REST
	msgbox CeladonMansionRoofHouse_Text_PharmacistCurse, MSGBOX_NPC
	closemessage
	release
	end

CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltRefused::
	msgbox CeladonMansionRoofHouse_Text_PharmacistNotNight, MSGBOX_NPC
	closemessage
	release
	end

CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltAfter::
	msgbox CeladonMansionRoofHouse_Text_PharmacistCurse, MSGBOX_NPC
	release
	end

CeladonMansionRoofHouse_Text_PharmacistIntro:
	.string "Déjame contarte un cuento terrorífico…$"

CeladonMansionRoofHouse_Text_PharmacistNotNight:
	.string "Aunque no da tanto miedo\n"
	.string "mientras haya luz afuera.\p"
	.string "Vuelve tras el ocaso, ¿sí?$"

CeladonMansionRoofHouse_Text_PharmacistStory:
	.string "Había una vez un\n"
	.string "niño que recibió una nueva\l"
	.string "BICYCLE…\p"
	.string "Quiso probarla enseguida…\p"
	.string "Se divertía tanto que\n"
	.string "no notó que el sol se puso…\p"
	.string "Al volver a casa en la\n"
	.string "oscuridad, la bici de pronto\l"
	.string "¡frenó!\p"
	.string "¡Los pedales pesaban mucho!\p"
	.string "Al dejar de pedalear, la\n"
	.string "¡bici empezó a retroceder!\p"
	.string "Era como si la bici estuviera\n"
	.string "maldita y quisiera llevarlo al\l"
	.string "olvido!\p"
	.string "…\p"
	.string "…\p"
	.string "¡¡¡AAAAAAHHH!!!\p"
	.string "¡El niño subía la colina de la\n"
	.string "CYCLING ROAD!\p"
	.string "…\n"
	.string "¡Tucún tucún!\p"
	.string "Por escuchar con paciencia,\n"
	.string "¡toma esto: TM44!$"

CeladonMansionRoofHouse_Text_PharmacistCurse:
	.string "La MT44 es DESCANSAR.\p"
	.string "Permite que tu POKéMON tome una\n"
	.string "siesta y recupere salud.\p"
	.string "¡Suerte durmiendo tras ese\n"
	.string "cuento tan terrorífico!$"

