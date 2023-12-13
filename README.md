# un-wcmc-dbms
Management system for United Nations Environment Porgram World Conservation Monitoring Centre database

## command to compile with g++
Assuming the project folder is in C:\Temp as well as wxWidgets folder (with source files and libraries)
(note : if your structure is different you need to adapt the following command)
```
g++ -o un-wcmc-dbms.exe un-wcmc-dbms.cpp -mthreads -DHAVE_W32API_H -D__WXMSW__ -DNDEBUG -D_UNICODE -IC:/Temp/wxWidgets/lib/gcc_dll/mswu -IC:/Temp/wxWidgets/include -DWXUSINGDLL -std=c++20 -mthreads -LC:/Temp/wxWidgets/lib/gcc_dll -mthreads -LC:/Temp/wxWidgets/lib/gcc_dll -lwxmsw32u_richtext -lwxmsw32u_xrc -lwxmsw32u_aui -lwxmsw32u_html -lwxmsw32u_adv -lwxmsw32u_core -lwxbase32u_xml -lwxbase32u_net -lwxbase32u -lwxscintilla -lwxtiff -lwxjpeg -lwxpng -lwxzlib -lwxregexu -lwxexpat -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwxregexu -lwinspool -lwinmm -lshell32 -lcomctl32 -lversion -lshlwapi -lole32 -loleaut32 -luuid -lrpcrt4 -ladvapi32 -lwsock32 -luxtheme -loleacc -lwxmsw32u_ribbon 
```