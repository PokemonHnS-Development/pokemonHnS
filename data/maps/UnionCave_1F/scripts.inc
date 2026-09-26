UnionCave_1F_MapScripts::
	.byte 0


UnionCave_1F_Trigger_Monview::
	special SpawnCameraObject
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	message Route29_Text_PressAorB
	waitbuttonpress
	closemessage
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	special RemoveCameraObject
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	end


UnionCave_1F_EventScript_HikerRussell::
	trainerbattle_single TRAINER_RUSSELL, UnionCave_1F_Text_HikerRussellSeen, UnionCave_1F_Text_HikerRussellBeaten
	msgbox UnionCave_1F_Text_HikerRussellAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_PokemaniacLarry::
	trainerbattle_single TRAINER_LARRY, UnionCave_1F_Text_PokemaniacLarrySeen, UnionCave_1F_Text_PokemaniacLarryBeaten
	msgbox UnionCave_1F_Text_PokemaniacLarryAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_HikerDaniel::
	trainerbattle_single TRAINER_DANIEL, UnionCave_1F_Text_HikerDanielSeen, UnionCave_1F_Text_HikerDanielBeaten
	msgbox UnionCave_1F_Text_HikerDanielAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_FirebreatherBill::
	trainerbattle_single TRAINER_BILL, UnionCave_1F_Text_FirebreatherBillSeen, UnionCave_1F_Text_FirebreatherBillBeaten
	msgbox UnionCave_1F_Text_FirebreatherBillAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_FirebreatherRay::
	trainerbattle_single TRAINER_RAY, UnionCave_1F_Text_FirebreatherRaySeen, UnionCave_1F_Text_FirebreatherRayBeaten
	msgbox UnionCave_1F_Text_FirebreatherRayAfter, MSGBOX_AUTOCLOSE
	end	

UnionCave_1F_EventScript_Item_Potion::
	finditem ITEM_POTION
	end

UnionCave_1F_EventScript_Item_GreatBall::
	finditem ITEM_GREAT_BALL
	end

UnionCave_1F_EventScript_Item_Xattack::
	finditem ITEM_X_ATTACK
	end

UnionCave_1F_EventScript_Item_Awakening::
	finditem ITEM_AWAKENING
	end

UnionCave_1F_Text_HikerRussellSeen:
	.string "Vas hacia PUEBLO AZALEA, ¿verdad?\p"
	.string "Veré si eres lo bastante bueno\n"
	.string "para luchar.$"

UnionCave_1F_Text_HikerRussellBeaten:
	.string "¡Oh, oh, oh!$"

UnionCave_1F_Text_HikerRussellAfter:
	.string "¡Muy bien! Ya me decidí.\p"
	.string "¡No me iré hasta que mis POKéMON\n"
	.string "sean más fuertes!$"

UnionCave_1F_Text_PokemaniacLarrySeen:
	.string "Viajo por todas partes buscando\n"
	.string "POKéMON.\p"
	.string "¿Tú también buscas POKéMON?\p"
	.string "¡Entonces eres mi rival!$"

UnionCave_1F_Text_PokemaniacLarryBeaten:
	.string "Ugh. Mis pobres POKéMON…$"

UnionCave_1F_Text_PokemaniacLarryAfter:
	.string "Cada viernes se oyen rugidos de\n"
	.string "POKéMON dentro de la cueva.$"

UnionCave_1F_Text_HikerDanielSeen:
	.string "¡Vaya! ¡Qué sorpresa!\p"
	.string "¡No esperaba ver a nadie aquí!$"

UnionCave_1F_Text_HikerDanielBeaten:
	.string "¡Vaya! ¡Me han derrotado!$"

UnionCave_1F_Text_HikerDanielAfter:
	.string "Me estafaron con una\n"
	.string "COLA de SLOWPOKE.\p"
	.string "Siento pena por el POKéMON.$"

UnionCave_1F_Text_FirebreatherBillSeen:
	.string "El SUPERSONIDO de ZUBAT confunde\n"
	.string "a mi POKéMON.\p"
	.string "¡Eso me molesta mucho!$"

UnionCave_1F_Text_FirebreatherBillBeaten:
	.string "¡Me quedé sin fuerzas!$"

UnionCave_1F_Text_FirebreatherBillAfter:
	.string "Los fines de semana se oyen rugidos\n"
	.string "extraños en la cueva.$"

UnionCave_1F_Text_FirebreatherRaySeen:
	.string "Con luz, la cueva no da miedo.\p"
	.string "Si eres fuerte, los POKéMON no\n"
	.string "dan miedo.$"

UnionCave_1F_Text_FirebreatherRayBeaten:
	.string "¡FLASH!$"

UnionCave_1F_Text_FirebreatherRayAfter:
	.string "El fuego de mi POKéMON es lo que\n"
	.string "ilumina esta cueva.$"
