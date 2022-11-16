#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

//GLOBAL VARIABLES
int qJogadores, qNavios, qSubmarinos, validation, countEmbarcacoesInimigas[3] = {1, 1, 1}, option, countNavJog2, countSubJog2, countNavJog3, countSubJog3, countNavJog4, countSubJog4, countEmbarcacoes, countNavios, countSubmarinos, jogadorAtacado;
char matrizNaval[9][9], matrizJogador2[9][9], matrizJogador3[9][9], matrizJogador4[9][9], tipoAtaque;

int verificaCoordenada(int letra, int numero) {
    if ((letra < 0 || letra > 8) || (numero < 0 || numero > 8)) return validation = 0;
    else return validation = 1;
}

void cancelarJogo() {
    char cancelar;
    printf("Deseja mesmo cancelar seu jogo? [S - Sim | N - Não]\nR: ");
    scanf("%s", &cancelar);
    cancelar = toupper(cancelar);
    if (cancelar == 'S') resetarJogo();
    else iniciarPartida();
}

void iniciarPartida() {
    int atNumero, atLetraInt, jogAtq;
    char respAtaque, atLetra, cancelar;
    system("cls || clear");
    while (countEmbarcacoes > 0) {
        if (countEmbarcacoes <= 0) {
            printf("Você perdeu o jogo!!\n");
            system("read -p 'Enter para retornar ao menu ' var");
            resetarJogo();
        } else {
            for (int i = 0; i < (qJogadores - 1); i++) {
                if (countEmbarcacoesInimigas[i] <= 0) {
                    printf("Você venceu o jogo!!\nEmbarcações restantes: %d\n", countEmbarcacoes);
                    system("read -p 'Enter para retornar ao menu ' var");
                    resetarJogo();
                }
            }
        }
        printf("------------------------------------------------------------------------\n");
        printf("|Seu campo naval:                                   Campo - jogador 2: |\n");
        printf("|  A B C D E F G H I                                  A B C D E F G H I|\n");
        for (int i = 0; i < 9; i++) {
            printf("|%d|", i + 1);
            for (int k = 0; k < 9; k++) {
                if (!matrizNaval[k][i]) matrizNaval[k][i] = ' ';
                printf("%c|", matrizNaval[k][i]);
            }
            // if (i == 0) printf("                               ");
            if (i == 0) printf("   -------------------------   ");
            else if (i == 1) printf("   |       restantes       |   ");
            else if (i == 2) printf("   -------------------------   ");
            else if (i == 3) printf("   |     |    nav |    sub |   ");
            else if (i == 4) printf("   | P 1 |      %d |      %d |   ", countNavios, countSubmarinos);
            else if (i == 5) printf("   | P 2 |      %d |      %d |   ", countNavJog2, countSubJog2);
            else if (i == 6) {
                if (qJogadores == 3 || qJogadores == 4) printf("   | P 3 |      %d |      %d |   ", countNavJog3, countSubJog3);
                else printf("   -------------------------   ");
            } else if (i == 7) {
                if (qJogadores == 4) printf("   | P 4 |      %d |      %d |   ", countNavJog4, countSubJog4);
                else if(qJogadores != 2) printf("   -------------------------   ");
                else printf("                               ");
            } else if (i == 8) {
                if (qJogadores == 4) printf("   -------------------------   ");
                else printf("                               ");
            }
            printf("%d|", i + 1);
            for (int k = 0; k < 9; k++) {
                if (!matrizJogador2[k][i]) matrizJogador2[k][i] = ' ';
                printf("%c|", matrizJogador2[k][i]);
            }
            printf("\n");
        }
        if (qJogadores == 3) {
            printf("|                                                                      |\n");
            printf("|                          Campo - jogador 3:                          |\n");
            printf("|                            A B C D E F G H I                         |\n");
            for (int i = 0; i < 9; i++) {
                printf("|                          %d|", i + 1);
                for (int k = 0; k < 9; k++) {
                    if (!matrizJogador3[k][i]) matrizJogador3[k][i] = ' ';
                    printf("%c|", matrizJogador3[k][i]);
                }
                printf("                        |\n");
            }
        } else if (qJogadores == 4) {
            printf("|                                                                      |\n");
            printf("|Campo - jogador 3:                                 Campo - jogador 4: |\n");
            printf("|  A B C D E F G H I                                  A B C D E F G H I|\n");
            for (int i = 0; i < 9; i++) {
                printf("|%d|", i + 1);
                for (int k = 0; k < 9; k++) {
                    if (!matrizJogador3[k][i]) matrizJogador3[k][i] = ' ';
                    printf("%c|", matrizJogador3[k][i]);
                }
                printf("                               %d|", i + 1);
                for (int k = 0; k < 9; k++) {
                    if (!matrizJogador4[k][i]) matrizJogador4[k][i] = ' ';
                    printf("%c|", matrizJogador4[k][i]);
                }
                printf("\n");
            }
        }
        printf("------------------------------------------------------------------------");
        printf("\n| Legenda do campo naval:                                              |");
        printf("\n| N - Navio         X - Embarcação destruída   A - Errou ataque aéreo  |");
        printf("\n| S - Submarino     : - Errou os dois ataques  T - Errou torpedo       |");
        printf("\n------------------------------------------------------------------------");
        printf("\n| Opções:              |");
        printf("\n| 1- Recebi um ataque  |");
        printf("\n| 2- Fiz um ataque     |");
        printf("\n------------------------");
        printf("\nEscolha uma opção: ");
        scanf("%d", &option);
        if (option == 2 && qJogadores > 2) {
            printf("\nQual jogador você está atacando? [2, 3, 4]\nR: ");
            scanf("%d", &jogadorAtacado);
        } else if (option == 2) jogadorAtacado = 2;
        printf("\nInforme o tipo de ataque (Torpedo & Ataque aéreo | B - Cancelar):");
        scanf("%s", &tipoAtaque);
        tipoAtaque = toupper(tipoAtaque);
        if (tipoAtaque == 'T') printf("Ataque selecionado: Torpedo");
        else if (tipoAtaque == 'A') printf("Ataque selecionado: Ataque aéreo");
        else if (tipoAtaque == 'B') cancelarJogo();
        else {
            printf("Opção inválida!\n");
            system("read -p 'Enter para continuar ' var");
            iniciarPartida();
        }
        printf("\nInforme as posições do ataque: ");
        scanf("%s %d", &atLetra, &atNumero);
        atLetra = toupper(atLetra);
        atLetraInt = atLetra - 65;
        atNumero--;
        jogAtq = jogadorAtacado - 2;
        if (verificaCoordenada(atLetraInt, atNumero) == 0) {
            printf("Valor Inválido!\n");
            system("read -p 'Enter para continuar ' var");
            iniciarPartida();
        }
        switch (option) {
            case 1:
                for (int k = 0; k < 9; k++) {
                    for (int l = 0; l < 9; l++) {
                        if (atLetraInt == k && atNumero == l) {
                                if (tipoAtaque == 'T' && matrizNaval[k][l] == 'S') {
                                    matrizNaval[k][l] = 'X';
                                    countEmbarcacoes--;
                                    printf("Você perdeu um submarino!\n");
                                    system("read -p 'Enter para continuar ' var");
                                    countSubmarinos--;
                                } else if (tipoAtaque == 'A' && matrizNaval[k][l] == 'N') {
                                    matrizNaval[k][l] = 'X';
                                    countEmbarcacoes--;
                                    printf("Você perdeu um Navio!\n");
                                    system("read -p 'Enter para continuar ' var");
                                    countNavios--;
                                } else {
                                    printf("O adversário errou o ataque!\n");
                                    system("read -p 'Enter para continuar ' var");
                                }
                            iniciarPartida();
                        }
                    }
                }
            break;
            case 2:
                printf("O ataque foi eficaz? [S/N] \nR:");
                scanf("%s", &respAtaque);
                respAtaque = toupper(respAtaque);
                switch (respAtaque) {
                    case 'S':
                        countEmbarcacoesInimigas[jogAtq]--;
                        for (int k = 0; k < 9; k++) {
                            for (int l = 0; l < 9; l++) {
                                if (atLetraInt == k && atNumero == l) {
                                    switch (jogadorAtacado) {
                                        case 2:
                                            matrizJogador2[k][l] = 'X';
                                            if (tipoAtaque == 'T') countSubJog2--;
                                            else if (tipoAtaque == 'A') countNavJog2--;
                                        break;
                                        case 3:
                                            matrizJogador3[k][l] = 'X';
                                            if (tipoAtaque == 'T') countSubJog3--;
                                            else if (tipoAtaque == 'A') countNavJog3--;
                                        break;
                                        case 4:
                                            matrizJogador4[k][l] = 'X';
                                            if (tipoAtaque == 'T') countSubJog4--;
                                            else if (tipoAtaque == 'A') countNavJog4--;
                                        break;
                                    }
                                    if (tipoAtaque == 'T') {
                                        printf("Você atingiu um Submarino adversário!\n");
                                        system("read -p 'Enter para continuar ' var");
                                    }
                                    else if (tipoAtaque == 'A') {
                                        printf("Você atingiu um Navio adversário!\n");
                                        system("read -p 'Enter para continuar ' var");
                                    }
                                    iniciarPartida();
                                }
                            }
                        }
                    break;
                    case 'N':
                        for (int k = 0; k < 9; k++) {
                            for (int l = 0; l < 9; l++) {
                                if (atLetraInt == k && atNumero == l) {
                                    switch (jogadorAtacado) {
                                        case 2:
                                            if ((tipoAtaque == 'T' && matrizJogador2[k][l] == 'A') || (tipoAtaque == 'A' && matrizJogador2[k][l] == 'T')) matrizJogador2[k][l] = ':';
                                            else {
                                                if (tipoAtaque == 'T') matrizJogador2[k][l] = 'T';
                                                else if (tipoAtaque == 'A') matrizJogador2[k][l] = 'A';
                                            }
                                        break;
                                        case 3:
                                            if ((tipoAtaque == 'T' && matrizJogador3[k][l] == 'A') || (tipoAtaque == 'A' && matrizJogador3[k][l] == 'T')) matrizJogador3[k][l] = ':';
                                            else {
                                                if (tipoAtaque == 'T') matrizJogador3[k][l] = 'T';
                                                else if (tipoAtaque == 'A') matrizJogador3[k][l] = 'A';
                                            }
                                        break;
                                        case 4:
                                            if ((tipoAtaque == 'T' && matrizJogador4[k][l] == 'A') || (tipoAtaque == 'A' && matrizJogador4[k][l] == 'T')) matrizJogador4[k][l] = ':';
                                            else {
                                                if (tipoAtaque == 'T') matrizJogador4[k][l] = 'T';
                                                else if (tipoAtaque == 'A') matrizJogador4[k][l] = 'A';
                                            }
                                        break;
                                    }
                                    printf("Você errou o alvo!\n");
                                    system("read -p 'Enter para continuar ' var");
                                    iniciarPartida();
                                }
                            }
                        }
                    break;
                    default:
                        printf("Opção indisponível!");
                        iniciarPartida();
                    break;
                }
            break;
            case 123:
                printf("Você deseja mesmo cancelar seu jogo? [S - Sim | N - Não]\nR: ");
                scanf("%s", &cancelar);
                if (cancelar == 'S') resetarJogo();
                else iniciarPartida();
            break;
        }
    }
}

void iniciarJogo() {
    int numero, letra;
    char letraChar;
    system("cls || clear");
    printf("Informe a quantidade de jogadores: ");
    scanf("%d", &qJogadores);
    while (qJogadores < 2 || qJogadores > 4) {
        printf("Quantidade inválida de jogadores!\nTente novamente: ");
        scanf("%d", &qJogadores);
        iniciarJogo();
    }
    printf("\nInforme a quantidade de cada embarcação: ");
    scanf("%d", &qNavios);
    while (qNavios < 1) {
        printf("Quantidade inválida de cada embarcação: ");
        scanf("%d", &qNavios);
    }
    qSubmarinos = qNavios;
    countEmbarcacoes = qNavios + qSubmarinos;
    countNavios = qNavios;
    countSubmarinos = qSubmarinos;
    countNavJog2 = qNavios;
    countSubJog2 = qSubmarinos;
    countNavJog3 = qNavios;
    countSubJog3 = qSubmarinos;
    countNavJog4 = qNavios;
    countSubJog4 = qSubmarinos;
    for (int i = 0; i < 3; i++) {
        countEmbarcacoesInimigas[i] = countEmbarcacoes;
    }
    for (int i = 0; i < qNavios; i++) {
        printf("\nInforme a posição do %d° navio: ", i + 1);
        scanf("%s %d", &letraChar, &numero);
        if (!isalpha(letraChar)) break;
        letraChar = toupper(letraChar);
        letra = letraChar - 65;
        numero--;
        if (verificaCoordenada(letra, numero) == 0) {
            i--;
            break;
        }
        for (int k = 0; k < 9; k++) {
            for (int l = 0; l < 9; l++) {
                if (letra == k && numero == l) {
                    if (matrizNaval[k][l] != ' ') {
                        printf("\nOpção inválida pois já há uma embarcação nesta posição!");
                        i--;
                        break;
                    } else {
                        matrizNaval[k][l] = 'N';
                    }
                }
            }
        }
    }
    for (int i = 0; i < qSubmarinos; i++) {
        printf("\nInforme a posição do %d° submarino: ", i + 1);
        scanf("%s %d", &letraChar, &numero);
        if (!isalpha(letraChar)) break;
        letraChar = toupper(letraChar);
        letra = letraChar - 65;
        numero--;
        if (verificaCoordenada(letra, numero) == 0) {
            i--;
            break;
        }
        for (int k = 0; k < 9; k++) {
            for (int l = 0; l < 9; l++) {
                if (letra == k && numero == l) {
                    if (matrizNaval[k][l] != ' ') {
                        printf("\nOpção inválida pois já há uma embarcação nesta posição!");
                        i--;
                        break;
                    } else {
                        matrizNaval[k][l] = 'S';
                    }
                }
            }
        }
    }
    iniciarPartida();
}

void resetarJogo() {
    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 9; k++) {
            matrizJogador2[k][i] = ' ';
            matrizJogador3[k][i] = ' ';
            matrizJogador4[k][i] = ' ';
            matrizNaval[k][i] = ' ';
        }
        countEmbarcacoesInimigas[i] = 0;
    }
    menu();
}

void regras() {
    printf("---------------[R E G R A S]---------------\n");
    printf("| 1- Manuseie o programa com cuidado      |\n");
    printf("|    para evitar erros.                   |\n");
    printf("-------------------------------------------\n");
    system("read -p 'Aperte Enter para voltar ' var || pause");
    menu();
}

void fecharJogo() {
    char escolha;
    printf("Tem certeza que deseja fechar o jogo? [S - Sim | N - Não]\n R: ");
    scanf("%s", &escolha);
    escolha = toupper(escolha);
    if (escolha == 'N') menu();
    else if (escolha == 'S') return system("exit");
    else {
        printf("Opção inválida!\n");
        system("read -p 'Enter para continuar ' var");
        fecharJogo();
    }
}

void menu() {
    system("cls || clear");
    printf("-----------------[M E N U]-----------------\n");
    printf("| 1- Iniciar jogo                         |\n");
    printf("| 2- Regras                               |\n");
    printf("| 3- Resetar                              |\n");
    printf("| 4- Fechar                               |\n");
    printf("-------------------------------------------\n");
    printf("Escolha uma opção: ");
    scanf("%d", &option);
    switch (option) {
        case 1:
            iniciarJogo();
        break;
        case 2:
            system("cls || clear");
            regras();
        break;
        case 3:
            printf("Jogo resetado com sucesso!\n");
            system("read -p 'Enter para continuar ' var");
            resetarJogo();
        break;
        case 4:
            system("cls || clear");
            fecharJogo();
        break;
        default:
            printf("Opção inválida!\n");
            system("read -p 'Enter para tentar novamente ' var");
            menu();
        break;
    }
}

int main() {
    setlocale(LC_ALL, "");
    system("cls || clear");
    printf("-------------------------------------------\n");
    printf("|                                         |\n");
    printf("|              B A T A L H A              |\n");
    printf("|                                         |\n");
    printf("|                N A V A L                |\n");
    printf("|                                   v1.0.2|\n");
    printf("-------------------------------------------\n");
    system("read -p 'Aperte Enter para iniciar ' var");
    system("cls || clear");
    printf("AVISO: Use o comando 123 para cancelar qualquer operação.\n");
    system("read -p 'Enter para continuar ' var");
    resetarJogo();
}
