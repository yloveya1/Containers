UNAME := $(shell uname)

all: test gcov_report

test:
	g++ tests/main_tests.cc -lgtest -lgmock -pthread -fprofile-arcs -ftest-coverage -std=c++17 -Wall -Werror -Wextra
	./a.out

gcov_report: test
	lcov -t report -o report.info -c -d . --no-external
	genhtml report.info -o finish

clean:
	rm -rf *.gcda *.gcno report.info a.out finish

html:
ifeq ($(UNAME), Linux)
	firefox finish/index.html
endif
ifeq ($(UNAME), Darwin)
	open finish/index.html
endif

lint:
	cp ../materials/linters/.clang-format ./
	clang-format -n */*.h *.h */*.cc
	clang-format -i */*.h *.h */*.cc
	rm -rf .clang-format