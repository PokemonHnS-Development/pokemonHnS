SeafoamIslands_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SeafoamIslands_Gym_OnTransition
	.byte 0

SeafoamIslands_Gym_OnTransition: 
	setflag FLAG_TEMP_1
	end

SeafoamIslands_Gym_EventScript_Blaine::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CINNABAR_ISLAND_GYM, SeafoamIslands_Gym_EventScript_Blaine_Defeated
	msgbox SeafoamIslands_Gym_Text_BlaineIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BLAINE, SeafoamIslands_Gym_Text_BlaineWinLoss
	message SeafoamIslands_Gym_Text_ReceivedVolcanoBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SeafoamIslands_Gym_Text_TM, MSGBOX_DEFAULT
	giveitem ITEM_TM_OVERHEAT
	setflag FLAG_BADGE15_GET
	setflag FLAG_DEFEATED_CINNABAR_ISLAND_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 15
	clearflag FLAG_HIDE_SEAFOAM_GYMGUY
	call Common_EventScript_SetGymTrainers
	closemessage
	release
	end

SeafoamIslands_Gym_EventScript_Blaine_Defeated::
	msgbox SeafoamIslands_Gym_Text_BlaineAfterBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

SeafomIslands2_EventScript_GymGuide::
	goto_if_set FLAG_TEMP_2, SeafomIslands2_EventScript_GymGuide2
	msgbox SeafoamIslands_Gym_Text_GymGuideWin, MSGBOX_NPC
	setflag FLAG_TEMP_2
	end
SeafomIslands2_EventScript_GymGuide2::
	msgbox SeafoamIslands_Gym_Text_GymGuideWin2, MSGBOX_NPC
	end

SeafoamIslands_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE15_GET, SeafoamIslands_Gym_EventScript_GymStatuePostVictory
	msgbox SeafoamIslands_Gym_Text_GymStatue
	releaseall
	end

SeafoamIslands_Gym_EventScript_GymStatuePostVictory::
	msgbox SeafoamIslands_Gym_Text_GymStatuePlayerWon
	releaseall
	end

SeafoamIslands_Gym_Text_GymStatue::
    .string "GIMNASIO POKéMON CANELA\n"
    .string "LÍDER: BLAINE\p"
	.string "GANADORES:\n"
	.string "BLUE, RED$"

SeafoamIslands_Gym_Text_GymStatuePlayerWon::
    .string "GIMNASIO POKéMON CANELA\n"
    .string "LÍDER: BLAINE\p"
    .string "GANADORES:\n"
	.string "BLUE, RED, {PLAYER}$"

SeafoamIslands_Gym_Text_TM:
	.string "Toma esto también. Esta MT tiene\n"
	.string "el increíble SOBRECALENTAR.\p"
	.string "¡Espero que tu rival tenga\n"
	.string "CURAQUEMADURAS extra! ¡Waaah!$"
SeafoamIslands_Gym_Text_BlaineIntro:
	.string "BLAINE: ¡Waaah!\p"
	.string "Mi GIMNASIO en CANELA ardió.\p"
	.string "Mis POKéMON de fuego y yo no\n"
	.string "tenemos hogar por el volcán.\p"
	.string "¡Waaah!\p"
	.string "Pero vuelvo a trabajar como LÍDER\n"
	.string "de GIMNASIO aquí en la cueva.\p"
	.string "Si me vences, te daré una\n"
	.string "MEDALLA.\p"
	.string "¡Ja! ¡Mejor ten CURAQUEMADURAS!$"

SeafoamIslands_Gym_Text_BlaineWinLoss:
	.string "BLAINE: Increíble. Me consumiste...\p"
	.string "¡Ganaste la MEDALLA VOLCÁN!$"

SeafoamIslands_Gym_Text_ReceivedVolcanoBadge:
	.string "{PLAYER} recibió MEDALLA VOLCÁN.$"

SeafoamIslands_Gym_Text_BlaineAfterBattle:
	.string "BLAINE: Perdí esta vez, pero\n"
	.string "ganaré la próxima.\p"
	.string "Cuando reconstruya mi GIMNASIO\n"
	.string "en CANELA, habrá una revancha.$"

SeafoamIslands_Gym_Text_BlaineFightDone:
	.string "BLAINE: Mis POKéMON de fuego\n"
	.string "serán aún más fuertes.\p"
	.string "¡Ya verás!$"

SeafoamIslands_Gym_Text_BlaineRematch:
	.string "BLAINE: ¡Vaya!\p"
	.string "¡Veo que te has vuelto el\n"
	.string "CAMPEÓN de KANTO!\p"
	.string "¡Eso es ardiente!\p"
	.string "Tus habilidades son supremas.\p"
	.string "Siempre estoy listo para luchar.\p"
	.string "¿Quieres una revancha conmigo?$"

SeafoamIslands_Gym_Text_BlaineRematchDefeat:
	.string "BLAINE: ¡Tus dotes son ardientes!\p"
	.string "Has incinerado todas mis\n"
	.string "defensas.$"

SeafoamIslands_Gym_Text_GymGuideWin:
	.string "¡Hola!\p"
	.string "... ¿Eh? ¿Ya terminó todo?\p"
	.string "¡Perdón, perdón!\p"
	.string "El GIMNASIO CINNABAR desapareció,\n"
	.string "no sabía dónde hallarte.\p"
	.string "Pero eres fuerte aun sin mis\n"
	.string "consejos. ¡Sabía que ganarías!$"

SeafoamIslands_Gym_Text_GymGuideWin2:
	.string "Un GIMNASIO POKéMON puede estar\n"
	.string "donde esté el LÍDER del GIMNASIO.\p"
	.string "No hace falta un edificio.$"
