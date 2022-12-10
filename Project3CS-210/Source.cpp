#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>
#include "Validator.h"

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
	PyObject* my_module = PyImport_ImportModule("python_modules.python_code");
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
	pName = PyUnicode_FromString((char*)"python_modules.python_code");
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
	pName = PyUnicode_FromString((char*)"python_modules.python_code");
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

//Handles if user input is within valid range.
//@param Validator validator - User input value that is not within valid range.

void handleInvalidInput(Validator validator) {

	cout << "Entered value is not valid, valid range is [";
	cout << validator.getMinValue() << " - " << validator.getMaxValue() << "]" << endl;
	cout << "Enter Selection:" << endl;
}

// Displays main menu.
// Asks for user input for menu selection.

void displayMainMenu() {

	cout << endl;
	cout << "Main Menu" << endl;
	cout << "1 - Display Total Inventory" << endl;
	cout << "2 - Purchase Quantity" << endl;
	cout << "3 - Items Purchased Histogram" << endl;
	cout << "4 - Exit Program" << endl;
	cout << endl;
	cout << "Enter Selection:" << endl;
}

// Displays total inventory.
// Calls to 'determineInventory()' method in python code.

void displayInventory() {

	cout << "TOTAL INVENTORY" << endl;
	CallProcedure("determineInventory");
}

// Displays purchase quantity.
// Calls to 'determineFrequency()' method in python code.
// In this case, we are determining how often 'Peas" was purchased.

void displayPurchaseQuanity() {

	cout << endl;
	cout << "Peas occur " << callIntFunc("determineFrequency", "Peas") << endl;
}

// Displays histogram of how often an item was purchased.
// Calls to 'output()' method in python code, which creates 'frequency.dat' file.
// displayHistogram() uses that file to iterate a * character to represent how many items were sold.

void displayHistogram() {

	ifstream inFS;
	string inventoryName;
	int inventoryQty;

	// calls output() from python code
	CallProcedure("output");
	
	//opens file 
	inFS.open("frequency.dat");

	// Will alert us if file does not open.
	if (!inFS.is_open()) {
		cout << "Couldn't open file." << endl;
	}

	// gets first string and integer from file
	inFS >> inventoryName;
	inFS >> inventoryQty;

	// loop that outputs inventoryName with * character for each iteration of inventoryQty
	while (!inFS.fail()) {
		cout << inventoryName << ": ";
		for (unsigned int i = 0; i < inventoryQty; ++i) {
			cout << "*";
		}
		// gets next inventoryName and inventoryQty to loop through
		cout << endl;
		inFS >> inventoryName;
		inFS >> inventoryQty;
	}
	// closes file
	inFS.close();
}


int main()
{
	//Constants for menu choices
	const int ITEMS_PURCHASED_LIST_MENU_CHOICE = 1;
	const int PURCHASE_QUANTITY_MENU_CHOICE = 2;
	const int ITEMS_PURCHASED_HISTOGRAM_MENU_CHOICE = 3;
	const int EXIT_PROGRAM_MENU_CHOICE = 4;

	int userMenuChoice = -1;

	Validator menuChoiceValidator(ITEMS_PURCHASED_LIST_MENU_CHOICE, EXIT_PROGRAM_MENU_CHOICE);  // validates user input

	// while loop for main menu
	while (userMenuChoice != EXIT_PROGRAM_MENU_CHOICE)
	{

		displayMainMenu();  // displays main menu

		cin >> userMenuChoice;  // get user input

		// Handles input validator user method
		while (!menuChoiceValidator.isValid(userMenuChoice)) {  // while loop that checks if userMenuChoice is within valid range.
			handleInvalidInput(menuChoiceValidator);   // Throws bad input.
			cout << endl;
			cout << "Enter Selection" << endl;   // asks for new input
			cin >> userMenuChoice;
		}

		if (userMenuChoice == ITEMS_PURCHASED_LIST_MENU_CHOICE)
		{
			displayInventory();
		}
		else if (userMenuChoice == PURCHASE_QUANTITY_MENU_CHOICE)
		{
			displayPurchaseQuanity();
		}
		else if (userMenuChoice == ITEMS_PURCHASED_HISTOGRAM_MENU_CHOICE)
		{
			 displayHistogram();
		}
	}
	return 0;
}