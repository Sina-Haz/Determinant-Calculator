all:fifth

fifth: fifth.c
	gcc -g -Wall -Werror -fsanitize=address determinant.c -o det_calc

clean:
	rm det_calc
