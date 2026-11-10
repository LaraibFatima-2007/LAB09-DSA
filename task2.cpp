/*
 * Name: Laraib Fatima
 * Class: BSDS 3A
 * Course Instructor: Dr. Fahad Ahmed Satti
 * Lab Engineer: Hassan Mohtashim
 * Date: November 10, 2026
 * Topic: Lab 9 - Task 2: Word Frequency Indexing using BST
 */

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct WordNode {
    string word;
    int count;
    WordNode* left;
    WordNode* right;

    WordNode(string w) {
        word = w;
        count = 1;
        left = NULL;
        right = NULL;
    }
};
string cleanWord(string str) {
    string result = "";
    for (size_t i = 0; i < str.length(); i++) {
        if (isalnum(str[i])) {
            result += tolower(str[i]);
        }
    }
    return result;
}

// Insert word into BST or increment frequency
WordNode* insertWord(WordNode* root, string word) {
    if (word.empty()) return root;

    if (root == NULL) {
        return new WordNode(word);
    }

    if (word < root->word) {
        root->left = insertWord(root->left, word);
    } else if (word > root->word) {
        root->right = insertWord(root->right, word);
    } else {
        root->count++;
    }
    return root;
}

// Display words in alphabetical order
void displayAlphabetical(WordNode* root) {
    if (root == NULL) return;
    displayAlphabetical(root->left);
    cout << root->word << " : " << root->count << endl;
    displayAlphabetical(root->right);
}

int countNodes(WordNode* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void fillArray(WordNode* root, WordNode** arr, int &index) {
    if (root == NULL) return;
    fillArray(root->left, arr, index);
    arr[index++] = root;
    fillArray(root->right, arr, index);
}

void sortByFrequency(WordNode** arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j]->count < arr[j + 1]->count || 
               (arr[j]->count == arr[j + 1]->count && arr[j]->word > arr[j + 1]->word)) {
                WordNode* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Display words sorted by frequency
void displayByFrequency(WordNode* root) {
    int total = countNodes(root);
    if (total == 0) return;

    WordNode** arr = new WordNode*[total];
    int idx = 0;
    fillArray(root, arr, idx);

    sortByFrequency(arr, total);

    cout << "Words sorted by frequency:" << endl;
    for (int i = 0; i < total; i++) {
        cout << arr[i]->word << " : " << arr[i]->count << endl;
    }

    delete[] arr;
}

// Display the word; highest occurrence
void findMostFrequentWord(WordNode* root) {
    int total = countNodes(root);
    if (total == 0) return;

    WordNode** arr = new WordNode*[total];
    int idx = 0;
    fillArray(root, arr, idx);

    int maxFreq = 0;
    for (int i = 0; i < total; i++) {
        if (arr[i]->count > maxFreq) {
            maxFreq = arr[i]->count;
        }
    }

    cout << "Most Frequent Word(s) [Frequency = " << maxFreq << "]:" << endl;
    for (int i = 0; i < total; i++) {
        if (arr[i]->count == maxFreq) {
            cout << "- " << arr[i]->word << endl;
        }
    }

    delete[] arr;
}

//  total unique words and  word count
void getSummary(WordNode* root, int &uniqueWords, int &totalWords) {
    if (root == NULL) return;
    getSummary(root->left, uniqueWords, totalWords);
    uniqueWords++;
    totalWords += root->count;
    getSummary(root->right, uniqueWords, totalWords);
}

int main() {
    string paragraph;
    cout << "Enter a paragraph: ";
    getline(cin, paragraph);

    WordNode* root = NULL;
    string temp = "";
    for (size_t i = 0; i <= paragraph.length(); i++) {
        if (i == paragraph.length() || isspace(paragraph[i])) {
            string cleaned = cleanWord(temp);
            if (!cleaned.empty()) {
                root = insertWord(root, cleaned);
            }
            temp = "";
        } else {
            temp += paragraph[i];
        }
    }

    cout << "\n.. Alphabetical Order .." << endl;
    displayAlphabetical(root);

    cout << "\n.. Sorted By Frequency .." << endl;
    displayByFrequency(root);

    cout << "\n.. Most Frequent Word .." << endl;
    findMostFrequentWord(root);

    int uniqueCount = 0, totalCount = 0;
    getSummary(root, uniqueCount, totalCount);

    cout << "\n...Summary Information .." << endl;
    cout << "Total Unique Words: " << uniqueCount << endl;
    cout << "Total Word Count:   " << totalCount << endl;

    return 0;
}