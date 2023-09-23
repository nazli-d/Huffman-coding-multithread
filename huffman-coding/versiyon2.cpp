#include <fstream>
#include <queue>
#include <iostream>
#include <map>

using namespace std;


struct Node {
    char c;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int freq, Node* left, Node* right) : c(c), freq(freq), left(left), right(right) {}

    ~Node() {
        delete left;
        delete right;
    }
};

struct comp {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

static void encode(Node* root, string str, map<char, string>& huffmanCode) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->c] = str;
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}


void buildHuffman(string& inputFile,  string& outputFile) {
    ifstream inFile(inputFile, ios::in);  
    map<char, int> freq;
    char c;
   
    for (char c; inFile.get(c);) {
    freq[c]++;
    }
    inFile.close();

    priority_queue<Node*, vector<Node*>, comp> pq;
    for ( auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second, nullptr, nullptr));
    }
    
    for (int size = pq.size(); size > 1; size = pq.size()) {
    for (int i = 0; i < size - 1; i += 2) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node('$', left->freq + right->freq, left, right);
        pq.push(newNode);
    }
}
    
    inFile.open(inputFile, ios::in);

    map<char, string> huffmanCode;
    encode(pq.top(), "", huffmanCode);

    string compressedText;
    for (char c; inFile.get(c); ) {
        compressedText += huffmanCode[c];
    }

    inFile.close();
    ofstream outFile(outputFile, ios::out);

    for (int i = 0; i < compressedText.length(); i++) {
        outFile.put(compressedText[i]);
    }
    
    cout << "Sıkıştırma işlemi "<< outputFile << " için tamamlandı." << endl;
    outFile.close();
}

int main() {
    
    vector<string> inputFiles = { "input1.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt" };
    vector<string> outputFiles = { "output1.txt", "output2.txt", "output3.txt", "output4.txt", "output5.txt" };

    for (int i = 0; i < inputFiles.size(); i++) {
        buildHuffman(inputFiles[i], outputFiles[i]);
    }

    return 0;
}
