ProfileMan_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_SYS_CHAT_USED, ProfileMan_EventScript_GivenProfileBefore
	msgbox ProfileMan_Text_CollectTrainerProfiles, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_AskToSeeProfile::
	msgbox ProfileMan_Text_MayISeeYourProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateProfile
	case 1, ProfileMan_EventScript_DeclineShowProfile
	case 2, ProfileMan_EventScript_Info
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineShowProfile
	end

ProfileMan_EventScript_Info::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_CreateProfile::
	msgbox ProfileMan_Text_LetsSeeItThen, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_CancelShowProfile::
	msgbox ProfileMan_Text_NotIntoItRightNow, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_ShowProfile::
	setvar VAR_0x8004, 0
	special ShowEasyChatProfile
	waitmessage
	delay 80
	msgbox ProfileMan_Text_FantasticProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_DeclineShowProfile::
	msgbox ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_GivenProfileBefore::
	msgbox ProfileMan_Text_YouHaveWonderfulSmile, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_AskToSeeNewProfile::
	msgbox ProfileMan_Text_MayISeeYourNewProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateNewProfile
	case 1, ProfileMan_EventScript_DeclineNewProfile
	case 2, ProfileMan_EventScript_InfoNewProfile
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineNewProfile
	end

ProfileMan_EventScript_InfoNewProfile::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_CreateNewProfile::
	msgbox ProfileMan_Text_EvenBetterThanLastProfile, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_DeclineNewProfile::
	msgbox ProfileMan_Text_LikeProfileWayItIs, MSGBOX_DEFAULT
	release
	end

@ Unused
ProfileMan_EventScript_Ret::
	return

ProfileMan_Text_CollectTrainerProfiles:
	.string "¡Hola, ENTRENADOR!\n"
	.string "Tienes una sonrisa maravillosa.\p"
	.string "Tengo un hobby: coleccionar los\n"
	.string "perfiles de ENTRENADORES POKéMON.$"

ProfileMan_Text_MayISeeYourProfile:
	.string "¿Qué te parece?\n"
	.string "¿Puedo ver tu perfil?$"

ProfileMan_Text_EasyChatExplanation:
	.string "Crea tu perfil uniendo cuatro\n"
	.string "palabras o frases.\p"
	.string "Mira, te daré un ejemplo de un\n"
	.string "perfil usando cuatro fragmentos.\p"
	.string "Puedes cambiar esos fragmentos por\n"
	.string "otros textos como quieras\l"
	.string "para crear tu propio perfil.\p"
	.string "Hay muchos fragmentos de texto\n"
	.string "que puedes usar.\p"
	.string "Están en grupos como POKéMON,\n"
	.string "estilos de vida y hobbies para\l"
	.string "que sea más fácil buscarlos.\p"
	.string "Primero, elige el grupo de texto\n"
	.string "para ver la lista de opciones.\p"
	.string "Luego, elige la que quieras.\p"
	.string "Repite esto con el resto y ya\n"
	.string "tendrás tu propio perfil.$"

ProfileMan_Text_LetsSeeItThen:
	.string "¡Sí! ¡Gracias!\n"
	.string "Entonces, ¡veámoslo!$"

ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile:
	.string "¿Ah, en serio?\p"
	.string "Imagino que alguien como tú tendría\n"
	.string "un perfil maravilloso…$"

ProfileMan_Text_NotIntoItRightNow:
	.string "¿Oh? ¿No te interesa ahora?\p"
	.string "¡Bueno, cuando quieras me parece bien!$"

ProfileMan_Text_YouHaveWonderfulSmile:
	.string "¡Hola, ENTRENADOR!\n"
	.string "Tienes una sonrisa maravillosa.$"

ProfileMan_Text_MayISeeYourNewProfile:
	.string "¿Puedo ver tu nuevo perfil?$"

ProfileMan_Text_EvenBetterThanLastProfile:
	.string "¡Sí! ¡Gracias!\p"
	.string "Espero que sea mejor que el perfil\n"
	.string "que me mostraste antes.$"

ProfileMan_Text_LikeProfileWayItIs:
	.string "Oh, te gusta tu perfil así.\p"
	.string "No te culpo, es un perfil\n"
	.string "maravilloso tal como está.$"

ProfileMan_Text_FantasticProfile:
	.string "¡F-fantástico!\p"
	.string "¡Tu perfil es maravilloso!\n"
	.string "Dice mucho de quién eres.\p"
	.string "¡Cualquiera que lo escuche\n"
	.string "quedaría cautivado por ti!\p"
	.string "¡Gracias!$"

@ Unused
ProfileMan_Text_YouKnowSecretSaying:
	.string " ¿Oh?\n"
	.string "¡Sabes la frase secreta!\p"
	.string "¡Ahora eres miembro del\n"
	.string "CLUB DE EVENTOS MISTERIO!$"
