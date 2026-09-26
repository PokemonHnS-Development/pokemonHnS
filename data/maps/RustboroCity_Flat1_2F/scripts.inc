.set LOCALID_WALDAS_DAD, 6

RustboroCity_Flat1_2F_MapScripts::
	.byte 0

RustboroCity_Flat1_2F_EventScript_WaldasDad::
	lock
	faceplayer
	specialvar VAR_RESULT, TryBufferWaldaPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase

RustboroCity_Flat1_2F_EventScript_GivePhrase::
	special DoWaldaNamingScreen
	waitstate
	goto_if_eq VAR_0x8004, 1, RustboroCity_Flat1_2F_EventScript_CancelGivePhrase
	goto_if_eq VAR_0x8004, 2, RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase
	specialvar VAR_RESULT, TryGetWallpaperWithWaldaPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase::
	msgbox RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhIsThatRight, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhYouDontKnowAny, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry2, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_OhShesLaughing, MSGBOX_DEFAULT
	applymovement LOCALID_WALDAS_DAD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda::
	turnobject LOCALID_WALDAS_DAD, DIR_EAST
	return

RustboroCity_Flat1_2F_EventScript_WaldasMom::
	msgbox RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard, MSGBOX_NPC
	end

RustboroCity_Flat1_2F_EventScript_PokeDoll::
	msgbox RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll, MSGBOX_SIGN
	end

RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard:
	.string "Ay, es tan difícil cada día…\p"
	.string "¿Qué es difícil?\n"
	.string "¿Tienes que preguntar?\p"
	.string "Pensar qué cocinar para las\n"
	.string "comidas cada día.\p"
	.string "No es nada fácil inventar\n"
	.string "menús todos los días.$"

RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase:
	.string "¡Oh, hola!\n"
	.string "Bienvenido a la casa PEPPER.\p"
	.string "Tengo una pregunta para ti.\n"
	.string "¿Has cuidado niños alguna vez?\p"
	.string "Soy padre primerizo, así que criar\n"
	.string "un niño es nuevo para mí.\p"
	.string "Y tengo un problema. Mi hija\n"
	.string "WALDA no ríe lo suficiente.\p"
	.string "Creo que reiría si le dijera\n"
	.string "algo gracioso.\p"
	.string "¿Conoces alguna palabra o frase\n"
	.string "divertida que me digas?$"

RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase:
	.string "He estado diciendo “{STR_VAR_1}”\n"
	.string "para divertirla últimamente.\p"
	.string "¿Sabes de alguna palabra o\n"
	.string "frase que funcione mejor?$"

RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion:
	.string "Oh, eso es maravilloso.\n"
	.string "Dime, ¿cuál es tu sugerencia?$"

RustboroCity_Flat1_2F_Text_OhIsThatRight:
	.string "Oh, ¿de verdad?\p"
	.string "Bueno, si se te ocurre una buena\n"
	.string "sugerencia, soy todo oídos.$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry2:
	.string "Ah, ya veo.\n"
	.string "Bueno, intentémoslo, ¿te parece?$"

RustboroCity_Flat1_2F_Text_OhShesLaughing:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "¡Oh, sí! ¡Se está riendo!\n"
	.string "¡Estoy tan feliz como ella!$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry:
	.string "Ah, ya veo.\n"
	.string "Bueno, intentémoslo, ¿te parece?$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Hmmm... No sonríe para nada.\n"
	.string "Quizá WALDA es una niña seria...$"

RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase:
	.string "Oh, no sabes palabras buenas.\n"
	.string "Mejor pensaré yo mismo.\p"
	.string "Hmm...\n"
	.string "¿Qué tal {STR_VAR_1}?\l"
	.string "Veamos si eso funciona.$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Hmmm... No sonríe para nada.\n"
	.string "Quizá WALDA es una niña seria...$"

RustboroCity_Flat1_2F_Text_OhYouDontKnowAny:
	.string "Oh, no conoces palabras agradables.\n"
	.string "Intentaré divertirla con el dicho\l"
	.string "que usé antes.\p"
	.string "Si tienes una buena sugerencia,\n"
	.string "no dudes en decírmelo, ¿está bien?$"

RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper:
	.string "¡Gracias!\p"
	.string "¡Gracias a ti, mi querida WALDA\n"
	.string "se rió conmigo!\p"
	.string "Quizás no parezca alguien\n"
	.string "especial, pero soy un experto\l"
	.string "de DEVON CORPORATION.\p"
	.string "¿Qué tal si hago algo por ti\n"
	.string "a cambio?\p"
	.string "¡Ya sé! Pondré fondos nuevos\n"
	.string "para las BOXES del PC\l"
	.string "POKéMON Storage System.\p"
	.string "En el menú de fondos,\n"
	.string "elige AMIGOS.\p"
	.string "Eso te dará acceso a los nuevos\n"
	.string "diseños de fondo.$"

RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll:
	.string "¡Es un MUÑECO de peluche POKéMON!$"

