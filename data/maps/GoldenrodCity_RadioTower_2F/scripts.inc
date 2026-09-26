GoldenrodCity_RadioTower_2F_MapScripts::
	.byte 0

GoldenrodRaidoTower2_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_3 GoldenrodCity_RadioTower_2F_Text_GruntM4Seen, GoldenrodCity_RadioTower_2F_Text_GruntM4Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM4After, MSGBOX_AUTOCLOSE
	end
GoldenrodRaidoTower2_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_4 GoldenrodCity_RadioTower_2F_Text_GruntM5Seen, GoldenrodCity_RadioTower_2F_Text_GruntM5Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM5After, MSGBOX_AUTOCLOSE
	end
GoldenrodRaidoTower2_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_5 GoldenrodCity_RadioTower_2F_Text_GruntM6Seen, GoldenrodCity_RadioTower_2F_Text_GruntM6Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM6After, MSGBOX_AUTOCLOSE
	end
GoldenrodRaidoTower2_EventScript_GruntF2::
	trainerbattle_single TRAINER_GRUNT_26 GoldenrodCity_RadioTower_2F_Text_GruntF2Seen, GoldenrodCity_RadioTower_2F_Text_GruntF2Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntF2After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_2F_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_SalesSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_OakTalkSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Boy::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Policeman::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_Policeman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Buena::
	lock
	faceplayer
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_2F_EventScript_Buena2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 7, GoldenrodCity_RadioTower_2F_EventScript_Buena2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 8, GoldenrodCity_RadioTower_2F_EventScript_Buena2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 9, GoldenrodCity_RadioTower_2F_EventScript_Buena2
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaShowPromo, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Buena2::
	msgbox RadioTower2FBuenaPasswordIsHelpText, MSGBOX_DEFAULT
	closemessage
	release
	end


GoldenrodCity_RadioTower_2F_EventScript_Teacher::
	lock
	faceplayer
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_2F_EventScript_Teacher2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 7, GoldenrodCity_RadioTower_2F_EventScript_Teacher2 
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 8, GoldenrodCity_RadioTower_2F_EventScript_Teacher2 
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 9, GoldenrodCity_RadioTower_2F_EventScript_Teacher2 
	msgbox GoldenrodCity_RadioTower_2F_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Teacher2::
	msgbox GoldenrodCity_RadioTower_2F_Text_TeacherRockets, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Jigglypuff::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	msgbox GoldenrodCity_RadioTower_2F_Text_Jigglypuff, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RadioTower2FBuenaPasswordIsHelpText:
	.string "BUENA: ¿Eh? ¿La clave de hoy?\n"
	.string "¡AYUDA, por supuesto!$"

GoldenrodCity_RadioTower_2F_Text_SuperNerd:
	.string "Puedes oír la radio\n"
	.string "donde sea. ¡Sintonízala!$"

GoldenrodCity_RadioTower_2F_Text_Policeman:
	.string "Acceso restringido más allá de\n"
	.string "este punto.$"

GoldenrodCity_RadioTower_2F_Text_Teacher:
	.string "Las canciones de cuna en la radio\n"
	.string "duermen a los POKéMON.$"

GoldenrodCity_RadioTower_2F_Text_TeacherRockets:
	.string "¿Por qué querrían apoderarse de\n"
	.string "la TORRE RADIO?$"

GoldenrodCity_RadioTower_2F_Text_Jigglypuff:
	.string "JIGGLYPUFF: Jiggly…$"

GoldenrodCity_RadioTower_2F_Text_BlackBelt1:
	.string "Lo siento. Solo personal autorizado\n"
	.string "más allá de aquí.\p"
	.string "Antes no era así.\p"
	.string "Algo pasa con el\n"
	.string "DIRECTOR…$"

GoldenrodCity_RadioTower_2F_Text_BlackBelt2:
	.string "Siéntete libre de mirar todo.\p"
	.string "El DIRECTOR es amable otra vez,\n"
	.string "como era antes.$"

GoldenrodCity_RadioTower_2F_Text_GruntM4Seen:
	.string "Hace tres años, TEAM ROCKET fue\n"
	.string "obligado a disolverse.\p"
	.string "¡Pero volveremos con fuerza!$"

GoldenrodCity_RadioTower_2F_Text_GruntM4Beaten:
	.string "¡Gwah! ¡No te hagas el listo!$"

GoldenrodCity_RadioTower_2F_Text_GruntM4After:
	.string "¡No dejaremos que arruines nuestros\n"
	.string "planes de regreso!$"

GoldenrodCity_RadioTower_2F_Text_GruntM5Seen:
	.string "¡Somos TEAM ROCKET, los explotadores\n"
	.string "de POKéMON!\p"
	.string "¡Amamos ser malos! ¿Tienes miedo?$"

GoldenrodCity_RadioTower_2F_Text_GruntM5Beaten:
	.string "¿Crees que eres un héroe?$"

GoldenrodCity_RadioTower_2F_Text_GruntM5After:
	.string "No siempre somos malos. Solo hacemos\n"
	.string "lo que nos da la gana.$"

GoldenrodCity_RadioTower_2F_Text_GruntM6Seen:
	.string "¡Oye, oye! ¡Quítate de nuestro camino!$"

GoldenrodCity_RadioTower_2F_Text_GruntM6Beaten:
	.string "Arggh. Me rindo.$"

GoldenrodCity_RadioTower_2F_Text_GruntM6After:
	.string "Nuestros EJECUTIVOS intentan tomar\n"
	.string "este lugar.\p"
	.string "Tienen un gran plan. Me pregunto\n"
	.string "¿cuál será?$"

GoldenrodCity_RadioTower_2F_Text_GruntF2Seen:
	.string "¡Jajaja!\p"
	.string "Qué aburrido. ¡Fue demasiado fácil\n"
	.string "tomar este lugar!\p"
	.string "¡Vamos, diviérteme!$"

GoldenrodCity_RadioTower_2F_Text_GruntF2Beaten:
	.string "¿Qu-quién eres tú?$"

GoldenrodCity_RadioTower_2F_Text_GruntF2After:
	.string "¡Me venciste y no lo olvidaré\n"
	.string "jamás!$"

GoldenrodCity_RadioTower_2F_Text_BuenaShowPromo:
	.string "BUENA: ¡Sintoniza mi SHOW de\n"
	.string "CONTRASEÑAS!$"

GoldenrodCity_RadioTower_2F_Text_SalesSign:
	.string "VENTAS 2F$"

GoldenrodCity_RadioTower_2F_Text_OakTalkSign:
	.string "CHARLA POKéMON DEL PROF.OAK\p"
	.string "¡El show más popular del aire!$"

GoldenrodCity_RadioTower_2F_Text_PokemonRadioSign:
	.string "Radio POKéMON en cualquier lugar$"
