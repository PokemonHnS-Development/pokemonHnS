SootopolisCity_House3_MapScripts::
	.byte 0

SootopolisCity_House3_EventScript_Woman::
	lock
	faceplayer
	msgbox SootopolisCity_House3_Text_JuanHasManyFansDoYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SootopolisCity_House3_EventScript_HaveFans
	msgbox SootopolisCity_House3_Text_LonesomeTryWorkingHarder, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_HaveFans::
	msgbox SootopolisCity_House3_Text_YouMustBePrettyStrong, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_Girl::
	msgbox SootopolisCity_House3_Text_TrainerFanClubWasWild, MSGBOX_NPC
	end

SootopolisCity_House3_Text_JuanHasManyFansDoYou:
	.string "Eres ENTRENADOR POKéMON, ¿verdad?\p"
	.string "JUAN de SOOTOPOLIS tiene muchos fans.\n"
	.string "¡Más que su alumno WALLACE!\p"
	.string "¿Tú tienes algunos?$"

SootopolisCity_House3_Text_YouMustBePrettyStrong:
	.string "Oh, entonces debes ser muy fuerte.$"

SootopolisCity_House3_Text_LonesomeTryWorkingHarder:
	.string "Oh, cielos...\n"
	.string "Eso es un poco solitario.\p"
	.string "Esfuérzate más para conseguir\n"
	.string "seguidores.$"

SootopolisCity_House3_Text_TrainerFanClubWasWild:
	.string "Hay fans que vienen incluso de fuera\n"
	.string "de HOENN.\p"
	.string "¡Fue una locura cuando fui al CLUB DE\n"
	.string "FANS en CIUDAD VERAZON!$"

