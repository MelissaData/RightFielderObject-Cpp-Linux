# Melissa Right Fielder Object Linux C++

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -g
LDLIBS = -lmdRightFielder
LDFLAGS = -L/home/emaiiii/MdLinuxExamples/melissarightfielderobjectlinuxcpp/MelissaRightFielderObjectLinuxCpp/Build
RM = rm -f

OUT_DIR = Build

MelissaRightFielderObjectLinuxCpp: Main.cpp RightFielderObject.cpp mdRightFielder.h mdRightFielderEnums.h | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) Main.cpp RightFielderObject.cpp $(LDFLAGS) $(LDLIBS) -o $(OUT_DIR)/$@

clean:
	$(RM) *.o $(OUT_DIR)/MelissaRightFielderObjectLinuxCpp

