# Define Macro
CC           = gcc
CFLAGS 		 = -I./include -O2 -Wall -W 
LIBNAME      = ./lib/libUnitTest.a

EXAPPNAME    = ./bin/ExApp

# Target
all          : $(LIBNAME) ${EXAPPNAME}

# Build Taxi Library
$(LIBNAME)   : ./lib/UnitTest.o
	$(AR) $(AFLAGS) -r $@ $^
	
${EXAPPNAME} : ./src/main.o ./src/DateTime.o ./src/CommLib.o
	${CC} -o $@ $(CFLAGS) $^ ${LIBNAME}  
		
clean        :
	rm -rf $(LIBNAME) ${EXAPPNAME} ./src/*.o ./lib/*.o	
	
#.c.o       :
#	$(CC) $(CFLAGS) -c $^
	
