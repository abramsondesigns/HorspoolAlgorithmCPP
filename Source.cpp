#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;

map<char, int> GenerateShiftTable(const vector<char>& Pattern, const vector<char>& Alphabet)
{
	//init and declare necessary variables
	map<char, int> ShiftTable;	//create a dictionary ADT where he keys are chars and the shifts are integers
	
	for (unsigned int i = 0; i < Alphabet.size(); i++)	//init the ShiftTable with the maximum shift size
	{
		ShiftTable.insert({ Alphabet[i], Pattern.size() });
	}

	for (unsigned int j = 0; j < (Pattern.size() - 1); j++)	//tailor entries of the shift table to the correct size
	{
		ShiftTable[Pattern[j]] = Pattern.size() - 1 - j;
	}

	return ShiftTable;
}

vector<char> generateVectorFromString(const string& inputString)
{
	//init and declare necessary variables
	vector<char> Alphabet;

	//Convert string to Alphabet
	for (unsigned int i = 0; i < inputString.length(); i++)
	{
		Alphabet.push_back(inputString[i]);
	}

	return Alphabet;
}

int HorspoolMatching(const vector<char>& Pattern, const vector<char>& Alphabet, const string& FullString)
{
	//declare and init necessary variables
	map<char, int> ShiftTable;
	unsigned int Position = 0;
	unsigned int NumMatchedCharacters = 0;
	
	//Generate the ShiftTable
	ShiftTable = GenerateShiftTable(Pattern, Alphabet);

	//position the pattern's right end
	Position = Pattern.size() - 1;

	//search for the pattern in the string
	while (Position <= FullString.length() - 1)
	{
		NumMatchedCharacters = 0;	//reset matched for new iteration

		//search for matching characters
		while (NumMatchedCharacters <= Pattern.size() - 1 && Pattern[Pattern.size() - 1 - NumMatchedCharacters] == FullString[Position - NumMatchedCharacters])
		{
			NumMatchedCharacters++;	//found a new matched character
		}

		//if we found all of the characters
		if (NumMatchedCharacters == Pattern.size())
		{
			return Position - Pattern.size() + 1;	//return the index of the last character
		}
		else //otherwise keep searching
		{
			Position = Position + ShiftTable[FullString[Position]];	//find the character in the ShiftTable and move the position
		}
	}

	return -1;	//failed to find the full pattern in the string
}

int HorspoolMatchingWithStatistics(const vector<char>& Pattern, const vector<char>& Alphabet, const string& FullString)
{
	//declare and init necessary variables
	map<char, int> ShiftTable;
	unsigned int Position = 0;
	unsigned int NumMatchedCharacters = 0;
	unsigned int counter = 0;

	//Generate the ShiftTable
	ShiftTable = GenerateShiftTable(Pattern, Alphabet);

	//position the pattern's right end
	Position = Pattern.size() - 1;

	//search for the pattern in the string
	while (Position <= FullString.length() - 1)
	{
		NumMatchedCharacters = 0;	//reset matched for new iteration

		//search for matching characters
		counter++;
		while (NumMatchedCharacters <= Pattern.size() - 1 && Pattern[Pattern.size() - 1 - NumMatchedCharacters] == FullString[Position - NumMatchedCharacters])
		{
			NumMatchedCharacters++;	//found a new matched character

			counter++;
		}

		//if we found all of the characters
		if (NumMatchedCharacters == Pattern.size())
		{
			cout << "The Algorithm compared " << counter << " characters" << endl << endl;
			return Position - Pattern.size() + 1;	//return the index of the last character
		}
		else //otherwise keep searching
		{
			Position = Position + ShiftTable[FullString[Position]];	//find the character in the ShiftTable and move the position
		}
	}

	cout << "The Algorithm compared " << counter << " characters" << endl << endl;
	return -1;	//failed to find the full pattern in the string
}


int main()
{
	//declare and init necessary variables
	vector<char> Pattern;
	vector <char> Alphabet;
	map<char, int> ShiftTable;
	int PatternPosition = 0;
	string AlphabetString = "";
	string PatternString = "";
	string FullString = "";

	//Generate the Alphabet
	AlphabetString = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 123456789!@#$%^&*()_+{}|[]:,.<>?`~";
	Alphabet = generateVectorFromString(AlphabetString);

	//generate from string?

	//Make the Pattern
	PatternString = "Bug";		//sim pass
	//PatternString = "Bed";	//sim fail
	Pattern = generateVectorFromString(PatternString);


	//Create the string to search
	FullString = "Snug as a Bug in a Rug";


	//Find the pattern in the string using Horspool's
	PatternPosition = HorspoolMatching(Pattern, Alphabet, FullString);


	if (PatternPosition != -1)
	{
		cout << "The string (" << FullString << ") contains the Pattern (" << PatternString << ") starting at index: " << PatternPosition << endl;
	}
	else
	{
		cout << "The string (" << FullString << ") does not contain the Pattern (" << PatternString << ")" << endl;
	}


	return 0;
}