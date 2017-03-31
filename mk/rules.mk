all:	$(OBJ)
	@$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) $(LOCAL_CXXFLAGS)

%.o:	%.cpp
	@echo "compiling $<"
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(LOCAL_CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
