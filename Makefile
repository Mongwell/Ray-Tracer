EXENAME = render
OBJS = Ray.o Sphere.o Scene.o Camera.o main.o
IMAGES = sphere

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic `libpng-config --cflags`

LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ `libpng-config --ldflags`


all : $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) -o $(EXENAME) $(OBJS) $(LDFLAGS) 

main.o : Ray.o Scene.o Sphere.o Camera.o main.cpp
	$(CXX) main.cpp $(CXXFLAGS)

Camera.o : Ray.o Camera.h Camera.cpp
	$(CXX) Camera.cpp $(CXXFLAGS)

Sphere.o : Hittable.h Sphere.h Sphere.cpp
	$(CXX) Sphere.cpp $(CXXFLAGS)

Scene.o : Hittable.h Scene.h Scene.cpp
	$(CXX) Scene.cpp $(CXXFLAGS)

Ray.o : Ray.h Ray.cpp
	$(CXX) Ray.cpp $(CXXFLAGS)

clean :
	rm -f *.o $(EXENAME) 

image-cleanup :
	rm -f $(IMAGES).png $(IMAGES).ppm
