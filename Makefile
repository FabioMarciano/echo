#
# Echo log library Makefile
# @author Fabio Marciano
#

LIB = libecho

DIR = src
BIN = bin
INC = include

VERSION_FILE = ./version

VERSION_MAJOR := `cat $(VERSION_FILE) | cut -d"." -f1`
VERSION_MINOR := `cat $(VERSION_FILE) | cut -d"." -f2`
VERSION_PATCH := `cat $(VERSION_FILE) | cut -d"." -f3`

LIB_SONAME = so.$(VERSION_MAJOR)
LIB_REAL_NAME = so.$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)
LIB_LINK_NAME = so

SRC = $(wildcard $(DIR)/*.c)
OBJ = $(SRC:.c=.o)
OPT = -Wall -fPIC -I$(INC)

.PHONY: mkbin purge clean

all: mkbin $(LIB) clean

$(LIB): $(OBJ)
	@echo Creating the shared lib $@.so
	@gcc -shared -Wl,-soname,$@.$(LIB_SONAME) -o $(BIN)/$@.$(LIB_REAL_NAME) $^ -lc
	@ldconfig -n $(BIN)
	@ln -s $@.$(LIB_SONAME) $(BIN)/$@.$(LIB_LINK_NAME)
	@echo Creating the static library $@.a
	@ar -rc $(BIN)/$@.a $^
	@ranlib $(BIN)/$@.a

%.o: %.c
	@echo Creating $@ from $^ source
	@gcc -c $(OPT) -o $@ $^

mkbin: purge
	@echo Creating binary folder
	@mkdir $(BIN)

purge:
	@echo Purging old binary files \(if exists\)
	@rm -rf $(BIN)

clean:
	@echo Removing temporary objects $(DIR)/*.o
	@rm -f $(OBJ)
