MtMortar_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMortar_B1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

MtMortar_B1F_OnTransition: 
	callnative SetTimeBasedEncounters
	end

MtMortar_B1F_EventScript_Item_HyperPotion::
    finditem ITEM_HYPER_POTION
    end

MtMortar_B1F_EventScript_Item_Carbos::
    finditem ITEM_CARBOS
    end

MtMortar_B1F_EventScript_Item_PPUp::
    finditem ITEM_PP_UP
    end

MtMortar_B1F_EventScript_Item_MaxEther::
    finditem ITEM_MAX_ETHER
    end

MtMortar_B1F_EventScript_Item_MaxRevive::
    finditem ITEM_MAX_REVIVE
    end

MountMortar4_EventScript_Kiyo::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TYROGUE, MountMortar4_EventScript_KiyoAfter
	goto_if_set FLAG_BEAT_KIYO, MountMortar4_EventScript_KiyoTryGiveTyrogue
	msgbox MountMortar4_Text_KiyoIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_KIYO, MountMortar4_Text_KiyoWin
	setflag FLAG_BEAT_KIYO
MountMortar4_EventScript_KiyoTryGiveTyrogue::
	msgbox MountMortar4_Text_KiyoTyrogueReward, MSGBOX_DEFAULT
	@HnS gift pokemon setup
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TYROGUE
	bufferspeciesname STR_VAR_1, SPECIES_TYROGUE
	givemon SPECIES_TYROGUE, 25
	call Common_EventScript_GiftMon
	setflag FLAG_GOT_TYROGUE
MountMortar4_EventScript_KiyoAfter::
	msgbox MountMortar4_Text_KiyoGotTyrogue, MSGBOX_DEFAULT
	closemessage
	release
	end


MountMortar4_Text_KiyoIntro:
	.string "¡Oye!\p"
	.string "¡Soy el REY DEL KARATE!\n"
	.string "¡Entreno solo aquí en la oscuridad!\p"
	.string "¡Tú! ¡Lucha conmigo!\n"
	.string "¡Hwaaarggh!$"

MountMortar4_Text_KiyoWin:
	.string "¡Waaaarggh!\n"
	.string "¡Me vencieron!$"

MountMortar4_Text_KiyoTyrogueReward:
	.string "Estoy... destrozado...\p"
	.string "Mi entrenamiento aún no\n"
	.string "es suficiente...\p"
	.string "Pero una derrota es una derrota.\n"
	.string "Lo admito.\p"
	.string "Como prueba de que me venciste,\n"
	.string "te daré un POKéMON de lucha\l"
	.string "poco común.$"

MountMortar4_Text_ReceiveTyrogue:
	.string "{PLAYER} recibió a TYROGUE.$"

MountMortar4_Text_KiyoGotTyrogue:
	.string "TYROGUE es tipo LUCHA.\p"
	.string "Evoluciona en un POKéMON\n"
	.string "más fuerte.\p"
	.string "Sigue esforzándote.\n"
	.string "Yo también seguiré entrenando.\p"
	.string "¡Adiós!$"

MountMortar4_Text_KiyoFullParty:
	.string "¡No tienes espacio en tu equipo!$"
