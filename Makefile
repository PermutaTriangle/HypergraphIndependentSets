
all: count_ish_2n count_ish_bt

%: %.cpp
	g++ -Wall -O2 $< -o $@

