#include <fstream>
#include <queue>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>

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
    constexpr bool operator()( Node* const left,  Node* const right) const {
        return left->freq > right->freq;
    }
};

mutex huffMutex;
mutex freqMutex;

static void encode(const Node* const root, const string str, map<char, string>& huffmanCode) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        lock_guard<mutex> lock(huffMutex);
        huffmanCode[root->c] = str;
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

static Node* buildHuffmanRecursive(priority_queue<Node*, vector<Node*>, comp>& pq) {
    if (pq.size() <= 1) {
        Node* root = pq.top();
        pq.pop();
        return root;
    }

    Node* left = pq.top();
    pq.pop();
    Node* right = pq.top();
    pq.pop();

    Node* newNode = new Node('$', left->freq + right->freq, left, right);
    pq.push(newNode);

    return buildHuffmanRecursive(pq);
}

void buildHuffman(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::in);
    map<char, int> freq;
    char c;

    for (char c; inFile.get(c); ) {
        freq[c]++;
    }
    inFile.close();

    priority_queue<Node*, vector<Node*>, comp> pq;
    for (const auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second, nullptr, nullptr));
    }
  
    if (!pq.empty()) {
        Node* root = buildHuffmanRecursive(pq);
        map<char, string> huffmanCode;
        encode(root, "", huffmanCode);

        inFile.open(inputFile, ios::in);
        string compressedText;
         for (char c; inFile.get(c); ) {
        compressedText += huffmanCode[c];
    }
        inFile.close();

        ofstream outFile(outputFile, ios::out);
        for (const char ch : compressedText) {
            outFile.put(ch);
        }
        outFile.close();

        cout << "Sıkıştırma işlemi " << outputFile << " için tamamlandı." << endl;
    }
}


int main() {
    const vector<string> inputFiles = { "input1.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt" };
    const vector<string> outputFiles = { "output1.txt", "output2.txt", "output3.txt", "output4.txt","output5.txt"};
     
    vector<thread> threads;
    for (int i = 0; i < inputFiles.size(); i++) {
        threads.emplace_back(buildHuffman, ref(inputFiles[i]), ref(outputFiles[i]));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}