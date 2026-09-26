MahoganyTown_Gym_MapScripts::
	.byte 0


MahoganyTown_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM,  MahoganyTown_Gym_EventScript_Statue2
	msgbox MahoganyTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_EventScript_Statue2::
	msgbox MahoganyTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON DE PUEBLO CAOBA$"

MahoganyTown_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE PUEBLO CAOBA\p"
	.string "ENTRENADORES DE PRYCE:\n"
	.string "{PLAYER}$"


MahoganyTown_GymEventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MahoganyTown_Gym_EventScript_GymGuy2
	msgbox MahoganyTown_Gym_Text_Guide, MSGBOX_DEFAULT
	closemessage
	release
	end
	
MahoganyTown_Gym_EventScript_GymGuy2::
	msgbox MahoganyTown_Gym_Text_GuideWin, MSGBOX_DEFAULT
	release
	end	

MahoganyTown_Gym_EventScript_Ronald::
	trainerbattle_single TRAINER_RONALD MahoganyTown_Gym_Text_BoarderRonaldSeen, MahoganyTown_Gym_Text_BoarderRonaldBeaten
	msgbox MahoganyTown_Gym_Text_BoarderRonaldAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Brad::
	trainerbattle_single TRAINER_BRAD MahoganyTown_Gym_Text_BoarderBradSeen, MahoganyTown_Gym_Text_BoarderBradBeaten
	msgbox MahoganyTown_Gym_Text_BoarderBradAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Douglas::
	trainerbattle_single TRAINER_DOUGLAS MahoganyTown_Gym_Text_BoarderDouglasSeen, MahoganyTown_Gym_Text_BoarderDouglasBeaten
	msgbox MahoganyTown_Gym_Text_BoarderDouglasAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE MahoganyTown_Gym_Text_SkierRoxanneSeen, MahoganyTown_Gym_Text_SkierRoxanneBeaten
	msgbox MahoganyTown_Gym_Text_SkierRoxanneAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Clarissa::
	trainerbattle_single TRAINER_CLARISSA MahoganyTown_Gym_Text_SkierClarissaSeen, MahoganyTown_Gym_Text_SkierClarissaBeaten
	msgbox MahoganyTown_Gym_Text_SkierClarissaAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Pryce::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MahoganyTown_Gym_EventScript_Pryce_Defeated
	msgbox MahoganyTown_Gym_Text_PryceIntro, MSGBOX_DEFAULT
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, MahoganyTown_Gym_EventScript_OlivineCheckCianwood
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, MahoganyTown_Gym_EventScript_CianwoodCheckOlivine
	goto MahoganyTown_Gym_EventScript_Pryce_Battle1

MahoganyTown_Gym_EventScript_PryceVictory::
	message MahoganyTown_Gym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MahoganyTown_Gym_Text_GlacierBadgeSpeech, MSGBOX_DEFAULT
	setflag FLAG_BADGE07_GET
	setflag FLAG_DEFEATED_MAHOGANY_TOWN_GYM
    addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	giveitem ITEM_TM_HAIL
	msgbox MahoganyTown_Gym_Text_HailSpeech, MSGBOX_DEFAULT
	setvar VAR_MAHOGANY_TOWN_STATE, 15
    setrespawn HEAL_LOCATION_MAHOGANYTOWN
	closemessage
	release
	end

MahoganyTown_Gym_EventScript_OlivineCheckCianwood::
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, MahoganyTown_Gym_EventScript_Pryce_Battle3
	goto MahoganyTown_Gym_EventScript_Pryce_Battle2

MahoganyTown_Gym_EventScript_CianwoodCheckOlivine::
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, MahoganyTown_Gym_EventScript_Pryce_Battle3
	goto MahoganyTown_Gym_EventScript_Pryce_Battle2
	
MahoganyTown_Gym_EventScript_Pryce_Battle1::
	trainerbattle_no_intro TRAINER_PRYCE_1, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Battle2::
	trainerbattle_no_intro TRAINER_PRYCE_1_2, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Battle3::
	trainerbattle_no_intro TRAINER_PRYCE_1_3, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Defeated::
	msgbox MahoganyTown_Gym_Text_CherishPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_PryceIntro:
    .string "Los POKéMON viven muchas cosas\n"
    .string "en su vida, igual que nosotros.\p"
    .string "Yo también he visto y sufrido\n"
    .string "mucho en mi vida.\p"
    .string "Como soy mayor, deja que te\n"
    .string "muestre a qué me refiero.\p"
    .string "He estado con POKéMON desde\n"
    .string "antes de que nacieras.\p"
    .string "No pierdo fácilmente.\p"
    .string "¡Yo, PRYCE, el entrenador de\n"
    .string "invierno, mostraré mi poder!$"

MahoganyTown_Gym_Text_PryceImpressed:
    .string "Ah, me impresiona tu\n"
    .string "destreza.\p"
    .string "Con tu voluntad, sé que\n"
    .string "superarás todo obstáculo.\p"
    .string "¡Eres digno de esta MEDALLA!$"

MahoganyTown_Gym_Text_ReceivedBadge:
    .string "{PLAYER} recibió MEDALLA GLACIAR.$"

MahoganyTown_Gym_Text_GlacierBadgeSpeech:
    .string "Esa MEDALLA subirá el ATAQUE\n"
    .string "ESPECIAL de los POKéMON.\p"
    .string "Permite que usen REMOLINO para\n"
    .string "cruzar\l"
    .string "remolinos reales.\p"
    .string "Y esto... ¡Es un regalo mío!$"

MahoganyTown_Gym_Text_HailSpeech:
    .string "Esa MT contiene GRANIZO.\p"
    .string "Causa daño cada\n"
    .string "turno por 5 turnos.\p"
    .string "Demuestra la dureza\n"
    .string "del invierno.$"

MahoganyTown_Gym_Text_CherishPokemon:
    .string "Cuando el hielo y nieve se funden,\n"
    .string "llega la primavera.\p"
    .string "Tú y tus POKéMON estarán\n"
    .string "juntos por muchos años.\p"
    .string "¡Valoren su tiempo juntos!$"

MahoganyTown_Gym_Text_PryceRematch:
    .string "¡Ah, CAMPEÓN DE JOHTO!\p"
    .string "Tus habilidades son\n"
    .string "realmente notables.\p"
    .string "Estoy impresionado.\p"
    .string "Pero aún hay mucho que\n"
    .string "aprender el uno del otro.\p"
    .string "Yo, PRYCE, el experto en invierno,\n"
    .string "aún tengo algunos trucos.\p"
    .string "¿Quieres una revancha?$"

MahoganyTown_Gym_Text_PryceRematchDefeat:
    .string "Ah, una vez más me impresiona\n"
    .string "tu destreza.\p"
    .string "Con tu voluntad, sé que\n"
    .string "superarás todo obstáculo.$"

MahoganyTown_Gym_Text_Guide:
    .string "PRYCE es un veterano que ha\n"
    .string "entrenado POKéMON por 50 años.\p"
    .string "Tiene un equipo sólido de\n"
    .string "POKéMON para cubrir cualquier\l"
    .string "cosa que uses.\p"
    .string "El fuego es buen comienzo,\n"
    .string "¡pero cuidado con la lluvia!$"

MahoganyTown_Gym_Text_GuideWin:
    .string "PRYCE es increíble, ¡pero tú\n"
    .string "lo eres aún más!\p"
    .string "¡Fue una batalla ardiente que\n"
    .string "unió a dos generaciones!$"

MahoganyTown_Gym_Text_BoarderRonaldSeen:
    .string "¡Congelaré a tus POKéMON\n"
    .string "para que no puedas hacer nada!$"

MahoganyTown_Gym_Text_BoarderRonaldBeaten:
    .string "Rayos. No pude hacer nada.$"

MahoganyTown_Gym_Text_BoarderRonaldAfter:
    .string "Creo que hay un movimiento que\n"
    .string "un POKéMON puede usar aunque\l"
    .string "esté congelado.$"

MahoganyTown_Gym_Text_BoarderBradSeen:
    .string "Este GIMNASIO tiene el suelo\p"
    .string "resbaladizo. Es divertido, ¿no?\p"
    .string "Pero bueno, ¡aquí no hemos\n"
    .string "venido a jugar!$"

MahoganyTown_Gym_Text_BoarderBradBeaten:
    .string "¿Ves lo serios que somos?$"

MahoganyTown_Gym_Text_BoarderBradAfter:
    .string "Este GIMNASIO es genial.\n"
    .string "¡Amo patinar con mis\l"
    .string "POKéMON!$"

MahoganyTown_Gym_Text_BoarderDouglasSeen:
    .string "Sé el secreto de PRYCE.$"

MahoganyTown_Gym_Text_BoarderDouglasBeaten:
    .string "Bien. Te diré el secreto de PRYCE.$"

MahoganyTown_Gym_Text_BoarderDouglasAfter:
    .string "El secreto del poder de PRYCE...\p"
    .string "Medita bajo una cascada\n"
    .string "cada día para fortalecer su mente\l"
    .string "y cuerpo.$"

MahoganyTown_Gym_Text_SkierRoxanneSeen:
    .string "Para llegar a PRYCE, el LÍDER,\n"
    .string "piensa antes de patinar.$"

MahoganyTown_Gym_Text_SkierRoxanneBeaten:
    .string "¡No perdería contra ti esquiando!$"

MahoganyTown_Gym_Text_SkierRoxanneAfter:
    .string "Si no patinas con precisión,\n"
    .string "no llegarás lejos en este GIMNASIO.$"

MahoganyTown_Gym_Text_SkierClarissaSeen:
    .string "¡Mira mi giro paralelo!$"

MahoganyTown_Gym_Text_SkierClarissaBeaten:
    .string "¡No! ¡Hice que me cayera!$"

MahoganyTown_Gym_Text_SkierClarissaAfter:
    .string "No debí presumir\n"
    .string "de mi esquí…$"

