GoldenrodCity_RadioTower_3F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodCity_RadioTower_3F_OnLoad
	.byte 0

GoldenrodCity_RadioTower_3F_OnLoad::
	call_if_set FLAG_HIDE_RADIOTOWER_GATE, GoldenrodCity_RadioTower_3F_HideGate
	end
	
GoldenrodCity_RadioTower_3F_HideGate::
	setmetatile 25, 8, 0x335, FALSE
	setmetatile 25, 9, 0x335, FALSE

	setmetatile 26, 8, 0X334, FALSE
	setmetatile 26, 9, 0X334, FALSE

	setmetatile 27, 8, 0X334, FALSE
	setmetatile 27, 9, 0X334, FALSE

	setmetatile 28, 8, 0X334, FALSE
	setmetatile 28, 9, 0X334, FALSE

	setmetatile 29, 8, 0X334, FALSE
	setmetatile 29, 9, 0X334, FALSE

	setmetatile 30, 8, 0X334, FALSE
	setmetatile 30, 9, 0X334, FALSE

	setmetatile 31, 8, 0X334, FALSE
	setmetatile 31, 9, 0X334, FALSE
	return


GoldenrodRaidoTower3_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_6 GoldenrodCity_RadioTower_3F_Text_GruntM7Seen, GoldenrodCity_RadioTower_3F_Text_GruntM7Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM7After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Grunt7::
	trainerbattle_single TRAINER_GRUNT_7 GoldenrodCity_RadioTower_3F_Text_GruntM8Seen, GoldenrodCity_RadioTower_3F_Text_GruntM8Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM8After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_8 GoldenrodCity_RadioTower_3F_Text_GruntM9Seen, GoldenrodCity_RadioTower_3F_Text_GruntM9Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM9After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Scientist::
	trainerbattle_single TRAINER_MARC GoldenrodCity_RadioTower_3F_Text_ScientistMarcSeen, GoldenrodCity_RadioTower_3F_Text_ScientistMarcBeaten
	msgbox GoldenrodCity_RadioTower_3F_Text_ScientistMarcAfter, MSGBOX_AUTOCLOSE
	end


GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SKILL_SWAP, GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer3
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 10, GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer2

	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFPleaseSave, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer2::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFHeroGift, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_TM_SKILL_SWAP
	setflag FLAG_GOT_SKILL_SWAP
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFSunnyDay, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer3::
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFMarvelous, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_3F_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Gate::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_CardKeySlot, MSGBOX_SIGN
	goto_if_set FLAG_HIDE_RADIOTOWER_GATE, GoldenrodCity_RadioTower_3F_EventScript_GateOpened
	checkitem ITEM_CARD_KEY
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_RadioTower_3F_EventScript_OpenGate
	closemessage
	release
	end


GoldenrodCity_RadioTower_3F_EventScript_GateOpened::
	msgbox GoldenrodCity_RadioTower_3F_Text_Open, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_OpenGate::
	msgbox GoldenrodCity_RadioTower_3F_Text_InsertedCardKey, MSGBOX_SIGN
	call GoldenrodCity_RadioTower_3F_HideGate
	playse SE_CLICK
	special DrawWholeMapView
	msgbox GoldenrodCity_RadioTower_3F_Text_Open, MSGBOX_SIGN
	setflag FLAG_HIDE_RADIOTOWER_GATE
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_PersonnelSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_PokemonMusicSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_Text_CardKeySlot:
	.string "Es la ranura de la CARD KEY.$"

GoldenrodCity_RadioTower_3F_Text_InsertedCardKey:
	.string "{PLAYER} insertó la CARD KEY.$"
 
GoldenrodCity_RadioTower_3F_Text_Open:
	.string "La puerta está abierta.$"

GoldenrodCity_RadioTower_3F_Text_PersonnelSign:
	.string "PERSONAL 3F$"

GoldenrodCity_RadioTower_3F_Text_PokemonMusicSign:
	.string "MÚSICA POKéMON con el DJ BEN$"

GoldenrodCity_RadioTower_3F_Text_SuperNerd:
	.string "Tenemos grabaciones de los gritos\n"
	.string "de todos los POKéMON que han\l"
	.string "sido hallados.\p"
	.string "Deben ser unos 400 tipos.$"

GoldenrodCity_RadioTower_3F_Text_GymGuideRockets:
	.string "Para los entrenadores, los POKéMON\n"
	.string "son sus queridos compañeros.\p"
	.string "Es terrible que el TEAM ROCKET\n"
	.string "intente controlarlos.$"

GoldenrodCity_RadioTower_3F_Text_GymGuide:
	.string "Transmitimos programas divertidos\n"
	.string "las 24 horas del día.\p"
	.string "¡Yo también daré lo mejor de mí\n"
	.string "todo el tiempo!$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFPleaseSave:
	.string "El jefe del TEAM ROCKET se encerró\n"
	.string "allí dentro.\p"
	.string "Pero el DIRECTOR puede abrirlo.\p"
	.string "Está en el quinto piso.\p"
	.string "¡Por favor, sálvalo!$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFDirectorSafe:
	.string "¿Está a salvo el DIRECTOR?$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFHeroGift:
	.string "¡Gracias! ¡Eres mi héroe!\p"
	.string "Toma esto como muestra de gratitud.$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFSunnyDay:
	.string "Es SKILL SWAP. Intercambia la\n"
	.string "habilidad de un POKéMON con otro.$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFMarvelous:
	.string "¡Estuviste simplemente maravilloso!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7Seen:
	.string "Recibí órdenes muy estrictas.\p"
	.string "¡Debo aplastar a quien desafíe al\n"
	.string "TEAM ROCKET!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7Beaten:
	.string "¡¿Qué?!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7After:
	.string "Fallé en mis deberes...\p"
	.string "ARCHER estará muy molesto...$"

GoldenrodCity_RadioTower_3F_Text_GruntM8Seen:
	.string "Es genial ordenar a los POKéMON\n"
	.string "cometer crímenes.$"

GoldenrodCity_RadioTower_3F_Text_GruntM8Beaten:
	.string "¡No puede ser!$"

GoldenrodCity_RadioTower_3F_Text_GruntM8After:
	.string "¡Me siento mal por perder!\p"
	.string "¡Rayos! ¡Odio los POKéMON inútiles!$"

GoldenrodCity_RadioTower_3F_Text_GruntM9Seen:
	.string "¿Por qué se abrió la persiana? ¿Tú\n"
	.string "tuviste algo que ver con esto?$"

GoldenrodCity_RadioTower_3F_Text_GruntM9Beaten:
	.string "¡Estoy acabado!$"

GoldenrodCity_RadioTower_3F_Text_GruntM9After:
	.string "¿Qué?! ¿Pasaste a nuestros hombres\n"
	.string "del UNDERGROUND?\p"
	.string "¿Cómo pudiste?$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcSeen:
	.string "¿Un niño desconocido por aquí?\p"
	.string "¿Quién eres tú?$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcBeaten:
	.string "¡Tch! ¡Te subestimé demasiado!$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcAfter:
	.string "Bwahahaha…\p"
	.string "Puedo transmitir una señal tan fuerte\n"
	.string "como necesite desde aquí.$"

