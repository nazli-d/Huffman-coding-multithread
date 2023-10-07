#include <fstream>
#include <iostream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <queue>
using namespace std;

struct Node {
    const char c;
    const int freq;
    Node* const left;
    Node* const right;

    Node(const char c, const int freq, Node* const left, Node* const right) : c(c), freq(freq), left(left), right(right) {}

    ~Node() {
        delete left;
        delete right;
    }
};

struct comp {
    constexpr bool operator()(Node* const left, Node* const right) const {
        return left->freq > right->freq;
    }
};

static void calculateFrequencies(const string& inputFile, unordered_map<char, int>& freq) {
    ifstream inFile(inputFile, ios::in);
    if (!inFile.is_open()) {
        cerr << "Error opening input file: " << inputFile << endl;
        return;
    }

    char c;
     for (char c; inFile.get(c);) {
        freq[c]++;
    }

    inFile.close();
}
static Node* buildHuffmanTree(const unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, comp> pq;
    for (const auto& pair : freq) {
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

    if (pq.empty()) {            //segmentation fault hatasını çözmek için yazdığım kod
        return nullptr; 
    }
    return pq.top();

}


static void encode(const Node* const root, const string str, vector<string>& huffmanCode) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->c] = str;
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void compressFile(const string& inputFile, const string& outputFile) {
    unordered_map<char, int> freq;
    calculateFrequencies(inputFile, freq);

    Node* root = buildHuffmanTree(freq);

    vector<string> huffmanCode(256);
    encode(root, "", huffmanCode);

    ifstream inFile(inputFile, ios::in);
    ofstream outFile(outputFile, ios::out);

    char c;
    for (char c; inFile.get(c);) {
        outFile << huffmanCode[c];
    }

    inFile.close();
    outFile.close();

    delete root;

     cout << "Sıkıştırma işlemi "<< outputFile << " için tamamlandı." << endl;
}

int main() {
    const vector<string> inputFiles = { "input1.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt" };
    const vector<string> outputFiles = { "output1.txt", "output2.txt", "output3.txt", "output4.txt","output5.txt"};

    vector<thread> threads;
    vector<unordered_map<char, int>> freqs(inputFiles.size());
    vector<Node*> roots(inputFiles.size());

    mutex mtx;
    for (int i = 0; i < inputFiles.size(); i++) {                                                                                                                     // Frekans hesaplamasını ve Huffman ağacı oluşturmayı farklı threadlerle gerçekleştiriyor.
        threads.emplace_back([&freqs, &roots, &mtx, i, &inputFiles]() {
            unordered_map<char, int> freq;
            calculateFrequencies(inputFiles[i], freq);

            lock_guard<mutex> lock(mtx);
            freqs[i] = freq;
        });

        threads.emplace_back([&freqs, &roots, &mtx, i]() {
            Node* root = buildHuffmanTree(freqs[i]);

            lock_guard<mutex> lock(mtx);
            roots[i] = root;
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    for (int i = 0; i < inputFiles.size(); i++) {                                                                                                                     
        compressFile(inputFiles[i], outputFiles[i]);
    }

    for (int i = 0; i < roots.size(); i++) {                                                                                                                           
        delete roots[i];
    }

    return 0;
}
