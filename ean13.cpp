#include<cstring>
#include <iostream>
#include <string>
#include <fstream>
/*
* Compilat pe Ubuntu 20.04 folosind comanda:
* g++ ean13.cpp
*/

using namespace std;

void G(int valoare, int bin[], int poz);
void L(int valoare, int bin[], int poz);
void R(int valoare, int bin[], int poz);


int main() {
    // Siruri necesare:
	int b[95]; // va fi sirul binar final.
	char codRO[]="594"; // codul Romaniei.
	char denumire[21], codDat[10];
	
	char sirChars[]="0123456789";

	// Un fel de titlu:
	cout << "Coduri de bare" << endl;
	
	// Prima solicitare:
    cout << "Introduceti denumirea produsului (maxim 20 caractere): " << endl;
    cin >> denumire;

    // A doua solicitare:
    cout << "Introduceti codul produsului (maxim 9 cifre, fara spatii): " << endl;
    cin >> codDat;

    // Verificam daca sunt mai putin de 9 cifre:
    int lungime = strlen(codDat);

    int i=0;
while(codDat[i]>='0' && codDat[i]<='9') {
i++;
}
if(i!=lungime) {
cout << "Ati introdus un cod eronat: " << codDat << endl;
return 0;
}

// Ne ocupam acum de cifrele 7:
char sirSapte[9]=""; // sirul initial este vid
if(lungime<9) {
int j;
for(j=0; j<9-lungime; j++) {
sirSapte[j] = '7';
}
// Limitez sirSapte la dreapta adaugandu-i un caracter '\0'
sirSapte[j]='\0';
}

// Unim codul Romaniei, cu 7-urile si cu cifrele introduse manual:
char ean13[13]; // codul final, ro+sapte+cifre+control.
strcpy(ean13, codRO);
strcat(ean13, sirSapte);
strcat(ean13, codDat);

// cout << "Primele 12 caractere sunt: " << ean13 << endl;

// De acum avem nevoie de valori numerice pentru a calcula cifra de control:
int nean13[13];
for(i=0; i<12; i++) {
nean13[i] = ean13[i]-48;
}

// Calculam cifra de control:
int s1=0, s2=0;
for(i=0; i<12; i=i+2) {
s1=s1+nean13[i];
s2=s2+nean13[i+1];
}
int S=s1+3*s2;
nean13[12]=10-S%10; // cifra de control.

cout << "Codul de bare generat este: ";
	for(i=0; i<13; i++) {
cout << "" << nean13[i];
}
	cout << endl;

	// Incepem de aici sa umplem sirul binar b[95]:
	// Il facem mai intai pe tot sa fie egal cu 0, apoi ne va fi mai usor:
	for(i=0; i<95; i++) {
		b[i]=0;
	}

// Se codifica inceputul cu 101, stim ca b[1] e deja 0:
b[0]=b[2]=1;

// Acum de la 1 la 6 - L G G L L G:
L(nean13[1], b, 3);
G(nean13[2], b, 10);
G(nean13[3], b, 17);
L(nean13[4], b, 24);
L(nean13[5], b, 31);
G(nean13[6], b, 38);

// Se codifica zona de separare din mijloc, 01010:
b[46]=b[48]=1;

// Se codifica partea a doua a codului (nean13[7] la nean13[12]) cu functia r:
for(i=0; i<6; i++) {
R(nean13[7+i], b, 50+i*7);
}

// Se codifica partea finala a codului cu 101:
b[92] = b[94] = 1;


// Sa il afisam si in binar:
cout << "Varianta binara este: " << endl;
for(i=0; i<95; i++) {
	cout << b[i];
}
cout << endl;


// Creare html cu SVG:
	fstream cod;
	string numeFisier=denumire;
cod.open(numeFisier+".html", ios::out);
cod << "<!DOCTYPE html>" << endl;
cod << "<html>" << endl;
cod << "<head>" << endl;
cod << "<title>" << endl;
cod << "Cod pentru produsul " << numeFisier << endl;
cod << "</title>" << endl;
cod << "</head>" << endl;
cod << "<body>" << endl;
cod << "<svg height=\"50\" width=\"200\">" << endl;

// Doi pixeli pentru fiecare bara
int pozx = 10; // De la acest x incep trasarea
for(i=0; i<95; i++) {
if(b[i]==1) // se traseaza o linie
cod << "<line x1=\"" << pozx << "\" y1=\"20\" x2=\"" << pozx
<< "\" y2=\"50\" style=\"stroke:rgb(0,0,0); stroke-width:2\" />" << endl;
// Avans cu 2px, indiferent daca s-a trasat sau nu
pozx=pozx+2;
}
cod << "</body>" << endl;
cod << "</html>" << endl;
cod.close();
// sfarsit functie desenare in SVG.

// Afisam rezultatul:
cout << "Codul de bare a fost creat in fisierul " << numeFisier << ".html." << endl;


} // sfarsit main function.


// Functia L:
void L(int valoare, int bin[], int poz) {
switch(valoare)
{
case 0: // 0001101
bin[poz+3]=bin[poz+4]=bin[poz+6]=1;
break;
case 1: // 0011001
bin[poz+2]=bin[poz+3]=bin[poz+6]=1;
break;
case 2: // 0010011
bin[poz+2]=bin[poz+5]=bin[poz+6]=1;
break;
case 3: // 0111101
bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+4]=bin[poz+6]=1;
break;
case 4: // 0100011
bin[poz+1]=bin[poz+5]=bin[poz+6]=1;
break;
case 5: // 0110001
bin[poz+1]=bin[poz+2]=bin[poz+6]=1;
break;
case 6: // 0101111
bin[poz+1]=bin[poz+3]=bin[poz+4]=bin[poz+5]=bin[poz+6]=1;
break;
case 7: // 0111011
bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+5]=bin[poz+6]=1;
break;
case 8: // 0110111
bin[poz+1]=bin[poz+2]=bin[poz+4]=bin[poz+5]=bin[poz+6]=1;
break;
case 9: // 0001011
bin[poz+3]=bin[poz+5]=bin[poz+6]=1;
break;
}
} // sfarsit functia L.

// Functia G:
void G(int valoare, int bin[], int poz) {
switch(valoare)
{
case 0: // 0100111
bin[poz+1]=bin[poz+4]=bin[poz+5]=bin[poz+6]=1;
break;
case 1: // 0110011
bin[poz+1]=bin[poz+2]=bin[poz+5]=bin[poz+6]=1;
break;
case 2: // 0111011
bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+5]=bin[poz+6]=1;
break;
case 3: // 0100001
bin[poz+1]=bin[poz+6]=1;
break;
case 4: // 0011101
bin[poz+2]=bin[poz+3]=bin[poz+4]=bin[poz+6]=1;
break;
case 5: // 0111001
bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+6]=1;
break;
case 6: // 0000101
bin[poz+4]=bin[poz+6]=1;
break;
case 7: // 0010001
bin[poz+2]=bin[poz+6]=1;
break;
case 8: // 0001001
bin[poz+3]=bin[poz+6]=1;
break;
case 9: // 0010111
bin[poz+2]=bin[poz+4]=bin[poz+5]=bin[poz+6]=1;
break;
}
} // sfarsit functia G.

// Functia R:
void R(int valoare, int bin[], int poz) {
switch(valoare)
{
case 0: // 1110010
bin[poz+0]=bin[poz+1]=bin[poz+2]=bin[poz+5]=1;
break;
case 1: // 1100110
bin[poz+0]=bin[poz+1]=bin[poz+4]=bin[poz+5]=1;
break;
case 2: // 1101100
bin[poz+0]=bin[poz+1]=bin[poz+4]=bin[poz+5]=1;
break;
case 3: // 1000010
bin[poz+0]=bin[poz+5]=1;
break;
case 4: // 1011100
bin[poz+0]=bin[poz+2]=bin[poz+3]=bin[poz+4]=1;
break;
case 5: // 1001110
bin[poz+0]=bin[poz+3]=bin[poz+4]=bin[poz+5]=1;
break;
case 6: // 1010000
bin[poz+0]=bin[poz+2]=1;
break;
case 7: // 1000100
bin[poz+0]=bin[poz+4]=1;
break;
case 8: // 1001000
bin[poz+0]=bin[poz+3]=1;
break;
case 9: // 1110100
bin[poz+0]=bin[poz+1]=bin[poz+2]=bin[poz+4]=1;
break;
}
} // sfarsit functia R.
