SootopolisCity_House2_MapScripts::
	.byte 0

SootopolisCity_House2_EventScript_ExpertF::
	lock
	faceplayer
	msgbox SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SootopolisCity_House2_EventScript_KnowAboutOrbs
	call_if_eq VAR_RESULT, NO, SootopolisCity_House2_EventScript_DontKnowAboutOrbs
	release
	end

SootopolisCity_House2_EventScript_KnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_YesTwoOrbsSideBySide, MSGBOX_DEFAULT
	return

SootopolisCity_House2_EventScript_DontKnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_OughtToVisitAndSee, MSGBOX_DEFAULT
	return

SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs:
	.string "MT. PYRE…\p"
	.string "En su cima hay dos orbes puestos\n"
	.string "juntos. ¿Lo sabías?$"

SootopolisCity_House2_Text_YesTwoOrbsSideBySide:
	.string "Sí, dos orbes uno al lado del otro…\p"
	.string "Verlos juntos…\n"
	.string "De algún modo es relajante…$"

SootopolisCity_House2_Text_OughtToVisitAndSee:
	.string "¿Ah, sí?\n"
	.string "Tal vez deberías ir a verlos…$"

