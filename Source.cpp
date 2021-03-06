#include <iostream>
#include <string>
using namespace std;
class Parser
{
public:
	string magazine = "";
	string input;
	string output = "";
	void push()
	{
		magazine += input[0];     // функція(*), яка посуває вхідну головку на один символ вправо
		input.erase(0, 1);
	}
	void L0()                    //L0:         (|#  → (#|            *   L0
	{
		if (magazine[magazine.length() - 1] == '(')
		{
			push();
			L0();
			return;
		}
		else L1();
	}
	void L1()                    //L1:        a |#  → F#|  видача 6  * 
	{
		if (magazine[magazine.length() - 1] == 'a')
		{
			magazine[magazine.length() - 1] = 'F';
			push();
			output += "6";
		}
		L2();
	}
	void L2()                    //L2:     T * F #|  → T# |  видача 3      L4
	{
		if (magazine.length() >= 4) {
			if (magazine[magazine.length() - 4] == 'T' && magazine[magazine.length() - 3] == '*' && magazine[magazine.length() - 2] == 'F')
			{
				magazine[magazine.length() - 4] = 'T';
				magazine[magazine.length() - 3] = magazine[magazine.length() - 1];
				magazine.erase(magazine.length() - 2, 2);
				output += "3";
				L4();
			}
		}
		L3();
	}
	void L3()                    //L3:            F#|    → T# |  видача 4
	{	
		if (magazine.length() >= 2) {
			if (magazine[magazine.length() - 2] == 'F')
			{
				magazine[magazine.length() - 2] = 'T';
				output += "4";
			}
		}
		L4();
	}
	void L4()                    //L4:            T*|# → T*#|                   *  L0
	{
		if (magazine.length() >= 2) {
			if (magazine[magazine.length() - 1] == '*' && magazine[magazine.length() - 2] == 'T')
			{
				push();
				L0();
			}
		}
		L5();
	}
	void L5()                    //L5:       E+T#|    → E# |   видача 1     L7
	{
		if (magazine.length() >= 4) {
			if (magazine[magazine.length() - 4] == 'E' && magazine[magazine.length() - 3] == '+' && magazine[magazine.length() - 2] == 'T')
			{
				magazine[magazine.length() - 4] = 'E';
				magazine[magazine.length() - 3] = magazine[magazine.length() - 1];
				magazine.erase(magazine.length() - 2, 2);
				output += "1";
				L7();
			}
		}
		L6();
	}
	void L6()                    //L6:            T#|    → E# |   видача 2
	{
		if (magazine.length() >= 2) {
			if (magazine[magazine.length() - 2] == 'T')
			{
				magazine[magazine.length() - 2] = 'E';
				output += "2";
			}
		}
		L7();
	}
	void L7()                    //L7:          E +|#→ E+# |                   *  L0
	{
		if (magazine.length() >= 2) {
			if (magazine[magazine.length() - 1] == '+' && magazine[magazine.length() - 2] == 'E')
			{
				push();
				L0();
			}
		}
		L8();
	}
	void L8()                    //L8:           (E)|#  → F# |   видача 5  *  L2
	{
		if (magazine.length() >= 3) 
		{if (magazine[magazine.length() - 3] == '(' && magazine[magazine.length() - 2] == 'E' && magazine[magazine.length() - 1] == ')')
			{
				magazine[magazine.length() - 3] = 'F';
				magazine.erase(magazine.length() - 2, 2);
				push();
				output += "5";
				L2();
			}
		}
		L9();
	}
	void L9()                    //L9:         $E$ |    →      |    допуск
	{
		if (magazine[0] == 'E'&& input=="")
			return;
		else L10();
	}
	void L10()                    //L10:          $  |     →     |   помилка
	{
		if (magazine[0] != 'E'&& input == "")
			cout << "Error, the string does not belong to the specified grammar!"<<endl;
		else L11();
	}
	void L11()                    //L11:              |#   → #  |                    *  L0
	{
		push();
		L0();
	}
};
void main()
{
	Parser a;
	cout << "Enter string: ";  
	cin >> a.input;
	a.L11();                    //початковий оператор
	cout << "Right parse: " << a.output << endl; 
	system("pause");
}