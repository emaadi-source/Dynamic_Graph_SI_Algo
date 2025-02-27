#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;


struct Pass {
    int startTime;
    int endTime;
    int senderID;
    int receiverID;
};


vector<Pass> loadPassesFromFile(const string& fileName) {
    ifstream inputFile(fileName);
    vector<Pass> passes;
    string line;

   
    if (!inputFile.is_open()) {
        cerr << "Error: Couldn't open the file \"" << fileName << "\".\n";
        return passes;
    }

    
    getline(inputFile, line);

    
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string value;
        Pass pass;

        getline(ss, value, ',');
        pass.startTime = stoi(value);

        getline(ss, value, ',');
        pass.endTime = stoi(value);

        getline(ss, value, ',');
        pass.senderID = stoi(value);

        getline(ss, value, ',');
        pass.receiverID = stoi(value);

        
        if (pass.senderID > 0 && pass.receiverID > 0) {
            passes.push_back(pass);
        }
        else {
            cerr << "Invalid data: Sender=" << pass.senderID
                << ", Receiver=" << pass.receiverID << ". Skipping.\n";
        }
    }

    inputFile.close();
    return passes;
}


void groupPassesIntoMatches(vector<Pass>& passes, vector<vector<Pass>>& matches, int matchLimit = 14) {
    while (!passes.empty() && matches.size() < matchLimit) {
        vector<Pass> currentMatch;
        Pass currentPass = passes[0];
        currentMatch.push_back(currentPass);
        passes.erase(passes.begin());

        while (true) {
            bool found = false;
            for (auto    it = passes.begin(); it != passes.end(); ++it) {
                if (it->startTime >= currentPass.endTime && it->senderID == currentPass.receiverID) {
                    currentPass = *it;
                    currentMatch.push_back(currentPass);
                    passes.erase(it);
                    found = true;
                    break;
                }
            }
            if (!found) break;
        }

        matches.push_back(currentMatch);
    }
}


void generateFilesForMatches(const vector<vector<Pass>>& matches, const unordered_set<int>& teamAPlayers) {
    for (size_t matchNumber = 0; matchNumber < matches.size(); ++matchNumber) {
        ofstream teamAFile("dg" + to_string(matchNumber * 2 + 1) + ".txt");
        ofstream teamBFile("dg" + to_string(matchNumber * 2 + 2) + ".txt");

        
        teamAFile << 14 << "\n";
        teamBFile << 14 << "\n";

        for (int i = 0; i < 14; ++i) {
            teamAFile << i << " \"V" << i + 1 << "\"\n";
            teamBFile << i << " \"V" << i + 1 << "\"\n";
        }

        vector<int> teamAEdges(14, 0);
        vector<int> teamBEdges(14, 0);

        
        for (const auto& pass : matches[matchNumber]) {
            if (teamAPlayers.count(pass.senderID) && teamAPlayers.count(pass.receiverID)) {
                if (pass.senderID - 1 >= 0) {
                    teamAEdges[pass.senderID - 1]++;
                }
            }
            else if (!teamAPlayers.count(pass.senderID) && !teamAPlayers.count(pass.receiverID)) {
                if (pass.senderID - 15 >= 0) {
                    teamBEdges[pass.senderID - 15]++;
                }
            }
        }

      
        for (int i = 0; i < 14; ++i) {
            teamAFile << teamAEdges[i] << "\n";
            for (const auto& pass : matches[matchNumber]) {
                if (teamAPlayers.count(pass.senderID) && pass.senderID - 1 == i) {
                    teamAFile << pass.senderID - 1 << " " << pass.receiverID - 1 << "\n";
                }
            }
        }

     
        for (int i = 0; i < 14; ++i) {
            teamBFile << teamBEdges[i] << "\n";
            for (const auto& pass : matches[matchNumber]) {
                if (!teamAPlayers.count(pass.senderID) && pass.senderID - 15 == i) {
                    teamBFile << pass.senderID - 15 << " " << pass.receiverID - 15 << "\n";
                }
            }
        }

        teamAFile.close();
        teamBFile.close();
    }
}

int main() {
    string inputFile = "passes1.csv";

    
    unordered_set<int> teamAPlayers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

   
    vector<Pass> allPasses = loadPassesFromFile(inputFile);

    if (allPasses.empty()) {
        cerr << "No valid data found. Exiting.\n";
        return 1;
    }

    
    vector<vector<Pass>> matches;
    groupPassesIntoMatches(allPasses, matches);

    
    generateFilesForMatches(matches, teamAPlayers);

    cout << "All files for Team A and Team B have been successfully generated.\n";
    return 0;
}