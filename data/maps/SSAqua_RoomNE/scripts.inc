SSAqua_RoomNE_MapScripts::
	.byte 0

SSAqua_RoomNE_EventScript_Noland::
	trainerbattle_single TRAINER_NOLAND SSAqua_RoomNE_Text_HikerNolandSeen, SSAqua_RoomNE_Text_HikerNolandBeaten
	msgbox SSAqua_RoomNE_Text_HikerNolandAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNE_EventScript_Ethan::
	trainerbattle_single TRAINER_ETHAN SSAqua_RoomNE_Text_PokemaniacEthanSeen, SSAqua_RoomNE_Text_PokemaniacEthanBeaten
	msgbox SSAqua_RoomNE_Text_PokemaniacEthanAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNE_Text_HikerNolandSeen:
    .string "¿Estás solo?\n"
    .string "¡Entonces luchemos!$"

SSAqua_RoomNE_Text_HikerNolandBeaten:
    .string "¡Es demasiado para mí!$"

SSAqua_RoomNE_Text_HikerNolandAfterBattle:
    .string "¿Habrá montañas que valga la\n"
    .string "pena escalar en KANTO?$"

SSAqua_RoomNE_Text_PokemaniacEthanSeen:
    .string "¿Conoces a LILY?\n"
    .string "Es una DJ famosa en KANTO.$"

SSAqua_RoomNE_Text_PokemaniacEthanBeaten:
    .string "¡Gyaaaah!$"

SSAqua_RoomNE_Text_PokemaniacEthanAfterBattle:
    .string "LILY es linda, pero\n"
    .string "¡MARY es la mejor!\n"
    .string "¡Quiero ver los\n"
    .string "programas de radio\n"
    .string "de JOHTO!$"
