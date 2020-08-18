#include<iostream>
#include <Windows.h>
#include<conio.h>
#include<string>
using namespace std;
HANDLE hstdout;
COORD destcord;

struct node
{
	char data;
	node* left;
	node* right;
	node* up;
	node* down;
	node* linehead;
	node()
	{
		data = NULL;
		left = right = up = down = linehead = nullptr;
	}
};
class NotePad
{
	node* head_of_notepad;
	node* cursor;
public:
	NotePad()
	{
		head_of_notepad = nullptr;
		cursor = nullptr;
	}
	void insertion(int key)
	{
		node* ptr = new node;
		if (key == '\r')
			ptr->data = '\n';
		else
			ptr->data = key;
		if (head_of_notepad == nullptr)
		{
			node* temp = new node;
			temp->data = '\0';
			temp->linehead = temp;
			ptr->linehead = temp;
			temp->right = ptr;
			ptr->left = temp;
			head_of_notepad = temp;
			cursor = ptr;
		}
		else if (cursor->right!=nullptr)
		{
			node* tempformidinsert = cursor->right;
			ptr->linehead = cursor->linehead;
			while (tempformidinsert->data != '\n')
			{
				swap(ptr->data, tempformidinsert->data);
				if (tempformidinsert->right == nullptr)
					break;
				tempformidinsert = tempformidinsert->right;
			}
			if (tempformidinsert->right == nullptr)
			{
				ptr->left = tempformidinsert;
				ptr->right = nullptr;
				tempformidinsert->right = ptr;
				cursor = cursor->right;
			}
			else
			{
				ptr->left = tempformidinsert->left;
				ptr->left->right = ptr;
				ptr->right = tempformidinsert;
				tempformidinsert->left = ptr;
				cursor = cursor->right;
			}
		}
		else
		{
			node* temp = head_of_notepad;
			while (temp->right != nullptr)
			{
				temp = temp->right;
			}
			if (key != '\r')
			{
				ptr->left = temp;
				temp->right = ptr;
				ptr->linehead = ptr->left->linehead;
			}
			else
			{
				ptr->data = '\n';
				ptr->linehead = ptr;
				ptr->left = temp;
				temp->right = ptr;
			}
			cursor = ptr;
		}
		//call setupdown function
		UpDownLink(ptr, ptr->data);
	}
	void Print_Text()
	{
		node* ptr = head_of_notepad;
		while (ptr != nullptr)
		{
			if (ptr->data == '\0')
				cout << "";
			else
			{
				//cout << "Main Node: ";
				cout << ptr->data <<"";
				//cout << endl;
				/*if (ptr->left != nullptr)
					cout << " L: " << ptr->left->data;
				if (ptr->right != nullptr)
					cout << " R: " << ptr->right->data;
				if (ptr->up != nullptr)
					cout << " U: " << ptr->up->data;
				if (ptr->down != nullptr)
					cout << " D: " << ptr->down->data;
				cout << endl;*/
			}
				
			ptr = ptr->right;
		}
	}
	void MoveCursor()
	{
		char temp = _getch();
		if ((int)temp == 77) //right key
		{
			if (cursor->right!=nullptr)
				cursor = cursor->right;
		}
		else if ((int)temp == 72) //Key up
		{
			if (cursor->up == nullptr)
			{
				//node* temppointer = cursor;
				while (cursor->up == nullptr && cursor!=cursor->linehead)
				{
					cursor = cursor->left;
				}
			}
			if(cursor!=cursor->linehead)
				cursor = cursor->up;
		}
		else if ((int)temp == 75) //Key left
		{
			if (cursor != head_of_notepad &&cursor->left!=nullptr)
				cursor = cursor->left;
		}
		else if ((int)temp == 80) //keydown
		{
			if (cursor->down == nullptr)
			{
				while (cursor->down == nullptr && cursor != cursor->linehead)
				{
					cursor = cursor->left;
				}
			}
			if (cursor != cursor->linehead)
				cursor = cursor->down;
		}

	}
	void UpDownLink(node* ptr, char key)
	{
		if (key != '\n')
		{
			if (ptr->left->up != nullptr)
			{
				if (ptr->left->up->right == ptr->linehead)
					ptr->up = nullptr;
				else
				{
					ptr->up = ptr->left->up->right;
					ptr->up->down = ptr;
				}
			}
			else
			{
				ptr->up = nullptr;
				if (ptr->left->down != nullptr )
					if(ptr->left->down->right!=nullptr)
						if (ptr->left->down->right->data != '/n')
						{
							ptr->down = ptr->left->down->right;
							ptr->down->up = ptr;
						}
			}
				
		}
		else
		{
			ptr->up = ptr->left->linehead;
			ptr->up->down = ptr;
		}
	}
	void Deletion()
	{
		node* tempfordel = cursor;
		if (cursor == head_of_notepad)
			return;
		if (tempfordel->right == nullptr)
		{
			cursor = cursor->left;
			cursor->right = nullptr;
			if (tempfordel->up != nullptr)
				tempfordel->up->down = nullptr;
			tempfordel->up = nullptr;
			if (tempfordel->down != nullptr)
				tempfordel->down->up = nullptr;
			tempfordel->down = nullptr;
			delete tempfordel;
		}
		else if (tempfordel->right != nullptr)
		{
			cursor = cursor->left;
			while (tempfordel->right->data != '\n') //exception here
			{
				swap(tempfordel->data, tempfordel->right->data);
				tempfordel = tempfordel->right;
				if (tempfordel->right == nullptr)
					break;
			}
				tempfordel->left->right = tempfordel->right;
				if (tempfordel->right != nullptr)
					tempfordel->right->left = tempfordel->left;

			if(tempfordel->up!=nullptr)
				tempfordel->up->down = nullptr;
			tempfordel->up = nullptr;
			if(tempfordel->down!=nullptr)
				tempfordel->down->up = nullptr;
			tempfordel->down = nullptr;
			delete tempfordel;
		}
	}
	bool SearchWord(string word)
	{
		node* tempforsearch = head_of_notepad;
		bool wordfound = false;
		for (int i = 0; word[i] != '\0'; )
		{
			if (tempforsearch == nullptr)
				break;
			if (tempforsearch->data == '\n' || tempforsearch->data == '\0')
			{
				i = -1;
				wordfound = false;
			}
			else if (tempforsearch->data == word[i])
			{
				wordfound = true;
			}
			else if (tempforsearch->data != word[i])
			{
				i = -1;
				wordfound = false;
			}
			tempforsearch = tempforsearch->right;
			i++;
			if (word[i] == '\0')
				break;
		}
		if (wordfound == true)
			return wordfound;
		return false;
	}
	void newSearchWord(string word,string replaceWord)
	{
		string temp = "";
		node* lastword = nullptr;
		bool wordfound = false;
		node* tempforsearch = head_of_notepad->right;
		while (tempforsearch != nullptr)
		{
			if (tempforsearch->data != '\n' && tempforsearch->data != ' ')
				temp.append(1, tempforsearch->data);
			else
			{
				if (temp == word)
				{
					wordfound = true;
					cursor = tempforsearch->left;
					break;
				}
				else
					temp = "";
			}

			if (tempforsearch->right == nullptr)
				lastword = tempforsearch;
			tempforsearch = tempforsearch->right;
		}
		if (temp == word)
		{
			if (tempforsearch == nullptr)
				cursor = lastword;
			replace(word, replaceWord);
		}
		else
			return;
	}
	void replace(string word,string replaceWord)
	{
		int len = word.length();
		for (int i = 0; i < len; i++)
		{
			Deletion();
		}
		for (int i = 0; i < replaceWord.length(); i++)
		{
			insertion(replaceWord[i]);
		}
	}
	void setCursor()
	{
		node* ptr = head_of_notepad->right;
			destcord.X = 0;
			destcord.Y = 0;
		while (ptr != nullptr)
		{
			if (ptr->data == '\n')
			{
				destcord.X = 0;
				destcord.Y++;
			}
			else
			{
				destcord.X++;
			}
			if (ptr == cursor)
				return;
			ptr = ptr->right;
		}
	}
};
int main()
{
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	destcord.X = 0;
	destcord.Y = 0;
	NotePad obj;
	char temp=NULL;
	while (1)
	{
		SetConsoleCursorPosition(hstdout, destcord);
		temp = _getch();
		if ((int)temp == (-32))
			obj.MoveCursor();
		else if (temp=='\b')
		{
			obj.Deletion();
			system("CLS");
			obj.Print_Text();
		}
		else if (temp == '\x12')
		{
			string tempword;
			string newword;
			cout << "\nEnter the word to find: ";
			getline(cin, tempword);
			cout << endl;
			cout << "Enter word to replace: ";
			getline(cin, newword);
			obj.newSearchWord(tempword,newword);
			system("CLS");
			obj.Print_Text();
		}
		else if (temp == '\x1b')
			break;
		else
		{
			obj.insertion(temp);
			system("CLS");
			obj.Print_Text();
		}
	obj.setCursor();
	}
	//system("CLS");
	//obj.Print_Text();
	system("pause");
}