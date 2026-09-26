.set LOCALID_OWNER, 1

LilycoveCity_CoveLilyMotel_1F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_1F_EventScript_MotelOwner::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot, MSGBOX_DEFAULT
	applymovement LOCALID_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem, MSGBOX_DEFAULT
	applymovement LOCALID_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar, MSGBOX_DEFAULT
	applymovement LOCALID_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_BlockingTV::
	lockall
	playse SE_PIN
	applymovement LOCALID_OWNER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_OWNER, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV
	applymovement LOCALID_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer
	waitmovement 0
	applymovement LOCALID_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn
	waitmovement 0
	release
	end

LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV:
	face_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer:
	walk_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn:
	face_down
	walk_down
	face_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot:
	.string "Hm, ¿duplicaron los huéspedes al\n"
	.string "usar POKéMON como atracción?\p"
	.string "Hm, tal vez debería poner un POKéMON\n"
	.string "lindo como mascota del hotel.\p"
	.string "¿Atraerá eso a más huéspedes para\n"
	.string "que se queden con nosotros?$"

LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua:
	.string "¡Oh, perdón, perdón!\n"
	.string "¡Estaba muy concentrado en la TV!\p"
	.string "Desde que el TEAM AQUA llegó al\n"
	.string "pueblo, los turistas no vienen.$"

LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV:
	.string "¡Oye, quítate de enfrente!\n"
	.string "¡No puedo ver la TV!$"

LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem:
	.string "¡Increíble! ¿Me dices que un POKéMON\n"
	.string "halló el objeto perdido de alguien?\p"
	.string "Eso es genial. Si tuviéramos un\n"
	.string "POKéMON inteligente así...\p"
	.string "Podríamos recuperar cualquier cosa\n"
	.string "que los huéspedes pierdan...$"

LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted:
	.string "¡Oh, perdón, perdón!\n"
	.string "¡Estaba muy concentrado en la TV!\p"
	.string "Oí que alguien destruyó la\n"
	.string "GUARIDA DEL TEAM AQUA.\p"
	.string "Gracias a eso, un grupo grande\n"
	.string "acaba de hacer una reserva.\p"
	.string "Era una empresa llamada... eh...\n"
	.string "GAME algo...$"

LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar:
	.string "¡Increíble! ¿Un POKéMON cuidador\n"
	.string "atrapó a un ladrón?\p"
	.string "Eso es genial. Si tuviéramos un\n"
	.string "POKéMON fuerte de seguridad...\p"
	.string "Podríamos dar a nuestros huéspedes\n"
	.string "una mayor seguridad.$"

LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner:
	.string "¡Oh, perdón, perdón!\n"
	.string "Estaba muy concentrado en la TV.\p"
	.string "Ah, sí. Un grupo grande de huéspedes\n"
	.string "llegó hace un momento.\p"
	.string "Se registraron como GAME FREAK,\n"
	.string "así que deben hacer juegos.\p"
	.string "¡Uy! ¡Mejor me pongo a preparar\n"
	.string "su cena!$"

