.set LOCALID_NURSE, 1

CianwoodPokecenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CianwoodPokecenter_OnTransition
	.byte 0

CianwoodPokecenter_OnTransition::
	setrespawn HEAL_LOCATION_CIANWOOD_CITY
	end

CianwoodPokemoncenter_EventScript_Fisher::
	lock
	faceplayer
	goto_if_set FLAG_TEMP_1, CianwoodPokemoncenter_EventScript_FisherNormal
	checkpartymove MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, CianwoodPokemoncenter_EventScript_FisherGiveTentacool
CianwoodPokemoncenter_EventScript_FisherNormal::
	msgbox CianwoodPokemoncenter_Text_Fisher1, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodPokemoncenter_EventScript_FisherGiveTentacool::
	msgbox CianwoodPokemoncenter_Text_Fisher2, MSGBOX_DEFAULT
	@HnS gift pokemon setup
	callnative DisableStaticRandomizer
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TENTACOOL
	bufferspeciesname STR_VAR_1, SPECIES_TENTACOOL
	givemon SPECIES_TENTACOOL, 25
	call Common_EventScript_GiftMon
	setflag FLAG_TEMP_1
	callnative EnableStaticRandomizer
	closemessage
	release
	end

CianwoodPokemoncenter_Text_Fisher1:
	.string "En cuanto a POKéMON de agua,\n"
	.string "¡TENTACOOL es el mejor por\l"
	.string "milla náutica!$"

CianwoodPokemoncenter_Text_Fisher2:
	.string "Parece que necesitas un\n"
	.string "POKéMON de agua.\p"
	.string "Toma este, tengo muchos.$"

CianwoodPokecenter_EventScript_Lass::
	lock
	faceplayer
	msgbox CianwoodCity_Text_PokecenterLass, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_PokecenterLass:
	.string "¿Conociste al POKéMANÍACO?\p"
	.string "Siempre presume de sus\n"
	.string "POKéMON raros.$"


CianwoodGym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, CianwoodGym_EventScript_GymGuideAfter
	msgbox CianwoodCity_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_EventScript_GymGuideAfter::
	msgbox CianwoodCity_Text_GymGuideWin, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_GymGuide:
	.string "Los entrenadores del GIMNASIO\n"
	.string "son unos abusivos.\p"
	.string "Si me quedo, podrían\n"
	.string "venir por mí.\p"
	.string "Un consejo: el LÍDER del GIMNASIO\n"
	.string "usa el tipo LUCHA.\p"
	.string "Confúndelo con POKéMON\n"
	.string "psíquicos.\p"
	.string "Véncelos antes de que usen\n"
	.string "su fuerza física.\p"
	.string "¿Y las rocas del centro\n"
	.string "del GIMNASIO?\p"
	.string "Si no las mueves bien,\n"
	.string "no llegarás al LÍDER.\p"
	.string "Si te atascas, sal fuera.$"

CianwoodCity_Text_GymGuideWin:
	.string "¡{PLAYER}! ¡Ganaste!\n"
	.string "¡Lo supe al verte!$"

CianwoodPokecenter_EventScript_Nerd::
	lock
	faceplayer
	msgbox CianwoodCity_Text_PokecenterSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_PokecenterSuperNerd:
	.string "Amo presumir los POKéMON\n"
	.string "que he criado.\p"
	.string "¿A ti no?\p"
	.string "¡Tendré muchas batallas\n"
	.string "para lucir mis POKéMON!$"
