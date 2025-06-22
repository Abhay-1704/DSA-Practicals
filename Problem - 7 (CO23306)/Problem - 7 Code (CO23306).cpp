/*Roll No :- CO23306
Name :- Abhay Pratap Singh
CCET CSE , 3rd Semester*/

//--------------------Modular program to implement ADT Binary Tree--------------------//

#include <bits/stdc++.h>
using namespace std;

// Define structure for binary tree nodes
struct Node {
    int info;
    Node* LST; // Left Subtree
    Node* RST; // Right Subtree
};

// Function to create a binary tree node
Node* createNode(int info) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->info = info;
    newNode->LST = NULL;
    newNode->RST = NULL;
    return newNode;
}

// Function to calculate height of the tree
int height(Node* node) {
    if (node == NULL) return 0;
    return max(height(node->LST), height(node->RST)) + 1;
}

// Function to print tree in structured format
void printTree(Node* root) {
    if (root == NULL) return;

    int h = height(root);
    int width = (1 << h) - 1;

    vector<vector<string>> tree(h, vector<string>(width, " "));

    queue<pair<Node*, int>> q;
    q.push({root, (width - 1) / 2});

    int level = 0;
    while (!q.empty() && level < h) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            auto [node, col] = q.front();
            q.pop();

            if (node) {
                tree[level][col] = to_string(node->info);
                q.push({node->LST, col - (1 << (h - level - 2))});
                q.push({node->RST, col + (1 << (h - level - 2))});
            }
        }
        level++;
    }

    for (const auto& row : tree) {
        for (const auto& value : row) {
            cout << setw(3) << value;
        }
        cout << endl;
    }
}

//------------------------------Functions For Tree To Traverse------------------------------//

// Function to build the tree recursively
Node* buildTree(const string& prompt) {
    cout << prompt;
    string input;
    cin >> input;

    if (input == "n") {
        return NULL; // Indicate a null node
    }

    int value = stoi(input); // Convert input to integer
    Node* node = createNode(value);
    cout << "Building left subtree of " << value << endl;
    node->LST = buildTree("Enter left child value (or 'n' for NULL): "); // Build left subtree
    cout << "Building right subtree of " << value << endl;
    node->RST = buildTree("Enter right child value (or 'n' for NULL): "); // Build right subtree

    return node;
}

// Function for pre-order traversal
void preorder(Node* node) {
    if (node == NULL) return;
    cout << node->info << " ";
    preorder(node->LST);
    preorder(node->RST);
}

// Function for in-order traversal
void inorder(Node* node) {
    if (node == NULL) return;
    inorder(node->LST);
    cout << node->info << " ";
    inorder(node->RST);
}

// Function for post-order traversal
void postorder(Node* node) {
    if (node == NULL) return;
    postorder(node->LST);
    postorder(node->RST);
    cout << node->info << " ";
}

//------------------------------Functions For Traverse To Tree------------------------------//

// Function to construct binary tree from post-order and in-order traversal
Node* buildTreeFromPostIn(int postOrder[], int inOrder[], int postStart, int postEnd, int inStart, int inEnd) {
    if (postStart > postEnd || inStart > inEnd) {
        return NULL;
    }

    int rootValue = postOrder[postEnd];
    Node* node = createNode(rootValue);

    int inIndex;
    for (int i = inStart; i <= inEnd; i++) {
        if (inOrder[i] == rootValue) {
            inIndex = i;
            break;
        }
    }

    int leftSubtreeSize = inIndex - inStart;

    node->LST = buildTreeFromPostIn(postOrder, inOrder, postStart, postStart + leftSubtreeSize - 1, inStart, inIndex - 1);
    node->RST = buildTreeFromPostIn(postOrder, inOrder, postStart + leftSubtreeSize, postEnd - 1, inIndex + 1, inEnd);

    return node;
}

// Function to construct binary tree from pre-order and in-order traversal
Node* buildTreeFromPreIn(int preOrder[], int inOrder[], int inStart, int inEnd, int& preIndex) {
    if (inStart > inEnd) return NULL;

    Node* node = createNode(preOrder[preIndex++]);

    if (inStart == inEnd) return node;

    int inIndex;
    for (int i = inStart; i <= inEnd; i++) {
        if (inOrder[i] == node->info) {
            inIndex = i;
            break;
        }
    }

    node->LST = buildTreeFromPreIn(preOrder, inOrder, inStart, inIndex - 1, preIndex);
    node->RST = buildTreeFromPreIn(preOrder, inOrder, inIndex + 1, inEnd, preIndex);

    return node;
}

// Function to construct binary tree from preorder and postorder traversal
Node* buildTree(int preorder[], int postorder[], int& preIndex, int postStart, int postEnd, int size) {
    if (preIndex >= size || postStart > postEnd) {
        return NULL;
    }

    Node* node = createNode(preorder[preIndex]);
    preIndex++;

    if (postStart == postEnd || preIndex >= size) {
        return node;
    }

    int leftChildVal = preorder[preIndex];
    int leftSubtreeSize = 0;

    for (int i = postStart; i <= postEnd; i++) {
        if (postorder[i] == leftChildVal) {
            leftSubtreeSize = i - postStart + 1;
            break;
        }
    }

    node->LST = buildTree(preorder, postorder, preIndex, postStart, postStart + leftSubtreeSize - 1, size);
    node->RST = buildTree(preorder, postorder, preIndex, postStart + leftSubtreeSize, postEnd - 1, size);

    return node;
}

// Function to construct binary tree from preorder and postorder traversal
Node* constructTree(int preorder[], int postorder[], int size) {
    int preIndex = 0;
    return buildTree(preorder, postorder, preIndex, 0, size - 1, size);
}

//------------------------------Main Function------------------------------//

int main() {
    Node* root = nullptr; // Initialize root
    int choice;

    do {
        cout << "Main Menu:\n";
        cout << "1: Build and Traverse a Tree\n";
        cout << "2: Construct a Tree from Traversals\n";
        cout << "3: Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
            	
            	//------------Choices For Tree To Traverse------------//
            	
                cout << "Building Tree" << endl;
                cout << "Enter root node value: ";
                int rootValue;
                cin >> rootValue;
                root = createNode(rootValue);
                root->LST = buildTree("Enter left child value of root (or 'n' for NULL): ");
                root->RST = buildTree("Enter right child value of root (or 'n' for NULL): ");
                cout << "Tree Structure:" << endl;
                printTree(root);
                cout << endl;

                int traversalChoice;
                do {
                    cout << "Choose traversal type:\n";
                    cout << "1: Pre-order\n";
                    cout << "2: In-order\n";
                    cout << "3: Post-order\n";
                    cout << "4: Exit to Main Menu\n";
                    cout << "Enter choice: ";
                    cin >> traversalChoice;

                    switch (traversalChoice) {
                        case 1:
                            cout << "Pre-order Traversal: " << endl;
                            preorder(root);
                            cout << "\n" << endl;
                            break;
                        case 2:
                            cout << "In-order Traversal: " << endl;
                            inorder(root);
                            cout << "\n" << endl;
                            break;
                        case 3:
                            cout << "Post-order Traversal: " << endl;
                            postorder(root);
                            cout << "\n" << endl;
                            break;
                        case 4:
                            cout << "Exiting to Main Menu...\n" << endl;
                            break;
                        default:
                            cout << "Invalid choice! Please try again.\n" << endl;
                    }
                } while (traversalChoice != 4);
                break;
            }
            case 2: {
            	
            	//------------Choices For Traverse To Tree------------//
            	
                int subChoice;
                cout << "Choose traversal type:\n";
                cout << "1: Post-order + In-order\n";
                cout << "2: Pre-order + In-order\n";
                cout << "3: Pre-order + Post-order (For Fully Binary Tree Only)\n";
                cout << "Enter choice: ";
                cin >> subChoice;

                int n;
                cout << "Enter number of nodes: ";
                cin >> n;

                int* postOrder = new int[n];
                int* inOrder = new int[n];
                int* preOrder = new int[n];
                int preIndex = 0;

                switch (subChoice) {
                    case 1:
                        cout << "Enter post-order traversal: ";
                        for (int i = 0; i < n; i++) {
                            cin >> postOrder[i];
                        }
                        cout << "Enter in-order traversal: ";
                        for (int i = 0; i < n; i++) {
                            cin >> inOrder[i];
                        }
                        root = buildTreeFromPostIn(postOrder, inOrder, 0, n - 1, 0, n - 1);
                        break;
                    case 2:
                        cout << "Enter pre-order traversal: ";
                        for (int i = 0; i < n; i++) {
                            cin >> preOrder[i];
                        }
                        cout << "Enter in-order traversal: ";
                        for (int i = 0; i < n; i++) {
                            cin >> inOrder[i];
                        }
                        root = buildTreeFromPreIn(preOrder, inOrder, 0, n - 1, preIndex);
                        break;
                    case 3:
                        cout << "Enter pre-order traversal: ";
                        for (int i = 0; i < n; i++) {
                            cin >> preOrder[i];
                        }
                        cout << "Enter post-order traversal: ";
                        for (int i = 0; i < n; i++) {
                            cin >> postOrder[i];
                        }
                        root = constructTree(preOrder, postOrder, n);
                        break;
                    default:
                        cout << "Invalid choice!\n";
                        continue;
                }

                cout << "Tree Structure:" << endl;
                printTree(root);
                cout << endl;

                // Clean up dynamically allocated memory
                delete[] postOrder;
                delete[] inOrder;
                delete[] preOrder;
                break;
            }
            case 3:
            	
            	//------------Exiting The Program------------//
            	
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again.\n" << endl;
        }
    } while (choice != 3);

    return 0;
}