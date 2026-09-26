CianwoodHouse2_MapScripts::
	.byte 0

CianwoodHouse2_EventScript_Teacher::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse2_EventScript_Lass::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseLass, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse2_EventScript_Twin::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseTwin, MSGBOX_DEFAULT
	closemessage
	release
	end
	
CianwoodCity_Text_LugiaHouseTeacher:
	.string "¿Vienes de CIUDAD OLIVO?\p"
	.string "¿Recuerdas las cuatro islas\n"
	.string "del camino?\p"
	.string "Oí que una criatura marina mítica\n"
	.string "se esconde en ellas.$"

CianwoodCity_Text_LugiaHouseLass:
	.string "Dicen que solo puedes verla\n"
	.string "si tienes un ALA DE PLATA.\p"
	.string "Debe tener el mismo aroma que\n"
	.string "la criatura.$"

CianwoodCity_Text_LugiaHouseTwin:
	.string "Oí que los remolinos de las\n"
	.string "islas son causados por\l"
	.string "la criatura marina.\p"
	.string "Quizás necesites un movimiento\n"
	.string "especial para pasarlos.$"
