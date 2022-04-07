#include <iostream>
#include <conio.h>

using namespace std;

struct Tree
{
	int number = 0;
	string FIO;
	Tree* left = NULL, * right = NULL;
};

struct Arr
{
	int number = 0;
	string FIO;
};

int correctInputInt();
void addData(Tree*& root);
Tree* createLeaf(int number, string FIO);
string checkInputString();
bool isAddLeaf(Tree*& root, int number, string FIO);
void deleteLeafSimple(Tree*& root, Tree*& del_element, Tree*& prev_del);
void deleteLeaf(Tree*& root);
void deleteLeafOneConnection(Tree*& root, Tree*& del_element, Tree*& prev_del);
void deleteLeafTwoConnections(Tree*& root, Tree*& del_element, Tree*& prev_del);
void balanceTree(Tree*& root);
void countElements(Tree* temp, int& number_of_elements);
void addElementsToArray(Tree* temp, Arr* arr, int& count);
void sortElements(Arr* arr, int number_of_elements);
void makeBalance(Tree*& root, Arr* arr, int n, int number_of_elements);
void findLeaf(Tree* root);
void countSymbols(Tree*& temp, int& count);
void deleteTree(Tree*& temp);
void viewTree(Tree* temp, int level);
bool isTreeExist(Tree* root);

int main()
{
	Tree* root = NULL;
	int code, count;
	while (true)
	{
		if (isTreeExist(root))
		{
			do
			{
				cout << "\n Enter input data - 1\n Balance Tree - 2\n Search leaf - 3\n Delete leaf - 4\n View tree - 5\n Individual task - 6\n Delete tree - 7\n EXIT - 0\n";
				code = correctInputInt();
			} while (code < 0 || code > 7);
		}
		else
		{
			do
			{
				cout << "\n Enter input data - 1\n EXIT - 0\n";
				code = correctInputInt();
			} while (code < 0 || code > 1);
		}
		switch (code)
		{
		case 1:
			addData(root);
			break;
		case 2:
			balanceTree(root);
			break;
		case 3:
			findLeaf(root);
			break;
		case 4:
			deleteLeaf(root);
			break;
		case 5:
			viewTree(root, 0);
			break;
		case 6:
			count = 0;
			countSymbols(root, count);
			cout << "Number of symbols in all strings: " << count << endl;
			break;
		case 7:
			deleteTree(root);
			cout << "Tree deleted successfully!" << endl;
			break;
		case 0:
			cout << "Safe exit..." << endl;
			if (root)
			{
				deleteTree(root);
				cout << "Tree deleted successfully!" << endl;
			}
			system("pause");
			return 0;
		}
	}
}

bool isTreeExist(Tree* root)
{
	if (root)
	{
		return true;
	}
	else
	{
		cout << "Tree doesn't exist!" << endl;
		return false;
	}
}

void viewTree(Tree* temp, int level)
{
	if (temp)
	{
		viewTree(temp->right, level + 1);
		for (int i = 0; i < level; i++)
		{
			cout << "    ";
		}
		cout << temp->number << endl;
		viewTree(temp->left, level + 1);
	}
}

void deleteTree(Tree*& temp)
{
	if (temp)
	{
		deleteTree(temp->right);
		deleteTree(temp->left);
		delete temp;
	}
	temp = NULL;
}

void countSymbols(Tree*& temp, int& count)
{
	if (temp)
	{
		countSymbols(temp->right, count);
		count += temp->FIO.size();
		countSymbols(temp->left, count);
	}
}

void findLeaf(Tree* root)
{
	int number;
	Tree* element;
	cout << "Enter number:" << endl;
	number = correctInputInt();
	element = root;
	while (element && element->number != number)
	{
		if (number > element->number)
		{
			element = element->right;
		}
		else
		{
			element = element->left;
		}
	}
	if (element == NULL)
	{
		cout << "There's no such number!" << endl;
		return;
	}
	cout << "Number: " << number << "\nFIO: " << element->FIO << endl;
}

void balanceTree(Tree*& root)
{
	int number_of_elements = 0;
	int elements = 0;
	countElements(root, number_of_elements);
	Arr* arr = new Arr[number_of_elements];
	addElementsToArray(root, arr, elements);
	sortElements(arr, number_of_elements);
	makeBalance(root, arr, 0, number_of_elements);
	delete[]arr;
	cout << "Tree balanced successfully!" << endl;
}

void makeBalance(Tree*& root, Arr* arr, int n, int number_of_elements)
{
	if (n == number_of_elements)
	{
		return;
	}
	else
	{
		int med = (n + number_of_elements) / 2;
		root = new Tree;
		root->number = arr[med].number;
		root->FIO = arr[med].FIO;
		makeBalance(root->left, arr, n, med);
		makeBalance(root->right, arr, med + 1, number_of_elements);
	}
}

void sortElements(Arr* arr, int number_of_elements)
{
	int temp_number;
	string temp_string;
	for (int i = 0; i < number_of_elements - 1; i++)
	{
		for (int j = 0; j < number_of_elements - 1; j++)
		{
			if (arr[j + 1].number < arr[j].number)
			{
				temp_number = arr[j + 1].number;
				temp_string = arr[j + 1].FIO;
				arr[j + 1].number = arr[j].number;
				arr[j + 1].FIO = arr[j].FIO;
				arr[j].number = temp_number;
				arr[j].FIO = temp_string;
			}
		}
	}
}

void addElementsToArray(Tree* temp, Arr* arr, int& count)
{
	if (temp)
	{
		addElementsToArray(temp->right, arr, count);
		arr[count].number = temp->number;
		arr[count].FIO = temp->FIO;
		count++;
		addElementsToArray(temp->left, arr, count);
	}
}

void countElements(Tree* temp, int& number_of_elements)
{
	if (temp)
	{
		countElements(temp->right, number_of_elements);
		number_of_elements++;
		countElements(temp->left, number_of_elements);
	}
}

void deleteLeaf(Tree*& root)
{
	int number;
	Tree* del_element, * prev_del;
	cout << "Enter number:" << endl;
	number = correctInputInt();
	del_element = root;
	prev_del = NULL;
	while (del_element && del_element->number != number)
	{
		prev_del = del_element;
		if (number > del_element->number)
		{
			del_element = del_element->right;
		}
		else
		{
			del_element = del_element->left;
		}
	}
	if (del_element == NULL)
	{
		cout << "There's no such number!" << endl;
		return;
	}
	if (del_element->left == NULL && del_element->right == NULL)
	{
		deleteLeafSimple(root, del_element, prev_del);
	}
	else if ((del_element->left != NULL && del_element->right == NULL) || (del_element->right != NULL && del_element->left == NULL))
	{
		deleteLeafOneConnection(root, del_element, prev_del);
	}
	else if (del_element->left != NULL && del_element->right != NULL)
	{
		deleteLeafTwoConnections(root, del_element, prev_del);
	}
}

void deleteLeafSimple(Tree*& root, Tree*& del_element, Tree*& prev_del)
{
	if (del_element != root)
	{
		if (del_element->number > prev_del->number)
		{
			prev_del->right = NULL;
		}
		else
		{
			prev_del->left = NULL;
		}
	}
	else
	{
		root = NULL;
	}
	delete del_element;
	cout << "Leaf succesfully deleted!" << endl;
}

void deleteLeafOneConnection(Tree*& root, Tree*& del_element, Tree*& prev_del)
{
	if (del_element != root)
	{
		if (del_element->number > prev_del->number)
		{
			if (del_element->right)
			{
				prev_del->right = del_element->right;
			}
			else
			{
				prev_del->right = del_element->left;
			}
		}
		else
		{
			if (del_element->right)
			{
				prev_del->left = del_element->right;
			}
			else
			{
				prev_del->left = del_element->left;
			}
		}
	}
	else
	{
		if (del_element->right)
		{
			root = del_element->right;
		}
		else
		{
			root = del_element->left;
		}
	}
	delete del_element;
	cout << "Leaf succesfully deleted!" << endl;
}

void deleteLeafTwoConnections(Tree*& root, Tree*& del_element, Tree*& prev_del)//самый левый в правом
{
	Tree* replacement = NULL, * prev_replacement = NULL;
	prev_replacement = del_element;
	replacement = del_element->right;
	while (replacement->left != NULL)
	{
		prev_replacement = replacement;
		replacement = replacement->left;
	}
	if (prev_replacement == del_element)
	{
		replacement->left = del_element->left;
	}
	else
	{
		replacement->left = del_element->left;
		prev_replacement->left = replacement->right;
		replacement->right = prev_replacement;
	}
	if (del_element == root)
	{
		root = replacement;
	}
	else
	{
		if (del_element->number < prev_del->number)

		{
			prev_del->left = replacement;
		}
		else
		{

			prev_del->right = replacement;
		}
	}
	delete del_element;
	cout << "Leaf succesfully deleted!" << endl;
}

void addData(Tree*& root)
{
	int number, n, i = 0;
	string FIO;
	do
	{
		cout << "How many records do you want to add?" << endl;
		n = correctInputInt();
	} while (n < 1);
	if (root == NULL)
	{
		cout << "\n-> " << i + 1 << endl;
		cout << "Enter number:" << endl;
		number = correctInputInt();
		cout << "Enter FIO:" << endl;
		FIO = checkInputString();
		root = createLeaf(number, FIO);
		i++;
	}
	for (i; i < n; i++)
	{
		cout << "\n-> " << i + 1 << endl;
		cout << "Enter number:" << endl;
		number = correctInputInt();
		cout << "Enter FIO:" << endl;
		FIO = checkInputString();
		if (!isAddLeaf(root, number, FIO))
		{
			i--;
		};
	}
}

Tree* createLeaf(int number, string FIO)
{
	Tree* temp = new Tree;
	temp->number = number;
	temp->FIO = FIO;
	temp->left = temp->right = NULL;
	//root = temp;
	return temp;
}

bool isAddLeaf(Tree*& root, int number, string FIO)
{
	Tree* prev = NULL, * temp = NULL;
	//bool is_duplicate_finded = false;
	temp = root;
	while (temp)
	{
		prev = temp;
		if (number == temp->number)
		{
			cout << "\nNumber isn't unique!" << endl;
			return false;
		}
		if (number < temp->number)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
	temp = createLeaf(number, FIO);
	if (number < prev->number)
	{
		prev->left = temp;
	}
	else
	{
		prev->right = temp;
	}
	return true;
}

string checkInputString()
{
	char symbol;
	string buffer;
	while (true)
	{
		symbol = _getch();
		if (symbol == '\r')
		{
			break;
		}
		if (symbol == '\b')//backspace
		{
			if (buffer.size() != 0)
			{
				cout << "\b \b";
				buffer.erase(buffer.length() - 1);
			}
			continue;
		}
		if (!((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || symbol == ' '))
		{
			continue;
		}
		buffer += symbol;
		cout << symbol;
	}
	return buffer;
}

int correctInputInt()
{
	int a;
	while (true)
	{
		cin >> a;
		if (cin.get() == '\n') {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error, please write Integer numbers!\n" << "Try again!" << endl;
		}
	}
	return a;
}