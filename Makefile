#Gavin Henderson 150010848

CFLAGS= -Wall -Wextra -pedantic

clean:
	rm -f OLS
	
all:
	cc $(CFLAGS) ordered_list_set.c ordered_list_set_tester.c -o OLS
	
run:
	./OLS
	