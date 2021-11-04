#include<iostream>
#include<queue>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
};

Node* newNode(int data) {
	struct Node* tmp = new Node();
	tmp->data = data;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}


//insert 1 node into the tree
Node* insertNode(Node* root, int data) {
	if (root == NULL)
		return newNode(data);

	/* Otherwise, recur down the tree */
	if (data < root->data)
		root->left = insertNode(root->left, data);
	else
		root->right = insertNode(root->right, data);

	/* return the (unchanged) node pointer */
	return root;
}


//.determine the height of the tree
int height(Node* node) {
	if (node == NULL) {
		return 0;
	}
	else {
		int left;
		int right;
		left = height(node->left);
		right = height(node->right);
		if (left > right) {
			return left + 1;
		}
		else {
			return right + 1;
		}
	}
}


//determine the number of elements in the tree
int numberOfNode(Node* node) {
	int count = 1;
	if (node == NULL) {
		return 0;
	}
	else {
		count += numberOfNode(node->left);
		count += numberOfNode(node->right);
	}
	return count;
}




void printNode(Node* node) {
	if (node == NULL) {
		return;
	}
	else {
		if (height(node->left) == height(node->right) && numberOfNode(node->left) == numberOfNode(node->right)) {
			cout << node->data;
		}
		else {
			printNode(node->right);
			printNode(node->left);
		}
	}
}


// print the number of leaves with a positive value
int numberOfPositiveLeaves(Node* node) {
	int count = 0;
	if (node == NULL) {
		return 0;
	}
	else {
		if (node->left != NULL || node->right != NULL) {
			count += numberOfPositiveLeaves(node->left);
			count += numberOfPositiveLeaves(node->right);
		}
		else if (node->left == NULL && node->right == NULL && node->data > 0) {
			count++;
		}
	}
	return count;
}



//print the number of buttons with the same value
int notesOfTheSameValue(Node* node, int data) {
	int count = 0;
	if (node == NULL) {
		return 0;
	}
	else {
		if (node->data != data) {
			count += notesOfTheSameValue(node->left, data);
			count += notesOfTheSameValue(node->right, data);
		}
		else if (node->data == data) {
			count += notesOfTheSameValue(node->left, data);
			count += notesOfTheSameValue(node->right, data);
			count++;
		}
	}
	return count;
}



//print values traverse from right to left
void printRightToLeft(Node* node) {
	if (node != NULL) {
		cout << node->data << " ";
		printRightToLeft(node->right);
		printRightToLeft(node->left);
	}
}



void printTree(Node* root, int level) {
	if (root) {
		printTree(root->right, level + 1);
		for (int i = 0; i < level; ++i)
			cout << "    ";
		cout << root->data << endl;
		printTree(root->left, level + 1);
	}
}


//double the value of nodes, traverse the tree by width
void printLevelOrder(Node* root) {
	if (root == NULL) return;
	queue<Node*> bf_queue;
	bf_queue.push(root);
	/* The loop ends when the queue is empty */
	while (!bf_queue.empty()) {
		Node* current = bf_queue.front();
		bf_queue.pop(); /* Get the first element out of the queue */
		current->data = (current->data) * 2;
		cout << current->data << ", ";
		/* Enqueue the left and right children of current into bf_queue.*/
		if (current->left != NULL) {
			bf_queue.push(current->left);
		}
		if (current->right != NULL) {
			bf_queue.push(current->right);
		}
	}
}

int main() {
	Node* root = NULL;
	cout << "-------------------Menu-------------------\n";
	cout << "[1] - Insert a node.\n";
	cout << "[2] - Print the number of leaves with a positive value.\n";
	cout << "[3] - Print a tree.\n";
	cout << "[4] - Calculate the number of nodes with the same value.\n";
	cout << "[5] - Print the tree after increasing the value of the traversal nodes by width.\n";
	cout << "[0] - Exit program!\n";
	cout << "------------------------------------------\n";


	int choice = 0;
	do
	{
		cout << "Input your choice: ";
		cin >> choice;

		cout << "\n---------------------------------------\n";
		switch (choice)
		{
		case 1:
			cout << "Enter size of tree: ";
			int n;
			cin >> n;
			cout << "Enter the data to insert into the tree: ";
			for (int i = 0; i < n; ++i) {
				int data;
				cin >> data;
				root = insertNode(root, data);
			}
			cout << "Done!";
			break;
		case 2:
			cout << "Number of leaves: " << numberOfPositiveLeaves(root);
			break;

		case 3:
			cout << "Tree: \n";
			printTree(root, 0);
			cout << "print Right to Left: ";
			printRightToLeft(root);
			break;
		case 4:
			cout << "Enter the value n: ";
			cin >> n;
			cout << endl << "Number of nodes with the same value: " << notesOfTheSameValue(root, n) << endl;
			break;
		case 5:
			cout << "traverse the tree by width: ";
			printLevelOrder(root);
			break;
		case 0:
			cout << endl << "Thanks for using program!";
			break;
		default:
			break;
		}
		cout << "\n---------------------------------------\n";
	} while (choice != 0);

	system("pause");
	return 0;
}