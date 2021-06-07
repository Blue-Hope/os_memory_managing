all: main.cpp
	g++ -I ./cycle \
		-I ./memory \
		-I ./process \
		-I ./queue \
		-I ./utils \
		-I ./utils/input \
		-o main \
		-w \
		main.cpp \
		cycle/cycle.cpp \
		process/process.cpp process/cpu_process.cpp process/sleep_process.cpp\
		queue/queue.cpp queue/run_queues.cpp queue/run_queue.cpp queue/sleep_queue.cpp queue/io_queue.cpp

clean:
	rm main