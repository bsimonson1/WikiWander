#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <random>
#include <queue>
#include <vector>
#include <stack>
#include <set>
#include <chrono>

struct Node {
    int id;
    Node* parent;
};

std::vector<int> BFS_Search(int startPage, int endPage, std::unordered_map<int, std::vector<int>>& adjacencyList) 
{
    std::unordered_set<int> visited;
    std::queue<Node*> toVisit;
    std::vector<int> path;
    std::stack<Node*> allNodes;

    Node* tempNode;
    tempNode = new Node;
    tempNode->id = startPage;
    tempNode->parent = nullptr;
    toVisit.push(tempNode);
    allNodes.push(tempNode);

    Node* currNode = tempNode;

    while (currNode->id != endPage) {
        // go through the adj list of the current node
        for (int i = 0; i < adjacencyList[currNode->id].size(); i++) {
            //check if it is already in set
            int currId = adjacencyList[currNode->id][i];
            auto it = visited.find(currId);
            if (it == visited.end()) {
                tempNode = new Node;
                tempNode->id = currId;
                tempNode->parent = currNode;
                toVisit.push(tempNode);
                visited.insert(currId);
                allNodes.push(tempNode);
            }
        }
        currNode = toVisit.front();
        toVisit.pop();
    }

    std::stack<int> history;
    // go back through the history
    while (currNode != nullptr) {
        history.push(currNode->id);
        currNode = currNode->parent;
    }
    // reverse the order
    while (history.size() != 0) {
        path.push_back(history.top());
        history.pop();
    }

    // DONT FORGET TO DELETE IF USING NEW
    for (int i = 0; i < allNodes.size(); i++) {
        delete allNodes.top();
        allNodes.pop();
    }

    return path;
    
}

std::set<int> DepthFirstTraversal(std::unordered_map<int, std::vector<int>>& adjacencyList, const int startingURL, const int endingURL) {
    std::set<int> visited;
    std::stack<int> s;
    s.push(startingURL);

    while (!s.empty()) 
    {
        int u = s.top();
        s.pop();

        // Check if this node has been visited
        if (visited.find(u) != visited.end())
        {
            continue;
        } 

        // Visit this node
        visited.insert(u);

        // Check if this is the ending URL
        if (u == endingURL) 
        {
            return visited;
        }

        // Iterate over neighbors
        for (const auto& v : adjacencyList[u]) 
        {
            if (visited.find(v) == visited.end()) 
            {
                s.push(v);
            }
        }
    }

    return visited; // If the ending URL is not found
}


int main(int argc, char* argv[]) 
{
    if (argc < 3) 
    {
        std::cerr << "Usage: program <start_url> <end_url>" << std::endl;
        return 1;
    }

    std::string start_url = argv[1];
    std::string end_url = argv[2];

    int startingURL = std::stoi(start_url);
    int endingURL = std::stoi(end_url);
// int main()
// {
//     int startingURL = 7;
//     int endingURL = 200;
    std::ifstream file("C:\\Users\\griff\\OneDrive\\Desktop\\Fall 2023\\DSA\\Final project\\enwiki-2013.csv");
    std::ifstream key("C:\\Users\\griff\\OneDrive\\Desktop\\Fall 2023\\DSA\\Final project\\enwiki-2013-names.csv");

    if (!file.is_open()) 
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;

    // now call respective files to build the data structures maybe we can just do one container but traverse differently
    std::unordered_map<int, std::vector<int>> adjacencyList;

    std::unordered_map<int, std::string> nameKey;

    std::string fromNodeID, toNodeID;
    bool first = true;

    // read in adjacency list
    while (std::getline(file, line)) 
    {
        std::istringstream ss(line);
        
        // comma-separated file
        std::getline(ss, fromNodeID, ',');
        std::getline(ss, toNodeID);

        // this skips the csv header
        if (first) {
            first = false;
            continue;
        }

        // this adds the toNode to the fromNode key
        adjacencyList[std::stoi(fromNodeID)].push_back(std::stoi(toNodeID));
    }
    // max link list length 8104
    file.close();

    //read in name map
    first = true;
    std::string nameId, nameString;
    while (std::getline(key, line)) {

        std::istringstream ss(line);
        
        // comma-separated file
        std::getline(ss, nameId, ',');
        std::getline(ss, nameString);

        // this skips the csv header
        if (first) {
            first = false;
            continue;
        }

        nameKey[std::stoi(nameId)] = nameString;
    }

    // now call methods to traverse accordingly
    // std::cout << BFS_Search(startingURL, endingURL, adjacencyList).size() - 1 << std::endl;
    // std::cout << DepthFirstTraversal(adjacencyList, startingURL, endingURL).size() - 1 << std::endl;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::seconds;
    using std::chrono::milliseconds;

    /*
    // Timer for BFS
    auto t1 = high_resolution_clock::now();
    int bfs_result_size = BFS_Search(startingURL, endingURL, adjacencyList).size() - 1;
    auto t2 = high_resolution_clock::now();
    auto millis_bfs = duration_cast<milliseconds>(t2 - t1);
    auto seconds_bfs = duration_cast<seconds>(t2 - t1);

    // Timer for DFS
    auto t3 = high_resolution_clock::now();
    int dfs_result_size = DepthFirstTraversal(adjacencyList, startingURL, endingURL).size() - 1;
    auto t4 = high_resolution_clock::now();
    auto millis_dfs = duration_cast<milliseconds>(t4 - t3);
    auto seconds_dfs = duration_cast<seconds>(t4 - t3);

    std::cout << nameKey[startingURL] << std::endl;
    std::cout << nameKey[endingURL] << std::endl;

    // Output results
    std::cout << bfs_result_size << std::endl;
    std::cout << seconds_bfs.count() << std::endl; 
    std::cout << millis_bfs.count() << std::endl;

    std::cout << dfs_result_size << std::endl;
    std::cout << seconds_dfs.count() << std::endl;
    std::cout << millis_dfs.count() << std::endl;
    // std::cout << dfs_duration_seconds << std::endl;
    */
    // lots of tests for comparison of the methods
    int numOfTests = 5;
    int rands[10];

    std::random_device rd;

    std::default_random_engine generator(rd());

    std::uniform_int_distribution<int> distribution(0, 4203323);

    for (int i = 0; i < 10; i++) {
        rands[i] = distribution(generator);
    }

    //put em in a csv
    
    // outFile << "Starting ID,Ending ID,BFS time (ms),DFS time (ms),BFS path,DFSpath\n";
    
    int startID = 0;
    int endID = 0;
    int offset = 0;
    //increment by 10

    // run the tests
    for (int i = 0; i < numOfTests; i++) {
        std::ofstream outFile("wiki_speed_tests.csv", std::ios::app);
        startID = rands[i*2 + offset];
        endID = rands[i*2 + offset + 1];
        if (startID == endID) {
            continue;
        }
        std::cout << "Test " << i + 1 << " in progress..." << std::endl;

        // BFS with timer
        auto t1 = high_resolution_clock::now();
        int bfs_result_size = BFS_Search(startID, endID, adjacencyList).size() - 1;
        auto t2 = high_resolution_clock::now();
        auto millis_bfs = duration_cast<milliseconds>(t2 - t1);

        // DFS with timer
        auto t3 = high_resolution_clock::now();
        int dfs_result_size = DepthFirstTraversal(adjacencyList, startID, endID).size() - 1;
        auto t4 = high_resolution_clock::now();
        auto millis_dfs = duration_cast<milliseconds>(t4 - t3);

        outFile << startID << ",";
        outFile << endID << ",";
        outFile << millis_bfs.count() << ",";
        outFile << millis_dfs.count() << ",";
        outFile << bfs_result_size << ",";
        outFile << dfs_result_size << "\n";
        outFile.close();
    }

    

    std::cout << "\n--DONE--\n";

    return 0;
}
