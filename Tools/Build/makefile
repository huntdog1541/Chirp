CC = g++
APP_NAME = Chirp

CXX_FLAGS =-std=c++11
SRC_ROOT =../../Source
DEST_DIR =build

#Create the include dirs in a list with -I in front of each item
INCLUDES = $(patsubst %, -I%, $(shell find $(SRC_ROOT) -type d))

#Set VPATH to find the source files
VPATH = $(shell find $(SRC_ROOT) -type d)

#Just get the filenames
SOURCE_FILES=$(notdir $(shell find $(SRC_ROOT) -name *.cpp))

#Turn the file names into object filenames
OBJECTS = $(SOURCE_FILES:%.cpp=$(DEST_DIR)/%.o)

# Debugging target
showvars: setup
	@echo "Source files = $(SOURCE_FILES)"
	@echo "Objects = $(OBJECTS)"
	@echo "Includes = $(INCLUDES)"
	@echo "VPATH = $(VPATH)"

.ONESHELL:
all: $(OBJECTS)
	$(CC) -o $(APP_NAME) $^ $(CXX_FLAGS)	

setup:
	@echo "Making a build folder"
	@mkdir -p $(DEST_DIR)

$(DEST_DIR)/%.o: %.cpp
	$(CC) -c $< -o $@ $(CXX_FLAGS) $(INCLUDES)

done:
	@echo "Build process is done! Output is in this folder - $(APP_NAME)"

clean:
	rm $(APP_NAME)
	rm $(DEST_DIR)/*.o
