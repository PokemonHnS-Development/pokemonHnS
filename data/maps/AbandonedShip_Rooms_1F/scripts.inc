AbandonedShip_Rooms_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SetTimeEncounters
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

AbandonedShip_Rooms_1F_EventScript_Gentleman::
	msgbox AbandonedShip_Rooms_1F_Text_TakingALookAround, MSGBOX_NPC
	end

AbandonedShip_Rooms_1F_EventScript_Demetrius::
	trainerbattle_single TRAINER_JULIA, AbandonedShip_Rooms_1F_Text_DemetriusIntro, AbandonedShip_Rooms_1F_Text_DemetriusDefeat
	msgbox AbandonedShip_Rooms_1F_Text_DemetriusPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_EventScript_Thalia::
	trainerbattle_single TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaIntro, AbandonedShip_Rooms_1F_Text_ThaliaDefeat, AbandonedShip_Rooms_1F_EventScript_RegisterThalia
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms_1F_EventScript_ThaliaRematch
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms_1F_EventScript_RegisterThalia::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_THALIA_1
	release
	end

AbandonedShip_Rooms_1F_EventScript_ThaliaRematch::
	trainerbattle_rematch TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro, AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_Text_TakingALookAround:
	.string "Barcos así son raros, así que estoy\n"
	.string "mirando el lugar.\p"
	.string "Hmhm...\n"
	.string "Parece que hay otras cabinas...$"

AbandonedShip_Rooms_1F_Text_ThaliaIntro:
	.string "¿Qué te impulsa a venir hasta aquí?\n"
	.string "¡Debes ser muy curioso!$"

AbandonedShip_Rooms_1F_Text_ThaliaDefeat:
	.string "No solo curioso, sino fuerte...$"

AbandonedShip_Rooms_1F_Text_ThaliaPostBattle:
	.string "El hombre de al lado...\p"
	.string "Dice que solo está de turismo,\n"
	.string "pero no estoy segura.$"

AbandonedShip_Rooms_1F_Text_ThaliaRegister:
	.string "¡Eres un TRAINER muy fuerte!\n"
	.string "¡Déjame registrarte de recuerdo!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro:
	.string "¿Qué te impulsa a volver aquí?\n"
	.string "¡Realmente eres muy curioso!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat:
	.string "¿No eres demasiado fuerte?$"

AbandonedShip_Rooms_1F_Text_ThaliaPostRematch:
	.string "¡Seguro que ese hombre trama algo!\n"
	.string "¡Actúa muy sospechosamente!$"

AbandonedShip_Rooms_1F_Text_DemetriusIntro:
	.string "¡Waaah!\n"
	.string "¡Me encontraron! ...¿Eh?$"

AbandonedShip_Rooms_1F_Text_DemetriusDefeat:
	.string "Ah, no eres mi mama.$"

AbandonedShip_Rooms_1F_Text_DemetriusPostBattle:
	.string "Tengo problemas con mi mamá y huí.\n"
	.string "¡No digas dónde estoy!$"

