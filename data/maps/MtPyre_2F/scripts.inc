MtPyre_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, MtPyre_2F_SetHoleWarp
	.byte 0

MtPyre_2F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_MT_PYRE_1F
	end

MtPyre_2F_EventScript_Woman::
	msgbox MtPyre_2F_Text_MemoriesOfSkitty, MSGBOX_NPC
	end

MtPyre_2F_EventScript_PokefanM::
	msgbox MtPyre_2F_Text_TumbledFromFloorAbove, MSGBOX_NPC
	end

MtPyre_2F_EventScript_Mark::
	trainerbattle_single TRAINER_MARK, MtPyre_2F_Text_MarkIntro, MtPyre_2F_Text_MarkDefeat
	msgbox MtPyre_2F_Text_MarkPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Luke::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_LukeIntro, MtPyre_2F_Text_LukeDefeat, MtPyre_2F_Text_LukeNotEnoughMons
	msgbox MtPyre_2F_Text_LukePostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Dez::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_DezIntro, MtPyre_2F_Text_DezDefeat, MtPyre_2F_Text_DezNotEnoughMons
	msgbox MtPyre_2F_Text_DezPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Leah::
	trainerbattle_single TRAINER_LEAH, MtPyre_2F_Text_LeahIntro, MtPyre_2F_Text_LeahDefeat
	msgbox MtPyre_2F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Zander::
	trainerbattle_single TRAINER_ZANDER, MtPyre_2F_Text_ZanderIntro, MtPyre_2F_Text_ZanderDefeat
	msgbox MtPyre_2F_Text_ZanderPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_Text_MemoriesOfSkitty:
	.string "Recuerdos de mi querido SKITTY…\n"
	.string "Lloro solo de pensarlo.$"

MtPyre_2F_Text_TumbledFromFloorAbove:
	.string "Ay, ay… Hay agujeros en el\n"
	.string "suelo por todas partes.\p"
	.string "No me fijé y me caí desde el\n"
	.string "piso de arriba.$"

MtPyre_2F_Text_MarkIntro:
	.string "¡Oye! ¿Buscas POKéMON?\n"
	.string "¡Llegaste después de mí! ¡Qué grosero!$"

MtPyre_2F_Text_MarkDefeat:
	.string "¡Ayieeeeh!\n"
	.string "¡Lo siento, perdóname, por favor!$"

MtPyre_2F_Text_MarkPostBattle:
	.string "Casi nadie viene aquí, así que\n"
	.string "creí que habría POKéMON raros.$"

MtPyre_2F_Text_LukeIntro:
	.string "LUKE: Estamos aquí por un reto.\p"
	.string "Jeje, si le muestro lo genial que soy,\n"
	.string "se enamorará de mí. ¡Lo sé!\p"
	.string "¡Ya sé! ¡Te aplastaré y le mostraré\n"
	.string "lo genial que soy!$"

MtPyre_2F_Text_LukeDefeat:
	.string "LUKE: ¡Ups!$"

MtPyre_2F_Text_LukePostBattle:
	.string "LUKE: ¡Perdimos, pero no importa!\n"
	.string "Estoy aquí a tu lado.\l"
	.string "¡Superaremos este reto!$"

MtPyre_2F_Text_LukeNotEnoughMons:
	.string "LUKE: Si quieres luchar,\n"
	.string "trae más POKéMON.\p"
	.string "¡Si no, no podré lucirme ante\n"
	.string "mi chica y ver qué tan genial soy!$"

MtPyre_2F_Text_DezIntro:
	.string "DEZ: Vine aquí por un reto con mi\n"
	.string "novio.\p"
	.string "Da miedo, pero estoy con él,\n"
	.string "así que todo está bien.\p"
	.string "¡Ya sé! ¡Haré que mi novio luzca\n"
	.string "genial venciéndote!$"

MtPyre_2F_Text_DezDefeat:
	.string "DEZ: ¡Waaaah! ¡Tengo miedo!$"

MtPyre_2F_Text_DezPostBattle:
	.string "DEZ: ¡Estamos muy enamorados,\n"
	.string "así que no importa si perdemos!$"

MtPyre_2F_Text_DezNotEnoughMons:
	.string "DEZ: Si quieres retarnos, trae al\n"
	.string "menos dos POKéMON.\p"
	.string "Mi novio es fuerte.\n"
	.string "Un solo POKéMON no bastará.$"

MtPyre_2F_Text_LeahIntro:
	.string "Eres un desconocido aquí...\n"
	.string "¡Vete antes de que pase algo malo!$"

MtPyre_2F_Text_LeahDefeat:
	.string "Hmm...\n"
	.string "Eres resistente.$"

MtPyre_2F_Text_LeahPostBattle:
	.string "Mi familia ha sido ENTRENADORA aquí\n"
	.string "desde tiempos de mi bisabuela...\p"
	.string "Es mi deber proteger esta\n"
	.string "montaña...$"

MtPyre_2F_Text_ZanderIntro:
	.string "¡Kiyaaaaah!\n"
	.string "¡Tengo terror!$"

MtPyre_2F_Text_ZanderDefeat:
	.string "¡Nooooooo!\n"
	.string "¡Perdí la razón!$"

MtPyre_2F_Text_ZanderPostBattle:
	.string "Me asusto cada vez que veo que\n"
	.string "algo se mueve…\p"
	.string "No debí venir aquí a entrenar…$"

