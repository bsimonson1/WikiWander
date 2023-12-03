#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <random>

int main() {
    std::ifstream file("C:\\Users\\bengs\\OneDrive\\Desktop\\WikiRace\\wikirace.csv");

    if (!file.is_open()) 
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }


    std::string line;
    // now call respective files to build the data structures maybe we can just do one container but traverse differently
    std::unordered_map<std::string, std::vector<std::string>> adjacencyList;

    while (std::getline(file, line)) 
    {
        std::istringstream ss(line);
        std::string fromNodeID, toNodeID;

        // comma-separated file
        std::getline(ss, fromNodeID, ',');
        std::getline(ss, toNodeID);

        // this adds the toNode to the fromNode key
        adjacencyList[fromNodeID].push_back(toNodeID);
    }

    file.close();

    // Random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, adjacencyList.size() - 1);

    // Select two random different starting and ending URLs
    auto iter = adjacencyList.begin();
    std::advance(iter, distrib(gen));
    std::string startingURL = iter->first;

    std::string endingURL;
    do {
        iter = adjacencyList.begin();
        std::advance(iter, distrib(gen));
        endingURL = iter->first;
    } while (startingURL == endingURL);

    std::cout << startingURL << std::endl;
    std::cout << endingURL << std::endl;

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
