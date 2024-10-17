# Vzdálenost letadel

**Termín odevzdání:** 28.11.2022 11:59:59  
**Pozdní odevzdání s penalizací:** 31.12.2022 23:59:59 (penále 100.0000 %)

## Zadání

Úkolem je vytvořit program, který pomůže obsluze radaru řídící věže.

Při řízení letového provozu je důležité hlídat potenciální kolize letadel. Radary snímají pozice letadel a program kontroluje vzdálenosti mezi nimi. Chceme realizovat program, který pro zadané souřadnice letadel rozhodne, kde hrozí potenciální kolize, tedy která letadla jsou k sobě nejblíže.

### Vstup

Vstupem programu jsou souřadnice a označení letadel. Předpokládáme rovinné souřadnice (x, y) jako desetinná čísla. Souřadnice jsou oddělené čárkou, za nimi následuje dvojtečka a identifikace letadla. Název letadla je řetězec bez mezer, maximálně 199 znaků dlouhý a nemusí být jednoznačný. Zadávání vstupu končí EOF (konec souboru).

### Výstup

Program vypíše vzdálenost nejbližších dvou letadel. Pokud existuje více dvojic letadel ve stejné vzdálenosti, program vypíše počet takových dvojic a seznam všech dvojic s touto minimální vzdáleností. Výpis nemusí být uspořádaný. Při nesprávném vstupu program vypíše chybovou hlášku.

### Chybové stavy
Program detekuje následující chyby:
- Nečíselné souřadnice
- Nesprávný formát vstupu (chybějící nebo nadbytečné oddělovače)
- Méně než dvě letadla

### Omezení

Program bude spuštěn v omezeném prostředí, které klade nároky na čas i paměť. Základní implementace s naivním algoritmem projde povinnými testy, ale pro dosažení bonusových bodů je potřeba efektivnější algoritmus.

### Ukázky

**Ukázka 1**

```
Pozice letadel:
0,0: KLM
5,0: Lufthansa
10,0: SmartWings
7,0: AirFrance
2,0: Qantas

Vzdalenost nejblizsich letadel: 2.000000
Nalezenych dvojic: 2
KLM - Qantas
Lufthansa - AirFrance
```

**Ukázka 2**

```
Pozice letadel:
0,5: Qantas
5,0: KLM
0,0: AirFrance
5,5: Lufthansa
2.5,2.5: KLM

Vzdalenost nejblizsich letadel: 3.535534
Nalezenych dvojic: 4
Qantas - KLM
AirFrance - KLM
KLM - KLM
KLM - Lufthansa
```

**Ukázka 3**

```
Pozice letadel:
-10,-5: Ryanair
10,0: LOT
12,12: SmartWings

Vzdalenost nejblizsich letadel: 12.165525
Nalezenych dvojic: 1
LOT - SmartWings
```

**Ukázka 4**

```
Pozice letadel:
-1000000,0: LOT
1000000,0: KLM
5000000,0: AirFrance

Vzdalenost nejblizsich letadel: 2000000.000000
Nalezenych dvojic: 1
LOT - KLM
```

**Ukázka 5**

```
Pozice letadel:
10,10: AirFrance
10,10: Lufthansa
20, 20: Ryanair
20,20: Wizz
20,20: Qantas
10,10: LOT

Vzdalenost nejblizsich letadel: 0.000000
Nalezenych dvojic: 6
AirFrance - Lufthansa
AirFrance - LOT
Lufthansa - LOT
Ryanair - Wizz
Ryanair - Qantas
Wizz - Qantas
```

**Ukázka 6**

```
Pozice letadel:
3,abc: CSA

Nespravny vstup.
```

**Ukázka 7**

```
Pozice letadel:
0,0: LOT
5,8 KLM

Nespravny vstup.
```

---

## Poznámky

- Program má pracovat s dynamickou alokací paměti v jazyce C.
- Nepoužívejte STL knihovny C++ (např. vector, list).
- Nezapomeňte uvolňovat dynamicky alokovanou paměť.
- Program musí být schopen správně zpracovat velká množství dat.
