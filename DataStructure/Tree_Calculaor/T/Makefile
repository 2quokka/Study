TreeCal.exe : ExpressionStack.o ExpressionTree.o Main.o
	gcc -o TreeCal.exe ExpressionStack.o ExpressionTree.o Main.o -lm

ExpressionStack.o : ExpressionStack.c
	gcc -c -o ExpressionStack.o ExpressionStack.c -lm

ExpressionTree.o : ExpressionTree.c
	gcc -c -o ExpressionTree.o ExpressionTree.c -lm

Main.o : Main.c
	gcc -c -o Main.o Main.c

clean :
	rm *.o

