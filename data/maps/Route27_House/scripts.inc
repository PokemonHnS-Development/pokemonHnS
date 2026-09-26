Route27_House_MapScripts::
	.byte 0

Route27_House_EventScript_Woman::
	lock
	faceplayer
	goto_if_unset FLAG_GOT_TM_SANDSTORM, Route27_House_EventScript_WomanBeforeGiven
	msgbox SandstormHouse_Text_TM37Description, MSGBOX_DEFAULT
	closemessage
	release
	end

Route27_House_EventScript_WomanBeforeGiven::
	msgbox SandstormHouse_Text_Woman1, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, Route27_House_EventScript_WomanHighFriendship
	playfirstmoncry
	applymovement OBJ_EVENT_ID_FOLLOWER FollowerLookAway
	waitmovement OBJ_EVENT_ID_FOLLOWER
	applymovement OBJ_EVENT_ID_FOLLOWER Common_Movement_QuestionMark
	waitmovement 0
	msgbox SandstormHouse_Text_DisloyalMon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route27_House_EventScript_WomanHighFriendship::
	playfirstmoncry
	applymovement OBJ_EVENT_ID_FOLLOWER FollowerDance
	waitmovement 0
	applymovement OBJ_EVENT_ID_FOLLOWER ContestHall_Movement_Heart
	waitmovement 0
	msgbox SandstormHouse_Text_LoyalMon, MSGBOX_DEFAULT
	giveitem ITEM_TM_SANDSTORM
	setflag FLAG_GOT_TM_SANDSTORM
	msgbox SandstormHouse_Text_TM37Description, MSGBOX_DEFAULT
	closemessage
	release
	end

Route27_Movement_FollowerJump:
	jump_in_place_down
	jump_in_place_down
	step_end

SandstormHouse_Text_Woman1:
    .string "¿A dónde vas con tus\n"
    .string "POKéMON?\p"
    .string "¿A la LIGA POKéMON?\p"
    .string "¿Tus POKéMON son lo bastante\n"
    .string "leales para ganar?\p"
    .string "Déjame ver...$"

SandstormHouse_Text_LoyalMon:
    .string "¡Ah! Tu POKéMON confía mucho\n"
    .string "en ti.\p"
    .string "Es bueno ver a un gran entrenador.\p"
    .string "Toma. Un regalo para tu viaje.$"

SandstormHouse_Text_TM37Description:
    .string "La MT37 es TORMENTA DE ARENA.\p"
    .string "Es un movimiento que daña a\n"
    .string "ambos luchadores.\p"
    .string "Es solo para entrenadores expertos.\p"
    .string "Úsala si te atreves. ¡Suerte!$"

SandstormHouse_Text_DisloyalMon:
    .string "Si no llega a confiar más en ti,\n"
    .string "será un camino difícil.\p"
    .string "La confianza es el vínculo entre\n"
    .string "POKéMON y entrenadores.$"


