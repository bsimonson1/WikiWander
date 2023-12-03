#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <random>

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
