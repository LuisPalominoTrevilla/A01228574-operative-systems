compila:
	gcc hello.c -o hello
	./hello
clean:
	rm -rf ./hello
push:
	git add .
	git commit -m "Makefile"
	git push origin master