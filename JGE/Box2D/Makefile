PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)
TARGET_LIB = libbox2d.a
OBJS =  Source/Collision/b2BroadPhase.o Source/Collision/b2CollideCircle.o \
		Source/Collision/b2CollidePoly.o Source/Collision/b2Distance.o \
		Source/Collision/b2PairManager.o Source/Collision/b2Shape.o \
		Source/Common/b2BlockAllocator.o Source/Common/b2Settings.o \
		Source/Common/b2StackAllocator.o \
		Source/Dynamics/b2Body.o Source/Dynamics/b2ContactManager.o \
		Source/Dynamics/b2Island.o Source/Dynamics/b2World.o Source/Dynamics/b2WorldCallbacks.o \
		Source/Dynamics/Contacts/b2CircleContact.o Source/Dynamics/Contacts/b2Contact.o \
		Source/Dynamics/Contacts/b2Conservative.o Source/Dynamics/Contacts/b2ContactSolver.o \
		Source/Dynamics/Contacts/b2PolyAndCircleContact.o Source/Dynamics/Contacts/b2PolyContact.o \
		Source/Dynamics/Joints/b2DistanceJoint.o Source/Dynamics/Joints/b2GearJoint.o \
		Source/Dynamics/Joints/b2Joint.o \
		Source/Dynamics/Joints/b2MouseJoint.o \
		Source/Dynamics/Joints/b2PrismaticJoint.o Source/Dynamics/Joints/b2PulleyJoint.o \
		Source/Dynamics/Joints/b2RevoluteJoint.o

INCDIR = include/psp include/psp/freetype2 Include
LIBDIR = lib/psp

CFLAGS = -O2 -G0 -Wall

LIBS = -lgif -lfreetype -ljpeg -lpng -lz -lmikmod -lpsppower -lpspmpeg -lpspaudiocodec -lpspaudiolib -lpspaudio -lpspgum -lpspgu -lpsprtc -lm -lstdc++

include $(PSPSDK)/lib/build.mak

install: $(TARGET_LIB)
	@cp libbox2d.a  Library
	@echo "Done"
