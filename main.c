#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "card.h"
#include "hand.h"

//contains all the game information
typedef struct Game{
    Hand playerHand;
    Hand dealerHand;
    int playerChips;
    int bet;
    Deck deck;
}Game;

//functions you must complete
int RunGame(Game* r, int bet);
void SaveGameToFile(Game game);
Game LoadGameFromFile();


void SaveDeckToFile(Deck deck, FILE *file);
Deck LoadDeckFromFile(FILE *file);


void SaveHandToFile(Hand hand, FILE *file);
Hand LoadHandFromFile(FILE *file);

int main(int argc, char** argv){
    
    Game game;
    game.playerHand = MakeHand();
    game.dealerHand = MakeHand();
    game.playerChips = 1000;
    game.deck = MakeDeck();

    int loaded = argc > 1;


  while(game.playerChips > 0){
    
    if(loaded == 0){
        printf("\nYou have %d chips\n",game.playerChips);
        printf("How much would you like to bet?\n");
        scanf("%d",&game.bet);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { } //clear input buffer to avoid issues
        if(game.bet == 0){
            break; //we're done
        }
        
        //this is how we deal cards
        AddCard(&game.playerHand, DrawCard(&game.deck));
        AddCard(&game.dealerHand, DrawCard(&game.deck));

        AddCard(&game.playerHand, DrawCard(&game.deck));
        AddCard(&game.dealerHand, DrawCard(&game.deck));
    }else{
        loaded = 0;
        game = LoadGameFromFile();
    }


    if(CalculatePoints(&game.playerHand) == 21){
        printf("You were dealt a 21!");
        PrintHand(game.playerHand);
        game.playerChips += (int)(double)game.bet/2.0;
        continue;
    }

    game.playerChips += RunGame(&game, game.bet);
    game.playerHand = MakeHand();
    game.dealerHand = MakeHand();
    game.deck = MakeDeck();
  }

  printf("Game over.\n");
  printf("You left with %d chips.\n", game.playerChips);
}

int RunGame(Game* r, int bet){ 

    printf("\n"); 
    int playerPoints = CalculatePoints(&r->playerHand);
    int dealerPoints = CalculatePoints(&r->dealerHand);
    char decision;

    if(playerPoints > 21) {
       printf("You busted\n");
       return -bet;
    }

    int dealer1st = GetCardPoints(r->dealerHand.cards[0]);
    printf("Dealer Score: %d + ???\n", dealer1st );
    printf("Dealer Hand: ");
    PrintCard(r->dealerHand.cards[0]);
    printf(", ??? of ???\n");
    printf("Player Score: %d\n", playerPoints);
    printf("Player Hand: ");
    PrintHand(r->playerHand);
   
    printf("Will you hit 'h' or stay 's' or take a break 'b'?\n");

    scanf(" %c", &decision);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    
    if (decision == 'h') {
        AddCard(&r->playerHand, DrawCard(&r->deck));
        return RunGame(r, bet);
    }

    if (decision == 'b'){
        printf("Saving game...\n");
        SaveGameToFile(*r);
        exit(0);
        return 0;

    }

    if (decision == 's'){

        while(dealerPoints<16){
            AddCard(&r->dealerHand, DrawCard(&r->deck));
            dealerPoints = CalculatePoints(&r->dealerHand);
            if (dealerPoints > 21){
                printf("\nYou won\n");
                printf("your Score: %d\n", playerPoints);
                printf("Player Hand: ");
                PrintHand(r->playerHand);
                printf("dealer score: %d\n",dealerPoints);
                printf("Dealer Hand: ");
                PrintHand(r->dealerHand);
                return bet;

            }
        }

        
        if (playerPoints==dealerPoints){
            printf("\ntied\n");
            printf("your Score: %d\n", playerPoints);
            printf("Player Hand: ");
            PrintHand(r->playerHand);
            printf("dealer score: %d\n",dealerPoints);
            printf("Dealer Hand: ");
            PrintHand(r->dealerHand);
            return 0;
        }
        else if (playerPoints>dealerPoints){
            printf("\nYou won\n");
            printf("your Score: %d\n", playerPoints);
            printf("Player Hand: ");
            PrintHand(r->playerHand);
            printf("dealer score: %d\n",dealerPoints);
            printf("Dealer Hand: ");
            PrintHand(r->dealerHand);
            return bet;
        }
        else{
            printf("\nLost\n");
            printf("your Score: %d\n", playerPoints);
            printf("Player Hand: ");
            PrintHand(r->playerHand);
            printf("dealer score: %d\n",dealerPoints);
            printf("Dealer Hand: ");
            PrintHand(r->dealerHand);
            return -bet;
        }
        
        
    }
    
    return 0;
    
}




void SaveGameToFile(Game game){
    FILE* outFile = NULL;   
    outFile = fopen("save.txt", "w");
    if (outFile == NULL) {
       printf("Could not open file save.txt.\n");
    }
    //SaveHandToFile(Hand hand, FILE *file)
    SaveHandToFile(game.playerHand, outFile);
    SaveHandToFile(game.dealerHand, outFile);
    fprintf(outFile,"%d\n",game.playerChips);
    fprintf(outFile,"%d\n", game.bet);
    SaveDeckToFile( game.deck , outFile);

    fclose(outFile);  

}
Game LoadGameFromFile(){
    //your code goes here
    Game game;
    FILE* file = NULL;   
    file = fopen("save.txt", "r");
    if (file == NULL) {
       printf("Could not open file save.txt.\n");
       exit(10);
    }
    game.playerHand = LoadHandFromFile(file);
    game.dealerHand = LoadHandFromFile(file);
    char temp[10];
    fgets(temp, 10, file);
    sscanf(temp, "%d" ,&game.playerChips);
    temp[0] = '\0';
    fgets(temp,10,file);
    sscanf(temp,"%d", &game.bet);

    game.deck = LoadDeckFromFile(file);
    fclose(file);
    //only here to keep the program from crashing, delete this when you are ready
    
    return game; 
}


//might be nice to break saving and loading down into steps using these functions!
void SaveHandToFile(Hand hand, FILE *file){
    int handSize;
    fprintf(file,"%d\n",hand.handSize);

    for (int i = 0; i<hand.handSize; i++){
        fprintf(file,"%d,", hand.cards[i].value);
        switch(hand.cards[i].suit) {
            case HEARTS:
                fprintf(file,"HEARTS\n");
                break;
            case DIAMONDS:
                fprintf(file,"DIAMONDS\n");
                break;
            case CLUBS:
                fprintf(file,"CLUBS\n");
                break;
            case SPADES:
                fprintf(file,"SPADES\n");
                break;
            default:
                printf("ERROR\n");
                break;
        }    
    }
}
Hand LoadHandFromFile(FILE *file){
    Hand h;
    char* line = (char*) malloc(50 * sizeof(char));
    fgets (line, 50 , file);
    sscanf(line, "%d", &h.handSize);
    line[0]='\0';
    for (int i = 0; i<h.handSize; i++){
        char suitCheck[10];
        fgets (line, 50 , file);
        sscanf(line, "%d,%s",&h.cards[i].value, suitCheck);

        if (strcmp(suitCheck,"HEARTS")==0) {
            h.cards[i].suit = HEARTS;
        } else if (strcmp(suitCheck, "CLUBS")==0) {
            h.cards[i].suit = CLUBS;
        } else if (strcmp(suitCheck, "DIAMONDS")==0) {
            h.cards[i].suit = DIAMONDS;
        } else if (strcmp(suitCheck, "SPADES")==0) {
            h.cards[i].suit = SPADES;
        }
        
        line[0]='\0';
    }
    free(line);
    return h;
}

void SaveDeckToFile(Deck deck, FILE *file){
    fprintf(file, "%d\n", deck.top);
    for (int i = deck.top; i<DECK_SIZE ; i++){

        fprintf(file,"%d,", deck.cards[i].value);
        switch(deck.cards[i].suit) {
            case HEARTS:
                fprintf(file,"HEARTS\n");
                break;
            case DIAMONDS:
                fprintf(file,"DIAMONDS\n");
                break;
            case CLUBS:
                fprintf(file,"CLUBS\n");
                break;
            case SPADES:
                fprintf(file,"SPADES\n");
                break;
            default:
                printf("ERROR\n");
                break;
        } 

    }
}
Deck LoadDeckFromFile(FILE *file) {
    Deck d;
    char* line = (char*) malloc(50 * sizeof(char));
    fgets (line, 50 , file);
    sscanf(line, "%d", &d.top);

    for (int i = d.top; i< DECK_SIZE; i++){
        char suitCheck[10];
        fgets (line, 50 , file);
        sscanf(line, "%d,%s",&d.cards[i].value, suitCheck);
        if (strcmp(suitCheck,"HEARTS")==0) {
            d.cards[i].suit = HEARTS;
        } else if (strcmp(suitCheck, "CLUBS")==0) {
            d.cards[i].suit = CLUBS;
        } else if (strcmp(suitCheck, "DIAMONDS")==0) {
            d.cards[i].suit = DIAMONDS;
        } else if (strcmp(suitCheck,"SPADES")==0) {
            d.cards[i].suit = SPADES;
        }
        line[0]='\0';

    }
    return d;

}
