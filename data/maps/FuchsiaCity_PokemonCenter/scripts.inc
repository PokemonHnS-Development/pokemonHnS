.set LOCALID_NURSE, 1
.set LOCALID_FUCHSIAPOKECENTER_WOMAN, 6
.set LOCALID_FUCHSIAPOKECENTER_JASMINE, 4

FuchsiaCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_PokemonCenter_OnTransition
	.byte 0

FuchsiaCity_PokemonCenter_OnTransition::
	setflag FLAG_TEMP_1
	setrespawn HEAL_LOCATION_FUCHSIA_CITY
	end

FuchsiaCity_PokemonCenter_EventScript_CooltrainerM::
	msgbox FuchsiaCity_PokemonCenter1F_Text_CooltrainerM, MSGBOX_NPC
	end

FuchsiaCity_PokemonCenter_EventScript_CooltrainerF::
	msgbox FuchsiaCity_PokemonCenter1F_Text_CooltrainerF, MSGBOX_NPC
	end

FuchsiaCity_PokemonCenter_EventScript_JanineClone::
	lock
	faceplayer
	msgbox FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator1, MSGBOX_DEFAULT
	applymovement LOCALID_FUCHSIAPOKECENTER_WOMAN, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	removeobject LOCALID_FUCHSIAPOKECENTER_WOMAN
	clearflag FLAG_TEMP_1
	addobject LOCALID_FUCHSIAPOKECENTER_JASMINE
	applymovement LOCALID_FUCHSIAPOKECENTER_JASMINE, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	applymovement LOCALID_FUCHSIAPOKECENTER_JASMINE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator2, MSGBOX_DEFAULT
	applymovement LOCALID_FUCHSIAPOKECENTER_JASMINE, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	removeobject LOCALID_FUCHSIAPOKECENTER_JASMINE
	clearflag FLAG_TEMP_2
	addobject LOCALID_FUCHSIAPOKECENTER_WOMAN
	applymovement LOCALID_FUCHSIAPOKECENTER_WOMAN, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	release
	closemessage
	end

FuchsiaCity_PokemonCenter1F_Text_CooltrainerM:
	.string "¡Hola! Tienes un nuevo tipo de\n"
	.string "POKéDEX.\p"
	.string "¿Te lo dio el PROF.OAK?$"

FuchsiaCity_PokemonCenter1F_Text_CooltrainerF:
	.string "Me sorprendí mucho en el GYM.\p"
	.string "Había un montón de chicas que\n"
	.string "se veían idénticas.$"

FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator1:
	.string "¡Soy JANINE! ¡Hocus-pocus... Puf!$"

FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator2:
	.string "¿Ves? ¡Ahora me veo igual que ella!$"

