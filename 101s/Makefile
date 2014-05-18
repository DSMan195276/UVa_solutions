
all: ./probc ./Main.class

./probc: ./prob.c
	gcc ./prob.c -o ./probc

./Main.class: ./prob.java
	javac prob.java

clean:
	rm -f ./probc ./Main.class

