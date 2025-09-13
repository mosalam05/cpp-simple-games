// Math Quiz Game in C++
// The player selects an operation, difficulty level, and number of questions.
// The program generates random math questions and evaluates user answers.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

enum class Operation { Addition = 1, Subtraction, Multiplication, Division, Random };

enum class Difficulty { Easy = 1, Medium, Hard };

/// Holds all details related to a single game session
struct GameDetails
{
  Operation operation;     // Chosen math operation
  Difficulty difficulty;   // Chosen difficulty level
  int totalQuestions;      // Number of questions in the game
  int correctAnswers = 0;  // Counter for correct answers
  int wrongAnswers = 0;    // Counter for wrong answers
  int minValue;            // Minimum value for operands
  int maxValue;            // Maximum value for operands

  // Set operands range based on difficulty
  void setLimits()
  {
    switch (difficulty)
    {
    case Difficulty::Easy:
      minValue = 1;
      maxValue = 10;
      break;
    case Difficulty::Medium:
      minValue = 10;
      maxValue = 50;
      break;
    case Difficulty::Hard:
      minValue = 50;
      maxValue = 100;
      break;
    }
  }
};

/// Represents a single math question
struct Question
{
  Operation currentOperation;
  double operand1;
  double operand2;
  double correctAnswer;
  char op;
};

/// Display the welcome screen
void printWelcomeScreen()
{
  cout << "\n===============================\n"
       << " WELCOME TO THE MATH TEST GAME "
       << "\n===============================\n";
}

/// Display available operations
void printOperationsScreen()
{
  cout << "\n\t  OPERATIONS  \t"
       << "\n-------------------------------\n"
       << "[1] Addition       (+)\n"
       << "[2] Subtraction    (-)\n"
       << "[3] Multiplication (*) \n"
       << "[4] Division       (/)\n"
       << "[5] Random      (+,-,*,/)\n"
       << "-------------------------------\n"
       << "Choose Operation: ";
}

/// Display difficulty options
void printDifficultyScreen()
{
  cout << "\n\tDIFFICULTY LEVEL\t"
       << "\n-------------------------------\n"
       << "[1] Easy   : ###-------\n"
       << "[2] Medium : ######----\n"
       << "[3] Hard   : ##########\n"
       << "-------------------------------\n"
       << "Choose Difficulty: ";
}

/// Ask user for number of questions
void printNumberOfQuestionsScreen()
{
  cout << "\nChoose Number of Questions: ";
}

/// Validate user integer input within a given range
int getValidInteger(int minValue = INT_MIN, int maxValue = INT_MAX)
{
  int input;
  while (!(cin >> input) || cin.peek() != '\n' || input < minValue || input > maxValue)
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid Input!\nPlease enter a number";
    if (input < minValue || input > maxValue)
      cout << " between " << minValue << " and " << maxValue;
    cout << ": ";
  }
  return input;
}

/// Validate user double input
double getValidDouble()
{
  double input;
  while (!(cin >> input) || cin.peek() != '\n')
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid Input!\nPlease enter a number: ";
  }
  return input;
}

/// Generate random integer between start and end
int getRandomNumber(int start = INT_MIN, int end = INT_MAX)
{
  if (start > end)
    swap(start, end);
  return (rand() % (end - start + 1) + start);
}

/// Generate a single question, ask user for answer, and update results
void generateQuestion(GameDetails &game)
{
  Question q;
  q.operand1 = getRandomNumber(game.minValue, game.maxValue);
  q.operand2 = getRandomNumber(game.minValue, game.maxValue);

  q.currentOperation = game.operation;
  if (game.operation == Operation::Random)
    q.currentOperation = (Operation) getRandomNumber(1, 4);

  switch (q.currentOperation)
  {
  case Operation::Addition:
    q.op = '+';
    q.correctAnswer = q.operand1 + q.operand2;
    break;
  case Operation::Subtraction:
    q.op = '-';
    q.correctAnswer = q.operand1 - q.operand2;
    break;
  case Operation::Multiplication:
    q.op = '*';
    q.correctAnswer = q.operand1 * q.operand2;
    break;
  case Operation::Division:
    q.op = '/';
    q.operand2 = (q.operand2 == 0.0 ? 1.0 : q.operand2); // Prevent division by zero by replacing 0 with 1
    q.correctAnswer = q.operand1 / q.operand2;
    break;
  }

  cout << q.operand1 << ' ' << q.op << ' ' << q.operand2 << " = ";
  double userAnswer = getValidDouble();

  if (q.correctAnswer == userAnswer)
  {
    cout << "Correct Answer! :)\n";
    game.correctAnswers++;
  }
  else
  {
    cout << "Incorrect Answer! :(\a\n"
         << "The correct answer is " << q.correctAnswer << '\n';
    game.wrongAnswers++;
  }
}

/// Prints all questions in sequence and evaluates user answers.
void printQuestions(GameDetails &game)
{
  for (int i = 1; i <= game.totalQuestions; i++)
  {
    cout << 'Q' << i << ") ";
    generateQuestion(game);
  }
}

/// Check if player passed (correct >= wrong)
bool hasPassed(const GameDetails &game)
{
  return (game.correctAnswers >= game.wrongAnswers);
}

/// Print the final game results
void printResults(const GameDetails &game)
{
  cout << "\n===============================\n"
       << "\t  Game Results  \t"
       << "\n===============================\n"
       << "Total Questions : " << game.totalQuestions << '\n'
       << "Correct Answers : " << game.correctAnswers << '\n'
       << "Wrong Answers   : " << game.wrongAnswers << '\n'
       << "Final Result    : " << (hasPassed(game) ? "Passed :)\n" : "Failed :(\n");
}

/// Main game Function: ask for settings, run quiz, and show results
void playGame()
{
  GameDetails game;
  printWelcomeScreen();

  printOperationsScreen();
  game.operation = (Operation)getValidInteger(1, 5);

  printDifficultyScreen();
  game.difficulty = (Difficulty)getValidInteger(1, 3);

  printNumberOfQuestionsScreen();
  game.totalQuestions = getValidInteger(1);

  game.setLimits();

  printQuestions(game);
  printResults(game);
}

/// Entry point of the program
int main()
{
  srand(time(NULL)); // Seed random number generator
  playGame();

  return 0;
}
