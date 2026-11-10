/*
 * Name: Laraib Fatima
 * Class: BSDS 3A
 * Course Instructor: Dr. Fahad Ahmed Satti
 * Lab Engineer: Hassan Mohtashim
 * Date: 10-10-26
 * Topic: Lab 9 - Task 1: Range Query and Successor/Predecessor Finder using BST
 */

#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

Node* insert(Node* root, int val) {
    if (root == NULL) {
        return new Node(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}
// Inorder Traversal
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Predecessor and Successor
void findPredecessorSuccessor(Node* root, Node*& pred, Node*& succ, int key) {
    if (root == NULL) return;

    if (root->data == key) {
        // Predecessor= Maximum value in left subtree
        if (root->left != NULL) {
            Node* temp = root->left;
            while (temp->right != NULL)
                temp = temp->right;
            pred = temp;
        }
        // Successor=Minimum value in right subtree
        if (root->right != NULL) {
            Node* temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            succ = temp;
        }
        return;
    }
    if (key < root->data) {
        succ = root;
        findPredecessorSuccessor(root->left, pred, succ, key);
    } else {
        pred = root;
        findPredecessorSuccessor(root->right, pred, succ, key);
    }
}

void rangeQueryRecursive(Node* root, int low, int high, int &compCount) {
    if (root == NULL) return;

    compCount++;
    if (low < root->data) {
        rangeQueryRecursive(root->left, low, high, compCount);
    }

    compCount++;
    if (root->data >= low && root->data <= high) {
        cout << root->data << " ";
    }

    compCount++;
    if (high > root->data) {
        rangeQueryRecursive(root->right, low, high, compCount);
    }
}

// Stack Structure for Iterative Range Query
struct StackNode {
    Node* treeNode;
    StackNode* next;
    StackNode(Node* tNode) {
        treeNode = tNode;
        next = NULL;
    }
};

void push(StackNode*& top, Node* tNode) {
    StackNode* newNode = new StackNode(tNode);
    newNode->next = top;
    top = newNode;
}

Node* pop(StackNode*& top) {
    if (top == NULL) return NULL;
    StackNode* temp = top;
    Node* res = temp->treeNode;
    top = top->next;
    delete temp;
    return res;
}

bool isEmpty(StackNode* top) {
    return top == NULL;
}
void rangeQueryIterative(Node* root, int low, int high, int &compCount) {
    StackNode* stack = NULL;
    Node* curr = root;

    while (curr != NULL || !isEmpty(stack)) {
        while (curr != NULL) {
            push(stack, curr);
            curr = curr->left;
        }
        curr = pop(stack);
        compCount++;
        if (curr->data >= low && curr->data <= high) {
            cout << curr->data << " ";
        }
        compCount++;
        if (curr->data > high) {
            while (!isEmpty(stack)) pop(stack);
            break;
        }
        curr = curr->right;
    }
}

int main() {
    Node* root = NULL;
    int initialData[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};
    int n = sizeof(initialData) / sizeof(initialData[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, initialData[i]);
    }

    cout << ".... Binary Search Tree Inorder Traversal..... " << endl;
    inorder(root);
    cout << endl << endl;

    // Predecessor / Successor Lookup
    int targetKey;
    cout << "Enter key to find predecessor and successor: ";
    cin >> targetKey;

    Node* pred = NULL;
    Node* succ = NULL;
    findPredecessorSuccessor(root, pred, succ, targetKey);

    cout << "\nResults for Key = " << targetKey << ":" << endl;
    cout << "Predecessor: " << (pred ? to_string(pred->data) : "None") << endl;
    cout << "Successor:   " << (succ ? to_string(succ->data) : "None") << endl << endl;

    int low, high;
    cout << "Enter range: ";
    cin >> low >> high;

    int compRec = 0;
    cout << "\n[Recursive] Range Query [" << low << ", " << high << "]: ";
    rangeQueryRecursive(root, low, high, compRec);
    cout << "\nRecursive Comparisons Count: " << compRec << endl;

    int compIter = 0;
    cout << "\n[Iterative] Range Query [" << low << ", " << high << "]: ";
    rangeQueryIterative(root, low, high, compIter);
    cout << "\nIterative Comparisons Count: " << compIter << endl;

    return 0;
}