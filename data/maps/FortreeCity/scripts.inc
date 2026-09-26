FortreeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, FortreeCity_OnResume
	.byte 0

FortreeCity_OnTransition:
	setflag FLAG_VISITED_VIRIDIAN_CITY
	end

FortreeCity_OnResume:
	setstepcallback STEP_CB_FORTREE_BRIDGE
	end

FortreeCity_EventScript_Man::
	msgbox FortreeCity_Text_SawGiganticPokemonInSky, MSGBOX_NPC
	end

FortreeCity_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_KECLEON_FLED_FORTREE, FortreeCity_EventScript_WomanGymAccessible
	msgbox FortreeCity_Text_SomethingBlockingGym, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_WomanGymAccessible::
	msgbox FortreeCity_Text_ThisTimeIllBeatWinona, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_Girl::
	msgbox FortreeCity_Text_TreesGrowByDrinkingRainwater, MSGBOX_NPC
	end

FortreeCity_EventScript_OldMan::
	msgbox FortreeCity_Text_EveryoneHealthyAndLively, MSGBOX_NPC
	end

FortreeCity_EventScript_Boy::
	msgbox FortreeCity_Text_BugPokemonComeThroughWindow, MSGBOX_NPC
	end

FortreeCity_EventScript_GameboyKid::
	msgbox FortreeCity_Text_PokemonThatEvolveWhenTraded, MSGBOX_NPC
	end

FortreeCity_EventScript_CitySign::
	msgbox FortreeCity_Text_CitySign, MSGBOX_SIGN
	end

FortreeCity_EventScript_GymSign::
	msgbox FortreeCity_Text_GymSign, MSGBOX_SIGN
	end

FortreeCity_EventScript_Kecleon::
	lock
	faceplayer
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_EventScript_AskUseDevonScope
	msgbox FortreeCity_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_AskUseDevonScope::
	msgbox FortreeCity_Text_UnseeableUseDevonScope, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FortreeCity_EventScript_UseDevonScope
	release
	end

FortreeCity_EventScript_UseDevonScope::
	msgbox FortreeCity_Text_UsedDevonScopePokemonFled, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	applymovement VAR_LAST_TALKED, FortreeCity_Movement_KecleonFlee
	waitmovement 0
	removeobject VAR_LAST_TALKED
	setflag FLAG_KECLEON_FLED_FORTREE
	release
	end

FortreeCity_Movement_KecleonFlee:
	walk_right
	step_end

FortreeCity_Text_SawGiganticPokemonInSky:
	.string "Nadie me cree, pero vi a ese\n"
	.string "POKéMON gigante en el cielo.\p"
	.string "Parecía retorcerse al volar hacia\n"
	.string "la RUTA 131.\p"
	.string "Por cierto... Sniff...\n"
	.string "Eh... Tú... hueles a quemado.\p"
	.string "¿Estuviste en un volcán o algo así?$"

FortreeCity_Text_SomethingBlockingGym:
	.string "Quiero ir al GIMNASIO POKéMON,\n"
	.string "pero algo bloquea el camino.\p"
	.string "Después de tanto esfuerzo\n"
	.string "entrenando en la RUTA 120...$"

FortreeCity_Text_ThisTimeIllBeatWinona:
	.string "Tengo conmigo a mi POKéMON\n"
	.string "favorito. ¡Esta vez venceré a WINONA!$"

FortreeCity_Text_TreesGrowByDrinkingRainwater:
	.string "El suelo absorbe el agua de lluvia\n"
	.string "y los árboles crecen con ella...\p"
	.string "CIUDAD BOSQUE existe porque\n"
	.string "hay agua y tierra.$"

FortreeCity_Text_EveryoneHealthyAndLively:
	.string "La CIUDAD tiene casas construidas\n"
	.string "sobre árboles.\p"
	.string "Quizás por ese estilo de vida,\n"
	.string "todos están sanos y activos.\p"
	.string "Incluso yo siento que soy\n"
	.string "treinta años más joven.$"

FortreeCity_Text_BugPokemonComeThroughWindow:
	.string "Vivir sobre árboles está bien.\p"
	.string "Pero a veces entran POKéMON BUG\n"
	.string "por las ventanas.\l"
	.string "Puede ser muy sorprendente.$"

FortreeCity_Text_PokemonThatEvolveWhenTraded:
	.string "¡Hay POKéMON que evolucionan al\n"
	.string "intercambiarlos! Eso escuché.$"

FortreeCity_Text_SomethingUnseeable:
	.string "Algo invisible bloquea el camino.$"

FortreeCity_Text_UnseeableUseDevonScope:
	.string "Algo invisible bloquea el camino.\p"
	.string "¿Quieres usar el DEVON SCOPE?$"

FortreeCity_Text_UsedDevonScopePokemonFled:
	.string "{PLAYER} usó el DEVON SCOPE.\p"
	.string "¡Un POKéMON invisible se volvió\n"
	.string "visible!\p"
	.string "¡El POKéMON huyó asustado!$"

FortreeCity_Text_CitySign:
	.string "CIUDAD FORTREE\n"
	.string "“La ciudad en las copas que juega\l"
	.string "con la naturaleza.”$"

FortreeCity_Text_GymSign:
	.string "GIMNASIO POKéMON DE FORTREE\n"
	.string "LÍDER: WINONA\p"
	.string "“La usuaria de aves que vuela por\n"
	.string "todo el mundo.”$"
