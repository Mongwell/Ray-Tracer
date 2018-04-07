EXENAME = render
OBJS = Ray.o Geometry/Sphere.o Geometry/Triangle.o Geometry/Quadrilateral.o Geometry/BoundingBox.o BVH.o Scene.o Cameras/PrspcCamera.o Cameras/OrthgCamera.o main.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic -o $@ `libpng-config --cflags`

LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ `libpng-config --ldflags`


all : $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) -o $(EXENAME) $(OBJS) $(LDFLAGS) 

main.o : Geometry/Hittable.h Ray.h Scene.h Geometry/Sphere.h Geometry/Triangle.h Geometry/Quadrilateral.h Cameras/PrspcCamera.h Cameras/OrthgCamera.h main.cpp
	$(CXX) main.cpp $(CXXFLAGS)

Cameras/PrspcCamera.o : Ray.h Cameras/PrspcCamera.h Cameras/PrspcCamera.cpp
	$(CXX) Cameras/PrspcCamera.cpp $(CXXFLAGS)

Cameras/OrthgCamera.o : Ray.h Cameras/OrthgCamera.h Cameras/OrthgCamera.cpp
	$(CXX) Cameras/OrthgCamera.cpp $(CXXFLAGS)

Geometry/Triangle.o : Geometry/Hittable.h Geometry/Triangle.h Geometry/Triangle.cpp
	$(CXX) Geometry/Triangle.cpp $(CXXFLAGS)

Geometry/Quadrilateral.o : Geometry/Hittable.h Geometry/Triangle.h Geometry/Quadrilateral.h Geometry/Quadrilateral.cpp
	$(CXX) Geometry/Quadrilateral.cpp $(CXXFLAGS)

Geometry/BoundingBox.o : Ray.h Geometry/BoundingBox.h Geometry/BoundingBox.cpp
	$(CXX) Geometry/BoundingBox.cpp $(CXXFLAGS)

Geometry/Sphere.o : Geometry/Hittable.h Geometry/Sphere.h Geometry/Sphere.cpp
	$(CXX) Geometry/Sphere.cpp $(CXXFLAGS)

Scene.o : Geometry/Hittable.h Ray.h Scene.h Scene.cpp
	$(CXX) Scene.cpp $(CXXFLAGS)

BVH.o : Geometry/Hittable.h BVH.h BVH.cpp 
	$(CXX) BVH.cpp $(CXXFLAGS)

Ray.o : Ray.h Ray.cpp
	$(CXX) Ray.cpp $(CXXFLAGS)

clean :
	rm -f **/*.o *.o $(EXENAME) 

image-cleanup :
	rm -f *.png *.ppm
