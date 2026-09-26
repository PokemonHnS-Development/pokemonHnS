.set LOCALID_NURSE, 1

GoldenrodCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodCity_PokemonCenter_OnTransition
	.byte 0

GoldenrodCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_GOLDENROD_CITY
	end

GoldenrodCity_PokemonCenter_EventScript_GbaKid1::
	lock
	faceplayer
	msgbox GoldenrodCity_PokemonCenter_GameboyKidText1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_PokemonCenter_EventScript_GbaKid2::
	lock
	faceplayer
	msgbox GoldenrodCity_PokemonCenter_GameboyKidText2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_PokemonCenter_EventScript_Granny::
	lock
	faceplayer
	msgbox GoldenrodCity_PokemonCenter_GrannyText, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_PokemonCenter_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodCity_PokemonCenter_LassText, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_PokemonCenter_GrannyText:
    .string "¡Amo vivir en la gran ciudad!\n"
    .string "¡Me mudé aquí cuando era un joven\l"
    .string "entrenador, como tú!$"

GoldenrodCity_PokemonCenter_GameboyKidText1:
    .string "Este es un POKéMON CENTER especial.\n"
    .string "¡El techo es de oro!$"

GoldenrodCity_PokemonCenter_GameboyKidText2:
    .string "Le dije a mi hermano que el techo\n"
    .string "es de oro real. ¡Él cree\l"
	.string "cualquier cosa!$"

GoldenrodCity_PokemonCenter_LassText:
    .string "Un POKéMON de nivel alto no\n"
    .string "siempre gana.\p"
    .string "Después de todo, puede tener\n"
    .string "desventaja de tipo.\p"
    .string "No creo que haya un solo\n"
    .string "POKéMON que sea el más fuerte.$"

GoldenrodPokeCenter_LinkReceptionistPleaseAcceptGSBallText:
    .string "{PLAYER}, ¿verdad?\p"
    .string "¡Felicidades!\p"
    .string "¡Como oferta especial, te enviamos\n"
    .string "una GS BALL solo para ti!\p"
    .string "¡Por favor, acéptala!$"

GoldenrodPokeCenter_LinkReceptionistPleaseDoComeAgainText:
    .string "¡Por favor, vuelve pronto!$"

GoldenrodCity_PokemonCenter_PokefanFDoYouHaveEonMailText:
    .string "¡Vaya, tu mochila se ve pesada!\p"
    .string "¡Oh! ¿De casualidad tienes\n"
    .string "algo llamado EON MAIL?\p"
    .string "Mi hija busca uno.\p"
    .string "Puedes darme uno, ¿verdad?$"

GoldenrodCity_PokemonCenter_AskGiveAwayAnEonMailText:
    .string "¿Dar un EON MAIL?$"

GoldenrodCity_PokemonCenter_PokefanFThisIsForYouText:
    .string "¡Oh, qué bien! ¡Gracias,\n"
    .string "cariño!\p"
    .string "¡Toma, esto es para ti!$"

GoldenrodCity_PokemonCenter_PokefanFDaughterWillBeDelightedText:
    .string "¡Mi hija estará encantada!$"

GoldenrodCity_PokemonCenter_PokefanFTooBadText:
    .string " ¿Oh? ¿No tienes uno? Qué mal.$"

GoldenrodCity_PokemonCenter_PokefanFAnotherTimeThenText:
    .string "Oh... Bueno, será en otra ocasión.$"

GoldenrodCity_PokemonCenter_PlayerGaveAwayTheEonMailText:
    .string "{PLAYER} entregó el EON MAIL.$"
