// Huffman Coding is a lossless data compression algorithm 
// that works by assigning codes to symbols in a way 
// that minimizes the total number of bits required to represent a message.

#include <bits/stdc++.h>
using namespace std;

// A node in the Huffman tree
struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }

    ~Node() {
        delete left;
        delete right;
    }
};

// Compare two nodes based on their frequency
struct Compare {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->freq > rhs->freq;
    }
};

// Build the Huffman tree based on the character frequencies
Node* buildHuffmanTree(const string& text) {
    // Calculate the character frequencies
    unordered_map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }

    // Build the Huffman tree using a priority queue
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& entry : freq) {
        pq.push(new Node(entry.first, entry.second));
    }
    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *parent = new Node('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    // Return the root of the Huffman tree
    return pq.top();
}

// Traverse the Huffman tree and assign codes to characters
void assignCodes(Node* node, string code, unordered_map<char, string>& codes) {
    if (node == nullptr) {
        return;
    }
    if (node->data != '$') {
        codes[node->data] = code;
    }
    assignCodes(node->left, code + "0", codes);
    assignCodes(node->right, code + "1", codes);
}

// Encode the text using the Huffman codes
string encode(const string& text, unordered_map<char, string>& codes) {
    string result;
    for (char c : text) {
        result += codes[c];
    }
    return result;
}

// Decode the encoded text using the Huffman tree
string decode(const string& encodedText, Node* root) {
    string result;
    Node* node = root;
    for (char c : encodedText) {
        if (c == '0') {
            node = node->left;
        } else {
            node = node->right;
        }
        if (node->data != '$') {
            result += node->data;
            node = root;
        }
    }
    return result;
}

int main() {
    string text = "Hello, world!";
    Node* root = buildHuffmanTree(text);
    unordered_map<char, string> codes;
    assignCodes(root, "", codes);
    string encodedText = encode(text, codes);
    string decodedText = decode(encodedText, root);
    cout << "Original text: " << text << endl;
    // Hello, world!
    cout << "Encoded text: " << encodedText << endl;
    // 000111101011101110100100111010000110111010
    cout << "Decoded text: " << decodedText << endl;
    // Hello, world!
    delete root;
    return 0;
}