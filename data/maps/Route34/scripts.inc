.set LOCALID_ROUTE34_DAYCAREMAN, 12

Route34_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route34_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route34_OnTransition: 
	specialvar VAR_RESULT, GetDaycareState
	call_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route34_MapScript_EggReady
	callnative SetTimeBasedEncounters
	end	

Route34_MapScript_EggReady::
	setobjectxyperm LOCALID_ROUTE34_DAYCAREMAN, 30, 34
	return

Route34_EventScript_YoungsterSamuel::
	trainerbattle_single TRAINER_SAMUEL Route34_Text_YoungsterSamuel_Seen, Route34_Text_YoungsterSamuel_Beaten
	msgbox Route34_Text_YoungsterSamuel_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_YoungsterIan::
	trainerbattle_single TRAINER_IAN Route34_Text_YoungsterIan_Seen, Route34_Text_YoungsterIan_Beaten
	msgbox Route34_Text_YoungsterIan_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_CamperTodd::
	trainerbattle_single TRAINER_TODD Route34_Text_CamperTodd_Seen, Route34_Text_CamperTodd_Beaten
	msgbox Route34_Text_CamperTodd_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_PicnickerGina::
	trainerbattle_single TRAINER_GINA Route34_Text_PicnickerGina_Seen, Route34_Text_PicnickerGina_Beaten
	msgbox Route34_Text_PicnickerGina_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_OfficerKeith::
	trainerbattle_single TRAINER_KEITH Route34_Text_OfficerKeith_Seen, Route34_Text_OfficerKeith_Win
	msgbox Route34_Text_OfficerKeith_After, MSGBOX_AUTOCLOSE
	end


Route34_EventScript_PokefanMBrandon::
	trainerbattle_single TRAINER_BRANDON Route34_Text_PokefanBrandon_Seen, Route34_Text_PokefanBrandon_Beaten
	msgbox Route34_Text_PokefanBrandon_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Irene::
	trainerbattle_single TRAINER_IRENE Route34_Text_CooltrainerIrene_Seen, Route34_Text_CooltrainerIrene_Beaten
	msgbox Route34_Text_CooltrainerIrene_After2, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Jenn::
	trainerbattle_single TRAINER_JENN Route34_Text_CooltrainerJenn_Seen, Route34_Text_CooltrainerJenn_Beaten
	msgbox Route34_Text_CooltrainerJenn_After2, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Kate::
	trainerbattle_single TRAINER_KATE Route34_Text_CooltrainerKate_Seen, Route34_Text_CooltrainerKate_Beaten
	msgbox Route34_Text_CooltrainerKate_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Sign1::
	lock
	msgbox Route34_Text_Sign_Route34, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Sign2::
	lock
	msgbox Route34_Text_Sign_DayCare, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Sign3::
	lock
	msgbox Route34_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Item_SoftSand::
	finditem ITEM_SOFT_SAND
	end

Route34_EventScript_Item_RareCandy::
	finditem ITEM_RARE_CANDY
	end

Route34_EventScript_Item_SuperPotion::
	finditem ITEM_SUPER_POTION
	end


Route34_Text_YoungsterSamuel_Seen:
	.string "¡Hola! ¡Busco a MANKEY!$"

Route34_Text_YoungsterSamuel_Beaten:
	.string "¡Me venció un desconocido!$"

Route34_Text_YoungsterSamuel_After:
	.string "Entrenaré aún más duro.\p"
	.string "Después de todo, quiero ser\n"
	.string "un LÍDER de GIMNASIO.$"

Route34_Text_YoungsterIan_Seen:
	.string "Soy el mejor de mi clase en\n"
	.string "POKéMON.$"

Route34_Text_YoungsterIan_Beaten:
	.string "¡No! Hay mejores entrenadores…$"

Route34_Text_YoungsterIan_After:
	.string "Me esfuerzo para ser la\n"
	.string "estrella de mi clase.$"

Route34_Text_CamperTodd_Seen:
	.string "Confío en mi habilidad para\n"
	.string "criar POKéMON.\p"
	.string "¿Quieres ver?$"

Route34_Text_CamperTodd_Beaten:
	.string "¿Fallé en mi entrenamiento?$"

Route34_Text_CamperTodd_After:
	.string "Tal vez lleve uno a la GUARDERÍA,\n"
	.string "o use algunos objetos…$"

Route34_Text_PicnickerGina_Seen:
	.string "¿Eres un ENTRENADOR?\p"
	.string "Tengamos una batalla de práctica.$"

Route34_Text_PicnickerGina_Beaten:
	.string "¡Oh, no! Simplemente no puedo ganar…$"

Route34_Text_PicnickerGina_After:
	.string "Eres muy fuerte para ser un\n"
	.string "compañero de práctica.$"

Route34_Text_OfficerKeith_Seen:
	.string "¿Quién anda ahí?\n"
	.string "¿Qué estás tramando?$"

Route34_Text_OfficerKeith_Win:
	.string "Eres un niño muy fuerte.$"

Route34_Text_OfficerKeith_After:
	.string "Sí, todo está bien hoy.\p"
	.string "Pórtate bien y evita problemas.$"

Route34_Text_OfficerKeith_Daytime:
	.string "Patrullo buscando personas\n"
	.string "sospechosas.$"

Route34_Text_PokefanBrandon_Seen:
	.string "Recuperé a mi POKéMON de la\n"
	.string "GUARDERÍA.\p"
	.string "¡Veamos cuánto ha crecido!$"

Route34_Text_PokefanBrandon_Beaten:
	.string "¿Por qué termina así?$"

Route34_Text_PokefanBrandon_After:
	.string "Mi POKéMON volvió con nuevos ataques.\p"
	.string "¡Eso me dejó muy sorprendido!$"

Route34_Text_Sign_IlexForest:
	.string "BOSQUE VERDE\n"
	.string "POR LA PUERTA$"

Route34_Text_Sign_Route34:
	.string "RUTA 34\n"
	.string "CIUDAD TRIGAL - PUEBLO AZALEA\p"
	.string "BOSQUE VERDE ESTÁ EN MEDIO$"

Route34_Text_TrainerTips:
	.string "CONSEJOS\p"
	.string "Los árboles de BAYAS dan BAYAS\n"
	.string "varias veces al día.\p"
	.string "Anota qué árbol da cada tipo\n"
	.string "de BAYA.$"

Route34_Text_CooltrainerIrene_Seen:
	.string "IRENE: ¡¿Quién eres?!$"

Route34_Text_CooltrainerIrene_Beaten:
	.string "IRENE: ¡Ohhh! ¡Eres muy fuerte!$"

Route34_Text_CooltrainerIrene_After1:
	.string "IRENE: ¡Mi hermana KATE se las\n"
	.string "pagará por esto!$"

Route34_Text_CooltrainerIrene_After2:
	.string "IRENE: ¿No es genial esta playa?\p"
	.string "¡Es nuestro refugio secreto!$"

Route34_Text_CooltrainerJenn_Seen:
	.string "JENN: ¿Pero qué...?\n"
	.string "¿Qué estás haciendo?$"

Route34_Text_CooltrainerJenn_Beaten:
	.string "JENN: ¡Lo siento, IRENE! ¡Hermanita!$"

Route34_Text_CooltrainerJenn_After1:
	.string "JENN: ¡No te confíes! ¡Mi hermana\n"
	.string "KATE es fuerte!$"

Route34_Text_CooltrainerJenn_After2:
	.string "JENN: La luz del sol hace que tu\n"
	.string "cuerpo sea más fuerte.$"

Route34_Text_CooltrainerKate_Seen:
	.string "KATE: ¡Debo pagarte por cuidar\n"
	.string "de mis hermanas!$"

Route34_Text_CooltrainerKate_Beaten:
	.string "KATE: ¡No! No puedo creer que perdí.$"

Route34_Text_CooltrainerKate_GiveSoftSand:
	.string "KATE: Eres muy fuerte.\n"
	.string "Perdimos sin excusas...\p"
	.string "¡Toma esto!$"

Route34_Text_CooltrainerKate_After:
	.string "KATE: Siento que te emboscáramos.\p"
	.string "No esperábamos que alguien nos\n"
	.string "hallara aquí. Nos asustaste.$"


Route34_Text_Sign_DayCare:
	.string "GUARDERÍA\p"
	.string "¡CUIDAMOS TUS POKéMON POR TI!$"
