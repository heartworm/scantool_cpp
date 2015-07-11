CC = $(NACL_TC)/pnacl-clang++ -std=gnu++11 -g -O0 --pnacl-exceptions=sjlj
INCLUDES = -I$(NACL)/include -Iinclude -Ilibraries/include
LIBPATHS = -L$(NACL)/lib/pnacl/Debug -Llibraries/lib
LIBS = -lppapi_cpp -lppapi -lopencv_contrib -lopencv_stitching -lopencv_nonfree -lopencv_superres -lopencv_ts \
	-lopencv_videostab -lopencv_gpu -lopencv_photo -lopencv_objdetect -lopencv_legacy -lopencv_video -lopencv_ml \
	-lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_imgproc -lopencv_flann -lopencv_core \
	-ltiff -lpng -ljpeg -lz


all: app.pexe

app.pexe: app.bc
	$(NACL_TC)/pnacl-finalize -o app.pexe app.bc

app.bc: MainModule.o MainInstance.o Processor.o ImageCommand.o CornerFinder.o KeystoneProcessor.o Preferences.o Corners.o
	$(CC) MainModule.o MainInstance.o Processor.o \
		ImageCommand.o CornerFinder.o KeystoneProcessor.o Preferences.o Corners.o -o app.bc $(INCLUDES) $(LIBPATHS) $(LIBS)
	
MainModule.o: MainModule.cpp
	$(CC) MainModule.cpp -c -o MainModule.o $(INCLUDES) $(LIBPATHS) $(LIBS)
	
MainInstance.o: MainInstance.cpp
	$(CC) MainInstance.cpp -c -o MainInstance.o $(INCLUDES) $(LIBPATHS) $(LIBS)
	
Processor.o: Processor.cpp
	$(CC) Processor.cpp -c -o Processor.o $(INCLUDES) $(LIBPATHS) $(LIBS)
	
ImageCommand.o: ImageCommand.cpp
	$(CC) ImageCommand.cpp -c -o ImageCommand.o $(INCLUDES) $(LIBPATHS) $(LIBS)

CornerFinder.o: CornerFinder.cpp
	$(CC) CornerFinder.cpp -c -o CornerFinder.o $(INCLUDES) $(LIBPATHS) $(LIBS)

KeystoneProcessor.o: KeystoneProcessor.cpp
	$(CC) KeystoneProcessor.cpp -c -o KeystoneProcessor.o $(INCLUDES) $(LIBPATHS) $(LIBS)
	
Preferences.o: Preferences.cpp
	$(CC) Preferences.cpp -c -o Preferences.o $(INCLUDES) $(LIBPATHS) $(LIBS)
	
Corners.o: Corners.cpp
	$(CC) Corners.cpp -c -o Corners.o $(INCLUDES) $(LIBPATHS) $(LIBS)