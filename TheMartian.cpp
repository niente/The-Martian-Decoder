#define _CRT_SECURE_NO_DEPRECATE // for use of _itoa
#ifdef _MSC_VER
#include <crtdbg.h> // check for memory leak
#endif
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Camera angle conversion: 360 / 16 = 22.5
#define HEX_DEGREES 22.5

///    class FileParser
// Opens a file, parses each line for numbers and stores them in an INT vector.
class FileParser
{
private:
	ifstream inFile;
	vector<int> degreeValues;
	string line, num;
public:
	const vector<int>& getDegreeValues() { return degreeValues; }
	bool openFile(string filename);
	void parseLine();
	
};

///     FileParser::openFile
// Opens the file with given input filename
bool FileParser::openFile(string filename)
{
	cout << "Opening input file: " << filename << "\n\n";
	inFile.open(filename);
	if (!inFile)
	{
		cout << "Unable to open " << filename << "!\n\n";
		return false;
	}
	return true;
}

///     FileParser::parseLine()
// Reads 1 line, checks each char to see if it's a digit. 
// If so, stores the digit in string "num". Once non-digit char
// is encountered, stores num in output vector as an int.
void FileParser::parseLine()
{
	while (getline(inFile, line))
	{
		num = "";
		for (auto i = line.begin(); i != line.end(); ++i)
		{
			if (isdigit(*i))
				num += *i;
			else if (num != "")
			{
				degreeValues.push_back(stoi(num));
				num = "";
			}
		}
	}
}

///    class ConvertDegHex
// Using an int vector as input, converts each pair of ints into hex values
// and stores them in a new vector.
class ConvertDegHex
{
private:
	char *hexChar = new char[2];
	vector<char*> hexCharVector;
	int intHold;
public:
	const vector<char*>& getHexCharVector() { return hexCharVector; }
	void buildHexCharVector(vector<int>& degreeValues);
	void degToHexStr(int i, vector<int>& degreeValues);
	~ConvertDegHex();
};

///     ConvertDegHex::buildHexCharVector
// For each pair of ints, convert to hex value using HEX_DEGREES (360 / 16)
// store in hexCharVector.
void ConvertDegHex::buildHexCharVector(vector<int>& degreeValues)
{
	int i = 0;
	if (degreeValues.size() % 2)
		degreeValues.pop_back(); // if we have ODD number elements, delete last element
	for (i = 0; i < degreeValues.size(); i += 2)
	{
		char *hexByte = new char[3];
		degToHexStr(i, degreeValues); // convert 1st number of degree pair
		strcpy(hexByte, hexChar); // write 1st char
		degToHexStr(i + 1, degreeValues); // convert 2nd
		strcat(hexByte, hexChar); // write 2nd char
		hexCharVector.push_back(hexByte); // insert to vector
	}
}

void ConvertDegHex::degToHexStr(int i, vector<int>& degreeValues)
{
	intHold = degreeValues[i] / HEX_DEGREES;
	_itoa(intHold, hexChar, 16);
}

///    ConvertDegHex::~ConvertDegHex()
// Release dynamically allocated memory
ConvertDegHex::~ConvertDegHex()
{
	delete[] hexChar;
	for (int i = 0; i < hexCharVector.size(); ++i)
		delete hexCharVector[i];
	hexCharVector.clear();
}

///   class ConvertHexAscii
// Using a char* vector as input, converts each hex value into ascii,
// stores in asciiCharVector.
class ConvertHexAscii
{
private:
	vector<char> asciiCharVector;
	char tempChar;
public:
	const vector<char>& getAsciiCharVector() { return asciiCharVector; }
	void buildAsciiCharVector(vector<char*>& hexCharVector);
};

///    ConvertHexAscii:buildAsciiCharVector
// Using a char* vector as input, convert from hex to ascii values.
void ConvertHexAscii::buildAsciiCharVector(vector<char*>& hexCharVector)
{
	for (int i = 0; i < hexCharVector.size(); i++)
	{
		tempChar = strtol(hexCharVector[i], NULL, 16);
		asciiCharVector.push_back(tempChar);
	}
}

///    printVector
// Template which prints contents of a vector of any type.
template <typename T>
void printVector(const T& inputVector)
{
	for (auto i = inputVector.begin(); i != inputVector.end(); ++i)
		cout << *i;
}

int main()
{
	// Use of { } here keeps _CrtDumpMemoryLeaks() call out of scope of vectors.
	{
		string filename = "AsciiDegrees.csv";
		FileParser datafile;
		datafile.openFile(filename);
		datafile.parseLine();
		vector<int> degreeValues = datafile.getDegreeValues();

		ConvertDegHex convertHex;
		convertHex.buildHexCharVector(degreeValues);
		vector<char*> hexCharValues = convertHex.getHexCharVector();

		ConvertHexAscii convertAscii;
		convertAscii.buildAsciiCharVector(hexCharValues);
		vector<char> asciiCharVector = convertAscii.getAsciiCharVector();

		printVector(asciiCharVector);
	}

	// check for memory leak
#ifdef _MSC_VER
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	cout << (_CrtDumpMemoryLeaks() ? "\nMemory Leak\n" : "\nNo Memory Leak\n");
	system("pause");
#endif

	return 0;
}
