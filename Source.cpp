/* Aaron Ciminelli 
CS-210-T2586 Programming Languages 21EW2
Bary Pollack Ph.D.
12/12/2021*/

#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
/* Aaron Ciminelli
CS-210-T2586 Programming Languages 21EW2
Bary Pollack Ph.D.
12/12/2021 */


int choice;
string str;
string fileLine;

void UserMenu() {
	cout << "***********************************************************  DISPLAY MENU **********************************************" << endl; // Creating menu 
	cout << "1. Produce a list of all items purchased in a given day along with the number of times each item was purchased." << endl; 
	cout << "2. Produce a number representing how many times a specific item was purchased in a given day." << endl; 
	cout << "3. Produce a text-based histogram listing all items purchased in a given day, along with a representation of the number of times each item was purchased." << endl; 
	cout << "4. Exit Program." << endl; 
	cout << "Please Enter your selection as 1, 2, 3, or 4." << endl; 
	cout << "************************************************************************************************************************" << endl; 

	cin >> choice; // first choice 
	if (choice == 1) {
		cout << "Creating List of Items and Quantities Sold Today: " << endl; // prints statment 
		CallProcedure("Items"); // calling on python code 
		cout << " " << endl;
		return; 
	}

	else if (choice == 2) { // second choice 
		cout << "Please Enter Specific Item Name: " << endl;
		cin >> str;
		cout << " " << endl;
		cout << "Creating List For The Sales For " << str << ": " << endl; // prints stetment and spesific item user entered 
		cout << str << ": " << callIntFunc("SpecificItem", str) << " " << endl; // calling on pythond code 
		return;
	}


	else if (choice == 3) { // third choice
		cout << "Creating text-based Histogram of all Items purchased today: " << endl; 
		CallProcedure("Histogram"); // calling on pythond code 
		cout << " " << endl; 
		ifstream frequencyFile("frequency.dat"); // counts all items and their frequency and creates a list without repeating the same item 
		string item; 
		int count; 
		while (getline(frequencyFile, fileLine)) {
			istringstream iss(fileLine); 
			if (!(iss >> item >> count)) { break;  }
			cout << item << " " << string(count, '|') << endl; // representation of number of items purchased
		}
		cout << " " << endl; 
		return; 
	}
	else if (choice == 4) { // fourth choice 
		cout << "Exiting Program............. " << endl; // ends the menu loop 
		exit(EXIT_SUCCESS); 

	}
	else { // if anything other that 1, 2, 3, or 4 is entered prints statement 
		cout << "Please Enter a Valid Input : 1, 2, 3, or 4 " << endl; 
		return; 

	}
}
int main() { // keeps menu looping indefinitely unless choice 4 is entered 
	while (1) {
		UserMenu(); 
	}
	return 0;
}


/* void main()   commenting out unnecessary code 
{
	CallProcedure("printsomething");
	cout << callIntFunc("PrintMe", "House") << endl;
	cout << callIntFunc("SquareValue", 2);

}*/

/* Aaron Ciminelli
CS-210-T2586 Programming Languages 21EW2
Bary Pollack Ph.D.
12/12/2021 */