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

struct Node {
    int id;
    Node* parent;
};

std::vector<int> BFS_Search(int startPage, int endPage, std::unordered_map<int, std::vector<int>>& adjacencyList) {
    std::unordered_set<int> visited;
    std::queue<Node> toVisit;
    std::vector<int> path;

    Node firstNode;
    firstNode.id = startPage;
    firstNode.parent = nullptr;
    toVisit.push(firstNode);

    Node* currNode = &firstNode;
    int iterations = 0;

    while (currNode->id != endPage) {
        // go through the adj list of the current node
        for (int i = 0; i < adjacencyList[currNode->id].size(); i++) {
            //check if it is already in set
            int currId = adjacencyList[currNode->id][i];
            auto it = visited.find(currId);
            if (it == visited.end()) {
                Node newNode;
                newNode.id = adjacencyList[currNode->id][i];
                newNode.parent = currNode;
                toVisit.push(newNode);
                
            }
        }
        visited.insert(currNode->id);
        currNode = &toVisit.front();
        toVisit.pop();
        iterations++;
        std::cout << "Iteration: " << iterations << "\tVisiting: " << currNode->id << "\tTo visit size: " << toVisit.size() << "\tVisited size: " << visited.size() << std::endl;
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
        if (visited.find(u) != visited.end()) continue;

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



int main() {
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

    // Random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, adjacencyList.size() - 1);

    // Select two random different starting and ending URLs
    auto iter = adjacencyList.begin();
    std::advance(iter, distrib(gen));
    int startingURL = iter->first;

    int endingURL;
    do {
        iter = adjacencyList.begin();
        std::advance(iter, distrib(gen));
        endingURL = iter->first;
    } while (startingURL == endingURL);

    std::cout << nameKey[startingURL] << std::endl;
    std::cout << nameKey[endingURL] << std::endl;

    // now call methods to traverse accordingly

    // BFS traversal:
    std::vector<int> BFSpath;

    //TEST from 7 to 6 - 7->5->6
    BFSpath = BFS_Search(21, 18, adjacencyList);

    std::cout << "BFS path: ";
    for (int i = 0; i < BFSpath.size(); i++) {
        std::cout << BFSpath[i] << ", ";
    }

    //DFS
    std::cout << DepthFirstTraversal(adjacencyList, 7, 6).size() - 1 << std::endl;


    return 0;

    // debugging, ensures that each key is populated correctly
    // (THIS ALSO NEEDS TO BE CHANGED SINCE WE NEED TO CREATE OUR OWN DATA STRUCTURE)
    // for (const auto& pair : adjacencyList) 
    // {
    //     // print the key
    //     std::cout << "FromNodeID " << pair.first << " links to: ";
    //     for (const auto& toNodeID : pair.second) 
    //     {
    //         // print the keys values
    //         std::cout << toNodeID << " ";
    //     }
    //     // new line after printing all of the keys values
    //     std::cout << std::endl;
    // }
}


