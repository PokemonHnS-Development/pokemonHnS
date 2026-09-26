MysteryGiftScript_VisitingTrainer::
	setvaddress MysteryGiftScript_VisitingTrainer
	special ValidateEReaderTrainer
	vgoto_if_eq VAR_RESULT, 0, MysteryGiftScript_VisitingTrainerArrived
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerInstructions
	waitmessage
	waitbuttonpress
	release
	end

MysteryGiftScript_VisitingTrainerArrived:
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerArrived
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftVisitingTrainerInstructions:
	.string "Gracias por usar el sistema de\n"
	.string "REGALO MISTERIOSO.\p"
	.string "Con esta TARJETA MARAVILLA,\n"
	.string "podrás hacer una encuesta en un\l"
	.string "CENTRO POKéMON.\p"
	.string "Usa las encuestas para invitar\n"
	.string "ENTRENADORES a CIUDAD CALOR.\p"
	.string "...Te daré una contraseña\n"
	.string "secreta para la encuesta:\p"
	.string "“DAME UN\n"
	.string "ENTRENADOR GENIAL”\p"
	.string "Escríbela en la encuesta y envíala\n"
	.string "al SISTEMA DE COMUNICACIÓN\l"
	.string "INALÁMBRICA.$"

sText_MysteryGiftVisitingTrainerArrived:
	.string "Gracias por usar el sistema de\n"
	.string "REGALO MISTERIOSO.\p"
	.string "Un ENTRENADOR ha llegado a\n"
	.string "CIUDAD CALOR buscándote.\p"
	.string "Esperamos que disfrutes la\n"
	.string "batalla con el ENTRENADOR.\p"
	.string "Puedes invitar a otros usando\n"
	.string "otras contraseñas.\p"
	.string "Intenta buscar más contraseñas\n"
	.string "que puedan funcionar.$"
