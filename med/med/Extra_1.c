#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef enum Beneficiu Beneficiu;
typedef struct PastaDeDinti PastaDeDinti;
typedef struct NodGrafLP NodGrafLP;
typedef struct NodGrafLS NodGrafLS;
typedef struct NodArbore NodArbore;
typedef struct NodLD NodLD;
typedef struct StivaStergereNodGraf StivaStergereNodGraf;

enum Beneficiu { AlbireDinti = 1, ExtraProtectie = 2, StopSangerare = 3 };

struct PastaDeDinti
{
	int id;
	char* marca;
	float pret;
	int cantitate;
	long codDeBare;
	Beneficiu beneficiu;
	int* rating;
	int nrRating;
};

struct NodGrafLP
{
	PastaDeDinti info;
	NodGrafLP* next;
	NodGrafLS* vecini;
};

struct NodGrafLS
{
	NodGrafLP* inf;
	NodGrafLS* next;
};

struct StivaStergereNodGraf
{
	int id;
	StivaStergereNodGraf* next;
};
struct NodArbore
{
	PastaDeDinti info;
	NodArbore* stanga;
	NodArbore* dreapta;
};

struct NodLD
{
	PastaDeDinti info;
	NodLD* next;
	NodLD* prev;

};

PastaDeDinti initializarePastaDeDinti(int _id, char* _marca, float _pret, int _cantitate, long _codDeBare, Beneficiu _beneficiu, int* _rating, int _nrRating)
{
	PastaDeDinti pd;
	pd.id = _id;
	pd.pret = _pret;
	pd.cantitate = _cantitate;
	pd.codDeBare = _codDeBare;
	pd.beneficiu = _beneficiu;
	pd.marca = (char*)malloc(strlen(_marca) + 1);
	strcpy(pd.marca, _marca);

	pd.nrRating = _nrRating;
	pd.rating = (int*)malloc(sizeof(int) * _nrRating);
	for (int i = 0; i < _nrRating; i++)
	{
		pd.rating[i] = _rating[i];
	}
}

PastaDeDinti citireFisier(FILE* streamFisier)
{
	if (streamFisier != NULL)
	{
		PastaDeDinti pd;
		char aux[30];

		//id
		fgets(aux, 10, streamFisier);
		pd.id = atoi(aux);

		//marca
		fgets(aux, 30, streamFisier);
		char* sir = strtok(aux, "\n");
		pd.marca = (char*)malloc(strlen(sir) + 1);
		strcpy(pd.marca, sir);

		//pret
		fgets(aux, 10, streamFisier);
		pd.pret = atof(aux);
		//cantitate
		fgets(aux, 10, streamFisier);
		pd.cantitate = atoi(aux);

		//cod de bare
		fgets(aux, 20, streamFisier);
		pd.codDeBare = atol(aux);

		//beneficiu
		fgets(aux, 30, streamFisier);
		char* sirb = strtok(aux, "\n");
		char* beneficiuChar = (char*)malloc(strlen(sirb) + 1);
		strcpy(beneficiuChar, sir);
		if (strcmp(beneficiuChar, "AlbireDinti") == 0)
		{
			pd.beneficiu = 1;
		}
		if (strcmp(beneficiuChar, "ExtraProtectie") == 0)
		{
			pd.beneficiu = 2;
		}
		if (strcmp(beneficiuChar, "StopSangerare") == 0)
		{
			pd.beneficiu = 3;
		}


		//nrRating
		fgets(aux, 10, streamFisier);
		pd.nrRating = atoi(aux);

		//rating
		pd.rating = (int*)malloc(pd.nrRating * sizeof(int));
		for (int i = 0; i < pd.nrRating; i++)
		{
			fgets(aux, 10, streamFisier);
			pd.rating[i] = atoi(aux);
		}
		return pd;
	}
}

char* getBeneficiuInCaractere(Beneficiu b)
{
	if (b == 1)
	{
		return "AlbireDinti";
	}
	if (b == 2)
	{
		return "ExtraProtectie";
	}
	if (b == 3)
	{
		return "StopSangerare";
	}
	return "Beneficiu gresit";
}

void afisarePastaDeDinti(PastaDeDinti pd)
{
	printf("id - %d, marca - %s, pret - %.2f, cantitate - %d, cod de bare - %ld, beneficiu - %s, numar rating - %d, valori rating - ",
		pd.id, pd.marca, pd.pret, pd.cantitate, pd.codDeBare, getBeneficiuInCaractere(pd.beneficiu), pd.nrRating);
	for (int i = 0; i < pd.nrRating; i++)
	{
		printf("%d, ", pd.rating[i]);
	}
	printf("\n");
}

NodGrafLP* inserareGrafLP(NodGrafLP* graf, PastaDeDinti pd)
{
	NodGrafLP* nou = (NodGrafLP*)malloc(sizeof(NodGrafLP));
	nou->info = pd;
	nou->next = NULL;
	nou->vecini = NULL;

	if (graf == NULL)
	{
		return nou;
	}
	else
	{
		NodGrafLP* aux = graf;
		while (aux->next)
			aux = aux->next;
		aux->next = nou;
	}
	return graf;
}
NodGrafLS* inserareGrafLS(NodGrafLS* cap, NodGrafLP* info)
{
	NodGrafLS* nou = (NodGrafLS*)malloc(sizeof(NodGrafLS));
	nou->inf = info;
	nou->next = NULL;
	if (cap == NULL)
	{
		return nou;
	}
	else
	{
		NodGrafLS* aux = cap;
		while (aux->next)
			aux = aux->next;
		aux->next = nou;
	}
	return cap;
}

void afisareVecini(NodGrafLP* nod)
{
	NodGrafLS* aux = nod->vecini;
	while (aux)
	{
		afisarePastaDeDinti(aux->inf->info);
		aux = aux->next;
	}
}

void afisareGrafLP(NodGrafLP* graf)
{
	while (graf)
	{
		printf("Pasta de dinti din lista principala:\n");
		afisarePastaDeDinti(graf->info);
		printf("Pastele de dinti din lista secundara:\n");
		afisareVecini(graf);
		printf("\n");
		graf = graf->next;
	}
}

NodGrafLP* cautareNod(NodGrafLP* graf, int id)
{
	while (graf && graf->info.id != id)
	{
		graf = graf->next;
	}
	return graf;
}

void inserareVecini(NodGrafLP* graf, int id1, int id2)
{
	NodGrafLP* nod1 = cautareNod(graf, id1);
	NodGrafLP* nod2 = cautareNod(graf, id2);

	if (nod1 && nod2)
	{
		nod1->vecini = inserareGrafLS(nod1->vecini, nod2);
		nod2->vecini = inserareGrafLS(nod2->vecini, nod1);
	}
}


//dezalocarea vecinilor unui nod
NodGrafLS* dezalocareVecini(NodGrafLP* nod)
{
	NodGrafLS* vecini = nod->vecini;
	while (vecini)
	{
		NodGrafLS* vecin_urmator = vecini->next;
		free(vecini);
		vecini = vecin_urmator;
	}
	return vecini;
}

//cerinta b - dezalocarea grafului
NodGrafLP* dezalocareGraf(NodGrafLP* graf)
{
	NodGrafLP* aux = graf;
	while (aux)
	{
		NodGrafLP* aux2 = aux->next;
		if (aux->vecini)
		{
			aux->vecini = dezalocareVecini(aux);
		}
		free(aux->info.rating);
		free(aux->info.marca);
		free(aux);
		aux = aux2;

	}
	return aux;
}

//cerinta a - dezalocarea unui nod din graf
NodGrafLP* dezalocareGrafNodId(NodGrafLP* graf, int id)
{
	NodGrafLP* nodDeSters = cautareNod(graf, id);
	//parcurg vecinii si le pun id-urile in stiva
	//ma duc in nodurile cu acele id-uri si-l scot pe nodul de sters

	nodDeSters->vecini = dezalocareVecini(nodDeSters);


	//elimin nodul de sters din LP
	return graf;
}





NodArbore* inserareArbore(NodArbore* radacina, PastaDeDinti pd)
{
	if (radacina == NULL)
	{
		NodArbore* nod = (NodArbore*)malloc(sizeof(NodArbore));
		nod->info = pd;
		nod->stanga = NULL;
		nod->dreapta = NULL;
		radacina = nod;
	}
	else
	{
		if (pd.id < radacina->info.id)
		{
			radacina->stanga = inserareArbore(radacina->stanga, pd);
		}
		else
		{
			radacina->dreapta = inserareArbore(radacina->dreapta, pd);
		}
	}
	return radacina;
}

void parcurgereInordine(NodArbore* radacina)
{
	if (radacina)
	{
		parcurgereInordine(radacina->stanga);
		afisarePastaDeDinti(radacina->info);
		parcurgereInordine(radacina->dreapta);
	}
}

//cerinta c
//NodArbore* stergereArboreNodId(NodArbore* radacina, int id)
//{
//	if (radacina && radacina->info.id!=id)
//	{
//		if (id < radacina->info.id)
//		{
//			radacina->stanga = stergereArboreNodId(radacina->stanga, id);
//		}
//		else
//		{
//			radacina->dreapta = stergereArboreNodId(radacina->dreapta, id);
//		}
//	}
//	else
//	{
//		if (radacina->info.id == id)
//		{
//			if (radacina->stanga == NULL && radacina->dreapta == NULL)
//			{
//				NodArbore* aux = radacina;
//				free(aux->info.marca);
//				free(aux->info.rating);
//				free(aux);
//				radacina = NULL;
//			}
//			else
//			{
//				if (radacina->stanga == NULL)
//				{
//					NodArbore* aux = radacina;
//					NodArbore* aux2 = radacina->dreapta;
//					free(aux->info.marca);
//					free(aux->info.rating);
//					free(aux);
//					radacina = aux2;
//				}
//				else
//				{
//					if (radacina->dreapta == NULL)
//					{
//						NodArbore* aux = radacina;
//						NodArbore* aux2 = radacina->stanga;
//						free(aux->info.marca);
//						free(aux->info.rating);
//						free(aux);
//						radacina = aux2;
//					}
//					else
//					{
//						NodArbore* aux = radacina->stanga;
//						NodArbore* aux2 = (NodArbore*)malloc(sizeof(NodArbore));
//						while (aux->dreapta)
//						{
//							aux2 = aux;
//							aux = aux->dreapta;
//						}
//						PastaDeDinti auxpd = aux->info;
//						aux->info = radacina->info;
//						radacina->info = auxpd;
//						if (aux->stanga == NULL)
//						{
//							NodArbore* auxx = aux;
//							free(auxx->info.marca);
//							free(auxx->info.rating);
//							free(auxx);
//							if (aux2)
//							{
//								aux2->dreapta = NULL;
//							}
//							aux = NULL;
//						}
//						else
//						{
//							NodArbore* auxx = aux;
//							NodArbore* auxx2 = aux->stanga;
//							free(auxx->info.marca);
//							free(auxx->info.rating);
//							free(auxx);
//							aux = auxx2;
//
//
//							printf("fhufw");
//						}
//					
//					}
//				}
//			}
//		}
//	}
//	return radacina;
//}
void stergereArboreNodId(NodArbore** radacina, int id)
{
	if ((*radacina) && (*radacina)->info.id != id)
	{
		if (id < (*radacina)->info.id)
		{
			stergereArboreNodId(&(*radacina)->stanga, id);
		}
		else
		{
			stergereArboreNodId(&(*radacina)->dreapta, id);
		}
	}
	else
	{
		if ((*radacina)->info.id == id)
		{
			if ((*radacina)->stanga == NULL && (*radacina)->dreapta == NULL)
			{
				NodArbore* aux = radacina;
				free(aux->info.marca);
				free(aux->info.rating);
				free(aux);
				radacina = NULL;
			}
			else if ((*radacina)->stanga == NULL && (*radacina)->dreapta != NULL)
			{
				NodArbore* aux = (*radacina);
				NodArbore* aux2 = (*radacina)->dreapta;
				free(aux->info.marca);
				free(aux->info.rating);
				free(aux);
				(*radacina) = aux2;
			}
			else if ((*radacina)->dreapta == NULL && (*radacina)->stanga != NULL)
			{
					NodArbore* aux = (*radacina);
					NodArbore* aux2 = (*radacina)->stanga;
					free(aux->info.marca);
					free(aux->info.rating);
					free(aux);
					(*radacina) = aux2;
			}
			else if ((*radacina)->dreapta != NULL && (*radacina)->stanga != NULL)	// both children
			{
				NodArbore* toDelete = NULL;
				if ((*radacina)->dreapta->stanga != NULL)	// comparam ca in poza din ppt
				{
					if ((*radacina)->stanga->info.id < (*radacina)->dreapta->stanga->info.id) {
						toDelete = (*radacina)->dreapta->stanga;
						if (toDelete->dreapta != NULL)
							(*radacina)->dreapta->stanga = toDelete->dreapta;
					}
				}
				else {
					toDelete = (*radacina)->stanga;
					if (toDelete->stanga != NULL)
						(*radacina)->stanga = toDelete->stanga;
				}

				(*radacina)->info = toDelete->info;
				free(toDelete);

				//NodArbore* aux = (*radacina)->stanga;
				//NodArbore* aux2 = (NodArbore*)malloc(sizeof(NodArbore));
				//while (aux->dreapta)
				//{
				//	aux2 = aux;
				//	aux = aux->dreapta;
				//}
				//PastaDeDinti auxpd = aux->info;
				//aux->info = (*radacina)->info;
				//(*radacina)->info = auxpd;
				//if (aux->stanga == NULL)
				//{
				//	NodArbore* auxx = aux;
				//	free(auxx->info.marca);
				//	free(auxx->info.rating);
				//	free(auxx);
				//	if (aux2)
				//	{
				//		aux2->dreapta = NULL;
				//	}
				//	aux = NULL;
				//}
				//else
				//{
				//	NodArbore* auxx = aux;
				//	NodArbore* auxx2 = aux->stanga;
				//	free(auxx->info.marca);
				//	free(auxx->info.rating);
				//	free(auxx);
				//	aux = auxx2;


				//	//printf("fhufw");
				///*}*/
			}
		}
	}
}

void main()
{
	//citirea din fisier - cerinta e
	char numefisier[11] = "pasta0.txt";
	PastaDeDinti p[8];
	for (int i = 0; i < 8; i++)
	{
		numefisier[5]++;
		FILE* fisier = fopen(numefisier, "r");
		p[i] = citireFisier(fisier);
		afisarePastaDeDinti(p[i]);
		fclose(fisier);
	}
	printf("\n\n----------\n\n");
	NodGrafLP* graf = NULL;
	for (int i = 0; i < 8; i++)
	{
		graf = inserareGrafLP(graf, p[i]);
	}
	inserareVecini(graf, 1, 2);
	inserareVecini(graf, 1, 3);
	inserareVecini(graf, 1, 4);
	inserareVecini(graf, 2, 4);
	inserareVecini(graf, 2, 8);
	inserareVecini(graf, 2, 7);
	inserareVecini(graf, 3, 5);
	inserareVecini(graf, 5, 6);
	inserareVecini(graf, 7, 6);
	inserareVecini(graf, 8, 7);

	afisareGrafLP(graf);
	printf("\n\n----------\n\n");
	//dezalocare Graf - cerinta b
	//graf = dezalocareGraf(graf);
	//graf = dezalocareNodId(graf, 5);
	//afisareGrafLP(graf);


	printf("\n\n----------\n\n");
	//grija mare daca rulez asta dupa dezalocarea grafului, ca se sterg pastele de dinti
	NodArbore* radacina = NULL;
	radacina = inserareArbore(radacina, p[4]);
	radacina = inserareArbore(radacina, p[2]);
	radacina = inserareArbore(radacina, p[5]);
	radacina = inserareArbore(radacina, p[7]);
	radacina = inserareArbore(radacina, p[6]);
	radacina = inserareArbore(radacina, p[3]);
	radacina = inserareArbore(radacina, p[1]);
	radacina = inserareArbore(radacina, p[0]);

	parcurgereInordine(radacina);

	stergereArboreNodId(&radacina, 3);

	printf("\n\n----------\n\n");
	parcurgereInordine(radacina);

}