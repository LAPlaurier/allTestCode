#####
# 2023/10/27
#####

CXX := g++

CXXFLAGS += -g -O0 -std=c++17 -Wall -Wno-deprecated -Wno-unused-but-set-variable


SOURCE_FILES = $(wildcard *.cpp)
# $(info test_patsubst: $(patsubst %.cpp, %.o, $(SOURCE_FILES)))
# $(info SOURCE_FILES: $(SOURCE_FILES))
# $(info test_addprefix: $(addprefix /path/to/, $(SOURCE_FILES)))
# 使用模式替换功能将.cpp扩展名替换为.o来生成变量，得到对象文件列表
OBJ_FILES = $(SOURCE_FILES:.cpp=.o)
# $(info OBJ_FILES: $(OBJ_FILES))

# 当你想要构建具体的目标（如main）时，你需要提供明确的文件名或文件列表，而不是使用模式。
main : $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.PHONY : clean
# 如果没有.PHONY指明clean是伪目标的话，当目录中有名为clean的文件时，make clean命令失效
clean:
# $(RM) -f main.o main.s main.i utils.o utils.s utils.i
# rm -f $(OBJ_FILES) main
	rm -f $(foreach FILE, $(OBJ_FILES), $(FILE))