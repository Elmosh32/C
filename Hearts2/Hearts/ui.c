/**********************************************************************************
                                   include
**********************************************************************************/
#include "../includes/ui.h"

/**********************************************************************************
                   Declaration of static Auxiliary function
**********************************************************************************/
static void PrintCard(int _card);

/**********************************************************************************
                                api functions
**********************************************************************************/
void Rules()
{
        char choice[20];
        printf("Do You want to see the game rules? (y/n)\n");

        scanf("%s", choice);
        if (strcmp(choice, "y") == 0)
        {
                printf("\n\n************************************************** Hearts Rules **************************************************\n");
                printf("1. The objective of Hearts is to get as few points as possible. Each heart gives one penalty point.\n"
                       "   There is also one special card, the Queen of spades, which gives 13 penalty points.\n");
                printf("2. When the game starts you select 3 cards to pass to one of your opponents.\n"
                       "   Typically you want to pass your three worst cards to get rid of them.\n"
                       "   Which opponent you pass to varies, you start by passing to the opponent on your left,\n"
                       "   then in the next game you pass to the opponent on your right,\n"
                       "   third game you pass across the table and in the fourth game there is no card passing.\n");
                printf("3. Each turn starts with one player playing a single card, also called leading.\n"
                       "   The suit of that card determines the suit of the trick. The other players then play one card each.\n"
                       "   If they have a card in the same suit as the first card then they must play that. If they don't then they can play one of their other cards.\n"
                       "   Once four cards have been played, the player who played the highest ranking card in the original suit takes the trick,\n"
                       "   i.e. he takes the four cards on the table and he then starts the next turn.\n"
                       "   Any penalty cards in the trick (hearts or queen of spades) are added to the players penalty score.\n"
                       "   So you want to avoid taking any tricks that have hearts or the queen of spades.\n");
                printf("4. The player who has the two of clubs at the start of the game leads in the first hand, and he MUST lead with the two of clubs.\n");
                printf("5. You cannot lead a trick with hearts, until hearts has been broken (played on another suit).\n"
                       "   So if it is your turn to lead and no heart has been played yet then you may not select a heart as the card to play first.\n"
                       "   In some variations of the game you can't play the queen of spades until hearts has been broken as well,\n"
                       "   but in this version you can always play the queen of spades and she doesn't break hearts.\n");
                printf("6. In the very first round you may never play a heart or the queen of spades,\n"
                       "   not even if you don't have any card in the suit of the lead card.\n");
                printf("7. Once all cards have been played the penalty points are counted and the player with the fewest points wins that hand.\n"
                       "   When one or more players reach 100 points or more then the entire game is finished, and the player with the least points win.\n"
                       "   If points are over 100 and there are two or more equal with the least points then play continues until there's only one winner.");
                printf("\n*****************************************************************************************************************************************\n");

                printf("Press any button to start the game\n");

                scanf("%s", choice);
                printf("__________________________________________________________________________\n");
                printf("||||||||||||||||||||||||||||||||| Hearts |||||||||||||||||||||||||||||||||\n");
                printf("__________________________________________________________________________\n");
                printf("%44s\n\n", "It's game time!");
        }
}

void UIChooseCard(int *_cardIndex, Suit _suitNumber)
{
        char *c;

        switch (_suitNumber)
        {
        case HEART_VAL:
                c = HEART;
                break;
        case SPADE_VAL:
                c = SPADE;
                break;
        case DIAMOND_VAL:
                c = DIAMOND;
                break;
        case CLUB_VAL:
                c = CLUB;
                break;

        default:
                c = "";
                break;
        }

        do
        {
                printf("choose card %s\n", c);
                scanf("%d", _cardIndex);
        } while (*_cardIndex < 0 || *_cardIndex > 12);
}

void UIPrintScore(char *_playerName, int _playerScore, int _playerPlace)
{
        switch (_playerPlace)
        {
        case 1:
                printf("\n--------------------------------------------------------\n");
                printf("The winner is: %s %s %s\n", WINNER, _playerName, WINNER);
                printf("%s In the first place\t=>\t%s with %d points\n", NO_1, _playerName, _playerScore);
                break;
        case 2:
                printf("%s In second place\t=>\t%s with %d points\n", NO_2, _playerName, _playerScore);
                break;
        case 3:
                printf("%s In third place\t=>\t%s with %d points\n", NO_3, _playerName, _playerScore);
                break;
        case 4:
                printf("%s In fourth place\t=>\t%s with %d points\n", NO_4, _playerName, _playerScore);
                break;
        default:
                if (strcmp(_playerName, "You") == 0)
                {
                        printf("%s Score: %d\n", "Your", _playerScore);
                }
                else
                {
                        printf("%s Score: %d\n", _playerName, _playerScore);
                }
                break;
        }
}

void PrintHand(Vector *_hand)
{
        int i, temp;
        size_t handSize;

        getNumOfItems(_hand, &handSize);

        for (i = 0; i < handSize; i++)
        {
                printf("(%d) ", i);
        }
        printf("\n");

        for (i = 0; i < handSize; i++)
        {
                getVector(_hand, i, &temp);
                PrintCard(temp);
        }
        printf("\n");
}

void UIPrintAllHands(Vector *_hand, char *_playerName)
{
        int i, temp;
        size_t handSize;
        getNumOfItems(_hand, &handSize);

        printf("\n%s hand:\t", _playerName);

        for (i = 0; i < handSize; i++)
        {
                getVector(_hand, i, &temp);
                PrintCard(temp);
        }

        printf("\n");
}

void PrintSeries(int _series[], int _size)
{
        int i;

        for (i = 0; i < SPACE_SIZE; i++)
        {
                printf(" ");
        }

        PrintCard(_series[2]);
        printf("\n\n");
        PrintCard(_series[1]);

        for (i = 0; i < 2 * SPACE_SIZE - 1; i++)
        {
                printf(" ");
        }

        PrintCard(_series[3]);
        printf("\n\n");

        for (i = 0; i < SPACE_SIZE; i++)
        {
                printf(" ");
        }

        PrintCard(_series[0]);
        printf("\n_________________");
        printf("\n");
}

void Choose2Club(int *_cardIndex)
{
        do
        {
                printf("choose card (2 CLUB)\n");
                scanf("%d", _cardIndex);
        } while (*_cardIndex < 0 || *_cardIndex > 12);
}

void WannaExit(int *_exit)
{
        char choice[20];
        printf("\nPlay another hand ? (y / n)\n");
        scanf("%s", choice);
        if (strcmp(choice, "y") != 0)
        {
                *_exit = 1;
        }
        else
        {
                *_exit = 0;
        }
}

/**********************************************************************************
                             Auxiliary function
**********************************************************************************/
static void PrintCard(int _card)
{
        int suit, num;
        char *c, *color;
        char sign[20];

        suit = CALC_SUIT(_card);
        num = CALC_CARD_NUM(_card);

        if (_card == NO_CARD)
        {
                printf(" ");
                return;
        }

        switch (suit)
        {
        case HEART_VAL:
                c = HEART;
                color = RED;
                break;
        case SPADE_VAL:
                c = SPADE;
                color = BLACK;
                break;
        case DIAMOND_VAL:
                c = DIAMOND;
                color = RED;
                break;
        case CLUB_VAL:
                c = CLUB;
                color = BLACK;
                break;
        }

        switch (num)
        {
        case JACK:
                strcpy(sign, "J");
                break;
        case QUEEN:
                strcpy(sign, "Q");
                break;
        case KING:
                strcpy(sign, "K");
                break;
        case ACE:
                strcpy(sign, "A");
                break;

        default:
                strcpy(sign, "");
                MyItoa(num + 2, sign);
                break;
        }

        printf("%s%s%s%s  ", color, sign, c, NORMAL);
}