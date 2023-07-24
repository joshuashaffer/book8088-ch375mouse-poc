!if $(__VERSION__) < 1250
RM = del /q /f 2>NUL
!else
RM = rm -f
!endif

mouse.com: src/main.cpp
	wcl -bcl=com -oatxhs -oi+ -xd -0 -d0 -DNDEBUG -s -fe=mouse.com src/main.cpp

clean: .SYMBOLIC
	$(RM) mouse.com main.o