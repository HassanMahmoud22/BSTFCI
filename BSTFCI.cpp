#include <iostream>
using namespace std;
template<class type>
class BSTFCI
{
public:
	class BSTNode
	{
	public:
		BSTNode* left;	
		BSTNode* right;
		type data;

	};
	BSTNode* root;
	BSTNode* newNode;
	BSTNode* current;
	BSTNode* trailCurrent;

	BSTFCI()
	{
		root = NULL;
	}
	void insert(type value)
	{
		newNode = new BSTNode;		//creating new node
		newNode->data = value;
		newNode->left = NULL;
		newNode->right = NULL;
		if (root == NULL)		//if the tree is empty
			root = newNode;		//then the new node will be the root node
		else
		{
			current = root;		//else make the current is the new node
			while (current != NULL)	// while the current node has childs
			{
				trailCurrent = current;		
				if (current->data == value)		//if the node's data = the new node data
				{
					cout << "The insert item is already in the list" << endl;	//print message that duplicate isn't allowed	
					return;
				}
				else if (current->data > value)		// if the current node data is greater than new node data 
					current = current->left;		//then move left
				else
					current = current->right;		//else move to right
			}
			if (trailCurrent->data > value)		//if the last node it's value is greater
				trailCurrent->left = newNode;		//then put the new node in the left
			else
				trailCurrent->right = newNode;		//else put it in the right
		}
	}

	bool isBalanced(BSTNode* theRoot)
	{
		int leftHeight;
		int rightHeight;

		if (theRoot == NULL)
			return 1;			//if the tree has one node return true

		leftHeight = height(theRoot->left);		
		rightHeight = height(theRoot->right);

		if (abs(leftHeight - rightHeight) <= 1 && isBalanced(theRoot->left) && isBalanced(theRoot->right))	//if their height difference is greater than one and every node with it's childs are balanced
			return 1;		//return true


		return 0;		//if it reached here means something doesn't happened from above then return false
	}

	int max(int a, int b)			//function return the maximum number of two numbers
	{
		return (a >= b) ? a : b;
	}

	int height(BSTNode* node)		//function return the height of the tree
	{
		if (node == NULL)	//if passed node is null then return 0
			return 0;

		return 1 + max(height(node->left), height(node->right));	//else return 1 + the maximum height of the two subtrees of the tree
	}
	void testBAlance()		//function to test the balance of the tree
	{
		int num = 0, input = 0;
		cout << "welcome to the Balance test" << endl;
		cout << "please enter the number of nodes of the tree" << endl;
		cin >> num;			//take the number of nodes from user
		cout << "please enter the  " << num << " nodes of the tree" << endl;
		for (int i = 0;i < num; i++)
		{						
			cin >> input;		//take the nodes from the user
			insert(input);		//insert them in the tree
		}
		if (isBalanced(root))		
		{
			cout << "it's balanced tree" << endl;
		}
		else
		{
			cout << "it's not balanced tree" << endl;
		}
	}
	friend bool areIdentical(BSTNode* root1, BSTNode* root2)	//function to check if the subtree is identical from the original tree
	{
		if (root1 == NULL && root2 == NULL)			//if both passed nodes are null then the true trees are identical
			return true;

		if (root1 == NULL || root2 == NULL)			//if one of them is null then they are not identical
			return false;

		return (root1->data == root2->data && areIdentical(root1->left, root2->left) &&	areIdentical(root1->right, root2->right));
	}

	friend bool isSubtree(BSTNode* node1, BSTNode* node2)
	{
		if (node2 == NULL)		//if node2 is null then return true
			return true;

		if (node1 == NULL)		//if node1 is null then return false
			return false;

		if (areIdentical(node1, node2))		//if they are identical then return true
			return true;

		return isSubtree(node1->left, node2) ||	isSubtree(node1->right, node2);        
	}

	void printRange(int min, int max, BSTNode* node)	//function to print range between two numbers
	{
		if (node == NULL)	//if node is null then return
			return;
		if (min < node->data)	//if min is less than the node data
			printRange(min, max, node->left);	//then move left

		if (min <= node->data && max >= node->data)		//if min is <= node data and max is >= node data
			cout << node->data << " ";			//then is data is in the range print it

		if (max > node->data)			//if max is greater than node data
			printRange(min, max, node->right);			//then move right
	}

	void flip(BSTNode* node)
	{
		if (node == NULL)	//if node is null then return
			return;
		else
		{
			BSTNode* temp;		//else create a temp pointer

			flip(node->left);		//then flip both sides
			flip(node->right);

			temp = node->left;			//swap left with right
			node->left = node->right;
			node->right = temp;
		}
	}
	void print(BSTNode* node)		//print inorder traverse
	{
		if (node == NULL)		//if node is null then return
			return;

		print(node->left);		//print left tree
		cout << node->data << " ";	//print data
		print(node->right);
	}
};
int main()			//main to test all functions
{
	BSTFCI<int> obj, obj1, obj2, obj3, obj4;
	BSTFCI<int>::BSTNode* node1;
	BSTFCI<int>::BSTNode* node2;
	BSTFCI<int>::BSTNode* node3;
	BSTFCI<int>::BSTNode* node4;

	obj.testBAlance();		//test balance

	int num = 0, input = 0, min = 0, max = 0;
	cout << "welcome to test if the tree is subtree of another one" << endl;			//test subtree
	cout << "Enter number of nodes of first tree" << endl;
	cin >> num;
	cout << "Enter the " << num << " nodes of the tree " << endl;
	for (int i = 0;i < num; i++)
	{
		cin >> input;
		obj1.insert(input);
	}
	cout << "Enter number of nodes of second tree" << endl;
	cin >> num;
	cout << "Enter the " << num << " nodes of the tree " << endl;
	for (int i = 0;i < num; i++)
	{
		cin >> input;
		obj2.insert(input);
	}
	node1 = obj1.root;
	node2 = obj2.root;
	if (isSubtree(node1, node2))
	{
		cout << "it's subtree" << endl;
	}
	else
	{
		cout << "not subtree" << endl;
	}

	cout << "welcome to test the range of the tree" << endl;			//test the range
	cout << "Enter number of nodes of the tree" << endl;
	cin >> num;
	cout << "Enter the " << num << " nodes of the tree " << endl;
	for (int i = 0;i < num; i++)
	{
		cin >> input;
		obj3.insert(input);
	}
	cout << "Enter the first number " << endl;
	cin >> min;
	cout << "Enter the second number " << endl;
	cin >> max;
	node3 = obj3.root;
	cout << "[" << " ";
	obj3.printRange(min, max, node3);
	cout << "]";
	cout << endl;
	cout << "welcome to the mirror test" << endl;			//test mirror
	cout << "Enter number of nodes of first tree" << endl;
	cin >> num;
	cout << "Enter the " << num << " nodes of the tree " << endl;
	for (int i = 0;i < num; i++)
	{
		cin >> input;
		obj4.insert(input);
	}
	node4 = obj4.root;
	cout << "inorder traverse of tree before mirroring" << endl;
	obj4.print(node4);
	cout << endl;
	obj4.flip(node4);
	cout << "inorder traverse of tree after mirroring" << endl;
	obj4.print(node4);
	return 0;
}
