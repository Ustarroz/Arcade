OBJ=	$(SRC:.cpp=.o)

all:	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) $(LOCAL_LDFLAGS) && echo  -e '\E[30;32m'"\033[1m[OK] $(BASE_NAME) with options: $(CXXFLAGS) $(LOCAL_CXXFLAGS) $(LDFLAGS) $(LOCAL_LDFLAGS)\033[0m";echo;

%.o:	%.cpp
	echo "compiling $<"
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LOCAL_CXXFLAGS)

clean:
	@$(RM) $(OBJ)
	@echo -e '\E[30;33m'"\033[1m[OK] Deleting objs: $(BASE_NAME)\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo -e '\E[30;33m'"\033[1m[OK] Deleting binary: $(BASE_NAME)\033[0m"

re: fclean all

.PHONY: clean fclean all re
