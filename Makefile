all: main.cpp
	g++ -I ./cycle \
		-I ./memory \
		-I ./process \
		-I ./queue \
		-I ./utils \
		-I ./utils/input \
		-o main \
		main.cpp cycle/cycle.cpp process/process.cpp

clean:
	rm main