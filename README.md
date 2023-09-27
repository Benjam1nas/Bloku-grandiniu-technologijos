# Hash_funkcija_v0.1
## Pseudo Kodas:  

function value(input):  
&emsp;ASCII_VALUE = 0  
&emsp;for each character c in input:  
&emsp;&emsp;ASCII_VALUE += ASCII value of c  
&emsp;return ASCII_VALUE  
  
function generateHash(input):  
&emsp;Hash = ""  
&emsp;unique_number = convert value(input) to string  
&emsp;symbols = "0abc1def2ghi3jkl4mno5pqr6st7uvw8xyz9"  
&emsp;for each character c in unique_number:  
&emsp;&emsp;Hash += symbols[c % 31]  
&emsp;i = 0  
&emsp;while length of Hash is not 32:  
&emsp;&emsp;Hash += symbols[Hash[i] % 31]  
&emsp;return Hash  
  
function stringToHex(input):  
&emsp;hexString = ""  
&emsp;for each character c in input:  
&emsp;&emsp;append hexadecimal representation of ASCII value of c to hexString, padded to width 2 with leading zeros  
&emsp;return hexString  
  
function main(argc, argv):  
&emsp;input = ""  
&emsp;if argc is 2:  
&emsp;&emsp;open input file specified in argv[1]  
&emsp;&emsp;if file cannot be opened:  
&emsp;&emsp;&emsp;display "Error: Could not open input file " + argv[1]  
&emsp;&emsp;&emsp;return 1  
&emsp;&emsp;while not end of file:  
&emsp;&emsp;&emsp;read a character x from the file  
&emsp;&emsp;&emsp;append x to input  
&emsp;else if argc is 1:  
&emsp;&emsp;display "Enter your input: "  
&emsp;&emsp;read a line of text from the user and store it in input  
&emsp;else:  
&emsp;&emsp;display "Usage: " + argv[0] + " [input_file]"  
&emsp;&emsp;return 1  
&emsp;output = generateHash(input)  
&emsp;hexOutput = stringToHex(output)  
&emsp;display "Hash: " + hexOutput  
&emsp;return 0  

## Eksperimentinė analizė:
1. Susikurkite testinių įvedimo failų pavyzdžių, tokių kad:  
&emsp;Bent du failai būtų sudaryti tik iš vieno, tačiau skirtingo, simbolio.  
&emsp;&emsp;1 failo išvedimas: <img width="391" alt="1 simbolis" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/2b095c33-66b7-44ea-a7ee-44bf4e9a8c15">  
&emsp;&emsp;2 failo išvedimas: <img width="392" alt="1 kitoks simbolis" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/4087047c-ebeb-4be2-8e0c-7f9c956c08c7">  
&emsp;Bent du failai būtų sudaryti iš daug (> 1000) atsitiktinai sugeneruotų simbolių.  
&emsp;&emsp;1 failo išvedimas: <img width="394" alt="random_c_1" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/dcaaf3a2-b44d-44f5-b729-893c8e9bae53">  
&emsp;&emsp;2 failo išvedimas: <img width="392" alt="random_c_2" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/c6761c3b-a1af-4e4b-b363-b5f6ad91a53d">  
&emsp;Bent du failai būtų sudaryti iš daug (> 1000) simbolių, bet skirtųsi vienas nuo kito tik vienu (pvz. vidurinėje pozicijoje esančiu) simboliu.  
&emsp;&emsp;1 failo išvedimas:<img width="395" alt="random1" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/4fe68e82-2af3-4f55-86bb-02c7585c3f5a">  
&emsp;&emsp;2 failo išvedimas: <img width="390" alt="random1changed" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/a2b32257-a9db-4c79-803a-7951cba5abce">  
&emsp;Tuščio failo.  
&emsp;&emsp;failo išvedimas:  <img width="389" alt="tuscias" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/1bc5bb46-804b-43fa-87b9-f69339e0c987">

2. Naudojant pirmame žingsnyje susikurtus testinius failus, kaip Jūsų programos input'us,
įsitikinkite, kad Jūsų hash funkcija atitinka 1-3 reikalavimus, t.y., nepriklausomai nuo
Input'o, Output'ai visada yra vienodo dydžio, o to paties failo hash'as yra tas pats
(deterministiškumas).  
&emsp;Pirmas reikalavimas: Maišos funkcijos įėjimas (angl. input) gali būti bet kokio dydžio simbolių eilutė (angl. string). **ATITINKA**  
&emsp;Antras reikalavimas: Maišos funkcijos išėjimas (angl. output) visuomet yra to paties, fiksuoto, dydžio rezultatas (pageidautina 256 bit'ų ilgio, t.y., 64 simbolių hex'as).  **ATITINKA**  
&emsp; Trečias reikalavimas: Maišos funkcija yra deterministinė, t. y., tam pačiam įvedimui (input'ui) išvedimas (output'as) visuomet yra tas pats. **ATITINKA**  

3. Ištirkite Jūsų sukurtos hash funkcijos efektyvumą, t.y., patikrinkite, kaip Jūsų hash'avimo funkcija atitinka 4-ą reikalavimą. Tuo tikslu pirmiausiai suhash'uokite vieną eilutę iš failo konstitucija.txt ir išmatuokite kiek laiko visa tai užtruko.  
&emsp;Tuomet pakartokite eksperimentą hash'uojant 2 eilutes, 4 eilutes, 8 eilutes ir t.t. (16, 32, 64, ...). Pažymime, kad reikia matuoti, tik hash'avimo funkcijos veikimo laiką (be input'o nuskaitymo/parengimo). Reiktų pateikti suvidurkintą (kartojant tą patį eksperimentą pvz. 5 kartus) hash'avimo laiko priklausomybę nuo input dydžio (eilučių skaičiaus). Kitaip sakant, reikia ištirti, kaip hash'avimo laikas didėja, didėjant input dydžiui.

| 2 eilutės | 4 eilutės | 8 eilutės | 16 eilučių | 32 eilutės | 64 eilutės | 128 eilutės | 256 eilutės |
| ---       | ---       | ---       | ---        | ---        | ---        | ---         | ---         |
| 0.000516s | 0.000558s | 0.000566s | 0.000594s  | 0.000614s  | 0.000649s  | 0.000694s   | 0.000736s   |  

&emsp;Rezultatą prašytume pavaizduoti grafiškai, parodant kaip laikas priklauso nuo input dydžio.  
<img width="361" alt="laikai" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/a8237eae-263a-40af-b036-665e87fa934e">  
&emsp;Galima (bet ne privaloma) ir algoritmų sudėtingumą (tiesinis, kvadratinis, logaritminis, eksponentinis ir pan.) pasitelkti, norint įvertinti šią priklausomybę.  
&emsp;&emsp;**Algoritmo sudėtingumas yra O(n). Visos naudojamos funkcijos priklauso nuo ivedamo parametro ir ciklai vykdomi n kartų.**

4. Susigeneruokite bent 100 000 atsitiktinių simbolių eilučių ( string 'ų) porų, pvz. (asdfg, hijkl), apsiribojant iki 1000 simbolių ilgiu. Toje pačioje poroje esančių string'ų ilgiai turi sutapti, tačiau skirtingos poros gali būti skirtingo ilgio. Rekomenduojame susigeneruoti taip: 25 000 porų, kurių ilgis 10 simbolių, kitas 25 000 porų, kurių ilgis - 100, dar kitas 25 000 poras - 500, ir galiausiai likusias 25 000 poras, kurių ilgis - 1000 simbolių.  
5. Naudodami 4 žingsnyje sugeneruotas poras, patikrinkite, ar visais atvejais gautieji porų hash'ai nesutampa. O jeigu sutampta, tai kaip dažnai tai nutinka. Tokiu būdu (jei visuomet hash'ai nesutampa) bent dalinai įsitikinsite, kad Jūsų hash funkcija atitinka 6-ą reikalavimą, t.y., atsparumą kolizijai.
**25 000 porų, ilgis 10 simbolių rezultatas:** <img width="395" alt="pirma pora" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/5895e965-acae-49f6-ae9b-2f2f54bc5f74">  
**25 000 porų, ilgis 100 simbolių rezultatas:** <img width="394" alt="pora100" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/b22a927c-7b34-4dec-a1a1-4fe4dacefc19">  
**25 000 porų, ilgis 500 simbolių rezultatas:** <img width="389" alt="pora500" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/ee2c225b-b782-4af0-992c-d370a357235b">  
**25 000 porų, ilgis 1000 simbolių rezultatas:** <img width="390" alt="pora1000" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/aa09b614-aef9-4004-a775-f77bcec67e40">
**Kolizijos nėra**




