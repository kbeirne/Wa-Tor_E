#macros
Executable_Name = game
Build_Name = main.c
Include_Files = Time.h Creature.h World.h Globals.h

#default Target
exec: \
compile #Target dependencies
	./$(Executable_Name)


#Target
compile: \
Makefile $(Build_Name) $(Include_Files) #Target dependencies
	gcc $(Build_Name) -o $(Executable_Name) -fopenmp
	touch compile #update timestamp

