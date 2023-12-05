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
        // pop node from stack to check
        int u = s.top();
        s.pop();
        //check if already visited
        if (visited.find(u) != visited.end())
        {
            continue;
        } 
        // if not visited, insert it to the visisted container
        visited.insert(u);
        // check complete condition
        if (u == endingURL) 
        {
            return visited;
        }
        // if not complete and not visisted, iterate through the nodes values and explore the first one
        for (const auto& v : adjacencyList[u]) 
        {
            if (visited.find(v) == visited.end()) 
            {
                s.push(v);
            }
        }
    }

    return visited; 
}

bool isDigit(std::string& word)
{
    for (char character : word)
    {
        if (!isdigit(character))
        {
            return false;
        }
    }
    return true;
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

    // int startingURL = std::stoi(start_url);
    // int endingURL = std::stoi(end_url);
// int main()
// {
//     // int startingURL = 7;
//     // int endingURL = 200;
//     std::string start_url = "Talageh";
//     std::string end_url = "Talageh-ye Sofla, Khuzestan";

    std::ifstream file("C:\\Users\\bengs\\OneDrive\\Desktop\\WikiWander\\sites.csv");
    std::ifstream key("C:\\Users\\bengs\\OneDrive\\Desktop\\WikiWander\\enwiki-2013-names.csv");

    if (!file.is_open()) 
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;

    // now call respective files to build the data structures maybe we can just do one container but traverse differently
    std::unordered_map<int, std::vector<int>> adjacencyList;

    //std::unordered_map<int, std::string> nameKey;

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
    // first = true;
    // std::string nameId, nameString;
    // while (std::getline(key, line)) {

    //     std::istringstream ss(line);
        
    //     // comma-separated file
    //     std::getline(ss, nameId, ',');
    //     std::getline(ss, nameString);

    //     // this skips the csv header
    //     if (first) {
    //         first = false;
    //         continue;
    //     }

    //     nameKey[std::stoi(nameId)] = nameString;
    // }
    int startingURL;
    int endingURL;
    std::unordered_map<std::string, int> nameKey;
    std::unordered_map<int, std::string> idKey;
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

        idKey[std::stoi(nameId)] = nameString;

        if (!nameString.empty() && nameString.front() == '\"') 
        {
            nameString.erase(0, 1);
        }
        if (!nameString.empty() && nameString.back() == '\"') 
        {
            nameString.pop_back(); 
        }

        nameKey[nameString] = std::stoi(nameId);
    }

    if (isDigit(start_url))
    {
        startingURL = std::stoi(start_url);
        start_url = idKey[std::stoi(start_url)];
    }
    else 
    {
        startingURL = nameKey[start_url];
    }
    if (isDigit(end_url))
    {
        endingURL = std::stoi(end_url);
        end_url = idKey[std::stoi(end_url)];
    }
    else 
    {
        endingURL = nameKey[end_url];
    }

    // std::cout << startingURL << std::endl;
    // std::cout << endingURL << std::endl;

    // now call methods to traverse accordingly
    // std::cout << BFS_Search(startingURL, endingURL, adjacencyList).size() - 1 << std::endl;
    // std::cout << DepthFirstTraversal(adjacencyList, startingURL, endingURL).size() - 1 << std::endl;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::seconds;
    using std::chrono::milliseconds;

    // Timer for BFS
    auto t1 = high_resolution_clock::now();
    std::vector<int> bfs_results = BFS_Search(startingURL, endingURL, adjacencyList);
    int bfs_result_size = bfs_results.size() - 1;
    auto t2 = high_resolution_clock::now();
    auto millis_bfs = duration_cast<milliseconds>(t2 - t1);
    auto seconds_bfs = duration_cast<seconds>(t2 - t1);

    // Timer for DFS
    auto t3 = high_resolution_clock::now();
    int dfs_result_size = DepthFirstTraversal(adjacencyList, startingURL, endingURL).size() - 1;
    auto t4 = high_resolution_clock::now();
    auto millis_dfs = duration_cast<milliseconds>(t4 - t3);
    auto seconds_dfs = duration_cast<seconds>(t4 - t3);

    std::cout << start_url << std::endl;
    std::cout << end_url << std::endl;

    // Output results
    std::cout << bfs_result_size << std::endl;
    std::cout << seconds_bfs.count() << std::endl; 
    std::cout << millis_bfs.count() << std::endl;

    std::cout << dfs_result_size << std::endl;
    std::cout << seconds_dfs.count() << std::endl;
    std::cout << millis_dfs.count() << std::endl;
    // std::cout << dfs_duration_seconds << std::endl;
    int counter = 0;
    if (bfs_result_size <= 10)
    {
        for (const auto& path : bfs_results)
        {
            if (counter == bfs_result_size)
            {
                std::cout << idKey[path];
            }
            else 
            {
                std::cout << idKey[path] << " -> ";
            }
            counter++;
        }
    }
    return 0;
}
