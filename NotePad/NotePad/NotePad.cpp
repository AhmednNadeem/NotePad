//#include<iostream>
//using namespace std;
//#define escape 27
//struct node
//{
//	char data;
//	node* left;
//	node* right;
//	node* up;
//	node* down;
//	node()
//	{
//		data = '\0';
//		left = right = up = down = nullptr;
//	}
//};
//class NotePad
//{
//	node* head_of_notepad;
//public:
//	NotePad()
//	{
//		head_of_notepad = nullptr;
//	}
//	void insertion(char key)
//	{
//		node* temp = head_of_notepad;
//		node* prevtemphead=head_of_notepad;
//		int prevwordcount = 0;
//		int newwordcount = 0;
//		bool insertion = false;
//		node* ptr = new node;
//		ptr->data = key;
//		ptr->left = ptr->right = ptr->up = ptr->down = nullptr;
//		if (head_of_notepad == nullptr)
//		{
//			head_of_notepad = ptr;
//			prevwordcount++;
//		}
//		else
//		{
//			while (temp->right != nullptr)
//			{
//				if(temp->data!='\n')
//					prevwordcount++;
//				temp = temp->right;
//
//				
//				if (temp->data == '\n')
//				{
//					prevwordcount++;
//					newwordcount = prevwordcount;
//					node*newline = temp->right;
//					while (newline != nullptr)
//					{
//						newwordcount++;
//						newline = newline->right;
//					}
//					int temp2 = newwordcount - prevwordcount;
//
//					int i = 1;
//					while (i <= temp2)
//					{
//						
//						temp = temp->right->right;
//						if (prevtemphead!= nullptr)
//						{
//							temp->up = prevtemphead;
//							prevtemphead->down = temp;
//							prevtemphead = prevtemphead->right;
//
//							temp->right = ptr;
//							ptr->left = temp;
//							insertion = true;
//						}
//						if (temp->right != nullptr)
//							temp = temp->right;
//						i++;
//					}
//					/*while (temp->data != '\n')
//					{
//						temp = temp->right;
//					}*/
//					prevtemphead = temp->up;
//				}
//			}
//			if (insertion == false)
//			{
//				temp->right = ptr;
//				ptr->left = temp;
//			}
//		}
//	}
//	void Print_text()
//	{
//		node* ptr = head_of_notepad;
//		while (ptr != nullptr)
//		{
//			cout << ptr->data;
//			ptr = ptr->right;
//		}
//	}
//};
//int main()
//{
//	NotePad obj;
//	char temp;
//	int i = 1;
//	cout << "Start writing text:" << endl;
//	
//	while (i <= 13)
//	{
//		temp = getchar();
//		if (temp == '\n')
//			obj.insertion('\n');
//		else
//			obj.insertion(temp);
//		i++;
//	}
//	system("CLS");
//	obj.Print_text();
//	cout << temp << endl;
//	system("pause");
//}