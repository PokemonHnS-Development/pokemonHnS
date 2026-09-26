.set LOCALID_NURSE, 1

FortreeCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FortreeCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FORTREE_CITY
	end

FortreeCity_PokemonCenter_1F_RhyperiorEvo::
	msgbox FortreeCity_PokemonCenter_1F_RhyperiorEvo_Text, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_RhyperiorEvo_Text:
	.string "RHYDON evoluciona al cambiarlo.\n"
	.string "Pero solo si es con un objeto.\p"
	.string "¿Qué objeto, te preguntarás?\p"
	.string "Bueno... Mi memoria no es tan buena\n"
	.string "como hace treinta años... Era un...\l"
	.string "DURO... DURO... Ah.\p"
	.string "No lo recuerdo. Lo siento.$"

FortreeCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox FortreeCity_PokemonCenter_1F_Text_GoToSafariZone, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Man::
	msgbox FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Boy::
	msgbox FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_Text_GoToSafariZone:
	.string "Oye, chico, ¿estás trabajando\n"
	.string "en una POKéDEX?\p"
	.string "Hmm... Ve a la ZONA SAFARI.\n"
	.string "Esa es mi sugerencia.$"

FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat:
	.string "¿Has hecho algo en el\n"
	.string "RINCÓN DE DISCOS?\p"
	.string "Es genial. Mezcla y combina\n"
	.string "los discos de los ENTRENADORES.\p"
	.string "No sé bien cómo funciona,\n"
	.string "pero es genial. ¡Es emocionante!$"

FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav:
	.string "¡Vaya, tienes un POKéNAV!\n"
	.string "¡Es igual al mío!\p"
	.string "¿Conoces el sistema MATCH CALL\n"
	.string "del POKéNAV?\p"
	.string "Úsalo y podrás chatear con\n"
	.string "ENTRENADORES registrados siempre.\p"
	.string "Muestra qué ENTRENADORES\n"
	.string "quieren revancha contigo.\p"
	.string "¡Es fantástico! ¡Los de DEVON\n"
	.string "saben lo que hacen!$"

