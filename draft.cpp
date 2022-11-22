#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <iostream>
	struct reg
	{
		char nome[40], team[20], draft[50], status;

	};
int tamanho(FILE *);
void cadastrar (FILE *);
void consultar (FILE *);
void gerararqtxt(FILE *);
void excluir (FILE *);


int main()
{
	int op;
	FILE *arq;
	setlocale(LC_ALL,"");
	if ((arq = fopen("dados1.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("dados1.dat", "wb+")) == NULL)
		{
			printf("Falha ao abrir o arquivo!\n");
			system("pause");
		}
	}
	
	do
	{
		system("cls");
		printf("=====NBA=====");
		printf("\n1. Registrar Jogador");
		printf("\n2. Consultar");
		printf("\n3. Gerar arquivo");
		printf("\n4. Excluir Jogador");
		printf("\n5. Sair\n\n");
		
			printf("Opção: ");
			scanf("%d", &op);
		printf("=====CONTATOS: %d=====\n", tamanho(arq));
		
		switch(op)
		{
			case 1:
				cadastrar(arq);
				break;
			case 2:
				consultar(arq);
				break;
			case 3:
				gerararqtxt(arq);
				break;
			case 4:
				excluir(arq);
				break;
			case 5:
				system("cls");
				printf("Você escolheu sair.");
				fclose(arq);
				break;
		}
	} while(op!=5);
	

}

void cadastrar (FILE *arq)
{
	reg contato;
	char confirma;
	
	fflush(stdin);
	
	
	
	printf("Registrando novo cadastro: \n");
	printf("Número do cadastro: %d\n\n", tamanho(arq) + 1);
	
	printf("Nome..........:");
	gets(contato.nome);
	
	printf("Team......:");
	gets(contato.team);
	
	printf("Draft........:");
	gets(contato.draft);
	
	printf("\nConfirma<s/n>: ");
	scanf("%c", &confirma);
	
	contato.status = ' ';
	
	if(toupper(confirma) == 'S')
	{
		printf("\n\ngravando....\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&contato, sizeof(reg),1, arq);
	}
	
}

void consultar(FILE *arq)
{
	reg contato;
	int nr;
	printf("Consulta pelo código.\n");
	printf("Informe o Codigo......: ");
	scanf("%d", &nr);
	
	if ((nr <= tamanho(arq)) && (nr > 0))
	{
		fseek(arq, (nr-1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' '){
		printf("Nome......... %s", contato.nome);
		printf("\nTeam....... %s", contato.team);
		printf("\nDraft...... %s\n\n", contato.draft);
		}
	}
	else
	{
		printf("Número de registro inválido.\n");
	}
	system("pause");
}

void gerararqtxt(FILE *arq)
{
	char nomearq[20];
	printf("Nome do arquivo: ");
	scanf("%s", nomearq);
	strcat(nomearq, ".txt");
	
	FILE *arqtxt = fopen(nomearq, "w");
	
	if(!arqtxt)
	{
		printf("Não foi possivel crirar este arquivo.");
	}
	
	fprintf(arqtxt, "NOME                         TEAM                         DRAFT\n");
	fprintf(arqtxt,"==========================================================================================\n");
	int nr;
	reg contato;
	for(nr=0;nr<tamanho(arq); nr++)
	{
		fseek(arq, nr * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		fprintf(arqtxt, "\n%-28s %-32s %s\n", contato.nome, contato.team, contato.draft);
		fprintf(arqtxt, "------------------------------------------------------------------------------------------\n");
	}
		fprintf(arqtxt, "\n==========================================================================================\n");
		fclose(arqtxt);
}

void excluir(FILE *arq)
{
	reg contato;
	int nr;
	char confirm;
	printf("Consulta pelo código.\n");
	printf("Informe o Codigo......: ");
	scanf("%d", &nr);
	
	if ((nr <= tamanho(arq)) && (nr > 0))
	{
		fseek(arq, (nr-1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' '){
		printf("Nome......... %s", contato.nome);
		printf("\nTeam....... %s", contato.team);
		printf("\nDraft...... %s\n\n", contato.draft);
		printf("\nDeseja mesmo deletar S/N ?\n\n");
		getchar();
		scanf("%s",&confirm);
		
		if (toupper(confirm) == 'S'){
			printf("\nExcluindo...\n\n");
			fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
			contato.status = '*';
			fwrite( & contato, sizeof(reg), 1, arq);
		}
		}
	else
	{
		printf("Número de registro inválido.\n");
	}
	system("pause");
	}
}

int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(reg);
}

