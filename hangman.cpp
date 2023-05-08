#include<algorithm>
#include<iomanip>
#include<iostream>
#include<limits>
#include<string>
#include <cctype>

#undef max

class Hangman
{
private:
	std::string wordName{ "" }, wordHint{ "" }, answer{ "" }, wordType{ "" };

	// Just for fun names
	const std::string HANGED[5]{ "JOHN","ALEX","MAX","JIMMY","TIM" };

	// Incase of variable resetting
	const std::string KEYBOARD_LAYOUT{ "\t\t  ___________________________________  \n"
									"\t\t |             KEYBOARD              | \n"
									"\t\t |-----------------------------------| \n"
									"\t\t | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | \n"
									"\t\t |-----------------------------------| \n"
									"\t\t | a | b | c | d | e | f | g | h | i | \n"
									"\t\t |-----------------------------------| \n"
									"\t\t | j | k | l | m | n | o | p | q | r | \n"
									"\t\t |-----------------------------------| \n"
									"\t\t | s | t | u | v | w | x | y | z | 0 | \n"
									"\t\t |-----------------------------------| \n"
									"\t\t |___________________________________| \n" };

	std::string keyboard{ KEYBOARD_LAYOUT };

	// How many parts of the hanged man
	int countHang{ 0 };

	// Input Variable
	char ch{ 0 };

	// check variables
	bool active{ 1 }, flag{ 1 }, tag{ 1 };

public:

	// Hangman() -> contructor Main Menu to link all the functions together
	// HintWord() -> Word inputs
	// Rules() -> pretty simple there
	// HangBoard() -> the main display board
	// HangCheck() -> Draws main-body of the Hangman and checks how many left
	// AgainMenu() -> Final display menu and variable resetting

	// Exiting Variable
	bool exit{ 0 };

	Hangman() {

		// STARTING WINDOW
		active = 1;
		while (active) {

		std::cout << R"RAW(
					 ____________________________________
					|              MAIN MENU             |
					|             -----------            |
					|     --XX---            ---XX--     |
					|       :      ~Hangman~     :       |
					|       :                    :       |
					|       O      1.  Play      O       |
					|      /|\                  /|\      |
					|      / \     2.  Rules    / \      |
					|                                    |
					|              3.  Exit              |
					|____________________________________|
					            -->   )RAW";

			// Choice menu with conditions incase of wrong input
			std::cin >> ch;

			if (ch == '1') {
				active = 0;
				system("cls");
				HintWord();
			}
			else if (ch == '2') {
				active = 0;
				system("cls");
				Rules();
			}
			else if (ch == '3') {
				system("cls");
				active = 0;
				exit = 1;
				// EXIT
			}
			else {
				system("cls");
				// WRONG CHOICE
			}
		}
	};


	void Rules() {

		std::cout << R"RAW(
							~WELCOME~
		------------------------------------------------------------------------------------------
		(1)Choose one person to be the 'host.' This is the person that invents the puzzle
		for the other person to solve. They will be tasked with choosing a word that 'the players'
		will have to solve.
		The host should be able to spell confidently or the game will be impossible to win.
		(2)If you are the host, choose a secret word. The other players will need to guess your
		word letter by letter, so choose a word you think will be difficult to guess. Difficult
		words usually have uncommon letters, like 'z,' or 'j,' and only a few vowels.
		(3)Start guessing letters if you are the player. Once the word has been chosen and the
		players know how many letters in the secret word, begin playing by entering which letters
		are in the word.
		(4)Whenever the players guess a letter that is not in the secret word they get a strike
		that brings them closer to losing. To show this, the game draws a simple stick figure of a
		man being hung, adding a new part to the drawing with every wrong answer.
			                            *** 1.  Go Back.
		------------------------------------------------------------------------------------------
			                                     -->  )RAW";
		std::cin >> ch;
		if (ch == '1') {
			active = 0;
			system("cls");
			Hangman();
		}
		else {
			system("cls");
			// WRONG CHOICE
		}
	}


	void HintWord() {

		std::cout << R"RAW(
				  ______
			         |      |
			         |      :
			         |
			         |          \ O    O
			         |           |\   /|7
			      ___|___       / \   / \
		 *** Host, Enter secret word to be found:               (*) PLAYERS DON'T LOOK AT THIS SCREEN!!
			              --> )RAW";

		std::cin >> wordName;

		// Takes main word input here and converts to lower-case
		std::transform(wordName.begin(), wordName.end(), wordName.begin(), tolower);

		std::cout << std::endl;
		std::cout << "\t\t *** Enter word type e.g Movie,Food/Drink,Song..etc: \n"

			"\t\t               --> ";

		// Had a problem here as the getline() function wasn't accepting all of the input correctly , which numeric limit seemed to fix here
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::getline(std::cin, wordType);
		std::cout << std::endl;

		std::cout << "\t\t *** Enter hint:                           \n"

			"\t\t               --> ";

		std::getline(std::cin, wordHint);

		// Converting all of it into Underscores
		for (unsigned i{ 0 }; i < wordName.length(); ++i)
			answer += "_";


		system("cls");
		HangBoard();

	}



	void HangBoard() {

		int i{ 0 };
		active = 1;

		while (active) {
			HangCheck();
			std::cout << "\t\t ~TYPE~ \"" << wordType << "\"\t\t  ";

			// Displaying the word as underscores with spaces
			for (unsigned i{ 0 }; i < wordName.length(); ++i) {

				std::cout << answer[i] << " ";
			}

			std::cout << "\n\n\t\t ~HINT~ \"" << wordHint << "\"\n\n";
			std::cout << "\t\t\t\t\t\t\t (*) '#' Shown on the keyboard means it's already tried.";
			std::cout << "\t\t\t\t\t\t\t\t (*)  Enter '.' to exit.";
			std::cout << "\n\n" << keyboard;

			// Just wanted to try doing a little fun trick , if they entered "#" as their first choice of character
			// It would automatically show the first letter of the hidden word , if they use "#" as any other input of character
			// Which isnt the first choice, it wouldn't work. I will mark the trick part with a //TRICK comment
			if (flag == 1) {

				std::cout << "\t\t     ~X~ -->"; std::cin >> ch;
			}

			// TRICK
			else {

				std::cout << "\t\t ;)  ~O~ -->"; std::cin >> ch;
			}

			// EXIT INPUT
			if (ch == '.') {
				system("cls");
				Hangman();
				active = 0;
				break;
			}

			// Converting ASCII values
			if (ch <= 90 && ch >= 65)
				ch += 32;

			// incase of input of any of those signs to keep keyboard(variable) same outline format , using # sign as letter being taken
			if (ch != '|'&& ch != '_' && ch != '-' && keyboard.find(ch) != std::string::npos)
				keyboard[keyboard.find(ch)] = '#';

			if (ch != '#')
				tag = 0;

			// TRICK
			if (ch == '#' && flag == 1 && tag == 1) {
				ch = wordName[0];
				flag = 0;
			}

			// Checking if correct input here with find function
			i = wordName.find(ch);
			while (wordName.find(ch, i) != std::string::npos) {

				answer[wordName.find(ch, i)] = ch;
				i++;
			}
			if (wordName.find(ch) == std::string::npos) {
				countHang++;

				// testing the basic alarm bell sound for wrong character input
				std::cout << "\a";
			}
			if (countHang == 6) {
				system("cls");
				AgainMenu();
			}
			else if (answer == wordName) {
				system("cls");
				AgainMenu();
			}

			system("cls");
		}

	}


	void AgainMenu() {

		active = 1;
		while (active) {
			if (countHang == 6) {

				std::cout << "\t\t  ____________________________________  \n"
					"\t\t |             " << std::setw(5) << HANGED[rand() % 5] << " DIED!            | \n"
					"\t\t |             -----------            | \n"
					"\t\t |              ( X _ X )             | \n"
					"\t\t |                                    | \n"
					"\t\t |                       ________     | \n"
					"\t\t |                      / Nooo!!!\\    | \n"
					"\t\t |       _____          \\  ______/    | \n"
					"\t\t |      (     )     <O>  \\/           | \n"
					"\t\t |      | RIP |      |                | \n"
					"\t\t |      |_____|     <<                | \n"
					"\t\t |   ------------------------------   | \n"
					"\t\t |                                    | \n"
					"\t\t |          1.  Play Again            | \n"
					"\t\t |                                    | \n"
					"\t\t |          2.  Exit                  | \n"
					"\t\t |____________________________________| \n\n\n";
			}
			else {
				std::cout << "\t\t  ____________________________________  \n"
					"\t\t |            " << std::setw(5) << HANGED[rand() % 5] << " LIVES!            | \n"
					"\t\t |             -----------            | \n"
					"\t\t |           ________                 | \n"
					"\t\t |          / I LIVE!\\                | \n"
					"\t\t |          \\  ______/                | \n"
					"\t\t |            \\/                      | \n"
					"\t\t |        |O/                         | \n"
					"\t\t |         |                          | \n"
					"\t\t |        / >                         | \n"
					"\t\t |      _____       \\O>   \\O/         | \n"
					"\t\t |     /     \\       |     |          | \n"
					"\t\t |    /       \\     < \\   / \\         | \n"
					"\t\t |   ------------------------------   | \n"
					"\t\t |                                    | \n"
					"\t\t |          1.  Play Again            | \n"
					"\t\t |                                    | \n"
					"\t\t |          2.  Exit                  | \n"
					"\t\t |____________________________________| \n\n\n";
			}
			std::cout << "\t\t            -->";
			std::cin >> ch;
			if (ch == '1') {
				active = 0;

				system("cls");

				// Variable resetting
				countHang = 0;
				flag = 1;
				tag = 1;
				wordName = "0";
				wordHint = "0";
				answer = "";
				wordType = "0";
				keyboard = KEYBOARD_LAYOUT;
				HintWord();
			}
			else if (ch == '2') {
				system("cls");
				active = 0;

				// EXIT
				exit = 1;
			}
			else {
				system("cls");
				// WRONG CHOICE
			}
		}


	}


	void HangCheck() {

		if (countHang == 0) {
			std::cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |                           \n"
				"\t\t    |                           \n"
				"\t\t    |                           \n"
				"\t\t ___|___                        \n\n\n";
		}
		else if (countHang == 1) {
			std::cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |                           \n"
				"\t\t    |                           \n"
				"\t\t ___|___                        \n\n\n";
		}
		else if (countHang == 2) {
			std::cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |      |                    \n"
				"\t\t    |                           \n"
				"\t\t ___|___                        \n\n\n";
		}
		else if (countHang == 3) {
			std::cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |      |\\                  \n"
				"\t\t    |                           \n"
				"\t\t ___|___                        \n\n\n";
		}
		else if (countHang == 4) {
			std::cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |     /|\\                  \n"
				"\t\t    |                           \n"
				"\t\t ___|___                        \n\n\n";
		}
		else if (countHang == 5) {
			std::cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |     /|\\                  \n"
				"\t\t    |     /                     \n"
				"\t\t ___|___                        \n\n\n";
		}
		else if (countHang == 6) {
			std::cout << "\t\t     ______                     \n"
				"\t\t    |      |                    \n"
				"\t\t    |      :                    \n"
				"\t\t    |      O                    \n"
				"\t\t    |     /|\\                  \n"
				"\t\t    |     / \\                  \n"
				"\t\t ___|___                        \n\n\n";
		}


	}


};


int hang() {

	// To make cout and cin faster by disabling stdio sync
	std::ios::sync_with_stdio(0);

	Hangman game;
	if (game.exit == 1) return 0;


	// To keep terminal window open
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
	return 0;
}
