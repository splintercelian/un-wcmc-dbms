CC = g++
CFLAGS =

INCLUDES = -IC:/Temp/wxWidgets/lib/gcc_dll/mswu -IC:/Temp/wxWidgets/include
LIBINCLUDES = -LC:/Temp/wxWidgets/lib/gcc_dll
LDFLAGS = -mthreads -DHAVE_W32API_H -D__WXMSW__ -DNDEBUG -D_UNICODE -DWXUSINGDLL -std=c++20 -mthreads -lwxmsw32u_richtext -lwxmsw32u_xrc -lwxmsw32u_aui -lwxmsw32u_html -lwxmsw32u_adv -lwxmsw32u_core -lwxbase32u_xml -lwxbase32u_net -lwxbase32u -lwxscintilla -lwxtiff -lwxjpeg -lwxpng -lwxzlib -lwxregexu -lwxexpat -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lversion -lshlwapi -lole32 -loleaut32 -luuid -lrpcrt4 -ladvapi32 -lwsock32 -luxtheme -loleacc -lwxmsw32u_ribbon

HEADERFILES = un-wcmc-dbms.h
CPPFILES = un-wcmc-dbms.cpp
OBJFILES = un-wcmc-dbms.o

TARGET = un-wcmc-dbms

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(INCLUDES) $(LIBINCLUDES) $(LDFLAGS)

$(OBJFILES): $(CPPFILES) $(HEADERFILES)
	$(CC) $(CFLAGS) -c $(CPPFILES) $(INCLUDES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~