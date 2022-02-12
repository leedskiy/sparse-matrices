#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

struct RozrArray {
	int value;
	int col;
	int row;

	RozrArray(int value, int row, int col) {
		this->value = value;
		this->row = row;
		this->col = col;
	}
};

void SetColor(int ForgC);
int Intro(vector<RozrArray> vector1, vector<RozrArray> vector2, vector<RozrArray> multivector, vector<RozrArray> sumvector);
int Decision(int action, vector<RozrArray> vector1, vector<RozrArray> vector2, vector<RozrArray> multivector, vector<RozrArray> sumvector);
int Next(int action, vector<RozrArray> vector1, vector<RozrArray> vector2, vector<RozrArray> multivector, vector<RozrArray> sumvector);
int MultiArray(vector<RozrArray> vector1, vector<RozrArray> vector2, vector<RozrArray> multivector);
int SumArray(vector<RozrArray> vector1, vector<RozrArray> vector2, vector<RozrArray> sumvector);

int main() {

	SetColor(17);

	vector<RozrArray> vector1;
	vector<RozrArray> vector2;
	vector<RozrArray> multivector;
	vector<RozrArray> sumvector;

	vector1.push_back(RozrArray(7, 4, 5));
	vector1.push_back(RozrArray(5, 15, 100));

	vector2.push_back(RozrArray(22, 2, 2));
	vector2.push_back(RozrArray(2, 4, 5));
	vector2.push_back(RozrArray(10, 15, 100));

	Intro(vector1, vector2, multivector, sumvector);

	return 0;
}

void SetColor(int ForgC){
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

int Intro(vector<RozrArray> vector1, vector<RozrArray> vector2,vector<RozrArray> multivector, vector<RozrArray> sumvector) {
	int action = 0;

	cout << "Summary and multiplication of sparse matrices.";
	Sleep(3000);
	system("cls");
	
	cout << "Here are two matrices.";
	Sleep(3000);
	system("cls");

	cout << "Elements of first: " << endl << endl;

	int iterator = 0;
	while (vector1.size() > iterator) {
		cout << "Element " << iterator << " row " << vector1.at(iterator).row << endl;
		cout << "Element " << iterator << " col " << vector1.at(iterator).col << endl;
		cout << "Element " << iterator << " value " << vector1.at(iterator).value << endl;
		cout << endl;
		iterator = iterator + 1;
	}

	cout << endl << "-----------------------------------------------------------------" << endl << endl << endl;

	cout << "Elements of second: " << endl << endl;

	iterator = 0;
	while (vector2.size() > iterator) {
		cout << "Element " << iterator << " row " << vector2.at(iterator).row << endl;
		cout << "Element " << iterator << " col " << vector2.at(iterator).col << endl;
		cout << "Element " << iterator << " value " << vector2.at(iterator).value << endl;
		cout << endl;
		iterator = iterator + 1;
	}

	Sleep(3000);

	cout << endl << "-----------------------------------------------------------------" << endl << endl;

	cout << endl << "Actions that you can do: " << endl << endl;
	cout << "0 - exit" << endl;
	cout << "1 - multiply" << endl;
	cout << "2 - add" << endl;

	Sleep(3000);

	cout << endl << "Your decision - ";
	cin >> action;

	Sleep(2000);

	system("cls");

	Decision(action, vector1, vector2, multivector, sumvector);
	Next(action, vector1, vector2, multivector, sumvector);

	return 0;
}

int Decision(int action, vector<RozrArray> vector1, vector<RozrArray> vector2, vector<RozrArray> multivector, vector<RozrArray> sumvector) {
	if (action == 0) {
		cout << "Thank you for using!" << endl;

		Sleep(2000);

		cout << "Have a nice day.";

		Sleep(2000);

		system("cls");

		return 0;
	}
	else if(action == 1) {
		MultiArray(vector1, vector2, multivector);
	}
	else if(action == 2) {
		SumArray(vector1, vector2, sumvector);
	}
	else {
		Sleep(2000);

		cout << "Wait...";

		Sleep(1000);
		system("cls");

		cout << "Wrong number. Please choose from list next time.";

		Sleep(3000);
		system("cls");

		Next(action, vector1, vector2, multivector, sumvector);
	}

	return 0;
}

int Next(int action, vector<RozrArray> vector1, vector<RozrArray> vector2, vector<RozrArray> multivector, vector<RozrArray> sumvector) {

	Sleep(3000);
	cout << endl << "-----------------------------------------------------------------" << endl << endl << endl;
	cout << "Something else?" << endl;

	cout << endl << "Action that you can do: " << endl << endl;
	cout << "0 - exit" << endl;
	cout << "1 - multiply" << endl;
	cout << "2 - add" << endl;

	Sleep(3000);

	cout << endl << "Your decision - ";
	cin >> action;

	Sleep(2000);

	system("cls");

	Decision(action, vector1, vector2, multivector, sumvector);

	if (action != 0) {
		Next(action, vector1, vector2, multivector, sumvector);
	}

	return 0;
}

int MultiArray(vector<RozrArray> vector1, vector<RozrArray> vector2, vector<RozrArray> multivector) {

	int iteratorRowsVec1 = 0;
	int iteratorColsVec1 = 0;
	int iteratorRowsVec2 = 0;
	int iteratorColsVec2 = 0;
	int multi = 0;

	while (vector1.size() > iteratorRowsVec1 && vector2.size() > iteratorRowsVec2) {
		if (vector1.at(iteratorRowsVec1).row == vector2.at(iteratorRowsVec2).row) {
			while (vector1.size() > iteratorColsVec1 && vector2.size() > iteratorColsVec2) {
				if (vector1.at(iteratorColsVec1).col == vector2.at(iteratorColsVec2).col) {
					multi = vector1.at(iteratorColsVec1).value * vector2.at(iteratorColsVec2).value;
					multivector.push_back(RozrArray(multi, vector2.at(iteratorRowsVec2).row, vector1.at(iteratorColsVec1).col));
					multi = 0;

					iteratorColsVec1 = iteratorColsVec1 + 1;
					iteratorColsVec2 = iteratorColsVec2 + 1;
					iteratorRowsVec1 = iteratorRowsVec1 + 1;
					iteratorRowsVec2 = iteratorRowsVec2 + 1;
				}
				else if (vector1.at(iteratorColsVec1).col > vector2.at(iteratorColsVec2).col) {
					iteratorColsVec2 = iteratorColsVec2 + 1;

					if (vector1.at(iteratorRowsVec1).row > vector2.at(iteratorRowsVec2).row) {
						iteratorRowsVec2 = iteratorRowsVec2 + 1;
					}
					else if (vector1.at(iteratorRowsVec1).row < vector2.at(iteratorRowsVec2).row) {
						iteratorRowsVec1 = iteratorRowsVec1 + 1;
					}
				}
				else if (vector1.at(iteratorColsVec1).col < vector2.at(iteratorColsVec2).col) {
					iteratorColsVec1 = iteratorColsVec1 + 1;

					if (vector1.at(iteratorRowsVec1).row > vector2.at(iteratorRowsVec2).row) {
						iteratorRowsVec2 = iteratorRowsVec2 + 1;
					}
					else if (vector1.at(iteratorRowsVec1).row < vector2.at(iteratorRowsVec2).row) {
						iteratorRowsVec1 = iteratorRowsVec1 + 1;
					}
				}
			}
		}
		else if (vector1.at(iteratorRowsVec1).row > vector2.at(iteratorRowsVec2).row) {
			iteratorRowsVec2 = iteratorRowsVec2 + 1;
			iteratorColsVec1 = 0;
			iteratorColsVec2 = iteratorColsVec2 + 1;
		}
		else if (vector1.at(iteratorRowsVec1).row < vector2.at(iteratorRowsVec2).row) {
			iteratorRowsVec1 = iteratorRowsVec1 + 1;
			iteratorColsVec1 = iteratorColsVec1 + 1;
			iteratorColsVec2 = 0;
		}
	}

	cout << "Matrix whose elements are multpilication of two: " << endl << endl;

	int iteratorMV = 0;
	while (multivector.size() > iteratorMV) {
		cout << "Element " << iteratorMV << " row: " << multivector.at(iteratorMV).row << endl;
		cout << "Element " << iteratorMV << " col: " << multivector.at(iteratorMV).col << endl;
		cout << "Element " << iteratorMV << " value: " << multivector.at(iteratorMV).value << endl;
		cout << endl;
		iteratorMV = iteratorMV + 1;
	}

	return 0;
}


int SumArray(vector<RozrArray> vector1, vector<RozrArray> vector2, vector<RozrArray> sumvector) {

	int iteratorRowsVec1 = 0;
	int iteratorColsVec1 = 0;
	int iteratorRowsVec2 = 0;
	int iteratorColsVec2 = 0;
	int sum = 0;

	while (vector1.size() > iteratorRowsVec1 && vector2.size() > iteratorRowsVec2) {
		if (vector1.at(iteratorRowsVec1).row == vector2.at(iteratorRowsVec2).row) {
			while (vector1.size() > iteratorColsVec1 && vector2.size() > iteratorColsVec2) {
				if (vector1.at(iteratorColsVec1).col == vector2.at(iteratorColsVec2).col) {
					sum = vector1.at(iteratorColsVec1).value + vector2.at(iteratorColsVec2).value;
					sumvector.push_back(RozrArray(sum, vector2.at(iteratorRowsVec2).row, vector1.at(iteratorColsVec1).col));
					sum = 0;

					iteratorColsVec1 = iteratorColsVec1 + 1;
					iteratorColsVec2 = iteratorColsVec2 + 1;
					iteratorRowsVec1 = iteratorRowsVec1 + 1;
					iteratorRowsVec2 = iteratorRowsVec2 + 1;
				}
				else if (vector1.at(iteratorColsVec1).col > vector2.at(iteratorColsVec2).col) {
					iteratorColsVec2 = iteratorColsVec2 + 1;

					if (vector1.at(iteratorRowsVec1).row > vector2.at(iteratorRowsVec2).row) {
						iteratorRowsVec2 = iteratorRowsVec2 + 1;
					}
					else if (vector1.at(iteratorRowsVec1).row < vector2.at(iteratorRowsVec2).row) {
						iteratorRowsVec1 = iteratorRowsVec1 + 1;
					}
				}
				else if (vector1.at(iteratorColsVec1).col < vector2.at(iteratorColsVec2).col) {
					iteratorColsVec1 = iteratorColsVec1 + 1;

					if (vector1.at(iteratorRowsVec1).row > vector2.at(iteratorRowsVec2).row) {
						iteratorRowsVec2 = iteratorRowsVec2 + 1;
					}
					else if (vector1.at(iteratorRowsVec1).row < vector2.at(iteratorRowsVec2).row) {
						iteratorRowsVec1 = iteratorRowsVec1 + 1;
					}
				}
			}
		}
		else if (vector1.at(iteratorRowsVec1).row > vector2.at(iteratorRowsVec2).row) {
			iteratorRowsVec2 = iteratorRowsVec2 + 1;
			iteratorColsVec1 = 0;
			iteratorColsVec2 = iteratorColsVec2 + 1;
		}
		else if (vector1.at(iteratorRowsVec1).row < vector2.at(iteratorRowsVec2).row) {
			iteratorRowsVec1 = iteratorRowsVec1 + 1;
			iteratorColsVec1 = iteratorColsVec1 + 1;
			iteratorColsVec2 = 0;
		}
	}

	cout << "Matrix whose elements are sum of two: " << endl << endl;

	int iteratorSV = 0;
	while (sumvector.size() > iteratorSV) {
		cout << "Element " << iteratorSV << " row: " << sumvector.at(iteratorSV).row << endl;
		cout << "Element " << iteratorSV << " col: " << sumvector.at(iteratorSV).col << endl;
		cout << "Element " << iteratorSV << " value: " << sumvector.at(iteratorSV).value << endl;
		cout << endl;
		iteratorSV = iteratorSV + 1;
	}

	return 0;
}
