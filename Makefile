# Simple wmake makefile that builds mouse8088.com
#

mouse.com: src/main.cpp
	wcl -bcl=com -oatxhs -oi+ -xd -0 -d0 -DNDEBUG -s -fe=mouse.com src/main.cpp