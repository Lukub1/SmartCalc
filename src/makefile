CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -std=c11
PROGRAM_NAME=calculator
INCLUDE_LIBS=-lcheck -lrt -lpthread -lm
INSTALL_DIRECTORY=S21_Calculator/
COMPILATION_DIRECTORY=mybuild/
FORMATS_FOR_DEL=*.o *.out *.info *.gcda *.gcno report CPPLINT.cfg *.log *.dvi *.pdf *.tmp *.aux *.tgz *.tar
DIST_NAME=SmartCalc_v1
all: clean s21_smartcalc_v1.a test gcov_report


s21_smartcalc_v1.o: s21_smartcalc_v1.c s21_smartcalc_v1.h
	@$(CC) $(CFLAGS) s21_smartcalc_v1.c s21_smartcalc_v1.h -lm
	
s21_smartcalc_v1.a: s21_smartcalc_v1.o
	@ar -rcs s21_smartcalc_v1.a s21_smartcalc_v1.o
	@ranlib $@
	@cp $@ lib$@
	

clean:
	@rm -rf *.out *.o *.gch  log.txt logTest.txt s21_smartcalc_v1 *dSYM
	@rm -rf coverage *.a *.gcda *gcno *.info Test *.cfg .clang-format
	@rm -rf S21_Calculator mybuild

OS = $(shell uname)
ifeq ($(OS), Linux)
	LINUX_LIBS=-lsubunit -lrt -lpthread -lm
	CC += -D OS_LINUX -g
	CHECK_LEAKS=valgrind --leak-check=full -s --log-file=log.txt
	OPEN_GCOV=firefox coverage/src/index.html
	OUT_LEAKS= grep log.txt
else
	LINUX_LIBS=
	CC += -D OS_MAC
	CHECK_LEAKS=CK_FORK=no leaks --atExit --
	OPEN_GCOV=open coverage/index.html
endif

test:	clean style
	@$(CC) -g s21_smartcalc_v1.c test.c -lcheck $(LINUX_LIBS) -o ./Test 
	@$(CHECK_LEAKS) ./Test

style: 
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -n *.c *.h calculator/c*.cpp calculator/c*.h calculator/d*.cpp calculator/d*.h calculator/g*.cpp calculator/g*.h calculator/m*.cpp calculator/m*.h
	@rm -rf .clang-format

gcov_report: s21_smartcalc_v1.c test.c s21_smartcalc_v1.h
	@$(CC) -fprofile-arcs -ftest-coverage test.c s21_smartcalc_v1.c -o Test -lcheck $(LINUX_LIBS) $(GCOV)
	@./Test
	@lcov -c -d . -o coverage.info
	@genhtml coverage.info -o coverage
	@$(OPEN_GCOV)

install: clean build
	@mkdir $(INSTALL_DIRECTORY)
	@cp $(COMPILATION_DIRECTORY)calculator $(INSTALL_DIRECTORY)$(PROGRAM_NAME)
	@rm -rf $(COMPILATION_DIRECTORY)
uninstall:
	@rm -rf $(INSTALL_DIRECTORY)

build:
	@mkdir $(COMPILATION_DIRECTORY)
	@cp calculator/calculator.pro $(COMPILATION_DIRECTORY)
	@cp *.c $(COMPILATION_DIRECTORY)
	@cp calculator/*.cpp $(COMPILATION_DIRECTORY)
	@cp calculator/*.h $(COMPILATION_DIRECTORY)
	@cp calculator/*.ui $(COMPILATION_DIRECTORY)
	@cd $(COMPILATION_DIRECTORY); qmake calculator.pro
	@cd $(COMPILATION_DIRECTORY); make all


dist:
	@tar -czf Smartcalc.tar.gz .

dvi:
ifeq ($(OS), Darwin)
	open calculator/dvi.html
else
	xdg-open calculator/dvi.html
endif

