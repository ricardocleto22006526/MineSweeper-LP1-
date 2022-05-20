#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#define DIMlinha 255
#define DIMarray 255


typedef struct bomba /*Estrutura das bombas*/
{
   int coordenadaX;
   int coordenadaY;
   int tempo; 
   struct bomba*next;

}bomba;

typedef struct listaLigada /*Estrutura da linkedlist*/
{
    bomba*head;
    bomba*tail;

}listaLigada;

void organizaBombs(listaLigada *list, bomba valorAInserirNaLista){
    
    bomba *new = (bomba*)malloc(sizeof(bomba)); /*Aloco memoria para as informacoes da bomba*/

    bomba *aux1=list->head;
    bomba *previous=NULL;
    
    *new = valorAInserirNaLista;
    new->next=NULL;

    if (list->head==NULL) /*Caso a linkedlist esteja vazia, preenche a Head e a Tail com a informacao da primeira bomba*/
    {
        list->head=new;
        list->tail=new;
        return;
    }

    /*Percorre a lista, e coloca as bombas por ordem de tempo na linkedlist (para que fiquem ordenadas) -> Inclui o ciclo FOR e o If/Else*/
    for (aux1=list->head; aux1->next != NULL; aux1=aux1->next) 
    {
        if ( (aux1->tempo < new->tempo || aux1->tempo==new->tempo) && aux1->coordenadaX==new->coordenadaX && aux1->coordenadaY==new->coordenadaY)
        {
            return;
        }
        
        if (aux1->tempo > new->tempo)
        {
            previous->next=new;
            new->next=previous;
            return;  
        }
        previous=aux1;
    }

    if (aux1->tempo > new->tempo)
    {
        previous->next=new;
        new->next=aux1;
    }else{
        list->tail->next=new;
        list->tail=new; 
    }
    
} 

void preencherListaComBombas (char **menuDefault,int *DIMX, int *DIMY, listaLigada *linkedlist, int coodernadaX, int coordenadaY, int tempo){
    
    bomba propagate={0,0,0,NULL}; /* Da reset na estrutura que contem CoordenadaX/Y,Tempo e Bomba->next */

    menuDefault[coodernadaX][coordenadaY]='R'; /*Para nao percorrer a mesma bomba varias vezes*/
    
    if ( (coodernadaX - 1) >= 0 && menuDefault[coodernadaX-1][coordenadaY]=='.') /*Verifica se ha: BOMBA -> CIMA */
    {   
        propagate.coordenadaX = coodernadaX - 1; propagate.coordenadaY = coordenadaY; propagate.tempo = tempo + 10; /*Adiciona as informacoes da bomba na estrutura*/
        organizaBombs(linkedlist,propagate); /*Chama a funcao que organiza as bombas na linkedlist*/
    }
    
    if ( (coodernadaX - 1) >= 0 && (coordenadaY - 1) >= 0 && menuDefault[coodernadaX-1][coordenadaY-1]=='.') /*Verifica se ha: BOMBA -> CIMA ESQUERDA*/ 
    {
        
        propagate.coordenadaX = coodernadaX - 1; propagate.coordenadaY = coordenadaY - 1; propagate.tempo = tempo + 11; /*Adiciona as informacoes da bomba na estrutura*/
        organizaBombs(linkedlist,propagate); /*Chama a funcao que organiza as bombas na linkedlist*/
    }

    if ( coodernadaX >= 0 && (coordenadaY - 1) >= 0 && menuDefault[coodernadaX][coordenadaY-1]=='.') /*Verifica se ha: BOMBA -> ESQUERDA*/ 
    {
        
        propagate.coordenadaX = coodernadaX; propagate.coordenadaY = coordenadaY - 1; propagate.tempo = tempo + 12; /*Adiciona as informacoes da bomba na estrutura*/
        organizaBombs(linkedlist,propagate); /*Chama a funcao que organiza as bombas na linkedlist*/
    }

    if ( (coodernadaX + 1) < *DIMX && (coordenadaY - 1) >= 0 && menuDefault[coodernadaX+1][coordenadaY-1]=='.') /*Verifica se ha: BOMBA -> BAIXO ESQUERDA*/ 
    {   
        
        propagate.coordenadaX = coodernadaX + 1; propagate.coordenadaY = coordenadaY - 1; propagate.tempo = tempo + 13; /*Adiciona as informacoes da bomba na estrutura*/
        organizaBombs(linkedlist,propagate); /*Chama a funcao que organiza as bombas na linkedlist*/
    }

    if ( (coodernadaX + 1) < *DIMX && menuDefault[coodernadaX+1][coordenadaY]=='.') /*Verifica se ha: BOMBA -> BAIXO*/
    {   
        
        propagate.coordenadaX = coodernadaX + 1; propagate.coordenadaY = coordenadaY; propagate.tempo = tempo + 14; /*Adiciona as informacoes da bomba na estrutura*/
        organizaBombs(linkedlist,propagate); /*Chama a funcao que organiza as bombas na linkedlist*/
    }

    if ( (coodernadaX + 1) < *DIMX && (coordenadaY + 1) < *DIMY && menuDefault[coodernadaX+1][coordenadaY+1]=='.') /*Verifica se ha: BOMBA -> BAIXO DIREITA*/ 
    {   
        
        propagate.coordenadaX = coodernadaX + 1; propagate.coordenadaY = coordenadaY + 1; propagate.tempo = tempo + 15; /*Adiciona as informacoes da bomba na estrutura*/
        organizaBombs(linkedlist,propagate); /*Chama a funcao que organiza as bombas na linkedlist*/
    }

    if ( (coordenadaY + 1) < *DIMY && menuDefault[coodernadaX][coordenadaY+1]=='.') /*Verifica se ha: BOMBA -> DIREITA*/
    {   
        
        propagate.coordenadaX = coodernadaX; propagate.coordenadaY = coordenadaY + 1; propagate.tempo = tempo + 16; /*Adiciona as informacoes da bomba na estrutura*/
        organizaBombs(linkedlist,propagate); /*Chama a funcao que organiza as bombas na linkedlist*/
    }

    if ( (coodernadaX - 1) >=0 && coordenadaY + 1 < *DIMY && menuDefault[coodernadaX-1][coordenadaY+1]=='.') /*Verifica se ha: BOMBA -> DIREITA CIMA*/
    {   
        
        propagate.coordenadaX = coodernadaX - 1; propagate.coordenadaY = coordenadaY + 1; propagate.tempo = tempo + 17; /*Adiciona as informacoes da bomba na estrutura*/
        organizaBombs(linkedlist,propagate); /*Chama a funcao que organiza as bombas na linkedlist*/
    }
    
}



void printMapaDefault(char **menuDefault, int DIMX, int DIMY){
    /* Funcao que ira imprimir o mapa default (limpo) */
    
    /*construirMapaDefault(menuDefault,DIMX,DIMY);*/
    int a,b;
    
    for ( a = 0; a < DIMX; a++)
    {
        for (b = 0; b < DIMY; b++)
        {   
            if (menuDefault[a][b] == 'R')
            {   
                /*As bombas que sejam 'R' equivalem a '.', so que utilizo o R para que nao percorra varias vezes a mesma bomba*/
                printf("%c", menuDefault[a][b]='.'); 
            }else{
                /*Da print ao mapa normal (Nao envolve Log nem Propagate)*/
                printf("%c", menuDefault[a][b]);
            }

        }
        printf("\n");
    }
    
}
   
char **readFicheiro(char **menuDefault, char *nomeFicheiro, char *linha, int *DIMX, int *DIMY){
    /* Funcao que vai ler o ficheiro pretendido */

    char opcao, copiaLinhaAnterior[125];
    int primeiraLinha=1;
    int x,y;
    int a,b,i;

    FILE *ficheiro;
    ficheiro=fopen(nomeFicheiro,"r"); /* abrir o ficheiro em modo read (modo leitura)  */

    if (ficheiro==NULL) /* Caso nao exista o nome deste ficheiro */
    { 
        printf("Error: could not open file\n");
        return NULL; /* O return NULL vai levar-nos para um if da Main */
    }

    while (!feof(ficheiro))
    {   
        strcpy(copiaLinhaAnterior,linha); /* Copia a linha anterior e grava em -> copiaLinhaAnterior */
        fgets(linha, DIMlinha, ficheiro);  /* o 'fgets' lê os caracteres até ao '\n' (le a linha inteira, basicamente) */

        x=-1; /* Caso seja dado uma coordenada X por omissao */
        y=-1; /* Caso seja dado uma coordenada X por omissao */
        /*As 2 linhas a cima: Caso o ficheiro tenha uma opcao, mas nao tenha coordenadas, o programa ira conta-las como invalidas (Pode-se dizer que sao valores por omissao) */

        sscanf(linha,"%c %d %d", &opcao, &x, &y); /* ira ler os dados introduzidos, ignorando os espacos, atraves de uma especie de concatenacao */

        if (opcao=='#' || opcao=='\r' || opcao=='\n' || strcmp(copiaLinhaAnterior,linha)==0) /* Caso a opcao seja um '#','\r' ou '\n' ou 2 linhas iguais, ignora a linha */
        {
            continue;
        } /* /r serve para limpar o espaco do fim da linha (tinha o /r no debugger, logo tive que "limpar" devido a esse esse problema) */

        if (primeiraLinha==1) /* Vai ler a primeira linha do ficheiro, neste caso o tamanho do mapa*/
        {   
            primeiraLinha=0; /* Vai fazer com que o programa, nao leia a primeira linha e avance no ficheiro */
            sscanf(linha," %d %d",&x,&y);
            
            *DIMX=x;
            *DIMY=y;
            
            if (sscanf(linha," %d %d",&x,&y)!=2)
            {
                printf("Error: file is corrupted\n");
                return NULL;  /* O return NULL vai levar-nos para um if da Main */
            }
            
            if (x < 0 || y < 0)
            {
                printf("Error: invalid map dimensions\n");
                return NULL;  /* O return NULL vai levar-nos para um if da Main */
            }

           /*Aloca a memoria necessaria para construir o tabuleiro*/
            menuDefault=(char**)malloc(x * sizeof(char*));
            for (i = 0; i < x; i++)
            {
                menuDefault[i]=(char*)malloc(y * sizeof(char));
            }

            /*Depois da alocacao de memoria, crio o tabuleiro LIMPO*/
            for ( a = 0; a < x; a++)
            {
                for (b = 0; b < y; b++)
                {
                    menuDefault[a][b]='_'; 
                }
            }

            continue;
        }
        
        if (!(opcao=='*' || opcao=='.')) /* Caso nao seja um '*' ou '.' */
        { 
            printf("Error: file is corrupted\n");
            return NULL;  /* O return NULL vai levar-nos para um if da Main */
        }
        
        if ((x < 0 || x >= *DIMX) || (y < 0 || y >= *DIMY))  /*verifica se as coordenadas introduzidas estao dentro dos limites [x,y] */
        {
            printf("Error: file is corrupted\n");
            return NULL;  /* O return NULL vai levar-nos para um if da Main */
        }
        
        menuDefault[x][y]=opcao; /*Preenche a coordenada do tabuleiro com '.' ou '*' mediante a 'opcao' que esteja a ser lida no ficheiro*/
    }  
    fclose(ficheiro); /* Fecha o ficheiro, para nao ocorrer nenhum problema, como a perda de dados devido ao ficar corrompido */
    return menuDefault; /*Retorna o tabuleiro*/
}

int exportFicheiro(char **menuDefault, char *nomeFicheiro,int DIMX, int DIMY){
    /* Funcao que vai dar export do jogo inserido pelo utilizador para um ficheiro externo */

    int a,b;
    char opcao;

    FILE *ficheiro;
    ficheiro=fopen(nomeFicheiro,"w"); /* Abrir o ficheiro em modo write (modo escrita)  */

    fprintf(ficheiro,"%d %d\n",DIMX,DIMY);

    for (a = 0; a < DIMX ; a++)
    {
        for (b = 0; b < DIMY; b++)
        {
           if (!(menuDefault[a][b]=='_')) /* Caso a posicao a ser lida seja diferente de '_', podendo tomar o valor de '*' ou '.' */
            {   
                opcao=menuDefault[a][b]; /* Vai guardar na variavel opcao, numa determinada posicao, qual o tipo de bomba '*' ou '.' */
                fprintf(ficheiro,"%c %d %d\n",opcao,a,b);  /* Vai imprimir todos os dados validos no ficheiro a exportar [opcao coordenadaX coordenadaY] */
            }
        }   
    }
    fclose(ficheiro); /* Fecha o ficheiro, para nao ocorrer nenhum problema, como a perda de dados devido ao ficar corrompido */
    return 0;
}

int main(int argc,char* argv[]){
  /*Parametros necessarios na main -> int argc,char* argv[]*/

    int DIMX=0,DIMY=0,tempo=0;
    int x,y;
    char opcao[DIMarray]="",nomeFicheiro[DIMarray]="",linha[DIMlinha]=""; 
    char menu[] = "+-----------------------------------------------------+\nshow                - show the mine map\npropagate <x> <y>   - explode bomb at <x> <y>\nlog <x> <y>         - explode bomb at <x> <y>\nplant <x> <y>       - place bomb at <x> <y>\nexport <filename>   - save file with current map\nquit                - exit program\nsos                 - show menu\n+-----------------------------------------------------+\n";
    char **menuDefault=NULL; /* menuDefault vai ser o tabuleiro de jogo*/

    bomba *percorrer;
    listaLigada *aux;
    
    if (argc < 2) /*Caso nao haja um nome do ficheiro a ser introduzido, quando iniciamos o programa*/
    {
        printf("Error: missing file name\n");
        exit(0); /*Termina o programa = return 0*/
    }
    
    if ((menuDefault=readFicheiro(menuDefault,argv[1],linha,&DIMX,&DIMY))==NULL){ /*argv[1] / "save1.txt"*/
        free(menuDefault); /*Liberta memoria do tabuleiro*/
        exit(0); /*Termina o programa = return 0*/
    } 

    printf("%s", menu); /* Vai dar print ao menu */
    
    do
    {  
        printf(">"); 
        
        scanf(" %s", opcao); /* Vai ler a opcao introduza pelo utilizador */ 

        if (!(strcmp(opcao,"log")==0 || strcmp(opcao,"propagate")==0 || strcmp(opcao,"show")==0 || strcmp(opcao,"plant")==0 || strcmp(opcao,"read")==0 || strcmp(opcao,"export")==0 || strcmp(opcao,"sos")==0 || strcmp(opcao,"quit")==0))
        {
            printf("Invalid command!\n");      
            continue;
        }

        if (strcmp(opcao,"show")==0) /* opcao show */
        { 
            printMapaDefault(menuDefault,DIMX,DIMY); /* Vai dar print do mapa limpo*/
        }

        if (strcmp(opcao,"propagate")==0) /* opcao propagate */
        { 
            /*Aloco memoria para as variaveis a colocar na linkedlist (Para nao gastar memoria desnecessariamente ao encher a linkedlist)*/
            percorrer =(bomba*)malloc(sizeof(bomba));
            aux = (listaLigada*)malloc(sizeof(listaLigada));

            scanf(" %d %d", &x, &y); /* Vai ler as coordenadas inseridas pelo utilizador */

            /*Variaveis necessarias para preencher a linkedlist*/
            percorrer->coordenadaX=x;
            percorrer->coordenadaY=y;
            percorrer->tempo=tempo;
            percorrer->next=NULL;
            aux->head = percorrer;
            aux->tail = percorrer;

            if ((x < 0 || x >= DIMX) || (y < 0 || y >= DIMY)) /* verifica se as coordenadas introduzidas estao dentro dos limites [x,y]  */
            {
                printf("Error: invalid coordinate\n"); /* Caso a coordenada esteja errada, ira enviar uma mensagem de erro */
                continue;
            }
            
            if (!(menuDefault[x][y]=='.' || menuDefault[x][y]=='*')) /* Caso seja diferente de '*' ou '.' */
            { 
                printf("Error: no bomb at specified coordinate\n"); /* Informa o utilizador que nao existe bombas naquela coordenada [x,y] */
                continue;
            }

            if (menuDefault[x][y]=='*') /* Caso ja esteja um '*' naquela posicao ira ignorar */
            { 
                continue; 
            }

            /*Percorre a linkedlist*/
            for (percorrer = aux->head  ; percorrer != NULL; percorrer=percorrer->next)
            {   
                /*Chama a funcao que preenche a linkedlist*/
                preencherListaComBombas (menuDefault,&DIMX,&DIMY,aux,percorrer->coordenadaX,percorrer->coordenadaY,percorrer->tempo);
            }
            
            /*Percorre a linkedlist novamente*/
            for (percorrer = aux->head  ; percorrer != NULL; percorrer=percorrer->next)
            {
               if (menuDefault[percorrer->coordenadaX][percorrer->coordenadaY]=='*') /*Se a bomba ja estiver explodida ignora*/
               {
                   continue;
               }

               menuDefault[percorrer->coordenadaX][percorrer->coordenadaX]='*'; /* "rebenta" a bomba na posicao especifica*/
               printMapaDefault(menuDefault,DIMX,DIMY); /*Da print do mapa alterado pelo propagate*/
               tempo=percorrer->tempo;/*Adiciona os tempos das bombas, no tempo geral*/
            }
            /*Liberta as memorias, para nao dar memory Leak ou nao usar memoria extra sem necessidade*/
            free(percorrer);
            free(aux);
            continue;
        }

        if (strcmp(opcao,"log")==0) /* opcao log */
        {   
            /*Aloco memoria para as variaveis a colocar na linkedlist (Para nao gastar memoria desnecessariamente ao encher a linkedlist)*/
            percorrer = (bomba*)malloc(sizeof(bomba));
            aux = (listaLigada*)malloc(sizeof(listaLigada));

            scanf(" %d %d", &x, &y); /* Vai ler as coordenadas inseridas pelo utilizador */

            /*Variaveis necessarias para preencher a linkedlist*/
            percorrer->coordenadaX=x;
            percorrer->coordenadaY=y;
            percorrer->tempo=tempo;
            percorrer->next=NULL;
            aux->head = percorrer;
            aux->tail = percorrer;

            if ((x < 0 || x >= DIMX) || (y < 0 || y >= DIMY)) /* verifica se as coordenadas introduzidas estao dentro dos limites [x,y]  */
            {
                printf("Error: invalid coordinate\n"); /* Caso a coordenada esteja errada, ira enviar uma mensagem de erro */
                continue;
            }
            
            if (!(menuDefault[x][y]=='.' || menuDefault[x][y]=='*')) /* Caso seja diferente de '*' ou '.' */
            { 
                printf("Error: no bomb at specified coordinate\n"); /* Informa o utilizador que nao existe bombas naquela coordenada [x,y] */
                continue;
            }

            if (menuDefault[x][y]=='*') /* Caso ja esteja um '*' naquela posicao ira ignorar */
            { 
                continue; 
            }

            /*Percorre a linkedlist*/
            for (percorrer = aux->head  ; percorrer != NULL; percorrer=percorrer->next)
            {
                menuDefault[percorrer->coordenadaX][percorrer->coordenadaY]='R'; /*Para nao percorrer a mesma bomba varias vezes*/
                /*Chama a funcao que preenche a linkedlist*/
                preencherListaComBombas (menuDefault,&DIMX,&DIMY,aux,percorrer->coordenadaX,percorrer->coordenadaY,percorrer->tempo);
            }

            /*Percorre a linkedlist novamente*/
            for (percorrer = aux->head  ; percorrer != NULL; percorrer=percorrer->next)
            {
               if (menuDefault[percorrer->coordenadaX][percorrer->coordenadaY]=='*') /*Se a bomba ja estiver explodida ignora*/
               {
                   continue;
               }

               menuDefault[percorrer->coordenadaX][percorrer->coordenadaY]='*'; /* "rebenta" a bomba na posicao especifica*/
               printf("%d [%d, %d]\n", percorrer->tempo,percorrer->coordenadaX,percorrer->coordenadaY); /*Da print das informacoes do LOG*/
               tempo=percorrer->tempo; /*Adiciona os tempos das bombas, no tempo geral*/
            }
            /*Liberta as memorias, para nao dar memory Leak ou nao usar memoria extra sem necessidade*/
            free(percorrer); 
            free(aux);
            continue;
        }

        if (strcmp(opcao,"plant")==0) /* opcao plant */
        {   
            scanf(" %d %d", &x, &y); /* Vai ler as coordenadas inseridas pelo utilizador */

            if ((x < 0 || x >= DIMX) || (y < 0 || y >= DIMY)) /* verifica se as coordenadas introduzidas estao dentro dos limites [x,y]  */
            {
                printf("Error: invalid coordinate\n"); /* Caso a coordenada esteja errada, ira enviar uma mensagem de erro */
                continue;
            }
        
            menuDefault[x][y]='.'; /*Coloca um bomba nas coordenadas desejadas*/
        }
        
        if (strcmp(opcao,"export")==0) /* opcao export */
        {
            scanf("%s", nomeFicheiro); /* vai ler o nome que o utilizador quer dar ao ficheiro a dar export */
            exportFicheiro(menuDefault,nomeFicheiro,DIMX,DIMY); /* funcao que transfere o jogo "da consola" para o ficheiro */
        }
        
        if (strcmp(opcao,"sos")==0) /* opcao sos */
        { 
            printf("%s", menu);  /*Da print do menu*/
        }

    } while (!strcmp(opcao,"quit")==0); /* opcao quit -> Finaliza o programa */
    free(menuDefault); /*Liberta a memoria do tabuleiro antes do fim do programa*/
    exit(0); /*Termina o programa = return 0*/
}