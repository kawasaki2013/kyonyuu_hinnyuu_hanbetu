
#ソースコードはwindows用のものと共用できるようにした。
#「../face_kirinuki_windows/OpenCV_test001/OpenCV_test001.cpp」を参照。

all : face_kirinuki_linux

face_kirinuki_linux : ../face_kirinuki_windows/OpenCV_test001/OpenCV_test001.cpp
	g++ -g `pkg-config --cflags opencv` -o face_kirinuki_linux ../face_kirinuki_windows/OpenCV_test001/OpenCV_test001.cpp `pkg-config --libs opencv`

clean :
	-rm face_kirinuki_linux

clean-all : clean
	-rm *~
