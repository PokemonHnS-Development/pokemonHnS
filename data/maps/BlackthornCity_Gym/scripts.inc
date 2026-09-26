BlackthornCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, BlackthornGym_OnLoad
	.byte 0

BlackthornGym_OnLoad::
	call_if_eq VAR_BLACKTHORN_GYM_STATE, 1, BlackthornGym_MapScript_Var1
	call_if_eq VAR_BLACKTHORN_GYM_STATE, 2, BlackthornGym_MapScript_Var2
	call_if_eq VAR_BLACKTHORN_GYM_STATE, 3, BlackthornGym_MapScript_Var3
	call_if_eq VAR_BLACKTHORN_GYM_STATE, 4, BlackthornGym_MapScript_Var4
	end

BlackthornGym_MapScript_Var1::
	call BlackthornGym_MapScript_BuildBridge1
	end

BlackthornGym_MapScript_Var2::
	call BlackthornGym_MapScript_BuildBridge1
	call BlackthornGym_MapScript_BuildBridge2
	end

BlackthornGym_MapScript_Var3::
	call BlackthornGym_MapScript_BuildBridge1
	call BlackthornGym_MapScript_BuildBridge2
	call BlackthornGym_MapScript_BuildBridge3
	end

BlackthornGym_MapScript_Var4::
	call BlackthornGym_MapScript_BuildBridge1
	call BlackthornGym_MapScript_BuildBridge2
	call BlackthornGym_MapScript_BuildBridge3
	call BlackthornGym_MapScript_BuildBridge4
	end

BlackthornGym_TriggerBridge1::
	call BlackthornGym_MapScript_BuildBridge1
	playse SE_BANG
	special DrawWholeMapView
	setvar VAR_BLACKTHORN_GYM_STATE, 1
	end

BlackthornGym_MapScript_BuildBridge1::
	setmetatile 19, 47, 0x35A, FALSE
	setmetatile 19, 48, 0x35A, FALSE
	setmetatile 19, 49, 0x35A, FALSE
	setmetatile 19, 50, 0x35A, FALSE
	setmetatile 19, 51, 0x35A, FALSE
	setmetatile 19, 52, 0x35A, FALSE
	setmetatile 19, 53, 0x35A, FALSE
	setmetatile 19, 54, 0x35A, FALSE
	setmetatile 20, 47, 0x35A, FALSE
	setmetatile 20, 48, 0x35A, FALSE
	setmetatile 20, 49, 0x35A, FALSE
	setmetatile 20, 50, 0x35A, FALSE
	setmetatile 20, 51, 0x35A, FALSE
	setmetatile 20, 52, 0x35A, FALSE
	setmetatile 20, 53, 0x35A, FALSE
	setmetatile 20, 54, 0x35A, FALSE
	setmetatile 21, 47, 0x35A, FALSE
	setmetatile 21, 48, 0x35A, FALSE
	setmetatile 21, 49, 0x35A, FALSE
	setmetatile 21, 50, 0x35A, FALSE
	setmetatile 21, 51, 0x35A, FALSE
	setmetatile 21, 52, 0x35A, FALSE
	setmetatile 21, 53, 0x35A, FALSE
	setmetatile 21, 54, 0x35A, FALSE
	return

BlackthornGym_TriggerBridge2::
	call BlackthornGym_MapScript_BuildBridge2
	playse SE_BANG
	special DrawWholeMapView
	setvar VAR_BLACKTHORN_GYM_STATE, 2
	end

BlackthornGym_MapScript_BuildBridge2::
	setmetatile 17, 35, 0x35A, FALSE
	setmetatile 17, 36, 0x35A, FALSE
	setmetatile 17, 37, 0x35A, FALSE
	setmetatile 17, 38, 0x35A, FALSE
	setmetatile 17, 39, 0x35A, FALSE
	setmetatile 17, 40, 0x35A, FALSE
	setmetatile 18, 35, 0x35A, FALSE
	setmetatile 18, 36, 0x35A, FALSE
	setmetatile 18, 37, 0x35A, FALSE
	setmetatile 18, 38, 0x35A, FALSE
	setmetatile 18, 39, 0x35A, FALSE
	setmetatile 18, 40, 0x35A, FALSE
	setmetatile 19, 35, 0x35A, FALSE
	setmetatile 19, 36, 0x35A, FALSE
	setmetatile 19, 37, 0x35A, FALSE
	setmetatile 19, 38, 0x35A, FALSE
	setmetatile 19, 39, 0x35A, FALSE
	setmetatile 19, 40, 0x35A, FALSE
	setmetatile 20, 32, 0x359, FALSE
	setmetatile 21, 32, 0x359, FALSE
	setmetatile 22, 32, 0x359, FALSE
	setmetatile 20, 35, 0x361, TRUE
	setmetatile 21, 35, 0x361, TRUE
	setmetatile 22, 35, 0x361, TRUE
	setmetatile 20, 33, 0x35A, FALSE
	setmetatile 20, 34, 0x35A, FALSE
	setmetatile 21, 33, 0x35A, FALSE
	setmetatile 21, 34, 0x35A, FALSE
	setmetatile 22, 33, 0x35A, FALSE
	setmetatile 22, 34, 0x35A, FALSE
	return

BlackthornGym_TriggerBridge3::
	call BlackthornGym_MapScript_BuildBridge3
	playse SE_BANG
	special DrawWholeMapView
	setvar VAR_BLACKTHORN_GYM_STATE, 3
	end

BlackthornGym_MapScript_BuildBridge3::
	setmetatile 17, 26, 0x359, FALSE
	setmetatile 18, 26, 0x359, FALSE
	setmetatile 19, 26, 0x359, FALSE
	setmetatile 20, 26, 0x359, FALSE
	setmetatile 21, 26, 0x359, FALSE
	setmetatile 22, 26, 0x359, FALSE
	setmetatile 23, 26, 0x359, FALSE

	setmetatile 17, 29, 0x361, TRUE
	setmetatile 18, 29, 0x361, TRUE
	setmetatile 19, 29, 0x361, TRUE
	setmetatile 20, 29, 0x361, TRUE
	setmetatile 21, 29, 0x361, TRUE
	setmetatile 22, 29, 0x361, TRUE
	setmetatile 23, 29, 0x361, TRUE

	setmetatile 17, 27, 0x35A, FALSE
	setmetatile 17, 28, 0x35A, FALSE
	setmetatile 18, 27, 0x35A, FALSE
	setmetatile 18, 28, 0x35A, FALSE
	setmetatile 19, 27, 0x35A, FALSE
	setmetatile 19, 28, 0x35A, FALSE
	setmetatile 20, 27, 0x35A, FALSE
	setmetatile 20, 28, 0x35A, FALSE
	setmetatile 21, 27, 0x35A, FALSE
	setmetatile 21, 28, 0x35A, FALSE
	setmetatile 22, 27, 0x35A, FALSE
	setmetatile 22, 28, 0x35A, FALSE
	setmetatile 23, 27, 0x35A, FALSE
	setmetatile 23, 28, 0x35A, FALSE
	return	

BlackthornGym_TriggerBridge4::
	call BlackthornGym_MapScript_BuildBridge4
	playse SE_BANG
	special DrawWholeMapView
	setvar VAR_BLACKTHORN_GYM_STATE, 4
	end

BlackthornGym_MapScript_BuildBridge4::
	setmetatile 19, 11, 0x35A, FALSE
	setmetatile 19, 12, 0x35A, FALSE
	setmetatile 19, 13, 0x35A, FALSE
	setmetatile 19, 14, 0x35A, FALSE
	setmetatile 19, 15, 0x35A, FALSE
	setmetatile 20, 11, 0x35A, FALSE
	setmetatile 20, 12, 0x35A, FALSE
	setmetatile 20, 13, 0x35A, FALSE
	setmetatile 20, 14, 0x35A, FALSE
	setmetatile 20, 15, 0x35A, FALSE
	setmetatile 21, 11, 0x35A, FALSE
	setmetatile 21, 12, 0x35A, FALSE
	setmetatile 21, 13, 0x35A, FALSE
	setmetatile 21, 14, 0x35A, FALSE
	setmetatile 21, 15, 0x35A, FALSE
	return


BlackthornGym_EventScript_Cody::
	trainerbattle_single TRAINER_CODY BlackthornGym_Text_CooltrainermCodySeenText, BlackthornGym_Text_CooltrainermCodyBeatenText
	msgbox BlackthornGym_Text_CooltrainermCodyAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Fran::
	trainerbattle_single TRAINER_FRAN BlackthornGym_Text_CooltrainerfFranSeenText, BlackthornGym_Text_CooltrainerfFranBeatenText
	msgbox BlackthornGym_Text_CooltrainerfFranAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Paul::
	trainerbattle_single TRAINER_PAUL BlackthornGym_Text_CooltrainermPaulSeenText, BlackthornGym_Text_CooltrainermPaulBeatenText
	msgbox BlackthornGym_Text_CooltrainermPaulAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Mike::
	trainerbattle_single TRAINER_MIKE BlackthornGym_Text_CooltrainermMikeSeenText, BlackthornGym_Text_CooltrainermMikeBeatenText
	msgbox BlackthornGym_Text_CooltrainermMikeAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Lola::
	trainerbattle_single TRAINER_LOLA BlackthornGym_Text_CooltrainerfLolaSeenText, BlackthornGym_Text_CooltrainerfLolaBeatenText
	msgbox BlackthornGym_Text_CooltrainerfLolaAfterBattleText, MSGBOX_AUTOCLOSE
	end


BlackthornGym_EventScript_Clair::
	lock
	faceplayer
	goto_if_set FLAG_IS_CHAMPION, BlackthornGym_EventScript_ClairAfterLeague
	goto_if_ge VAR_BLACKTHORN_CITY_STATE, 4, BlackthornGym_EventScript_Clair_Defeated
	goto_if_eq VAR_BLACKTHORN_CITY_STATE, 2, BlackthornGym_EventScript_ClairDuringChallenge
	msgbox BlackthornGym_Text_ClairIntroText, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_CLAIR_1, BlackthornGym_Text_ClairWinText
	msgbox BlackthornGym_Text_ClairText_GoToDragonsDen, MSGBOX_DEFAULT
	setvar VAR_0x8008, 8
	call Common_EventScript_SetGymTrainers
	setvar VAR_BLACKTHORN_CITY_STATE, 2
	closemessage
	release
	end

BlackthornGym_EventScript_ClairDuringChallenge::
	msgbox BlackthornGym_Text_ClairText_TooMuchToExpect, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_EventScript_Clair_Defeated::
	msgbox BlackthornGym_Text_ClairText_League, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_EventScript_ClairAfterLeague::
	msgbox BlackthornGym_Text_ClairAfterLeague, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_Text_ClairIntroText:
    .string "Soy CLAIR.\p"
    .string "La mejor maestra dragón del mundo.\p"
    .string "Puedo luchar contra el ALTO MANDO\n"
    .string "de la LIGA POKéMON.\p"
    .string "¿Aún quieres enfrentarte a mí?\p"
    .string "...Bien. ¡Hagámoslo!\p"
    .string "¡Como LÍDER de GIMNASIO, usaré todo\n"
    .string "mi poder contra cualquier rival!$"

BlackthornGym_Text_ClairWinText:
    .string "¿Perdí?\p"
    .string "No lo creo. Debe haber\n"
    .string "algún error...$"

BlackthornGym_Text_ClairText_GoToDragonsDen:
    .string "No lo admitiré.\p"
    .string "Perdí, pero aún no estás listo\n"
    .string "para la LIGA POKéMON.\p"
    .string "Lo sé. Deberías aceptar el reto\n"
    .string "de los usuarios de dragones.\p"
    .string "Tras este GIMNASIO está el lugar\n"
    .string "llamado GUARIDA DRAGÓN.\p"
    .string "Hay un pequeño altar en el centro.\n"
    .string "Ve allí.\p"
    .string "Si pruebas que dejaste atrás tus\n"
    .string "ideales perezosos, te reconoceré\l"
    .string "como un ENTRENADOR digno de una\l"
    .string "MEDALLA de GIMNASIO!$"

BlackthornGym_Text_ClairText_TooMuchToExpect:
    .string "¿Qué pasa?\p"
    .string "¿Es demasiado pedirte a ti?$"

BlackthornGym_Text_ClairText_YouKeptMeWaiting:
    .string "¡Me has hecho esperar!\p"
    .string "¡Toma! ¡Toma esto!$"

BlackthornGym_Text_ClairText_DescribeTM:
    .string "Contiene GARRA DRAGÓN.\p"
    .string "Ya descubrirás para qué sirve.$"

BlackthornGym_Text_ClairText_League:
    .string "¿Qué pasa?\p"
    .string "¿No vas camino a la LIGA\n"
    .string "POKéMON?\p"
    .string "¿No sabes dónde queda?\p"
    .string "Ve a PUEBLO PRIMAVERA.\p"
    .string "Luego usa SURF al este. Esa ruta\n"
    .string "es muy dura.\p"
    .string "¡No te atrevas a perder en la LIGA\n"
    .string "POKéMON!\p"
    .string "¡Si lo haces, me sentiré peor por\n"
    .string "haber perdido contra ti!\p"
    .string "¡Da todo lo que tengas!$"

BlackthornGym_Text_ClairAfterLeague:
    .string "Lo lograste, ¿eh?\p"
    .string "Ahora eres el CAMPEÓN de JOHTO.$"

BlackthornGym_Text_ClairRematchText:
    .string "Lo lograste, ¿eh?\p"
    .string "Ahora eres el CAMPEÓN DE JOHTO.\p"
    .string "Probaste tu fuerza, pero ¿puedes\n"
    .string "vencerme otra vez?\p"
    .string "Como Maestro Dragón, no me\n"
    .string "contendré.\p"
    .string "No esta vez.\p"
    .string "¿Quieres una revancha?$"

BlackthornGym_Text_ClairRematchDefeatText:
    .string "¿Perdí?\p"
    .string "¿Otra vez?\p"
    .string "No lo creo. Debe haber\n"
    .string "algún error…$"

BlackthornGym_Text_CooltrainermCodySeenText:
    .string "¡Ya puedo usar POKéMON de tipo\n"
    .string "DRAGÓN!$"

BlackthornGym_Text_CooltrainermCodyBeatenText:
    .string "¡Rayos! ¡Ojalá tuviera un DRAGONITE!$"

BlackthornGym_Text_CooltrainermCodyAfterBattleText:
    .string "Los miembros de nuestro clan\n"
    .string "solo usan POKéMON dragón si el\l"
    .string "MAESTRO lo permite.$"

BlackthornGym_Text_CooltrainerfFranSeenText:
    .string "¡No dejaré pasar a un\n"
    .string "entrenador desconocido!\p"
    .string "¡CLAIR se enfurecería!$"

BlackthornGym_Text_CooltrainerfFranBeatenText:
    .string "Aww… perdí…$"

BlackthornGym_Text_CooltrainerfFranAfterBattleText:
    .string "Oh no… CLAIR se va a enojar…$"

BlackthornGym_Text_CooltrainermPaulSeenText:
    .string "¿Tu primera batalla de dragones?\p"
    .string "¡Verás lo fuertes que son!$"

BlackthornGym_Text_CooltrainermPaulBeatenText:
    .string "¿Perdió mi POKéMON dragón?$"

BlackthornGym_Text_CooltrainermPaulAfterBattleText:
    .string "¿LANCE dijo que quiere\n"
    .string "verte de nuevo?\p"
    .string "¡Ni hablar!$"

BlackthornGym_Text_CooltrainermMikeSeenText:
    .string "¿Mi probabilidad de perder?\n"
    .string "¡Ni un solo por ciento!$"

BlackthornGym_Text_CooltrainermMikeBeatenText:
    .string "Qué extraño.$"

BlackthornGym_Text_CooltrainermMikeAfterBattleText:
    .string "Ya sé cuáles son mis fallas.\p"
    .string "¡Gracias por mostrármelas!$"

BlackthornGym_Text_CooltrainerfLolaSeenText:
    .string "Los dragones son sagrados.\p"
    .string "Tienen mucha energía vital.\p"
    .string "Si no vas en serio, no podrás\n"
    .string "vencerlos.$"

BlackthornGym_Text_CooltrainerfLolaBeatenText:
    .string "¡Así se hace!$"

BlackthornGym_Text_CooltrainerfLolaAfterBattleText:
    .string "Los Dragón son débiles ante los\n"
    .string "movimientos tipo DRAGÓN.$"

BlackthornGym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_BLACKTHORN_GYM, EcruteakCity_Gym_EventScript_GymGuy2
	msgbox BlackthornGym_Text_GuideText, MSGBOX_DEFAULT
	closemessage
	release
	end
	
BlackthornGym_EventScript_GymGuy2::
	msgbox BlackthornGym_Text_GuideWinText, MSGBOX_DEFAULT
	release
	end	

BlackthornGym_Text_GuideText:
    .string "¡Hola! ¡Futuro CAMPEÓN!\p"
    .string "Ha sido un viaje largo, pero ya\n"
    .string "¡estamos casi listos! ¡Cuenta conmigo!\p"
    .string "Aunque CLAIR admira al Maestro\n"
    .string "Dragón, LANCE, ella ha logrado\l"
    .string "crear su propia identidad con\l"
    .string "un equipo de dragones del\l"
    .string "mar.\p"
    .string "Se supone que los dragones son\n"
    .string "débiles ante ataques de HIELO,\l"
    .string "pero necesitarás ataques tipo\l"
	.string "DRAGÓN o HADA si quieres\l"
    .string "ganar.$"
    .string "¡Tú puedes!$"

BlackthornGym_Text_GuideWinText:
    .string "¡Genial que vencieras a CLAIR!\p"
    .string "Solo queda el desafío de la\n"
    .string "LIGA POKéMON.\p"
    .string "¡Vas camino a convertirte en el\n"
    .string "CAMPEÓN POKéMON!$"


BlackthornGym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_BLACKTHORN_GYM, BlackthornGym_EventScript_Statue2
	msgbox BlackthornGym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_EventScript_Statue2::
	msgbox BlackthornGym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_Text_GymStatue:
	.string "GIMNASIO POKéMON CIUDAD ENDRINO$"

BlackthornGym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON CIUDAD ENDRINO\p"
	.string "ENTRENADORES DE CLAIR:\n"
	.string "{PLAYER}$"
