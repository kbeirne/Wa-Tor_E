#macros
Executable_Name = game
Build_Name = main.c
Include_Files = Time.h Fish.h

#default Target
exec: \
compile #Target dependencies
	./$(Executable_Name)


#Target
compile: \
Makefile $(Build_Name) $(Include_Files) #Target dependencies
	gcc $(Build_Name) -o $(Executable_Name)
	touch compile #update timestamp

