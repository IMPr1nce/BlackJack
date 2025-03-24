blackjack: main.c card.c hand.c deck.c
	gcc -o blackjack.exe main.c card.c hand.c deck.c

clean:
	del *.exe *.txt
