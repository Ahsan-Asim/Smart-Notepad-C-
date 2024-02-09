// C++ implementation of search and insert
// operations on Trie
#include <iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<stdio.h>
#include <windows.h> //for setting console handler
#include<cctype>
using namespace std;

string Read_File()
{
	string line;
	fstream new_File;			// Declaring the file type variable

	new_File.open("encryption.txt", ios::in);			// Opening the file in INPUT mode

	if (!(new_File.is_open()))			// Will open the file ONLY if it exists
	{
		cout << "File does NOT exist, or you do NOT have sufficient rights to access it" << endl;			// Displaying error message on the CONSOLE screen
	}
	else
	{
		while (!(new_File.eof()))			// Read the file till End of File (EOF)
		{
			new_File >> line;			// Storing data of FILE in string type variable 'line'
			if (new_File.eof())			// If EOF has been reached break the condition (Done to avoid double printing of last character)
			{
				break;
			}
			else
			{
				cout << line << " ";			// Displaying the data of file on CONSOLE screen
			}
		}

		return line;
	}

	new_File.close();			// Closing the file

	cout << endl << endl << "The Data has been read from the file" << endl;			// Displaying confirmation message on the CONSOLE screen
	cout << endl << endl;
}

void Write_File(string newEncodedString)
{
	fstream new_File;			// Declaring the file type variable

	new_File.open("encryption.txt", ios::app);			// Opening the file in APPEND mode
	if (!(new_File.is_open()))			// Will open the file ONLY if it exists
	{
		cout << "File does NOT exist, or you do NOT have sufficient rights to access it." << endl;			// Displaying error message on the CONSOLE screen
	}
	else
	{
		new_File << newEncodedString << " ";			// Writing a line to the FILE
		new_File << endl << endl;
		cout << endl << "Encrypted data has been written successfully to the file." << endl << endl;			// Displaying confirmation message on the CONSOLE screen
	}

	new_File.close();			// Closing the file

}

class Node  // node class / used this to create a linked list and then used to create Tree
{
public:   // data declaration
	int frequency;
	char character;
	Node* next;
	Node* leftchild;
	Node* rightchild;
	bool checkerRight;
	bool checkerLeft;

	Node() // default constructor
	{
		// data initialization
		frequency = 0;
		next = NULL;
		leftchild = NULL;
		rightchild = NULL;
		checkerRight = 0;
		checkerLeft = 0;
	}
	Node(char Input)  // parameterised constructor
	{
		// data initialization
		character = Input;
		frequency = 1;
		next = NULL;
		leftchild = NULL;
		rightchild = NULL;
		checkerRight = 0;
		checkerLeft = 0;
	}
};

class Tree
{
	// data declaration
	Node* Head;  // Head node will be used to create linkedlist then further used to create tree from the linked list

public:
	Tree()  // default constructor
	{
		// data initialization
		Head = NULL;
	}
	Node* getNode()   // this function returns the Head pointer which will be used later.
	{
		return Head;
	}

	void Create_List(string Input)   // this function will create a linkedlist containing characters and there frequency.
	{
		unsigned long int Size = Input.length();
		for (int i = 0; i < Size; i++)    // loop to pass single character of string at time.
		{
			search(Input[i]);  // search and adding characters in the linked list.
		}
		Sort_List(); // To sort the Linked list to use while creating Max heap.
	}

	void search(char Input) // search and adding characters in the linked list.
	{
		int flag = 0;
		if (Head == NULL)  // checking if the Head is empty.
		{
			Head = new Node(Input);     // adding character because head is NULL.
			flag = 1;
		}
		else
		{
			Node* temp = Head;
			while (temp->next != NULL)  // loop to iterate in linked list.
			{
				if (Input == temp->character) // checking if character if in the Linked list.
				{
					temp->frequency++;  // if character is present in the list then increment in the frequency.
					flag = 1;  //
					return;
				}
				temp = temp->next;
			}
			if (flag == 0)  // to check if the character is incremented in the list or not
			{
				if (temp->character != Input)
				{
					temp->next = new Node(Input);  // if character is not found in the list then add this character to the list.
				}
				else
				{
					temp->frequency++;  // increment if character is not added.
				}
			}
		}
	}

	void Sort_List()  // function to sort linked list.
	{
		//Node current will point to head
		Node* current = Head, * index = NULL;
		int tempFrequency;
		char tempCharacter;

		if (Head == NULL)
		{
			return;
		}
		else
		{
			while (current != NULL) {
				//Node index will point to node next to current
				index = current->next;

				while (index != NULL) {
					//If current node's data is greater than index's node data, swap the data between them
					if (current->frequency > index->frequency)
					{
						tempFrequency = current->frequency;
						current->frequency = index->frequency; // swaping frequency of the nodes
						index->frequency = tempFrequency;

						tempCharacter = current->character;
						current->character = index->character; // swaping character of the nodes
						index->character = tempCharacter;
					}
					index = index->next;  // iteration
				}
				current = current->next;  // iteration
			}
		}
	}

	void Sorted_Insert(Node* newNode)  //this function inserts node in the the sorted way.
	{
		if (Head == NULL || Head->frequency >= newNode->frequency)  //adds node to the Head and checks if Head's Frequency is greater or not.
		{
			newNode->next = Head;
			Head = newNode;
		}
		else
		{
			Node* temp2 = Head;
			while (temp2->next != NULL && temp2->next->frequency < newNode->frequency)  // condition to get location of insertion.
			{
				temp2 = temp2->next;   // Iteration
			}
			newNode->next = temp2->next; // insertion of the node.
			temp2->next = newNode;
		}
	}

	void Create_Tree(string Input)
	{
		Create_List(Input);  // This functions create the linked list from the given string.

		Node* temp1 = new Node;

		while (Head->next != NULL)  // while until there is only one node remaining in the linked list.
		{
			temp1 = new Node;

			temp1->frequency = Head->frequency + Head->next->frequency;   // adding the frequency of node characters in the new node.
			temp1->character = '@'; // assigning a new character to the node for our convenience
			Head->checkerLeft = true;   // setting the checker to check if the node is left or right child of the parent node which will be used when back tracing the tree for decoding.
			temp1->leftchild = Head;  //  creating the tree by adding the first node to the leftchild of the sub tree. which will be used to encode the string.
			Head = Head->next;     //iterating in the linked list
			Head->checkerRight = true; // setting the checker to check if the node is left or right child of the parent node which will be used when back tracing the tree for decoding.
			temp1->rightchild = Head;//  creating the tree by adding the first node to the rightchild of the sub tree. which will be used to encode the string.
			Head = Head->next;//iterating in the linked list

			Sorted_Insert(temp1);  // inserting the node in the linked list in sorted order.
		}
	}

	string Code_For_Character(Node* root, char Input)  // function returns the encoded code for a single character.
	{
		string code;
		if (root == NULL) // condition if node  is null then return nothing.
			return "";

		if (root->leftchild == NULL && root->rightchild == NULL)  // condition checking if you child is NULL, meaning you have a leave node.
		{
			if (root->character == Input) // checking if given character has matched the leave node you are searching for.
			{
				if (root->checkerLeft == true)  // checking if the node is left child of the parent node.
				{
					//   code="0";
					return "0";
				}
				else if (root->checkerRight == true)  // checking if the node is right child of the parent node.
				{
					//   code="1";
					return "1";
				}
			}
		}

		if (root->checkerLeft == true)  // checking if the node is left child of the parent node.
		{
			code = "0";  // this helps in back tracing to generate the code for the given character.
		}
		else if (root->checkerRight == true) // checking if the node is right child of the parent node.
		{
			code = "1"; // this helps in back tracing to generate the code for the given character.
		}

		if (If_Node_Exists(root->leftchild, Input))  // this condition checks if the given character is in the present in the in left child.
		{
			return code + Code_For_Character(root->leftchild, Input); // if node exists then traverse in this sub tree.
		}
		else if (If_Node_Exists(root->rightchild, Input))  // this condition checks if the given character is in the present in the right child.
		{
			return code + Code_For_Character(root->rightchild, Input);  // if node exists then traverse in this sub tree.
		}

		return "";  // Non-void function does not return a value in all control paths (for my compiler only)
	}

	bool If_Node_Exists(Node* node, char key)  // this function checks if the node if present in the tree.
	{
		if (node == NULL)
			return false;

		if (node->character == key)
			return true;

		/* then recur on left subtree */
		bool res1 = If_Node_Exists(node->leftchild, key);
		// node found, no need to look further
		if (res1) return true;

		/* node is not found in left,
		so recur on right subtree */
		bool res2 = If_Node_Exists(node->rightchild, key);

		return res2;
	}

	string Encode(string Input)  //encode function adds the encoded code for a single character to make a whole string
	{
		Create_Tree(Input);  // creates the tree of the given string.
		string encodedString;

		unsigned long int Size = Input.length();
		for (int i = 0; i < Size; i++) // loop for the size of string so all characters are converted into code.
		{
			if (i != 0)  // to remove first space
			{
				encodedString = encodedString + " " + Code_For_Character(Head, Input[i]); // concatenating the string to get the whole string of encoded code.
			}
			else if (i == 0)  // to remove first space
			{
				encodedString = encodedString + Code_For_Character(Head, Input[i]); // concatenating the string to get the whole string of encoded code.
			}
		}
		return encodedString;  // returning the whole encoded string.
	}

	string Get_String(char x)         // string class has a constructor that allows us to specify size of string as first parameter and character to be filled in given size as second parameter.
	{
		string s(1, x);
		return s;
	}
	string Decode_For_Character(string Input)  // this function decodes the a single character by traversing in the tree and returns single character in string form.
	{
		Node* temp = Head;
		unsigned long int Size = Input.length();
		for (int i = 0; i < Size; i++) // loop for the size of single character encoded string.
		{
			if (Input[i] == '0')  // if 0 in string then traverse in leftchild.
			{
				temp = temp->leftchild;
			}
			else if (Input[i] == '1') // if 1 in string then traverse in rightchild.
			{
				temp = temp->rightchild;
			}
		}
		return Get_String(temp->character); //returns a single character decoded in string form.
	}

	string Decode(string Input) // concatenate the single characters to form the orignal string which was encoded.
	{
		string subCode = Get_String(Input[0]);
		string decodeString;
		unsigned long int Size = Input.length();
		for (int i = 1; i < Size; i++)    // loop for the size of string.
		{
			if (Input[i] != ' ')  //checks if there is space in the encoded string.
				subCode = subCode + Input[i];  // concatenate till there is no spaces.
			if (Input[i] == ' ')  // calls the single character decoding function.
			{
				decodeString += Decode_For_Character(subCode);  //concatenates the characters to form a whole decoded string
				subCode = Get_String(Input[i]); // used to set a new character in the subCode string.
			}
		}
		decodeString += Decode_For_Character(subCode); // this is to add the last character.
		return decodeString;  // returns the whole decoded string.
	}

};

// trie node
struct TrieNode
{
	char Data;
	struct TrieNode* Children[26];

	// isEndOfWord is true if the node represents
	// end of a word
	bool Is_End_Of_Word;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode* Get_Node(char ch)
{
	struct TrieNode* pNode = new TrieNode;
	pNode->Data = ch;
	pNode->Is_End_Of_Word = false;

	for (int i = 0; i < 26; i++)
		pNode->Children[i] = NULL;

	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
class TrieTress
{
	struct TrieNode* root;
public:
	TrieTress()
	{
		root = Get_Node('\0');
	}

	TrieNode* Get_Root()
	{
		return this->root;
	}

	bool Insert(struct TrieNode* root, string key)
	{
		struct TrieNode* NewRoot = root;

		for (int i = 0; i < key.length(); i++)
		{
			if (key[i] == ';' || key[i] == ',' || key[i] == ':' || key[i] == '"' || key[i] == '(' || key[i] == ')' || key[i] == '{' || key[i] == '}' ||
				key[i] == '[' || key[i] == ']' || key[i] == '*' || key[i] == '+' || key[i] == '!' || key[i] == '@' || key[i] == '#' ||
				key[i] == '$' || key[i] == '%' || key[i] == '^' || key[i] == '&' || key[i] == '-' || key[i] == '_' || key[i] == '<' || key[i] == '>' ||
				key[i] == '?' || key[i] == '/' || key[i] == '~' || key[i] == '`' || key[i] == '.')
				return false;
			if (key[i] >= '0' && key[i] <= '9')//If user enter a number in the string, so not insert in the tree
			{
				return false;
			}
			if (key[i] >= 'A' && key[i] <= 'Z')//If user enters capital letter so make it small case
				key[i] = tolower(key[i]);
			int index = key[i] - 'a';//calculate index number
			if (NewRoot->Children[index] == NULL)//If this root value does not exist, so make it 
				NewRoot->Children[index] = Get_Node(key[i]);

			NewRoot = NewRoot->Children[index];
		}

		// mark last node as leaf
		if (NewRoot->Is_End_Of_Word == true)//If already word exist
		{
			cout << endl << "This word already exist in the dictionary" << endl;
			return false;
		}
		else//If word doesn't exist
		{
			NewRoot->Is_End_Of_Word = true;
			return true;
		}
	}

	bool Insert_Word(string key)
	{
		return Insert(root, key);
	}


	// Returns true if key presents in trie, else
	// false
	bool Search(struct TrieNode* root, string key)
	{
		struct TrieNode* pCrawl = root;

		for (int i = 0; i < key.length(); i++)
		{
			if (key[i] == ';' || key[i] == ',' || key[i] == ':' || key[i] == '"' || key[i] == '(' || key[i] == ')' || key[i] == '{' || key[i] == '}' ||
				key[i] == '[' || key[i] == ']' || key[i] == '*' || key[i] == '+' || key[i] == '!' || key[i] == '@' || key[i] == '#' ||
				key[i] == '$' || key[i] == '%' || key[i] == '^' || key[i] == '&' || key[i] == '-' || key[i] == '_' || key[i] == '<' || key[i] == '>' ||
				key[i] == '?' || key[i] == '/' || key[i] == '~' || key[i] == '`' || key[i] == '.')
				return false;
			if (key[i] >= '0' && key[i] <= '9')//If user enter a number in the string
				return false;
			if (key[i] >= 'A' && key[i] <= 'Z')//if user enters capital letter so make into small case
				key[i] = tolower(key[i]);
			int index = key[i] - 'a';//make to the index
			if (!pCrawl->Children[index])//If this value doesn't exist so return false because this word doesn't exist
				return false;

			pCrawl = pCrawl->Children[index];
		}

		return pCrawl->Is_End_Of_Word;
	}

	bool Search_Word(string key)
	{
		return Search(root, key);
	}

	//This function will remove a specific word after searching
	bool Search_Remove(struct TrieNode* root, string key)
	{
		struct TrieNode* pCrawl = root;

		for (int i = 0; i < key.length(); i++)
		{
			if (key[i] == ';' || key[i] == ',' || key[i] == ':' || key[i] == '"' || key[i] == '(' || key[i] == ')' || key[i] == '{' || key[i] == '}' ||
				key[i] == '[' || key[i] == ']' || key[i] == '*' || key[i] == '+' || key[i] == '!' || key[i] == '@' || key[i] == '#' ||
				key[i] == '$' || key[i] == '%' || key[i] == '^' || key[i] == '&' || key[i] == '-' || key[i] == '_' || key[i] == '<' || key[i] == '>' ||
				key[i] == '?' || key[i] == '/' || key[i] == '~' || key[i] == '`' || key[i] == '.')
				return false;
			if (key[i] >= '0' && key[i] <= '9')//If user enter a number in the string
				return false;
			if (key[i] >= 'A' && key[i] <= 'Z')//Change into small case 
				key[i] = tolower(key[i]);
			int index = key[i] - 'a';//move to the index
			if (!pCrawl->Children[index])//if doesn't exist 
				return false;

			pCrawl = pCrawl->Children[index];
		}
		if (pCrawl->Is_End_Of_Word == true)//if word exist so make it false means remove
		{
			pCrawl->Is_End_Of_Word = false;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Search_Word_Remove(string key)
	{
		return Search_Remove(root, key);
	}

	int j = 0;//make global for counter to input in the string array that we will return for suggestions

	void Print_Word(char* str, int n, string*& arr)
	{
		cout << endl;
		str[n] = '\0';//Make last character NULL character
		arr[j++] = str;

	}

	int count = 0;
	// Print all words in Trie
	void Print_All_Words(TrieNode* root, char* wordArray, int size, int pos, string*& arr)
	{
		int k = 0;

		if (root == NULL)
		{
			if (count == 0)
				cout << endl << "------------Sorry No Suggestion Found-----------------" << endl;
			return;
		}

		if (root->Is_End_Of_Word)//If word exist
		{
			count++;
			Print_Word(wordArray, pos, arr);
		}

		if (count == 10)//if 10 suggestions are completed
			return;

		for (int i = 0; i < 26; i++)//Ths loop will check the 26 children that exist or not
		{
			if (root->Children[i] != NULL)
			{
				//pos = j;
				wordArray[size] = i + 'a';
				Print_All_Words(root->Children[i], wordArray, ++size, pos + 1, arr);
			}
			if (i == 25)
			{
				k++;
				size = size - k;
				wordArray[size] = ' ';
			}
		}
	}

	//The below function is to save the inputed text of the NotePad in teh file
	void Safer(TrieTress*, char* array)
	{
		Tree Array2;
		string NewArray1, NewArray2;
		NewArray1 = array;
		int size = NewArray1.length();
		NewArray1[size] = '\0';
		//strcat(array, NewArray1.c_str());
		//NewArray1 = string.valueOf(array);
		string choice = "No";
		cout << "Do you want to save it?";
		cin >> choice;
		if (choice != "No" && choice != "no")
		{
			cout << "\n\n The String is : \n\n" << NewArray1;
			cout << " \n\n";
			string NewArray2 = Array2.Encode(NewArray1);
			cout << "After encoding :\n" << NewArray2;
			cout << "\n\n";
			Write_File(NewArray1);
			cout << "The Decoded String is :\n\n" << Array2.Decode(NewArray2);
			cout << "\n\n";
			cout << "\n\n";

			cout << endl << endl;
			/*cout << "Reading data from file" << endl << endl;
			Read_File();
			cout << endl << endl;*/
		}
	}

	//The below function move the P node at the last of the inputed word and then pass to the function for suggestions found.
	void Success(string arr, int position, string* arr1)
	{
		TrieNode* p = root;
		//string arr1;
		char wordArray[100];
		int size = 0;
		for (int k = position; arr[k] != '\0'; k++)
		{
			if (arr[k] == ';' || arr[k] == ',' || arr[k] == ':' || arr[k] == '"' || arr[k] == '(' || arr[k] == ')' || arr[k] == '{' || arr[k] == '}' ||
				arr[k] == '[' || arr[k] == ']' || arr[k] == '*' || arr[k] == '+' || arr[k] == '!' || arr[k] == '@' || arr[k] == '#' ||
				arr[k] == '$' || arr[k] == '%' || arr[k] == '^' || arr[k] == '&' || arr[k] == '-' || arr[k] == '_' || arr[k] == '<' || arr[k] == '>' ||
				arr[k] == '?' || arr[k] == '/' || arr[k] == '~' || arr[k] == '`' || arr[k] == '.')
				return;
			if (arr[k] >= '0' && arr[k] <= '9')//If numbers so return
				return;
			if (arr[k] >= 'A' && arr[k] <= 'Z')//If upper case so make them small case 
				arr[k] = tolower(arr[k]);
			int index = arr[k] - 'a';
			p = p->Children[index];
			if (p == NULL)
			{
				Print_All_Words(p, wordArray, size, size, arr1);
				return;
			}
		}
		//Now P is at last index of the inputed word
		for (int k = position, o = 0; arr[k] != '\0'; k++, o++)
		{
			wordArray[o] = arr[k];//Now copy the inputed text into the array
		}
		size = arr.length() - position;//find size of the array
		Print_All_Words(p, wordArray, size, size, arr1);
	}

	//The below function will show instructions for the NotePad suggestions and ask user to continue or not.
	void Instruction(TrieTress* t1)
	{
		cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t Welcome to the Notepad" << endl;
		cout << "\t\t\t\t\t\t\t\t\t I am here for your help" << endl;
		cout << "\t\t\t\t\t\t\t\t\t Here are some Instructions for you." << endl;
		cout << "\t\t\t\t\t\t\t\t\t When you write words, we will give you suggestions." << endl;
		cout << "\t\t\t\t\t\t\t\t\t You can chosse any suggestion by entering its number" << endl;
		cout << "\t\t\t\t\t\t\t\t\t Please don't be oversmart, write neately." << endl;
		cout << "\t\t\t\t\t\t\t\t\t T H A N K Y O U" << endl;
		cout << "\t\t\t\t\t\t\t\t\t Do you want to continue it?" << endl;
		string flag = "No";
		cin >> flag;
		if (flag != "No" && flag != "no")
		{
			system("cls");
			Note_Pad(t1);
		}
		else
			return;
	}

	//The below function is to write the paragraph in the character array.
	void Note_Pad(TrieTress* t1)
	{
		string exit = "No";
		string array[10];
		int symptom = 0;
		int num;
		int size1;
		int jk = 0;
		int j = 0, f = 0;
		int lo = 0;
		cout << "----------------------------Welcome to the Notepad! I am here for your help.----------------------------------------" << endl;
		char s1[1000] = { 0 };
		cout << "Enter the Paragraph" << endl;
		int K = 0;
		for (int i = 0; i < 1000; i++)
		{
			//K = i;
			s1[i] = _getche();//Take character
			if (s1[i] == '.')//If user enter comma, then we will ask from user to end of it or not?
			{
				cout << endl << "Do you want to exit?";
				cin >> exit;
				if (exit != "No" && exit != "no")
				{
					Safer(t1, s1);
					return;
				}
			}

			if (s1[i] == ' ')//If user enter space then we will start suggestions from the next word
			{
				f = i + 1;
				j = -1;
			}
			if ((j - K) > 1)
			{
				s1[i + 1] = '\0';
				t1->Success(s1, f, array);
				cout << endl;
				jk++;
				for (int l = 0; l < t1->count; l++)
				{
					cout << array[l] << endl;//Suggestion array
					symptom = 1;
				}
				t1->j = 0;
				if (symptom == 1)//If suggestion displayed so we ask from the suer to which suggestion, he/she wanted to select.
				{
					symptom = 0;
					cout << "Enter suggestion number:";
					cin >> num;
					switch (num)
					{
					case 1:
						if (array[0] != "")//If suggestion exist so it will occur
						{
							for (int s = f; s < i; s++)
							{
								s1[s] = '\0';
							}
							strcat_s(s1, array[0].c_str());

							lo = array[0].length() - 1;
							if (i < 5)
								i = lo;
							else
							{
								i += array[0].length() - j - 1;
							}
						}
						break;
					case 2:
						if (array[1] != "")
						{
							for (int s = f; s < i; s++)
								s1[s] = '\0';
							strcat_s(s1, array[1].c_str());
							lo = array[1].length() - 1;
							if (i < 5)
								i = lo;
							else
							{
								i += array[1].length() - j - 1;
							}
						}
						break;
					case 3:
						if (array[2] != "")
						{
							for (int s = f; s < i; s++)
								s1[s] = '\0';
							strcat_s(s1, array[2].c_str());
							lo = array[2].length() - 1;
							if (i < 5)
								i = lo;
							else
							{
								i += array[2].length() - j - 1;
							}
						}
						break;
					case 4:
						if (array[3] != "")
						{
							for (int s = f; s < i; s++)
								s1[s] = '\0';
							strcat_s(s1, array[3].c_str());
							lo = array[3].length() - 1;
							if (i < 5)
								i = lo;
							else
							{
								i += array[3].length() - j - 1;
							}
						}
						break;
					case 5:
						if (array[4] != "")
						{
							for (int s = f; s < i; s++)
								s1[s] = '\0';
							strcat_s(s1, array[4].c_str());
							lo = array[4].length() - 1;
							if (i < 5)
								i = lo;
							else
							{
								i += (array[4].length() - j - 1);
							}
						}
						break;
					case 6:
						if (array[5] != "")
						{
							for (int s = f; s < i; s++)
								s1[s] = '\0';
							strcat_s(s1, array[5].c_str());

							lo = array[5].length() - 1;
							if (i < 5)
								i = lo;
							else
							{
								i += array[5].length() - j - 1;
							}
						}
						break;
					case 7:
						if (array[6] != "")
						{
							for (int s = f; s < i; s++)
								s1[s] = '\0';
							strcat_s(s1, array[6].c_str());

							lo = array[6].length() - 1;
							if (i < 5)
								i = lo;
							else
							{
								i += array[6].length() - j - 1;
							}
						}
						break;
					case 8:
						if (array[7] != "")
						{
							for (int s = f; s < i; s++)
								s1[s] = '\0';
							strcat_s(s1, array[7].c_str());

							lo = array[7].length() - 1;
							if (i < 5)
								i = lo;
							else
							{
								i += array[7].length() - j - 1;
							}
						}
						break;
					case 9:
						if (array[8] != "")
						{
							for (int s = f; s < i; s++)
								s1[s] = '\0';
							strcat_s(s1, array[8].c_str());

							lo = array[8].length() - 1;
							if (i < 5)
								i = lo;
							else
							{
								i += array[8].length() - j - 1;
							}
						}
						break;
					case 10:
						if (array[9] != "")
						{
							for (int s = f; s < i; s++)
								s1[s] = '\0';
							strcat_s(s1, array[9].c_str());

							lo = array[9].length() - 1;
							if (i < 5)
								i = lo;
							else
							{
								i += array[9].length() - j - 1;
							}
						}
						break;
					case 11:
						s1[i + 1] = '\0';
						break;
					}
					for (int j = 0; j < t1->count; j++)
						array[j].clear();
				}

				system("cls");
				t1->count = 0;
				cout << endl << "New Paragraph:" << endl;
				cout << s1;
			}
			/*system("cls");
			cout << endl << "New Paragraph:" << endl;
			cout << s1;*/
			j++;
		}
	}

	void page() // page for welcome and instructions
	{
		ifstream in;
		in.open("outfile.txt");//file opened for input from dictionary to the Trie Tress
		TrieTress t1;

		string m1;//This string is used to take input from a file as a line.

		if (!in.is_open())
		{
				cout << "Error: Unable to open file 'outfile.txt'" << endl;
		}

		else
		{
			while (!in.eof())//until end of file not come, insert strings in the tress
			{
				getline(in, m1);
				t1.Insert_Word(m1);
			}
		}
		in.close();//file has closed

		int choice = 0;//This var is used to take user choice as he wants to insert,remove, search, or notepad
		string choice1 = "No";
		string choice2 = "No";
		string key = " ";
		//TrieTress t1;
		int ch;//It is a control variable in which user give input to start game 
		Beep(400, 500);
		Beep(500, 500);
		Beep(200, 500);

		cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t W E L C O M E" << endl
			<< endl
			<< endl;
		Beep(200, 500);//beep is used for sound
		Beep(400, 500);
		Beep(500, 500);

		cout << "\t\t\t//          ||  ////////////////// //                   //                            ///////////////////" << endl;
		cout << "\t\t\t//          ||  //                 //                   //                            |                 |" << endl;
		cout << "\t\t\t//          ||  //                 //                   //                            |                 |" << endl;
		cout << "\t\t\t//          ||  //                 //                   //                            |                 |" << endl;
		cout << "\t\t\t//          ||  //                 //                   //                            |                 |" << endl;
		cout << "\t\t\t//////////////////                 //                   //                            |                 |" << endl;
		cout << "\t\t\t//          ||  // /////////////// //                   //                            |                 |" << endl;
		cout << "\t\t\t//          ||  //                 //                   //                            |                 |" << endl;
		cout << "\t\t\t//          ||  //                 //                   //                            |                 |" << endl;
		cout << "\t\t\t//          ||  //                 //                   //                            |                 |" << endl;
		cout << "\t\t\t//          ||  //                 //                   //                            |                 |" << endl;
		cout << "\t\t\t//          ||  ////////////////// //////////////////// ///////////////////////////// |//////////////////" << endl;
		Beep(200, 500);
		Beep(400, 500);
		Beep(500, 500);
		Beep(200, 500);
		Beep(200, 500);
		cout << "Press any integer to continue:";//it is user input and he/she can input any integer to continue
		ch = _getch();
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t Welcome to the Notepad" << endl;
		cout << "\t\t\t\t\t\t\t\t\t You have following choices:" << endl;
		cout << "\t\t\t\t\t\t\t\t\t 1.Insert a word in the dictionary" << endl;
		cout << "\t\t\t\t\t\t\t\t\t 2.Search a specific word" << endl;
		cout << "\t\t\t\t\t\t\t\t\t 2.remove a specific word from the dictionary" << endl;
		cout << "\t\t\t\t\t\t\t\t\t 4.Start a Notepad" << endl;
		cout << "\t\t\t\t\t\t\t\t\t   Or Quit" << endl;
		do {
			if (choice2 != "No" && choice2 != "no")
			{
				system("cls");
				cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t Welcome to the Notepad" << endl;
				cout << "\t\t\t\t\t\t\t\t\t You have following choices:" << endl;
				cout << "\t\t\t\t\t\t\t\t\t 1.Insert a word in the dictionary" << endl;
				cout << "\t\t\t\t\t\t\t\t\t 2.Search a specific word" << endl;
				cout << "\t\t\t\t\t\t\t\t\t 2.remove a specific word from the dictionary" << endl;
				cout << "\t\t\t\t\t\t\t\t\t 4.Start a Notepad" << endl;
				cout << "\t\t\t\t\t\t\t\t\t   Or Quit" << endl;
			}
			cout << "\t\t\t\t\t\t\t\t\t   Enter your choice plz" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "Enter the word you want to enter in the dictionary:";
				cin >> key;
				if (key != " ")
					t1.Insert_Word(key);
				break;
			case 2:
				cout << "Enter the word you want to search in the dictionary:";
				cin >> key;
				if (t1.Search_Word(key))
				{
					cout << endl << "This value has found" << endl;
					cout << "Do you want to remove it?";
					cin >> choice1;
					if (choice1 != "No" && choice1 != "no")
					{
						if (t1.Search_Word_Remove(key))
							cout << endl << "Removed successfully" << endl;
					}

				}
				else
				{
					cout << endl << "This value does not exist" << endl;
					cout << "Do you want to insert it?";
					cin >> choice1;
					if (choice1 != "No" && choice1 != "no")
					{
						if (t1.Insert_Word(key))
							cout << endl << "Inserted successfully" << endl;
					}
				}
				break;
			case 3:
				cout << "Enter word:";
				cin >> key;
				if (key != " ")
				{
					if (t1.Search_Word_Remove(key))
						cout << endl << "Removed Successfully" << endl;
					else
					{
						cout << endl << "Not found" << endl;
					}
				}
				break;
			case 4:
				system("cls");
				Instruction(&t1);
				cout << endl << "Do you want to continue all things?";
				cin >> choice2;
				if (choice2 == "No" || choice2 == "no")
					return;
				break;
			case 5:
				cout << endl << "Ok" << endl;
				break;
			}
		} while (choice == 1 || choice == 2 || choice == 3 || choice == 4);
	}



};






// Driver
int main()
{

	TrieTress t1;
	cout << endl << endl << endl;
	t1.page();


	return 0;
}

