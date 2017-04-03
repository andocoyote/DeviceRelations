#Best nmake tutorial: http://www.bogotobogo.com/cplusplus/make.php
INCS=\

# Specify the location to my SDK libs (e.g. DbgHelp.Lib)
LIBS=\
	"C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib" 
	
CC=cl
CFLAGS=/c /EHsc
#LDFLAGS=/link /LIBPATH:$(LIBS)
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.obj)
EXECUTABLE=main

#Uncomment the following to enable debugging
DBGFLAGS=/Zi

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(DBGFLAGS) $(OBJECTS) -Fe$@ $(LDFLAGS)

.cpp.obj:
	$(CC) $(CFLAGS) $< -Fe$@

clean:
   del *.exe *.obj *.pdb *.ilk
