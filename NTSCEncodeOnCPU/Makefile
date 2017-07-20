release:
	g++ qa_encntsc.cpp encntsc.cpp -o encntsc `pkg-config --cflags --libs opencv`

csv:
	g++ -DSHOW_IMAGE='' -DWRITE_CSV='' -DDEBUG='' qa_encntsc.cpp encntsc.cpp -o encntsc `pkg-config --cflags --libs opencv`

image:
	g++ -DSHOW_IMAGE=''  -DDEBUG='' qa_encntsc.cpp encntsc.cpp -o encntsc `pkg-config --cflags --libs opencv`

debug:
	g++ -DDEBUG='' qa_encntsc.cpp encntsc.cpp -o encntsc `pkg-config --cflags --libs opencv`
