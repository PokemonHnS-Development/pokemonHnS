extern const u8 EventScript_FollowerIsShivering[];
extern const u8 EventScript_FollowerNostalgia[];
extern const u8 EventScript_FollowerHopping[];
extern const u8 EventScript_FollowerJumpOnPlayer[];
extern const u8 EventScript_FollowerCuddling[];
extern const u8 EventScript_FollowerShiverCuddling[];
extern const u8 EventScript_FollowerGetCloser[];
extern const u8 EventScript_FollowerPokingPlayer[];
extern const u8 EventScript_FollowerLookAround[];
extern const u8 EventScript_FollowerLookAway[];
extern const u8 EventScript_FollowerLookAwayBark[];
extern const u8 EventScript_FollowerLookAwayPoke[];
extern const u8 EventScript_FollowerPokeGround[];
extern const u8 EventScript_FollowerStartled[];
extern const u8 EventScript_FollowerFastHopping[];
extern const u8 EventScript_FollowerDizzy[];
extern const u8 EventScript_FollowerLookAroundScared[];
extern const u8 EventScript_FollowerDance[];
extern const u8 EventScript_FollowerLookUp[];

// 'Generic', unconditional happy messages
static const u8 sHappyMsg00[] = _("{STR_VAR_1} empezó a picarte el\nestómago.");
static const u8 sHappyMsg01[] = _("{STR_VAR_1} está feliz pero tímido.");
static const u8 sHappyMsg02[] = _("{STR_VAR_1} avanza muy contento.");
static const u8 sHappyMsg03[] = _("{STR_VAR_1} está tranquilo.");
static const u8 sHappyMsg04[] = _("{STR_VAR_1} ¡se siente genial\nal caminar contigo!");
static const u8 sHappyMsg05[] = _("{STR_VAR_1} irradia salud.");
static const u8 sHappyMsg06[] = _("{STR_VAR_1} se ve muy feliz.");
static const u8 sHappyMsg07[] = _("{STR_VAR_1} se esforzó al máximo.");
static const u8 sHappyMsg08[] = _("{STR_VAR_1} huele los aromas\ndel aire circundante.");
static const u8 sHappyMsg09[] = _("¡{STR_VAR_1} salta de alegría!");
static const u8 sHappyMsg10[] = _("¡{STR_VAR_1} se sigue sintiendo bien!");
static const u8 sHappyMsg11[] = _("Tu POKéMON ha captado el olor\na humo.");
static const u8 sHappyMsg12[] = _("{STR_VAR_1} te toca la barriga.");
static const u8 sHappyMsg13[] = _("Tu POKéMON se estiró y\nahora se relaja.");
static const u8 sHappyMsg14[] = _("¡Parece que {STR_VAR_1}\nquiere guiarte!");
static const u8 sHappyMsg15[] = _("{STR_VAR_1} hace lo posible por\nno quedarse atrás.");
static const u8 sHappyMsg16[] = _("¡{STR_VAR_1} se acurruca\nfelizmente junto a ti!");
static const u8 sHappyMsg17[] = _("¡{STR_VAR_1} está lleno de vida!");
static const u8 sHappyMsg18[] = _("¡{STR_VAR_1} parece muy feliz!");
static const u8 sHappyMsg19[] = _("{STR_VAR_1} está tan feliz\nque no se queda quieto!");
static const u8 sHappyMsg20[] = _("{STR_VAR_1} asintió lentamente.");
static const u8 sHappyMsg21[] = _("¡{STR_VAR_1} está muy ansioso!");
static const u8 sHappyMsg22[] = _("{STR_VAR_1} vaga por ahí y\nescucha los sonidos.");
static const u8 sHappyMsg23[] = _("{STR_VAR_1} se ve muy interesado.");
static const u8 sHappyMsg24[] = _("{STR_VAR_1} se esfuerza por\nseguir adelante.");
static const u8 sHappyMsg25[] = _("¡{STR_VAR_1} te miró con alegría!");
static const u8 sHappyMsg26[] = _("{STR_VAR_1} te mira feliz\ny te sonríe.");
static const u8 sHappyMsg27[] = _("Tu POKéMON huele el aroma\nde flores.");
static const u8 sHappyMsg28[] = _("¡{STR_VAR_1} parece muy feliz de\nverte!");
static const u8 sHappyMsg29[] = _("{STR_VAR_1} se giró hacia ti\ny sonrió.");
static const u8 sHappyMsg30[] = _("¡{STR_VAR_1} se acurrucó feliz\ncontigo!");
// Conditional messages begin here, index 31
static const u8 sHappyMsg31[] = _("Tu POKéMON parece feliz con\nel buen tiempo.");
static const u8 sHappyMsg32[] = _("{STR_VAR_1} se ve muy sereno y\nseguro de sí mismo!");

const struct FollowerMsgInfo gFollowerHappyMessages[] = {
    {sHappyMsg00, EventScript_FollowerPokingPlayer},
    {sHappyMsg01}, {sHappyMsg02}, {sHappyMsg03}, {sHappyMsg04}, {sHappyMsg05}, {sHappyMsg06}, {sHappyMsg07},
    {sHappyMsg08, EventScript_FollowerLookAround},
    {sHappyMsg09, EventScript_FollowerHopping},
    {sHappyMsg10}, {sHappyMsg11},
    {sHappyMsg12, EventScript_FollowerPokingPlayer},
    {sHappyMsg13, EventScript_FollowerLookAround},
    {sHappyMsg14}, {sHappyMsg15},
    {sHappyMsg16, EventScript_FollowerCuddling},
    {sHappyMsg17}, {sHappyMsg18},
    {sHappyMsg19, EventScript_FollowerFastHopping},
    {sHappyMsg20}, {sHappyMsg21}, {sHappyMsg22}, {sHappyMsg23}, {sHappyMsg24}, {sHappyMsg25}, {sHappyMsg26}, {sHappyMsg27}, {sHappyMsg28}, {sHappyMsg29},
    {sHappyMsg30, EventScript_FollowerCuddling},
    {sHappyMsg31}, {sHappyMsg32},
};

// Unconditional neutral messages
static const u8 sNeutralMsg00[] = _("{STR_VAR_1} pica el suelo\nconstantemente.");
static const u8 sNeutralMsg01[] = _("{STR_VAR_1} está montando guardia.");
static const u8 sNeutralMsg02[] = _("{STR_VAR_1} mira pacientemente a\nnada en absoluto.");
static const u8 sNeutralMsg03[] = _("{STR_VAR_1} vaga por ahí.");
static const u8 sNeutralMsg04[] = _("¡Tu POKéMON bostezó fuerte!");
static const u8 sNeutralMsg05[] = _("Tu POKéMON mira alrededor\ninquieto.");
static const u8 sNeutralMsg06[] = _("{STR_VAR_1} mira hacia aquí y\nsonríe.");
static const u8 sNeutralMsg07[] = _("{STR_VAR_1} mira a su alrededor\ninquieto.");
static const u8 sNeutralMsg08[] = _("{STR_VAR_1} lanzó un grito de batalla.");
static const u8 sNeutralMsg09[] = _("{STR_VAR_1} ¡hizo un baile\nmaravilloso!");
static const u8 sNeutralMsg10[] = _("{STR_VAR_1} está muy ansioso.");
static const u8 sNeutralMsg11[] = _("{STR_VAR_1} mira fijamente hacia\nla distancia.");
static const u8 sNeutralMsg12[] = _("{STR_VAR_1} ¡está vigilando!");
static const u8 sNeutralMsg13[] = _("{STR_VAR_1} miró a lo lejos\ny ladró!");

const struct FollowerMsgInfo gFollowerNeutralMessages[] = {
    {sNeutralMsg00, EventScript_FollowerPokeGround},
    {sNeutralMsg01},
    {sNeutralMsg02, EventScript_FollowerLookAway},
    {sNeutralMsg03, EventScript_FollowerLookAround},
    {sNeutralMsg04},
    {sNeutralMsg05, EventScript_FollowerLookAround},
    {sNeutralMsg06}, {sNeutralMsg07}, {sNeutralMsg08},
    {sNeutralMsg09, EventScript_FollowerDance},
    {sNeutralMsg10},
    {sNeutralMsg11, EventScript_FollowerLookAway},
    {sNeutralMsg12},
    {sNeutralMsg13, EventScript_FollowerLookAwayBark},
};

// Unconditional sad messages
static const u8 sSadMsg00[] = _("{STR_VAR_1} está mareado.");
static const u8 sSadMsg01[] = _("{STR_VAR_1} te está pisando\nlos pies!");
static const u8 sSadMsg02[] = _("{STR_VAR_1} parece algo cansado.");
// Conditional messages begin, index 3
static const u8 sSadMsg03[] = _("{STR_VAR_1} no está feliz.");
static const u8 sSadMsg04[] = _("¡{STR_VAR_1} se va a caer!\n");
static const u8 sSadMsg05[] = _("¡Parece que {STR_VAR_1} está a\npunto de caerse!");
static const u8 sSadMsg06[] = _("{STR_VAR_1} se esfuerza mucho\npor seguirte…");
static const u8 sSadMsg07[] = _("{STR_VAR_1} está nervioso.");

const struct FollowerMsgInfo gFollowerSadMessages[] = {
    {sSadMsg00, EventScript_FollowerDizzy},
    {sSadMsg01}, {sSadMsg02},
    {sSadMsg03}, {sSadMsg04}, {sSadMsg05}, {sSadMsg06}, {sSadMsg07},
};

// Unconditional upset messages
static const u8 sUpsetMsg00[] = _("{STR_VAR_1} parece infeliz por algo...");
static const u8 sUpsetMsg01[] = _("{STR_VAR_1} tiene una cara\ninfeliz.");
static const u8 sUpsetMsg02[] = _("…Tu POKéMON parece tener\nfrío.");
// Conditional messages, index 3
static const u8 sUpsetMsg03[] = _("{STR_VAR_1} se refugia en la\nhierba por la lluvia.");

const struct FollowerMsgInfo gFollowerUpsetMessages[] = {
    {sUpsetMsg00}, {sUpsetMsg01},
    {sUpsetMsg02, EventScript_FollowerIsShivering},
    {sUpsetMsg03},
};

// Unconditional angry messages
static const u8 sAngryMsg00[] = _("¡{STR_VAR_1} lanzó un rugido!");
static const u8 sAngryMsg01[] = _("¡{STR_VAR_1} pone cara de\nestar enojado!");
static const u8 sAngryMsg02[] = _("{STR_VAR_1} parece estar enojado\npor alguna razón.");
static const u8 sAngryMsg03[] = _("Tu POKéMON se dio la vuelta,\nmostrando cara desafiante.");
static const u8 sAngryMsg04[] = _("{STR_VAR_1} gritó.");

const struct FollowerMsgInfo gFollowerAngryMessages[] = {
    {sAngryMsg00}, {sAngryMsg01}, {sAngryMsg02},
    {sAngryMsg03, EventScript_FollowerLookAway},
    {sAngryMsg04},
};

// Unconditional pensive messages
static const u8 sPensiveMsg00[] = _("{STR_VAR_1} mira hacia abajo\n fijamente.");
static const u8 sPensiveMsg01[] = _("{STR_VAR_1} observa el área.");
static const u8 sPensiveMsg02[] = _("{STR_VAR_1} mira hacia abajo.");
static const u8 sPensiveMsg03[] = _("{STR_VAR_1} intenta luchar\ncontra el sueño...");
static const u8 sPensiveMsg04[] = _("{STR_VAR_1} parece estar\nvagando por ahí.");
static const u8 sPensiveMsg05[] = _("{STR_VAR_1} mira a su alrededor\ndistraídamente.");
static const u8 sPensiveMsg06[] = _("¡{STR_VAR_1} bostezó muy fuerte!");
static const u8 sPensiveMsg07[] = _("{STR_VAR_1} se relaja cómodamente.");
static const u8 sPensiveMsg08[] = _("{STR_VAR_1} te mira fijamente\na la cara.");
static const u8 sPensiveMsg09[] = _("{STR_VAR_1} te observa con\nmucha atención.");
static const u8 sPensiveMsg10[] = _("{STR_VAR_1} centra su\natención en ti.");
static const u8 sPensiveMsg11[] = _("{STR_VAR_1} mira hacia\nel vacío.");
static const u8 sPensiveMsg12[] = _("{STR_VAR_1} olfatea el\nsuelo.");
static const u8 sPensiveMsg13[] = _("Tu POKéMON mira fijamente\na la nada.");
static const u8 sPensiveMsg14[] = _("¡{STR_VAR_1} se concentra con\nuna mirada aguda!");
static const u8 sPensiveMsg15[] = _("{STR_VAR_1} se está concentrando.");
static const u8 sPensiveMsg16[] = _("{STR_VAR_1} miró hacia aquí y\nasintió.");
static const u8 sPensiveMsg17[] = _("{STR_VAR_1} parece algo nervioso...");
static const u8 sPensiveMsg18[] = _("{STR_VAR_1} mira tus\nhuellas.");
static const u8 sPensiveMsg19[] = _("{STR_VAR_1} te mira\nfijamente a los ojos.");

const struct FollowerMsgInfo gFollowerPensiveMessages[] = {
    {sPensiveMsg00},
    {sPensiveMsg01, EventScript_FollowerLookAround},
    {sPensiveMsg02}, {sPensiveMsg03}, {sPensiveMsg04},
    {sPensiveMsg05, EventScript_FollowerLookAround},
    {sPensiveMsg06}, {sPensiveMsg07}, {sPensiveMsg08}, {sPensiveMsg09}, {sPensiveMsg10},
    {sPensiveMsg11, EventScript_FollowerLookAway},
    {sPensiveMsg12, EventScript_FollowerPokeGround},
    {sPensiveMsg13, EventScript_FollowerLookAway},
    {sPensiveMsg14}, {sPensiveMsg15}, {sPensiveMsg16}, {sPensiveMsg17}, {sPensiveMsg18}, {sPensiveMsg19},
};

// All 'love' messages are unconditional
static const u8 sLoveMsg00[] = _("¡{STR_VAR_1} empezó a\nacercarse de repente!");
static const u8 sLoveMsg01[] = _("¡Las mejillas de {STR_VAR_1}\nse ponen rosadas!");
static const u8 sLoveMsg02[] = _("¡Vaya! ¡{STR_VAR_1} te\nabrazó de repente!");
static const u8 sLoveMsg03[] = _("¡Vaya! ¡{STR_VAR_1} de repente\nestá juguetón!");
static const u8 sLoveMsg04[] = _("{STR_VAR_1} se frota contra tus\npiernas!");
static const u8 sLoveMsg05[] = _("{STR_VAR_1} se sonroja.");
static const u8 sLoveMsg06[] = _("¡Ah! ¡{STR_VAR_1} te abraza!");
static const u8 sLoveMsg07[] = _("¡{STR_VAR_1} te mira con\nadoración!");
static const u8 sLoveMsg08[] = _("{STR_VAR_1} se acercó a ti.");
static const u8 sLoveMsg09[] = _("{STR_VAR_1} se mantiene cerca de\ntus pies.");

const struct FollowerMsgInfo gFollowerLoveMessages[] = {
    {sLoveMsg00, EventScript_FollowerGetCloser},
    {sLoveMsg01},
    {sLoveMsg02, EventScript_FollowerCuddling},
    {sLoveMsg03},
    {sLoveMsg04, EventScript_FollowerCuddling},
    {sLoveMsg05},
    {sLoveMsg06, EventScript_FollowerCuddling},
    {sLoveMsg07},
    {sLoveMsg08, EventScript_FollowerGetCloser},
    {sLoveMsg09},
};

// Unconditional surprised messages
static const u8 sSurpriseMsg00[] = _("¡{STR_VAR_1} corre el riesgo de\ncaerse!");
static const u8 sSurpriseMsg01[] = _("¡{STR_VAR_1} chocó contigo!");
static const u8 sSurpriseMsg02[] = _("{STR_VAR_1} aún no hace honor\na su nombre.");
static const u8 sSurpriseMsg03[] = _("{STR_VAR_1} mira hacia abajo.");
static const u8 sSurpriseMsg04[] = _("¡Tu POKéMON tropezó y casi\nse cae!");
static const u8 sSurpriseMsg05[] = _("{STR_VAR_1} siente algo y\nestá aullando!");
static const u8 sSurpriseMsg06[] = _("{STR_VAR_1} parece renovado.");
static const u8 sSurpriseMsg07[] = _("¡{STR_VAR_1} se dio la vuelta\ny empezó a ladrar!");
static const u8 sSurpriseMsg08[] = _("{STR_VAR_1} se dio la vuelta.");
static const u8 sSurpriseMsg09[] = _("¡Tu POKéMON se sorprendió\ncuando le hablaste de pronto!");
static const u8 sSurpriseMsg10[] = _("¡Olfateo, olfateo, algo huele\nmuy bien!");
static const u8 sSurpriseMsg11[] = _("{STR_VAR_1} se siente renovado.");
static const u8 sSurpriseMsg12[] = _("{STR_VAR_1} se tambalea y parece\nque va a caerse.");
static const u8 sSurpriseMsg13[] = _("{STR_VAR_1} corre el riesgo de\ncaerse.");
static const u8 sSurpriseMsg14[] = _("{STR_VAR_1} camina con\nprecaución.");
static const u8 sSurpriseMsg15[] = _("{STR_VAR_1} se pone tenso por\nlos nervios.");
static const u8 sSurpriseMsg16[] = _("{STR_VAR_1} sintió algo extraño\n¡y se sorprendió!");
static const u8 sSurpriseMsg17[] = _("{STR_VAR_1} tiene miedo y se\nacurruca junto a ti!");
static const u8 sSurpriseMsg18[] = _("{STR_VAR_1} siente una presencia\ninusual…");
static const u8 sSurpriseMsg19[] = _("{STR_VAR_1} se pone tenso por\nla energía nerviosa.");
// Conditional messages, index 20
static const u8 sSurpriseMsg20[] = _("¡{STR_VAR_1} parece muy\nsorprendido de que llueva!");

const struct FollowerMsgInfo gFollowerSurpriseMessages[] = {
    {sSurpriseMsg00},
    {sSurpriseMsg01, EventScript_FollowerPokingPlayer},
    {sSurpriseMsg02}, {sSurpriseMsg03}, {sSurpriseMsg04}, {sSurpriseMsg05}, {sSurpriseMsg06},
    {sSurpriseMsg07, EventScript_FollowerLookAwayBark},
    {sSurpriseMsg08, EventScript_FollowerLookAway},
    {sSurpriseMsg09},
    {sSurpriseMsg10, EventScript_FollowerLookAround},
    {sSurpriseMsg11}, {sSurpriseMsg12}, {sSurpriseMsg13}, {sSurpriseMsg14}, {sSurpriseMsg15}, {sSurpriseMsg16},
    {sSurpriseMsg17, EventScript_FollowerCuddling},
    {sSurpriseMsg18},
    {sSurpriseMsg19, EventScript_FollowerLookAround},
    {sSurpriseMsg20},
};

// Unconditional curious messages
static const u8 sCuriousMsg00[] = _("Tu POKéMON busca algo\ncon inquietud.");
static const u8 sCuriousMsg01[] = _("¡Tu POKéMON no miraba por\n dónde iba y chocó contigo!");
static const u8 sCuriousMsg02[] = _("¡Olfatea, olfatea! ¿Hay algo\ncerca?");
static const u8 sCuriousMsg03[] = _("{STR_VAR_1} juega a rodar\nuna piedrita.");
static const u8 sCuriousMsg04[] = _("{STR_VAR_1} vaga por ahí\nbuscando algo.");
static const u8 sCuriousMsg05[] = _("{STR_VAR_1} te está olfateando.");
static const u8 sCuriousMsg06[] = _("{STR_VAR_1} parece estar un\npoco dudoso...");

const struct FollowerMsgInfo gFollowerCuriousMessages[] = {
    {sCuriousMsg00, EventScript_FollowerLookAround},
    {sCuriousMsg01, EventScript_FollowerPokingPlayer},
    {sCuriousMsg02}, {sCuriousMsg03},
    {sCuriousMsg04, EventScript_FollowerLookAround},
    {sCuriousMsg05}, {sCuriousMsg06},
};

// Unconditional music messages
static const u8 sMusicMsg00[] = _("{STR_VAR_1} ¡presume de su\nagilidad!");
static const u8 sMusicMsg01[] = _("¡{STR_VAR_1} se mueve\ncon alegría!");
static const u8 sMusicMsg02[] = _("¡Vaya! ¡{STR_VAR_1} empezó a\nbailar de alegría!");
static const u8 sMusicMsg03[] = _("¡{STR_VAR_1} te sigue el ritmo\nsin detenerse!");
static const u8 sMusicMsg04[] = _("{STR_VAR_1} parece que quiere\njugar contigo.");
static const u8 sMusicMsg05[] = _("{STR_VAR_1} salta felizmente.");
static const u8 sMusicMsg06[] = _("{STR_VAR_1} canta y tararea.");
static const u8 sMusicMsg07[] = _("¡{STR_VAR_1} te muerde los pies!");
static const u8 sMusicMsg08[] = _("{STR_VAR_1} se da la vuelta y\nte mira.");
static const u8 sMusicMsg09[] = _("{STR_VAR_1} se esfuerza por mostrar\nsu gran poder!");
static const u8 sMusicMsg10[] = _("¡Vaya! ¡{STR_VAR_1} bailó de\nfelicidad de repente!");
static const u8 sMusicMsg11[] = _("¡{STR_VAR_1} está alegre!");
static const u8 sMusicMsg12[] = _("{STR_VAR_1} salta por ahí\ncon alegría!");
static const u8 sMusicMsg13[] = _("Tu POKéMON parece oler un aroma\nnostálgicamente familiar…");
// Conditional music messages, index 14
static const u8 sMusicMsg14[] = _("{STR_VAR_1} está muy feliz por la\nlluvia.");

const struct FollowerMsgInfo gFollowerMusicMessages[] = {
    {sMusicMsg00, EventScript_FollowerLookAround},
    {sMusicMsg01},
    {sMusicMsg02, EventScript_FollowerDance},
    {sMusicMsg03},
    {sMusicMsg04, EventScript_FollowerHopping},
    {sMusicMsg05, EventScript_FollowerHopping},
    {sMusicMsg06}, {sMusicMsg07}, {sMusicMsg08}, {sMusicMsg09},
    {sMusicMsg10, EventScript_FollowerDance},
    {sMusicMsg11},
    {sMusicMsg12, EventScript_FollowerHopping},
    {sMusicMsg13, EventScript_FollowerNostalgia},
    {sMusicMsg14}
};


static const u8 sPoisonedMsg00[] = _("{STR_VAR_1} tiembla por los\nefectos del veneno.");

const struct FollowerMsgInfo gFollowerPoisonedMessages[] = {
    {sPoisonedMsg00, EventScript_FollowerIsShivering},
};
