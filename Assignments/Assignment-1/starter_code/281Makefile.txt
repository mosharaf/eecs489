## EECS 281 Advanced Makefile

# How to use this Makefile...
###################
###################
##               ##
##  $ make help  ##
##               ##
###################
###################

# IMPORTANT NOTES:
#   1. Set EXECUTABLE to the command name given in the project specification.
#   2. To enable automatic creation of unit test rules, your program logic
#      (where main() is) should be in a file named project*.cpp or specified
#      in the PROJECTFILE variable.
#   3. Files you want to include in your final submission cannot match the
#      test*.cpp pattern.

# Version 4 - 2015-05-03, Marcus M. Darden (mmdarden@umich.edu)
#   * Updated build rules for tests
# Version 3.0.1 - 2015-01-22, Waleed Khan (wkhan@umich.edu)
#   * Added '$(EXECUTABLE): $(OBJECTS)' target. Now you can compile with
#     'make executable', and re-linking isn't done unnecessarily.
# Version 3 - 2015-01-16, Marcus M. Darden (mmdarden@umich.edu)
#   * Add help rule and message
#   * All customization locations are cleary marked.
# Version 2 - 2014-11-02, Marcus M. Darden (mmdarden@umich.edu)
#   * Move customization section to the bottom of the file
#   * Add support for submit without test cases, to prevent submission
#     deduction while testing, when code fails to compile
#       usage: make partialsubmit  <- includes no test case files
#              make fullsubmit     <- includes all test case files
#   * Add automatic creation of test targets for test driver files
#       usage: (add cpp files to the project folder with a test prefix)
#              make alltests       <- builds all test*.cpp
#              make test_insert    <- builds testinsert from test_insert.cpp
#              make test2          <- builds testinsert from test2.cpp
#   * Add documentation and changelog
# Version 1 - 2014-09-21, David Snider (sniderdj@umich.edu)
# Vertion 0 - ????-??-??, Matt Diffenderfer (mjdiffy@umich.edu)

# enables c++14 on CAEN
PATH := /usr/um/gcc-5.1.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-5.1.0/lib64
LD_RUN_PATH := /usr/um/gcc-5.1.0/lib64

# TODO
# Change EXECUTABLE to match the command name given in the project spec.
EXECUTABLE 	= MineEscape

# designate which compiler to use
CXX			= g++

# list of test drivers (with main()) for development
TESTSOURCES = $(wildcard test*.cpp)
# names of test executables
TESTS       = $(TESTSOURCES:%.cpp=%)

# list of sources used in project
SOURCES 	= $(wildcard *.cpp)
SOURCES     := $(filter-out $(TESTSOURCES), $(SOURCES))
# list of objects used in project
OBJECTS		= $(SOURCES:%.cpp=%.o)

# TODO
# If main() is in a file named project*.cpp, use the following line
PROJECTFILE = $(wildcard project*.cpp)
# TODO
# If main() is in another file delete the line above, edit and uncomment below
#PROJECTFILE = mymainfile.cpp

# name of the tar ball created for submission
PARTIAL_SUBMITFILE = partialsubmit.tar.gz
FULL_SUBMITFILE = fullsubmit.tar.gz

#Default Flags
CXXFLAGS = -std=c++14 -Wconversion -Wall -Werror -Wextra -pedantic 

# make release - will compile "all" with $(CXXFLAGS) and the -O3 flag
#				 also defines NDEBUG so that asserts will not check
release: CXXFLAGS += -O3 -DNDEBUG
release: all

# make debug - will compile "all" with $(CXXFLAGS) and the -g flag
#              also defines DEBUG so that "#ifdef DEBUG /*...*/ #endif" works
debug: CXXFLAGS += -g3 -DDEBUG
debug: clean all

# make profile - will compile "all" with $(CXXFLAGS) and the -pg flag
profile: CXXFLAGS += -pg
profile: clean all

# highest target; sews together all objects into executable
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
ifeq ($(EXECUTABLE), executable)
	@echo Edit EXECUTABLE variable in Makefile.
	@echo Using default a.out.
	$(CXX) $(CXXFLAGS) $(OBJECTS)
else
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)
endif

# Automatically generate any build rules for test*.cpp files
define make_tests
    ifeq ($$(PROJECTFILE),)
	    @echo Edit PROJECTFILE variable to .cpp file with main\(\)
	    @exit 1
    endif
    SRCS = $$(filter-out $$(PROJECTFILE), $$(SOURCES))
    OBJS = $$(SRCS:%.cpp=%.o)
    HDRS = $$(wildcard *.h)
    $(1): CXXFLAGS += -g3 -DDEBUG
    $(1): $$(OBJS) $$(HDRS) $(1).cpp
	$$(CXX) $$(CXXFLAGS) $$(OBJS) $(1).cpp -o $(1)
endef
$(foreach test, $(TESTS), $(eval $(call make_tests, $(test))))

alltests: clean $(TESTS)

# rule for creating objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp

# make clean - remove .o files, executables, tarball
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TESTS) $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE)

# make partialsubmit.tar.gz - cleans, runs dos2unix, creates tarball omitting test cases
PARTIAL_SUBMITFILES=$(filter-out $(TESTSOURCES), $(wildcard Makefile *.h *.cpp))
$(PARTIAL_SUBMITFILE): $(PARTIAL_SUBMITFILES)
	rm -f $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE)
	-dos2unix $(PARTIAL_SUBMITFILES)
	COPYFILE_DISABLE=true tar -vczf $(PARTIAL_SUBMITFILE) $(PARTIAL_SUBMITFILES)
	@echo !!! WARNING: No test cases included. Use 'make fullsubmit' to include test cases. !!!

# make fullsubmit.tar.gz - cleans, runs dos2unix, creates tarball including test cases
FULL_SUBMITFILES=$(filter-out $(TESTSOURCES), $(wildcard Makefile *.h *.cpp test*.txt))
$(FULL_SUBMITFILE): $(FULL_SUBMITFILES)
	rm -f $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE)
	-dos2unix $(FULL_SUBMITFILES)
	COPYFILE_DISABLE=true tar -vczf $(FULL_SUBMITFILE) $(FULL_SUBMITFILES)
	@echo !!! Final submission prepared, test cases included... READY FOR GRADING !!!

# shortcut for make submit tarballs
partialsubmit: $(PARTIAL_SUBMITFILE)
fullsubmit: $(FULL_SUBMITFILE)

define MAKEFILE_HELP
EECS281 Advanced Makefile Help
* This Makefile uses advanced techniques, for more information:
    $$ man make

* General usage
    1. Follow directions at each "TODO" in this file.
       a. Set EXECUTABLE equal to the name given in the project specification.
       b. Set PROJECTFILE equal to the name of the source file with main()
       c. Add any dependency rules specific to your files.
    2. Build, test, submit... repeat as necessary.

* Preparing submissions
    A) To build 'partialsubmit.tar.gz', a tarball without tests used to find
       buggy solutions in the autograder.  This is useful for faster autograder
       runs during development and free submissions if the project does not
       build.
           $$ make partialsubmit
    B) Build 'fullsubmit.tar.gz' a tarball complete with autograder test cases.
       ALWAYS USE THIS FOR FINAL GRADING!  It is also useful when trying to
       find buggy solutions in the autograder.
           $$ make fullsubmit

* Unit testing support
    A) Source files for unit testing should be named test*.cpp.  Examples
       include test_input.cpp or test3.cpp.
    B) Automatic build rules are generated to support the following:
           $$ make test_input
           $$ make test3
           $$ make alltests        (this builds all test drivers)
    C) If test drivers need special dependencies, they must be added manually.
    D) IMPORTANT: NO SOURCE FILES THAT BEGIN WITH test WILL BE ADDED TO ANY
       SUBMISSION TARBALLS.
endef
export MAKEFILE_HELP

help:
	@echo "$$MAKEFILE_HELP"

#######################
# TODO (begin) #
#######################
# individual dependencies for objects
# Examples:
# "Add a header file dependency"
# project2.o: project2.cpp project2.h
#
# "Add multiple headers and a separate class"
# HEADERS = some.h special.h header.h files.h
# myclass.o: myclass.cpp myclass.h $(HEADERS)
# project5.o: project5.cpp myclass.o $(HEADERS)
#
# ADD YOUR OWN DEPENDENCIES HERE

# tests

class.o: class.cpp class.h

project0.o: project0.cpp class.h

######################
# TODO (end) #
######################

# these targets do not create any files
.PHONY: all release debug profile clean alltests partialsubmit fullsubmit help
# disable built-in rules
.SUFFIXES:
