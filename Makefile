EXENAME = main
OBJS = imageOutput.o Ray.o
IMAGES = gradient.ppm gradient.png

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic `libpng-config --cflags`

LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ `libpng-config --ldflags`


all : $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) -o $(EXENAME) $(OBJS) $(LDFLAGS) 

imageOutput.o : imageOutput.cpp
	$(CXX) imageOutput.cpp $(CXXFLAGS)

Ray.o : Ray.h Ray.cpp
	$(CXX) Ray.cpp $(CXXFLAGS)

clean :
	rm -f *.o $(EXENAME) 

image-cleanup :
	rm -f $(IMAGES)
