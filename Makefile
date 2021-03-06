CC := g++-4.8
FLAGS := -std=c++11 -w
BIN := bin
BUILD := build
INC := include
SRC := src
INCLUDE := -I./$(INC)

$(BIN)/agenda: $(BUILD)/Agenda.o $(BUILD)/User.o $(BUILD)/Storage.o $(BUILD)/Meeting.o $(BUILD)/Date.o $(BUILD)/AgendaUI.o $(BUILD)/AgendaService.o
	@mkdir -p $(BIN)
	$(CC) $(FLAGS) $(INCLUDE) $(BUILD)/Agenda.o $(BUILD)/User.o $(BUILD)/Storage.o $(BUILD)/Meeting.o $(BUILD)/Date.o $(BUILD)/AgendaUI.o $(BUILD)/AgendaService.o -g -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(BUILD)
	$(CC) $(FLAGS) $(INCLUDE) -g -c -o $@ $<

clean:
	@rm -rf $(BUILD)
	@rm -rf $(BIN)
