/*CONSTANTINESCU Daria - 311CB*/

# TASK 1:

 - Pentru primul task ne folosim de functiile InitHeap, InserareHeap, ExtragereHeap, CreeazaSatelit si ConstruiesteArbore;

 - InitHeap : alocam dinamic heap-ul si vectorul de sateliti, dam valori pentru nrMax, nrElem (nrElem la initializarea heap-ului e zero) si ii dam functia de comparare care in cazul nostru e un Min-Heap dupa frecventa si daca frecventele sunt egale punem in ordine alfabetica;

 - CreeazaSatelit : functia aceasta aloca memorie pentru noul satelit, ii seteaza frecventa si pentru situatia in care e frunza, verificam daca respecta cerinta (numele unui satelit este un sir de cel mult 15 caractere), ii setam numele, st si dr raman NULL si il returnam;
 pentru situatia in care nu e frunza e important pentru functia ConstruiesteArbore. Iar daca apare o eroare la alocarea memoriei (pentru satelit sau pentru nume), se elibereaza memoria deja alocata si se returneaza NULL;

 - InserareHeap : adauga satelitii creati anterior cu functia CreeazaSatelit in heap respectand regula Min-Heap. Mai intai functia verifica daca heap-ul este plin, in acest caz nu mai adaugam elemente in heap (nrelem == nrMax). Insereaza noul satelit la finalul vectorului si incrementeaza nr de elemente din heap. Dupa inserare, functia reordoneaza heap-ul cu functia de comparare. Cat timp elementul nu este radacina, comparam nodul curent cu parintele sau. Daca nodul curent are frecventa mai mica (si in cazul in care au aceeasi frecventa se ia in ordine alfabetica) decat parintele, se face swap intre ele. Procesul se repeta pana cand nodul este la pozitia corecta si heap-ul respecta din nou regula Min-Heap.

 - ConstruiesteArbore : Aici ne folosim de functiile de extragere si creare sateliti.  Cat timp exista cel putin 2 sateliti in heap, extragem 2 sateliti cu frecventa cea mai mica din heap (deoarece heap ul e sortat dupa regula ceruta, la radacina o sa fie cele cu frecventa mai mica). Dupa cream noul satelit, cu numele concatenat si cu frecventa fiind suma celor doua frecvente ale celor 2 sateliti extrasi, cu ajutorul functiei de creare sateliti. Acum intervine a doua metoda din functie, cea in care nu este frunza si creeaza nodul in arbore care are stanga si dreapta nodurile extrase cu frecventa mica. Daca nu puneam aceasta conditie de separare, nu putem verifica daca sateliti adaugati in input respecta regula numelui. Deoarece in heap sunt deja ordonate conform Min-Heap in functie de frecventa (sau nume daca frecv sunt egale) nu am de ce sa imi fac griji de st si dr (sa mai pun o conditie in plus), daca sunt puse corect. Noul satelit se insereaza inapoi in heap, mentinand proprietatea de Min-Heap. Se repeta procesul pana cand in heap mai ramane un singur satelit care devine radacina arborelui binar construit. La final functia returneaza radacina arborelui binar.

 - ExtragereHeap : este functia care extrage satelitii cu frecventa cea mai mica din heap si reface structura de Min-Heap. Daca heap-ul este gol, returnam NULL. Se extrage radacina (o punem intr-o alta variabila de tip satelit min), ultimul element din heap este mutat pe pozitia 0 iar nr de elemente este decrementat, verificam pe rand daca parintele este mai mare decat copilul din stanga sau din dreapta, daca ambii sunt mai mici il ia pe cel mai mic din cei doi si il face parinte, si se repeta acest proces pana heap-ul este din nou ordonat Min-Heap. Ne folosim de minP pentru a tine evidenta parintelui prin compararea lui cu copii, se termina atunci cand minP ramane neschimbat, nu s-au mai gasit copii mai mici decat el. La final returneaza radacina (elementul cu frecventa cea mai mica, de dinainte de reordonare, satelitul min).

 Astfel la final, dupa ce in main.c ne realizam arborele binar conform cerintei, ii dam functiei AfisareNiveluri radacina pentru a afisa arborele creat corect. 

 - AfisareNiveluri : Verifica daca arborele este gol, daca radacina este NULL (adica nu exista), nu face nimic. Aloca memorie pentru un vector care va fi folosit ca o coada pentru parcurgerea arborelui nivel cu nivel. Punem radacina in vector pe pozitia 0, si ne folosim de inc si sf astfel : inc - inceput (va tine cont de nodul curent) si sf - sfarsit (va tine cont de pozitia unde se adauga urmatorul nod in vector). Cat timp sunt noduri (inc < sf), se parcurg nivel cu nivel. Aflam cate noduri se afla pe nivelul curent, se parcurg nodurile nivelului curent si se afiseaza pentru fiecare nod curent numele si frecventa. Daca avem copil in stanga incrementam sf, la fel si pentru copilul din dreapta (daca exista). Dupa ce terminam cu un nivel punem new line si trecem la urmatorul. La final eliberam memoria alocata pentru vectorul aux.

 # TASK 2:

 - DecodificareMesaj : Aceasta functie primeste radacina si codul (sir de caractere cu 0 si 1). Se porneste de la inceputul codului (poz = 0) si parcurgem caracter cu caracter pana cand se termina, adica atunci cand pozitia este mai mare decat lungimea codului. Incepem de la radacina si parcurgem arborele in functie de fiecare caracter al codului : 0 - in stanga si 1 - in dreapta. La fiecare pas trecem la urmatoarea pozitie din cod si ne oprim atunci cand ajungem la un nod de tip frunza. Cand am ajuns intr-o frunza inseamna ca am gasit un satelitul. Repetam procesul pana cand am parcurs tot sirul codificat si gasim toti sateliti. 

 # TASK 3:

 - CautareCod : Avem vectorul de caractere cod in care ne construim codul. Daca nodul este NULL, inseamna ca nu avem nod, returnam 0. Daca numele nodului curent este cel pe care il cautam returnam 1, si punem sfarsit de sir in vectorul de caractere (cod). Daca nu l-am gasit inca, cautam in subarborele stang, punem in vectorul de caractere '0' si apelam recursiv in stanga si crestem nivelul, daca functia returneaza 1 inseamna ca l-a gasit. Daca nu e in stanga cautam in dreapta, punem '1' in vector si apelam recursiv in dreapta pana il gasim. Daca nu e nici in stanga, nici in dreapta returnam 0.

 # TASK 4:

    Pentru acest task ne folosim de 2 functii:

 - GasesteCale : cauta un satelit dupa nume folosindu-se de vectorul cale. Retine drumul de la radacina pana la nodul pe care il cautam, in cale pentru fiecare nivel se retine nodul, pana gasim nodul pe care il cautam.

 - CautaParinte : cale este o matrice de pointeri la sateliti pe care il setam cu 0 la inceput, pentru fiecare satelit pentru care vrem parintele comun avem in aceasta matrice drumul de la radacina catre ele. Calculam lungimea fiecarui drum. Aflam lungimea minima dintre toate caile (pentru a nu iesi in afara vreunei cai la pasul urmator). Parcurgem toate drumurile simultan, pas cu pas, pana cand gasim pozitia in care nodurile difera : cat timp toate drumurile trec prin acelasi nod, continuam iar atunci cand un nod difera fata de celelalte, ne oprim. Ultimul nod comun este parintele comun. Returnam acel nod la final.

 # MAIN :

 In main procesam nr de sateliti si satelitii (nume si frecventa) cititi dintr-un fisier. Verificam argumentele din linia de comanda si deschidem fisierele de intrare/iesire(daca nu reusesim, iese cu eroare). Apoi creez heap-ul unde inserez toti satelitii dupa care construiesc arborele binar pe baza heap-ului. Apoi se trateaza fiecare task, pentru 1 doar afisez arborele pe nivele, pentru 2 citesc nr de coduri si codul si apelez functia de descifrare, pentru 3 citesc nr de sat si nume de sateliti si ii caut in arbore apoi afisez codul binar care ajunge la acele noduri, iar pentru 4 citesc nr de sat si primesc mai multe nume de sateliti si aflu cel mai apropiat stramos folosind functia corespunzatoare. La final, trebuie sa eliberez memoria pentru heap si pentru arbore.
