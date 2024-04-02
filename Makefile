all: getsections getsyms getsections_d1 getsyms_d1 objcopy

# Making the executables
getsections: getsections.o libobjdata.a
	gcc getsections.o ./libobjdata.a -lbfd -o getsections

getsyms: getsyms.o libobjdata.a
	gcc getsyms.o ./libobjdata.a -lbfd -o getsyms

objcopy: objcopy.o
	gcc objcopy.c -o objcopy -lbfd



# Making the dynamic library
libobjdata.so: objsect_pic.o objsym_pic.o objcopy_pic.o
	gcc -shared -o libobjdata.so objsect_pic.o objsym_pic.o objcopy_pic.o

# Making the dynamic executables
getsections_d1: getsections_d1.o libobjdata.so
	gcc getsections_d1.o -L. -Wl,-rpath,'$ORIGIN' -lbfd -ldl -o getsections_d1

getsyms_d1: getsyms_d1.o libobjdata.so
	gcc getsyms_d1.o -L. -Wl,-rpath,'$ORIGIN' -lbfd -ldl -o getsyms_d1

# Making the static library
libobjdata.a: objsect.o objsym.o objcopy.o
	ar rcs libobjdata.a objsect.o objsym.o objcopy.o

# Making object files for static library
objsect.o: objsect.c
	gcc -c objsect.c -o objsect.o

objsym.o: objsym.c
	gcc -c objsym.c -o objsym.o

objcopy.o: objcopy.c 
	gcc -c objcopy.c -o objcopy.o

# Making PIC object files for dynamic library
objsect_pic.o: objsect.c
	gcc -c -fPIC objsect.c -o objsect_pic.o

objsym_pic.o: objsym.c
	gcc -c -fPIC objsym.c -o objsym_pic.o

objcopy_pic.o: objcopy.c
	gcc -c -fPIC objcopy.c -o objcopy_pic.o

# Making object files for the dynamic executables
getsections_d1.o: getsections_d1.c
	gcc -c getsections_d1.c

getsyms_d1.o: getsyms_d1.c
	gcc -c getsyms_d1.c

clean:
	rm -f *.o *.log getsections getsyms getsections_d1 getsyms_d1 libobjdata.a libobjdata.so objcopy