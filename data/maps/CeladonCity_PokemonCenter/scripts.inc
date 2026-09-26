.set LOCALID_NURSE, 1

CeladonCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeladonCity_PokemonCenter_OnTransition
	.byte 0

CeladonCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_CELADON_CITY
	end

CeladonCity_PokemonCenter_EventScript_CooltrainerF::
	msgbox CeladonCity_PokemonCenter1F_Text_CooltrainerF, MSGBOX_NPC
	end

CeladonCity_PokemonCenter_EventScript_Pharmacist::
	msgbox CeladonCity_PokemonCenter1F_Text_Pharmacist, MSGBOX_NPC
	end

CeladonCity_PokemonCenter_EventScript_Eusine::
	msgbox Celadon_Text_Eusine1, MSGBOX_NPC
	end

CeladonCity_PokemonCenter1F_Text_CooltrainerF:
	.string "ERIKA es maestra de los POKéMON\n"
	.string "de planta.\p"
	.string "Te hará pagar si no tienes\n"
	.string "cuidado.$"

CeladonCity_PokemonCenter1F_Text_Pharmacist:
	.string "La base del TEAM ROCKET está en el\n"
	.string "sótano del CASINO.\p"
	.string "Ah, espera. Eso fue hace tres\n"
	.string "años.$"

Celadon_Text_Eusine1:
	.string "EUSINE: ¡Hola!\p"
	.string "He vuelto a visitar mi pueblo.\p"
	.string "Ha pasado bastante tiempo.$"

Celadon_Text_EusineLeaves:
	.string "{PLAYER}, ¿te has enterado?\p"
	.string "Hay rumores de un POKéMON\n"
	.string "de colores del arcoíris\n"
	.string "en la TORRE CAMPANA.\p"
	.string "Ya curé a mi equipo,\n"
	.string "así que voy a CIUDAD IRIS.\p"
	.string "¡Nos vemos, {PLAYER}!$"

Celadon_Text_NoBeasts:
	.string "Ah, por cierto, {PLAYER}.\p"
	.string "¿Atrapaste a los legendarios\n"
	.string "RAIKOU y ENTEI?\p"
	.string "<……><……><……>\p"
	.string "Está bien...\p"
	.string "Si atrapas aunque sea uno,\n"
	.string "espero que me avises.\p"
	.string "¡Cuento contigo, {PLAYER}!$"
