/*
- Este jogo foi criado com a utilização de 4 ficheiros "categoria.txt" colocados na pasta do .exe
- Pode alterar os itens nos ficheiros txt sem alterar o código, desde que mantenham o número de itens
  iguais em todos os ficheiros
- Pode acrescentar/alterar categorias alterando código no main() na secção do menu e no switch.
- O código inicial foi pensado para 10 itens em cada categoria, pode aumentar alterando
  o array sortido[x][20] onde x é o número de itens e #define MAXLINHA x e
  strcpy(palavra, sortido[rand() % x]);
- */

#define _CRT_SECURE_NO_WARNINGS
#define MAXNOME 20
#define MAXLINHA 10


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <time.h>

char sortido[10][20]; // todos os ficeiros categoria têm 10 itens

void Grafico(int a)
{
	system("cls");
	printf("- - - - - - - - Jogo da Forca - - - - - - - -\n\n");
	printf("   %c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 187);
	printf("   %c        %c\n", 186, 186);
	printf("   %c        |\n", 186);
	//printf("   %c        O\n", 186); OK
	a <= 0 ? printf("   %c         \n", 186) : NULL;
	a >= 1 ? printf("   %c        O\n", 186) : NULL;
	a == 2 ? printf("   %c        |\n", 186) : NULL;
	a == 3 ? printf("   %c       /|\n", 186) : NULL;
	a >= 4 ? printf("   %c       /|\\\n", 186) : NULL;
	a == 5 ? printf("   %c       / \n", 186) : NULL;
	a >= 6 ? printf("   %c       / \\\n", 186) : NULL;
	printf("   %c\n", 186);
	printf("   %c\n", 186);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 202, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	printf("\n\n\n");
}

void LerCategoria(int *a) //ler todos os itens do ficheiro .txt para o array sortido 
{
	FILE* fhCategoria;
	char palavra[20];
	fhCategoria = NULL;
	fhCategoria = fopen(a, "r");

	for (int i = 0; i < MAXLINHA; i++) //inicializar palavra[]
	{
		palavra[i] = '\0';
	}
	int i = 0;

	while ((fscanf(fhCategoria, "%s", palavra)) != EOF)
	{
		strcpy(sortido[i], palavra);
		i++;
	}
}

main()
{
	char resp = '\0';
	do
	{
		int jogada = 0, categoria = 0, engano = 0, acerto = 0, correct = 0;
		char letra = '\0';
		const char nomecategoria[4][15] = { "Profissoes", "Animais", "Cidades", "Nomes" };
		char fileCategoria[20] = { '\0' };
		char palavra[20] = { '\0' };
		char mascara[20] = { '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };
		srand(time(NULL));

		//menu
		system("cls");
		printf("- - - - - - - - Jogo da Forca - - - - - - - -\n\n");
		printf("1-Profissoes\n");
		printf("2-Animais\n");
		printf("3-Cidads/Paises\n");
		printf("4-Nomes\n");

		do
		{
			printf("\nSeleccione uma categoria: ");
			scanf_s("%d", &categoria);
			getchar();
			switch (categoria)
			{
			case 1:
				strcpy(fileCategoria, "Profissoes.txt");
				LerCategoria(fileCategoria);
				break;

			case 2:
				strcpy(fileCategoria, "Animais.txt");
				LerCategoria(fileCategoria);
				break;

			case 3:
				strcpy(fileCategoria, "Cidades.txt");
				LerCategoria(fileCategoria);
				break;

			case 4:
				strcpy(fileCategoria, "Nomes.txt");
				LerCategoria(fileCategoria);
				break;

			default:
				printf("\nOpcao invalida. Novas categorias na proxima expansao!\n");
				system("pause");
				break;
			}
		} while (categoria > 4);

		strcpy(palavra, sortido[rand() % 10]); //escolher aleatoriamente palavra/posição do array sortido[i]

		do
		{
			system("cls");
			Grafico(engano); // desenhar Forca consoante os enganos
			printf("\n\nCategoria: ");
			puts(nomecategoria[categoria-1]);
			for (int i = 0; i < strlen(palavra); i++)
			{
				mascara[i] == '1' ? printf("%c ", palavra[i]) : printf("  ");
			}
			printf("\n");
			for (int i = 0; i < strlen(palavra); i++)
			{
				printf("_ ");
			}

			printf("\n\n\nEscolha uma letra: ");
			scanf_s("%c", &letra);
			letra = toupper(letra);
			getchar();
			printf("\n");

			for (int i = 0; i < strlen(palavra); i++)
			{
				if (palavra[i] == letra)
				{
					mascara[i] = '1'; //mascara[i] muda para '1' caso letra certa
					acerto = 1; //acertou letra? sim = 1
					correct++; //cada letra certa aumenta este contador até número letras palavra
				}
			}

			if (acerto == 1)
			{
				printf("\nBoa!!!!\n");
			}
			else
			{
				printf("\nNao acertou! Tenta de novo!\n");
				engano++;
			}
			acerto = 0;
			system("pause");
		} while (engano < 6 && correct != strlen(palavra));
		
		Grafico(engano);
		printf("Palavra: "); puts(palavra);

		if (correct == strlen(palavra))
		{
			printf("\nAcertou na palavra! Ganhou o jogo!!\n\nQuer jogar de novo? (S/N) ");
		}
		else if (engano == 6)
		{
			printf("\nMorreste!!!\n\nQuer jogar de novo? (S/N) ");
		}
		scanf_s("%c", &resp);

	} while ( resp != 'n' && resp != 'N');
	printf("\n * * * * * Fim do Jogo * * * * *\n");
}