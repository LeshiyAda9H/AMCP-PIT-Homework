#include "database.h"
#include <cstring>
#include <limits>

int main()
{
	DataBase data;

	char command[32];

	while (true) {
		std::cout << "> ";
		std::cin >> command;
		if (strcmp(command, "add") == 0) {
			Stock stockich;

			while (isdigit(std::cin.peek()) == 0) { std::cin.ignore(); }

			try {
				std::cin >> stockich;
			}
			catch (WrongFormatDate& error) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Wrong date format: " << error.what() << std::endl;
				continue;
			}
			catch (WrongFormatTime& error) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Wrong time format: " << error.what() << std::endl;
				continue;
			}
			catch (WrongValueTime& error) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Time value is invalid: " << error.what() << std::endl;
				continue;
			}
			catch (WrongValueMonth& error) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Month value is invalid: " << error.what() << std::endl;
				continue;
			}
			catch (WrongValueDay& error) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Day value is invalid: " << error.what() << std::endl;
				continue;
			}
			catch (WrongType& error) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Unknown command: " << error.what() << std::endl;
				continue;
			}
			catch (...) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Unknown command" << std::endl;
				continue;
			}
			data.add(stockich);
		}
		else if (strcmp(command, "load") == 0) {
			std::cin >> command;

			std::ifstream inFile(command);

			if (inFile.is_open()) {
				data.load(inFile);
				inFile.close();
			}
			else {
				std::cout << "Can not open database";
			}
		}
		else if (strcmp(command, "save") == 0) {
			std::cin >> command;

			std::ofstream outFile(command);

			if (outFile.is_open()) {
				data.save(outFile);
				outFile.close();
			}
			else {
				std::cout << "Can not write to file";
			}
		}
		else if (strcmp(command, "delete") == 0) {
			int id;
			std::cin >> id;

			data.kill(id);
		}

		else if (strcmp(command, "clear") == 0) {
			data.clear();
		}
		else if (strcmp(command, "print") == 0) {
			data.print(std::cout);
		}
		else if (strcmp(command, "dom") == 0) {
			std::cin >> command;

			data.dom(command, std::cout);
		}
		else if (strcmp(command, "export") == 0) {
			std::cin >> command;

			std::ofstream outFile(command);

			if (outFile.is_open()) {
				data.exporti(outFile);
				outFile.close();
			}
			else {
				std::cout << "Can not write to file";
			}
		}
		else if (strcmp(command, "quit") == 0) {
			break;
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Unknown command: " << command << std::endl;
		}
	}

	return 0;
}
