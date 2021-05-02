

all:
	rm -f RB.cv
	cat rb_header.h > RB.cv
	cat *.c >> RB.cv
	time gcc -static *.c -o RedBLTree
clean:
	rm -f a.out *.rb *.md *.cv RedBLTree
cop:
