
# Specify the compiler
GXX=g++ -g

# Specify the target
all: searchTree.exe

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
searchTree.exe: BinNode.o BST.o  BSTmain.o
	$(GXX) BinNode.o BST.o  BSTmain.o -o searchTree.exe

# Specify how the object files should be created from source files
BSTmain.o: BSTmain.cpp
	$(GXX)  -c  BSTmain.cpp

BinNode.o: BinNode.cpp
	$(GXX)  -c  BinNode.cpp

BST.o: BST.cpp
	$(GXX)  -c  BST.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o *~ core searchTree.exe
