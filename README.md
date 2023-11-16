# Supaprastintos blokų grandinės (blockchain) kūrimas

## Užduoties atlikimas:
1. Sugeneruoti ~1000 tinklo vartotojų (aka user'ių), kurie turėtų bent tris atributus:  
&emsp;vardą,  
&emsp;viešąjį hash raktą ( public_key )  
&emsp;tam tikros valiutos atsitiktinį balansą (pvz., nuo 100 iki 1000000 valiutos vienetų)  
Atlikimas: <img width="651" alt="uzd1" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/8535b6ee-015f-492d-afdc-00ec5cbc1679">
2. Sugeneruoti ~10000 naujų, į jokį bloką dar neįdėtų, transakcijų pool'ą, o transakcijų struktūra turėtų bent šiuos atributus:  
&emsp;transakcijos ID (kitų transakcijos laukų hash'as),  
&emsp;siuntėjas (jo viešasis raktas)  
&emsp;gavėjas (jo viešasis raktas)  
&emsp;suma  
&emsp;Transakcijų struktūrą galite tobulinti savo nuožiūra pvz., vietoj sąskaitos modelio (angl.account model) galite adaptuoti UTXO modelį.
Atlikimas: <img width="549" alt="uzd2" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/d8929aab-def5-4ea9-a11e-7bab1df92c93">
3. Iš transakcijų pool'o atsitiktinai pasirinkti 100-ą transakcijų, kurias bandysime įdėti į naują bloką. Tarsime, kad naujas blokas talpins apie 100 transakcijų. Reikiama bloko struktūra ir būtini atributai pateikti paveiksle aukščiau.
Atlikimas: <img width="233" alt="3 uzd" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/7448bb2a-a969-4910-b985-99cbec93e6b1">
4. Realizuokite naujų blokų kasimo (angl. mining) Proof-of-Work (PoW) tipo procesą, kurio tikslas yra surasti naujam blokui hash'ą, tenkinantį Difficulty Targer reikalavimą, t.y., hash'o pradžioje esančių nulių tam tikrą skaičių. Nulių skaičius priklauso nuo Jūsų sukurtos hash funkcijos savybių ir efektyvumo. Paeksperimentuokite, kad tai neužtruktų per ilgai. Kaip matyti, bloko kasimui yra reikalingas transakcijų Merkle hash'as, kuris taip pat turi būti realizuotas (žr. detalizaciją versijų reikalavimuose)
Atlikimas: <img width="482" alt="4" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/3f21d5cb-1371-4dd9-9578-92fe15700cb8">
<img width="448" alt="4 uzd" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/8bb79316-b60b-4523-84b6-7cf711ff817a">
<img width="464" alt="4uzd 2" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/442a2e32-6c18-4f32-9f9d-8411dceedd73">
<img width="218" alt="4 uzd 3" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/c27aa943-e2e2-4147-9de5-45143db9004c">
<img width="398" alt="4 uzd 4" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/64ba8b14-519f-4ba6-a58e-299077f7ce7d">
Ši užduotis yra tobulinta pagal V0.2 reikalavimus, paimami 5 kandidatai. Blockchainas yra aprašytas klasės pavidalu, galimą bloką pridėti neieškant kandidatų ir tiesiog kasti bloką arba galima su kandidatais priklausomai nuo kviečiamų klasės funkcijų.
5. Suradus reikiamų savybių naujo bloko hash'ą:  
&emsp;iš transakcijų pool'o ištrinkite į naują bloką priskirtas transakcijas;  
&emsp;"įvykdykite" transakcijas, t.y., atnaujinkite tinklo vartotojų balansus;  
&emsp;naują bloką pridėkite prie blockchain grandinės.  
Atlikimas: <img width="447" alt="uzd 5" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/c8d92d38-67f6-4622-9545-9327cae2ba90">
<img width="191" alt="5" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/b01862f0-bc6d-40dc-b043-f004d9af983d">
<img width="365" alt="5 uzd 3" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/5b9f2dec-ce64-4964-b1f4-611fa4c3c642">
Užduotis tobulinta pagal V0.2 reikalavimus.
6. Kartoti 3-5 žingsnius tol, kol yra laisvų transakcijų. Galima būtų kartoti ir visus 1-5 žingsnius, tokiu būdu įtraukiant ir naujų vartotojų bei transakcijų kūrimą, o ciklą stabdyti naudojantis kitomis logiškomis sąlygomis.
Atlikimas: <img width="194" alt="uzd 6" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/1d679c88-bd74-49df-9df8-675b72d30462">  
Merkle hash relizacija:
<img width="452" alt="merkle root" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/54065091-5e5f-4660-a256-27834c821151">  
Transakcijos hash'o tikrinimas: Pool'o lygmenyje realizuokite validumo patikrinimą, t.y., ar tranksakcijos informacijos hash'as sutampa su transakcijos ID. Tokiu būdu įsitikinsite, kad transakcija nebuvo suklastota, kol ji "keliavo" iki transakcijų pool'o.  
Atlikimas: <img width="480" alt="validation" src="https://github.com/Benjam1nas/Bloku-grandiniu-technologijos/assets/116347949/00ed85b8-92a9-49ed-ad8a-caecb8fc6c69">


 















