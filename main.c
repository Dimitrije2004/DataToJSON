#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 1000

char* Remplacer(const char* chaine, const char* MotAremplacer, const char* MotNouveau)
{
	char* resultat;
	int i, cnt = 0;
	int MotNouveau_Longueur = strlen(MotNouveau);
	int MotAremplacer_Longueur = strlen(MotAremplacer);

	for (i = 0; chaine[i] != '\0'; i++) {
		if (strstr(&chaine[i], MotAremplacer) == &chaine[i]) {
			cnt++;

			i += MotAremplacer_Longueur - 1;
		}
	}

	resultat = (char*)malloc(i + cnt * (MotNouveau_Longueur - MotAremplacer_Longueur) + 1);

	i = 0;
	while (*chaine) {

		if (strstr(chaine, MotAremplacer) == chaine) {
			strcpy(&resultat[i], MotNouveau);
			i += MotNouveau_Longueur;
			chaine += MotAremplacer_Longueur;
		}
		else
			resultat[i++] = *chaine++;
	}

	resultat[i] = '\0';
	return resultat;
}

char* Inserer(char chaine[], const char insert[], int pos) {
    char buf[TAILLE_MAX] = {};

    strncpy(buf, chaine, pos);
    int len = strlen(buf);
    strcpy(buf+len, insert);
    len += strlen(insert);
    strcpy(buf+len, chaine+pos);

    strcpy(chaine, buf);

    return chaine;
}

int main()
{
    FILE* monFichier = NULL;
    FILE* monFichierJSON = NULL;
	char Data[TAILLE_MAX] = "";

    monFichier = fopen("Data.txt","r");

    fgets(Data,TAILLE_MAX,monFichier);

    char Data2[TAILLE_MAX];

    strncpy(Data2, Data, strlen(Data) -1);

	char* result = Remplacer(Data2, ":", "\" : \"");
    char* result2 = Remplacer(result,";","\", \n\"");

    char* result3 = Inserer(result2,"\"",0);

    strncat(result3,"\"",1);

    monFichierJSON = fopen("Donnee.json","w");

    fputs(result3,monFichierJSON);

	printf("%s\n", result3);

	return 0;
}
