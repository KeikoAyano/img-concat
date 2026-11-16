CXXFLAGS = -std=c++20 -O2 -Wall
SRCS = *.cpp *.h
LIBRARY_SOURCES := $(filter-out main.cpp, $(SRCS))
OPENCV_DIR = /home/shirika/Libs/opencv
INCLUDES = -I$(OPENCV_DIR)/include/opencv4
LDFLAGS = -L$(OPENCV_DIR)/lib64 \
          -Wl,-rpath,$(OPENCV_DIR)/lib64
LDLIBS = -lopencv_core \
         -lopencv_imgproc \
         -lopencv_imgcodecs \
         -lopencv_highgui \
         -lopencv_videoio

BIN: $(SRCS)
	g++ $(CXXFLAGS) \
        $(SRCS) \
        -o main \
        -Iincludes/ \
        $(INCLUDES) $(LDFLAGS) $(LDLIBS)

LIBRARY: $(LIBRARY_SOURCES)
	g++ $(LIBRARY_SOURCES) \
        -fPIC -shared -o libimgcat.so \
        $(INCLUDES) $(LDFLAGS) $(LDLIBS)

STATICLIB: $(LIBRARY_SOURCES)
	g++ -c -static $(LIBRARY_SOURCES) $(INCLUDES) $(LDFLAGS) $(LDLIBS)
	ar rvs libimgcat.a img_concat.o
	rm img_concat.o

clean:
	rm -f main libimgcat.so libimgcat.a img_concat.o
