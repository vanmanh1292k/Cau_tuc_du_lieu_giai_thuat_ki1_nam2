#include <iostream>
#include <fstream>
#define COUNT 10 
#define MAX 100

using namespace std;

class BST {
    const char* pathInput;
    const char* pathSearch;
    const char* pathDelete;
    int key;
    BST* left, * right;
public:
    // Default constructor.
    BST() : key(0), left(NULL), right(NULL) {}


    // Parameterized constructor.
    BST(int value) {
        key = value;
        left = right = NULL;
    }

    // Get link-path to file Input, Search and Delete
    void getPath(const char* pathInput, const char* pathSearch, const char* pathDelete) {
        this->pathInput = pathInput;
        this->pathSearch = pathSearch;
        this->pathDelete = pathDelete;
    }

    // Insert function.// chèn nút 
    BST* Insert(BST* root, int value) {
        if (!root) {
            // Insert the first node, if root is NULL.
            return new BST(value);
        }

        // Insert key.
        if (value > root->key) {
            // Insert right node key, if the 'value'
            // to be inserted is greater than 'root' node key.

            // Process right nodes.
            root->right = Insert(root->right, value);
        }
        else {
            // Insert left node key, if the 'value'
            // to be inserted is greater than 'root' node key.

            // Process left nodes.
            root->left = Insert(root->left, value);
        }

        // Return 'root' node, after insertion.
        return root;
    }

    // Input key // enter input // nhập key 
    void inputKey(int key[], int n) {
        for (int i = 0; i < n; i++) {
            cout << "Please enter key[" << i + 1 << "]: "; cin >> key[i];
        }
    }

    // Create file inputTree.txt and write all key to file // tạo tệp và thêm các key vào file 
    void createFileInput(int key[], int n) {
        ofstream fo(pathInput, ios::out | ios::app);
        for (int i = 0; i < n; i++) {
            fo << key[i] << " ";
        }
        fo.close();
    }

    // Read file inputTree.txt and insert key to Tree // đọc tệp và chèn key  vào cây 
    BST* readFileInput(BST& tree, int& n) {
        ifstream fi(pathInput);
        BST* root = NULL;
        //string treeTemp;
        int key;

        if (!fi) {
            cout << "File Input not found." << endl;
            return NULL;
        }
        int count = 0;
        while (!fi.eof()) {
            fi >> key;
            if (fi.eof()) break;
            if (count == 0) {
                root = tree.Insert(root, key);
                count++;
            }
            else {
                tree.Insert(root, key);
                count++;
            }
        }
        fi.close();
        n = count;
        return root;
    }

    // create file searchKey.txt
    void createFileSearch(int keySearch) {
        ofstream fo(pathSearch, ios::out | ios::app);
        fo << keySearch << " ";
        fo.close();
    }

    // read file searchKey.txt and search key in Tree
    void readFileSearch(BST* root, BST tree) {
        ifstream fi(pathSearch);
        int keySearch;
        if (!fi) {
            cout << "File Search not found." << endl;
            return;
        }
        while (!fi.eof()) {
            fi >> keySearch;
            if (fi.eof()) break;

            //Search all in file search
            /*if (tree.search(root, keySearch) == NULL)
                cout << keySearch << " does not exist in trees." << endl;
            else
                cout << keySearch << " found in trees." << endl;*/
        }

        //Search only one last elemment in file search
        if (tree.search(root, keySearch) == NULL)
            cout << keySearch << " does not exist in trees." << endl;
        else
            cout << keySearch << " found in trees." << endl;
        fi.close();
    }

    // create file deleteKey.txt
    void createFileDelete(int keyDelete) {
        ofstream fo(pathDelete, ios::out | ios::app);
        fo << keyDelete << " ";
        fo.close();
    }

    // read file deleteKey.txt and delete key in Tree
    void readFileDelete(BST* root, BST tree) {
        ifstream fi(pathDelete);
        int keyDelete;
        if (!fi) {
            cout << "File Delete not found." << endl;
            return;
        }
        while (!fi.eof()) {
            fi >> keyDelete;
            if (fi.eof()) break;
            root = tree.deleteNode(root, keyDelete);
        }
        fi.close();
    }

    // delete 3 file inputTree.txt, searchKey.txt and deleteKey.txt
    void removeAllFile() {
        remove(pathInput);
        remove(pathSearch);
        remove(pathDelete);
    }

    // Function to print binary tree in 2D  
    // It does reverse inorder traversal  (RNL)
    void print2D(BST* root, int space) {
        // Base case  
        if (root == NULL)
            return;

        // Increase distance between levels // tăng khoảng cách giữa các cấp   
        space += COUNT;

        // Process right child first  // xử lí bên phải trước 
        print2D(root->right, space);

        // Print current node after space  
        // count  
        cout << endl;
        for (int i = COUNT; i < space; i++)
            cout << " ";
        cout << root->key << endl;

        // Process left child  // xử lí bên trái
        print2D(root->left, space);
    }


    // Search key in Tree
    BST* search(BST* root, int key) {
        if (root != NULL) {
            if (key == root->key)
                return root;
            if (key < root->key)
                return search(root->left, key);
            else
                return search(root->right, key);
        }
        else return NULL;
    }
    /* Given a non-empty binary search tree, return the node with minimum
    key value found in that tree. Note that the entire tree does not
    need to be searched. */
    BST* minValueNode(BST* root) {
        BST* current = root;

        /* loop down to find the leftmost leaf */
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    // Delete key in Tree
    /* Given a binary search tree and a key, this function deletes the key
and returns the new root */
    BST* deleteNode(BST* root, int key) {
        // base case 
        if (root == NULL) return root;

        // If the key to be deleted is smaller than the root's key, 
        // then it lies in left subtree // nó nằm ở cây con bên trái 
        if (key < root->key)
            root->left = deleteNode(root->left, key);

        // If the key to be deleted is greater than the root's key, 
        // then it lies in right subtree 
        else if (key > root->key)
            root->right = deleteNode(root->right, key);

        // if key is same as root's key, then This is the node 
        // to be deleted 
        else
        {
            // node with only one child or no child 
            if (root->left == NULL)
            {
                BST* temp = root->right;
                free(root); // giải phóng bộ nhớ 
                return temp;
            }
            else if (root->right == NULL)
            {
                BST* temp = root->left;
                free(root);
                return temp;
            }

            // node with two children: Get the inorder successor (smallest 
            // in the right subtree) 
            BST* temp = minValueNode(root->right);

            // Copy the inorder successor's content to this node 
            root->key = temp->key;

            // Delete the inorder successor 
            root->right = deleteNode(root->right, temp->key);
        }
        return root;
    }
};


int main()
{
    BST tree;
    BST* root = NULL;
    int key[MAX], n = 0;
    int keySearch, keyDelete;
    const char* pathInput = "inputTree.txt";
    const char* pathSearch = "searchKey.txt";
    const char* pathDelete = "deleteKey.txt";

    tree.getPath(pathInput, pathSearch, pathDelete); // nhận đường dẫn đến các tệp 

    cout << "Welcome to the binary search tree manager program." << endl;
    while (1) {
        int choose;
        cout << "1. Import elements into tree." << endl;
        cout << "2. Show tree." << endl;
        cout << "3. Search element in tree." << endl;
        cout << "4. Remove the element from the tree." << endl;
        cout << "5. Delete all data and trees." << endl;
        cout << "Please choose: "; cin >> choose;
        switch (choose) {
        case 1:
            cout << "Please numbers of keys: "; cin >> n;
            tree.inputKey(key, n); // cin các ph tử cây 
            tree.createFileInput(key, n); // tạo và ghi các ph tử vào cây 
            root = tree.readFileInput(tree, n); // đọc tệp và chèn key  vào cây 
            break;
        case 2:
            root = tree.readFileInput(tree, n);
            tree.readFileDelete(root, tree);
            if (root == NULL)
                cout << "The tree has nothing!!!" << endl << endl;
            else {
                tree.print2D(root, 0);
            }
            break;
        case 3:
            root = tree.readFileInput(tree, n);
            tree.readFileDelete(root, tree);

            if (root == NULL)
                cout << "The tree has nothing!!!" << endl << endl;
            else {
                cout << "Enter the key to search: "; cin >> keySearch;
                tree.createFileSearch(keySearch);
                tree.readFileSearch(root, tree);
            }
            break;
        case 4:
            if (root == NULL)
                cout << "The tree has nothing!!!" << endl << endl;
            else {
                cout << "Enter the key to delete: "; cin >> keyDelete;
                if (tree.search(root, keyDelete) == NULL)
                    cout << keyDelete << " does not exist in trees." << endl << endl;
                root = tree.deleteNode(root, keyDelete);
                tree.createFileDelete(keyDelete);
                tree.readFileDelete(root, tree);
            }
            break;
        case 5:
            tree.removeAllFile();
            delete root;
            root = NULL;
            break;
        default:
            cout << "You enter wrong! Please try again." << endl;
            break;
        }
        char c;
        cout << "Do you want continue(y/n): "; cin >> c; cout << endl;
        if (c == 'n' || c == 'N') break;
    }
    return 0;
}
