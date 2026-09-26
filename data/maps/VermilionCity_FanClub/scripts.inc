.set LOCALID_FAN_CLUB_CLEFAIRY_DOLL, 5

VermilionCity_FanClub_MapScripts::
	.byte 0

VermilionCity_FanClub_EventScript_Chairman::
	lock
	faceplayer
	goto_if_eq VAR_FAN_CLUB_GUY, 1, VermilionCity_FanClub_EventScript_ChairmanAfter
	msgbox PokemonFanClub_Text_Chairman_Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, VermilionCity_FanClub_EventScript_ChairmanRefused
	msgbox PokemonFanClub_Text_Chairman_Rapidash, MSGBOX_DEFAULT
	msgbox PokemonFanClub_Text_Chairman_Gift, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_FAN_CLUB_GUY, 1
	msgbox PokemonFanClub_Text_Chairman_Candy, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_ChairmanRefused::
	msgbox PokemonFanClub_Text_Chairman_Disappointed, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_ChairmanAfter::
	msgbox PokemonFanClub_Text_Chairman_MoreTales, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_Woman1::
	msgbox PokemonFanClub_Text_Receptionist, MSGBOX_NPC
	end

VermilionCity_FanClub_EventScript_Woman2::
	msgbox PokemonFanClub_Text_Teacher, MSGBOX_NPC
	end

VermilionCity_FanClub_EventScript_ClefairyGuy::
	lock
	faceplayer
	msgbox PokemonFanClub_Text_ClefairyGuy_Adorable, MSGBOX_DEFAULT
	goto_if_eq VAR_FAN_CLUB_CLEFAIRY, 1, VermilionCity_FanClub_EventScript_ClefairyGiveDoll
	goto_if_ge VAR_FAN_CLUB_CLEFAIRY, 2, VermilionCity_FanClub_EventScript_ClefairyAfter
	msgbox PokemonFanClub_Text_ClefairyGuy_MakingDo, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_ClefairyGiveDoll::
	msgbox PokemonFanClub_Text_ClefairyGuy_ReturnDoll, MSGBOX_DEFAULT
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_FAN_CLUB_CLEFAIRY_DOLL
	removeobject LOCALID_FAN_CLUB_CLEFAIRY_DOLL
	fadescreenswapbuffers FADE_FROM_BLACK
	giveitem ITEM_LOST_ITEM
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_FAN_CLUB_CLEFAIRY, 2
	msgbox PokemonFanClub_Text_ClefairyGuy_GoingToGetOne, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_ClefairyAfter::
	msgbox PokemonFanClub_Text_ClefairyGuy_GoingToGetOne, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_Bayleef::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BAYLEEF, CRY_MODE_NORMAL
	msgbox PokemonFanClub_Text_Bayleef, MSGBOX_DEFAULT
	waitmoncry
	release
	end


PokemonFanClub_Text_Chairman_Intro:
	.string "Soy el PRESIDENTE del CLUB DE\n"
	.string "FANS POKéMON.\p"
	.string "He criado más de 150 POKéMON.\p"
	.string "Soy muy exigente con mis\n"
	.string "POKéMON.\p"
	.string "¿Viniste solo para oír hablar\n"
	.string "de mis POKéMON?$"

PokemonFanClub_Text_Chairman_Rapidash:
	.string "¡Bien! ¡Entonces escucha!\p"
	.string "Así que... mi RAPIDASH favorito...\p"
	.string "Es... lindo... adorable... listo...\n"
	.string "insoportable...\l"
	.string "además... increíble... oh... ¿tú\l"
	.string "crees?...\l"
	.string "Demasiado... salvaje... hermoso...\l"
	.string "amable...\l"
	.string "¡lo amo!\p"
	.string "Lo abrazo... al... dormir... cálido\n"
	.string "y tierno...\l"
	.string "Oh, y... espectacular...\l"
	.string "radiante... simplemente divino...\p"
	.string "¡Vaya! ¡Mira la hora!\n"
	.string "¡Te he retenido mucho tiempo!$"

PokemonFanClub_Text_Chairman_Gift:
	.string "Gracias por escucharme.\n"
	.string "¡Quiero que tengas esto!$"

PokemonFanClub_Text_Chairman_Candy:
	.string "Es un CARAMELO RARO que hace\n"
	.string "más fuertes a los POKéMON.\p"
	.string "Prefiero que mis POKéMON sean\n"
	.string "fuertes luchando, así que\l"
	.string "tómalo tú.$"

PokemonFanClub_Text_Chairman_MoreTales:
	.string "¡Hola, {PLAYER}!\p"
	.string "¿Viniste a verme por mis\n"
	.string "POKéMON otra vez?\p"
	.string "¿No? Oh... tenía más historias\n"
	.string "que contar...$"

PokemonFanClub_Text_Chairman_Disappointed:
	.string "Qué decepción...\p"
	.string "Vuelve si quieres escuchar.$"

PokemonFanClub_Text_Receptionist:
	.string "Nuestro PRESIDENTE habla mucho\n"
	.string "cuando se trata de POKéMON...$"

@=Clefairy=Guy=========================================================================================================
PokemonFanClub_Text_ClefairyGuy_Adorable:
	.string "Amo cómo CLEFAIRY mueve\n"
	.string "su dedo cuando intenta\l"
	.string "usar METRÓNOMO.\p"
	.string "¡Es tan adorable!$"

PokemonFanClub_Text_ClefairyGuy_MakingDo:
	.string "Amo a CLEFAIRY, pero nunca\n"
	.string "pude atrapar uno.\p"
	.string "Así que uso un POKé DOLL\n"
	.string "que encontré.$"

PokemonFanClub_Text_ClefairyGuy_ReturnDoll:
	.string "Ya veo. La niña que perdió\n"
	.string "este POKé DOLL está triste...\p"
	.string "¿Podrías devolverle el POKé DOLL\n"
	.string "a esa pobre niña?\p"
	.string "Algún día tendré un CLEFAIRY\n"
	.string "de verdad. ¡No te preocupes!$"

PokemonFanClub_Text_ClefairyGuy_GoingToGetOne:
	.string "Ya verás. Tendré un CLEFAIRY\n"
	.string "de verdad como amigo.$"

@============================================================================================================================

PokemonFanClub_Text_Teacher:
	.string "¡Mira a mi lindo BAYLEEF!\p"
	.string "¡La hoja de su cabeza es tierna!$"

PokemonFanClub_Text_ClefairyDoll:
	.string "¡Es un CLEFAIRY! ¿Eh?\p"
	.string "Ah, cierto. Es un POKé DOLL\n"
	.string "de CLEFAIRY.$"

PokemonFanClub_Text_Bayleef:
	.string "BAYLEEF: ¡Li liif!$"

PokemonFanClub_Text_Listen:
	.string "Escuchemos con respeto a los\n"
	.string "demás ENTRENADORES.$"

PokemonFanClub_Text_Bragging:
	.string "¡Si alguien presume, presume\n"
	.string "tú también!$"
