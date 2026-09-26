# Traduccion al espanol (latino neutro) - Pokemon Heart & Soul 1.2.1

Parche `.ups` que traduce el hack **Pokemon Heart & Soul 1.2.1** al **espanol latino neutro**
(sin voseo, sin modismos de Espana), conservando los nombres propios de la comunidad.

## Descarga

- Parche: **`pokemonHnS-es-v1.2.1-final.ups`** (archivo adjunto en el release `es-1.2.1-v2`)
- ROM base: **Pokemon Heart and Soul v1.2.1** (el hack original, sin parchear)
- Verificado sobre ROM de **32,0 MB**; ROM resultante **CRC32 `8119F21A`**

## Como aplicar

1. Consigue el ROM base de Heart & Soul v1.2.1.
2. Aplica el `.ups` con cualquier parcheador UPS (Flips, MultiPatch, o `python aplicar_ups.py`).
3. Renombra el resultado a `.gba` y juega en mGBA / VBA-M.

## Estado de la traduccion

Medido con auditoria automatizada sobre **el ROM compilado** (no solo el codigo fuente):

| Metrica | Valor |
|---|---|
| Literales de texto analizados | **50.765** |
| Texto visible al jugador en ingles | **0** |
| Cadenas marcadas por el auditor | 62 (61 falsos positivos del detector + 1 etiqueta interna de debug) |
| Cobertura visible | **~100%** |

Sistemas revisados: menus, batalla, objetos, movimientos, habilidades, Pokedex, Pokegear,
dialogos, mapas, TV, Palabras Faciles (Easy Chat), Frontera de Batalla, nombres de zona.

## Convenciones usadas

- **Espanol latino neutro** con tildes y enie; sin voseo.
- `SHINY` se mantiene (termino de la comunidad); `NUZLOCKE` se mantiene.
- `HP -> PS`, `TM -> MT`, `Pokemon Center -> CENTRO POKeMON`.
- Nombres de zona en MAYUSCULAS, con los nombres oficiales verificados en WikiDex
  (p. ej. `ENCINAR`, `TORRE BELLSPROUT`, `TORRE QUEMADA`, `RUTA HELADA`, `FARO DE OLIVO`,
  `ISLA SUPREMA`, `TORRE OCULTA`, `PUEBLO PARDAL`).
- Acentos: el charmap y las fuentes del juego ya incluyen A E I O U N U con tilde
  (glifos verificados pixel a pixel en las 5 fuentes latinas).

## Notas tecnicas

- El cartel de zona sale de `src/data/region_map/region_map_sections*.json` -> plantilla `.json.txt`
  -> `tools/jsonproc` -> `region_map_entries.h` -> tabla de `src/region_map.c`.
- `jsonproc` deriva el nombre del simbolo C del texto del nombre; los acentos de mayuscula
  pasan por `cleanString` (un solo `_` por caracter UTF-8 completo).
- `« »` (U+00AB/BB) **no compilan** en `.inc`/`.s`; se usan comillas tipograficas `“ ”`.
- Fecha del build: 2026-09-26

## Creditos

- Hack original: **Pokemon Heart & Soul** (equipo HnS).
- Traduccion: **Si-Gon**, con asistencia de herramientas de traduccion y auditoria.
- Correcciones de nombres de zona verificadas contra WikiDex.
