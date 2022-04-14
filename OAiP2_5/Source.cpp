#include <iostream>
#include <conio.h>

using namespace std;

struct Tree
{
	int number = 0;
	string FIO;
	Tree* left = nullptr, * right = nullptr;
};

struct Arr
{
	int number = 0;
	string FIO;
};

struct Queue
{
	Tree* number;
	Queue* prev, * next;
};

Tree* createLeaf(int number, string FIO);
Tree* popQueue(Queue*& begin, Queue*& end);
string checkInputString();
void addData(Tree*& root);
void deleteLeaf(Tree*& root);
void deleteLeafSimple(Tree*& root, Tree*& del_element, Tree*& prev_del);
void deleteLeafOneConnection(Tree*& root, Tree*& del_element, Tree*& prev_del);
void deleteLeafTwoConnections(Tree*& root, Tree*& del_element, Tree*& prev_del);
void balanceTree(Tree*& root);
void countElements(Tree* temp, int& number_of_elements);
void addElementsToArray(Tree* temp, Arr* arr, int& count);
void makeBalance(Tree*& root, Arr* arr, int n, int number_of_elements);
void findLeaf(Tree* root);
void countSymbols(Tree* temp, int& count);
void deleteTree(Tree*& temp);
void viewTree(Tree* temp, int level);
void printInfoDirectBypass(Tree* temp);
void printInfoReverseBypass(Tree* temp);
void printInfoAscendingBypass(Tree* temp);
void viewTree2(Tree* root);
void pushQueue(Queue*& begin, Queue*& end, Tree* number);
void deleteQueue(Queue*& begin, Queue*& end);
bool isAddLeaf(Tree*& root, int number, string FIO);
bool isTreeExist(Tree* root);
int heightTree(Tree* temp);
int maxNumber(int res, int rate);
int pow_2(int res, int rate);
int correctInputInt();
int countDigits(double num, int i);
int findMaxLength(int height, int res, int max_length_of_number);
int getNumberOfDigits(double number);
int findMaxLengthOfNumber(Tree* temp);

int main()
{
	Tree* root = nullptr;
	int code, count;
	while (true)
	{
		if (isTreeExist(root))
		{
			do
			{
				cout << "\n Enter input data -> 1\n Balance Tree -> 2\n Search leaf -> 3\n Delete leaf -> 4\n View tree -> 5\n Individual task -> 6\n"
					<< " Delete tree -> 7\n Print info(direct bypass) -> 8\n Print info(reverse bypass) -> 9\n Print info(ascending bypass) -> 10\n EXIT -> 0\n";
				code = correctInputInt();
			} while (code < 0 || code > 10);
		}
		else
		{
			do
			{
				cout << "\n Enter input data -> 1\n EXIT -> 0\n";
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
			cout << "-------------------------------------------" << endl;
			viewTree2(root);
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
		case 8:
			printInfoDirectBypass(root);
			cout << endl;
			break;
		case 9:
			printInfoReverseBypass(root);
			cout << endl;
			break;
		case 10:
			printInfoAscendingBypass(root);
			cout << endl;
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

void viewTree2(Tree* root)
{
	int count_of_pushed_elements = 0, count_of_printed_elements = 0, count_of_levels = 0, num_of_elements_in_string = 2;
	int num_of_digits, count_of_spaces, offset_of_element;
	bool is_not_start_of_string = false, is_not_start = false;
	int height = heightTree(root);
	int number_of_elements_max = maxNumber(1, height);
	int max_length_of_number = findMaxLengthOfNumber(root);
	if (max_length_of_number < 3)max_length_of_number = 3;
	int max_length = findMaxLength(height, 1, round(max_length_of_number / 2.));
	int length = max_length / 2;
	Queue* begin = nullptr, * end = nullptr;
	Tree* current_leaf = nullptr;
	pushQueue(begin, end, root);
	while (count_of_printed_elements < number_of_elements_max)
	{
		current_leaf = popQueue(begin, end);
		if (current_leaf)
		{
			num_of_digits = getNumberOfDigits(current_leaf->number);
			count_of_spaces = length * 2 - round(num_of_digits / 2.);
			if (is_not_start_of_string)
			{
				if (is_not_start)
				{
					count_of_spaces -= offset_of_element;
					is_not_start = false;
				}
			}
			else
			{
				cout << count_of_levels++ << "|";
				is_not_start_of_string = true;
				count_of_spaces -= length;
				if (is_not_start)
				{
					count_of_spaces -= offset_of_element;
					is_not_start = false;
				}
			}
			for (int i = 0; i < count_of_spaces; i++)cout << " ";
			offset_of_element = round(num_of_digits / 2. - 0.1);
			is_not_start = true;
			cout << current_leaf->number;
			pushQueue(begin, end, current_leaf->left);
			pushQueue(begin, end, current_leaf->right);
		}
		else
		{
			count_of_spaces = length * 2 - 1;
			if (is_not_start_of_string)
			{
				if (is_not_start)
				{
					count_of_spaces -= offset_of_element;
					is_not_start = false;
				}
			}
			else
			{
				cout << count_of_levels++ << "|";
				is_not_start_of_string = true;
				count_of_spaces -= length;
				if (is_not_start)
				{
					count_of_spaces -= offset_of_element;
					is_not_start = false;
				}
			}
			for (int i = 0; i < count_of_spaces; i++)cout << " ";
			cout << "-";
			pushQueue(begin, end, nullptr);
			pushQueue(begin, end, nullptr);
		}
		count_of_printed_elements++;
		count_of_pushed_elements += 2;
		if (count_of_pushed_elements % num_of_elements_in_string == 0)
		{
			cout << endl;
			num_of_elements_in_string *= 2;
			length /= 2;
			count_of_pushed_elements = 0;
			is_not_start_of_string = false;
			is_not_start = false;
		}
	}
	deleteQueue(begin, end);
}

int maxNumber(int res, int rate)
{
	if (rate == 0)
	{
		return res;
	}
	res += pow_2(1, rate);
	return maxNumber(res, rate - 1);
}

int pow_2(int res, int rate)
{
	if (rate == 0)
	{
		return res;
	}
	res *= 2;
	return pow_2(res, rate - 1);
}

int countDigits(double num, int i)
{
	if (num > -1 && num < 1)
	{
		return i;
	}
	return countDigits(num / 10, i + 1);
}

int findMaxLength(int height, int res, int max_length_of_number)
{
	if (height == 0)
	{
		return 2;
	}
	if (height * res / pow_2(1, height + 1) >= max_length_of_number)
	{
		return height * res;
	}
	return findMaxLength(height, res * 2, max_length_of_number);
}

int getNumberOfDigits(double number)
{
	int length = 0;
	length = countDigits(number, length);
	if (number < 0.)length++;
	return length;
}

int findMaxLengthOfNumber(Tree* temp)
{
	Tree* var = temp;
	int length_left, length_right;
	while (var->left != nullptr)
	{
		var = var->left;
	}
	length_left = getNumberOfDigits(var->number);
	var = temp;
	while (var->right != nullptr)
	{
		var = var->right;
	}
	length_right = getNumberOfDigits(var->number);
	if (length_left >= length_right)return length_left;
	else return length_right;
}

void pushQueue(Queue*& begin, Queue*& end, Tree* number)
{
	Queue* temp = new Queue;
	temp->number = number;
	if (begin == nullptr)
	{
		temp->next = temp->prev = nullptr;
		begin = temp;
		end = temp;
	}
	else
	{
		temp->next = nullptr;//сзади нет
		temp->prev = end;//впереди есть
		end->next = temp;
		end = temp;
	}
}

Tree* popQueue(Queue*& begin, Queue*& end)//по адресу
{
	Queue* temp = begin;
	Tree* out;
	out = begin->number;
	if (begin != end)
	{
		begin = begin->next;
		begin->prev = nullptr;
	}
	else
	{
		begin = end = nullptr;
	}
	delete temp;
	return out;
}

void deleteQueue(Queue*& begin, Queue*& end)
{
	while (begin)
	{
		Queue* temp = begin;
		begin = begin->next;
		delete temp;
	}
	end = nullptr;
	cout << "\nQueue deleted successfully" << endl;
}

int heightTree(Tree* temp)
{
	if (temp == nullptr)
	{
		return 0;
	}
	else if (temp->left == nullptr && temp->right == nullptr)
	{
		return 0;
	}
	else if (heightTree(temp->left) > heightTree(temp->right))
	{
		return heightTree(temp->left) + 1;
	}
	else
	{
		return heightTree(temp->right) + 1;
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
	temp = nullptr;
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
	if (element == nullptr)
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
	makeBalance(root, arr, 0, number_of_elements);
	delete[]arr;
	cout << "Tree balanced successfully!" << endl;
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

void addElementsToArray(Tree* temp, Arr* arr, int& count)
{
	if (temp)
	{
		addElementsToArray(temp->left, arr, count);
		arr[count].number = temp->number;
		arr[count].FIO = temp->FIO;
		count++;
		addElementsToArray(temp->right, arr, count);
	}
}

void makeBalance(Tree*& root, Arr* arr, int n, int number_of_elements)
{
	if (n == number_of_elements)
	{
		return;
	}
	else
	{
		int middle = (n + number_of_elements) / 2;
		root = new Tree;
		root->number = arr[middle].number;
		root->FIO = arr[middle].FIO;
		makeBalance(root->left, arr, n, middle);
		makeBalance(root->right, arr, middle + 1, number_of_elements);
	}
}

void countSymbols(Tree* temp, int& count)
{
	if (temp)
	{
		countSymbols(temp->right, count);
		count += temp->FIO.size();
		countSymbols(temp->left, count);
	}
}

void deleteLeaf(Tree*& root)
{
	int number;
	Tree* del_element, * prev_del;
	cout << "Enter number:" << endl;
	number = correctInputInt();
	del_element = root;
	prev_del = nullptr;
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
	if (del_element == nullptr)
	{
		cout << "There's no such number!" << endl;
		return;
	}
	if (del_element->left == nullptr && del_element->right == nullptr)
	{
		deleteLeafSimple(root, del_element, prev_del);
	}
	else if ((del_element->left != nullptr && del_element->right == nullptr) || (del_element->right != nullptr && del_element->left == nullptr))
	{
		deleteLeafOneConnection(root, del_element, prev_del);
	}
	else if (del_element->left != nullptr && del_element->right != nullptr)
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
			prev_del->right = nullptr;
		}
		else
		{
			prev_del->left = nullptr;
		}
	}
	else
	{
		root = nullptr;
	}
	delete del_element;
	cout << "Leaf successfully deleted!" << endl;
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
	cout << "Leaf successfully deleted!" << endl;
}

void deleteLeafTwoConnections(Tree*& root, Tree*& del_element, Tree*& prev_del)//самый левый в правом
{
	Tree* replacement = nullptr, * prev_replacement = nullptr;
	prev_replacement = del_element;
	replacement = del_element->right;
	while (replacement->left != nullptr)
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
	if (root == nullptr)
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
		}
	}
}

Tree* createLeaf(int number, string FIO)
{
	Tree* temp = new Tree;
	temp->number = number;
	temp->FIO = FIO;
	temp->left = temp->right = nullptr;
	return temp;
}

bool isAddLeaf(Tree*& root, int number, string FIO)
{
	Tree* prev = nullptr, * temp = nullptr;
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
	if (prev)
	{
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
	else
	{
		return false;
	}
}

void printInfoDirectBypass(Tree* temp)//прямой левый обход
{
	if (temp)
	{
		cout << temp->number << '\t';
		printInfoDirectBypass(temp->left);
		printInfoDirectBypass(temp->right);
	}
}

void printInfoReverseBypass(Tree* temp)//обратный левый обход
{
	if (temp)
	{
		printInfoReverseBypass(temp->left);
		printInfoReverseBypass(temp->right);
		cout << temp->number << '\t';
	}
}

void printInfoAscendingBypass(Tree* temp)//по возрастанию
{
	if (temp)
	{
		printInfoAscendingBypass(temp->left);
		cout << temp->number << '\t';
		printInfoAscendingBypass(temp->right);
	}
}

string checkInputString()
{
	char symbol;
	string buffer;
	while (true)
	{
		symbol = (char)_getch();
		if (symbol == '\r')
		{
			if (buffer.empty())
			{
				cout << "String is empty! Try again!" << endl;
				continue;
			}
			if (buffer.at(buffer.size() - 1) == ' ')
			{
				cout << "\b \b";
				buffer.erase(buffer.size() - 1);
			}
			break;
		}
		if (symbol == '\b')//backspace
		{
			if (!buffer.empty())
			{
				cout << "\b \b";
				buffer.erase(buffer.size() - 1);
			}
			continue;
		}
		if (!((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || symbol == ' '))
		{
			continue;
		}
		else if ((!buffer.empty() && symbol == ' ' && buffer.at(buffer.size() - 1) == ' ') || (buffer.empty() && symbol == ' '))
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