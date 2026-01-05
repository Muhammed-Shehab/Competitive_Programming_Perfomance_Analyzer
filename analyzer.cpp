#include <bits/stdc++.h>
using namespace std;

struct Problem {
    string id;
    int rating;
    string topic;
    string verdict;
    int timeTaken; // in minutes
};

class CPAnalyzer {
    vector<Problem> problems;
    unordered_map<string, int> totalAttempts;
    unordered_map<string, int> correctAttempts;
    unordered_map<string, int> totalTime;
    map<int, vector<int>> difficultyTimes;
public:
    void loadData(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file\n";
            exit(1);
        }
        string line;
        getline(file, line); // skip header
        while (getline(file, line)) {
            stringstream ss(line);
            Problem p;
            getline(ss, p.id, ',');
            ss >> p.rating;
            ss.ignore();
            getline(ss, p.topic, ',');
            getline(ss, p.verdict, ',');
            ss >> p.timeTaken;
            problems.push_back(p);
        }
        file.close();
    }

    void analyzeTopics() {
        for (auto &p : problems) {
            totalAttempts[p.topic]++;
            totalTime[p.topic] += p.timeTaken;
            if (p.verdict == "AC") {
                correctAttempts[p.topic]++;
            }
        }
    }

    void analyzeDifficulty() {
        for (auto &p : problems) {
            difficultyTimes[p.rating].push_back(p.timeTaken);
        }
    }

    void printTopicStats() {
        cout << "\n=== Topic-wise Performance ===\n";
        for (auto &entry : totalAttempts) {
            string topic = entry.first;
            int total = entry.second;
            int correct = correctAttempts[topic];
            double accuracy = (double)correct / total * 100.0;
            double avgTime = (double)totalTime[topic] / total;
            cout << "Topic: " << topic
                 << " | Accuracy: " << fixed << setprecision(2) << accuracy << "%"
                 << " | Avg Time: " << avgTime << " min\n";
        }
    }

    void printDifficultyStats() {
        cout << "\n=== Difficulty-wise Average Time ===\n";
        for (auto &entry : difficultyTimes) {
            int rating = entry.first;
            auto &times = entry.second;
            double avg = accumulate(times.begin(), times.end(), 0.0) / times.size();
            cout << "Rating " << rating << " -> Avg Time: " << avg << " min\n";
        }
    }

    void recommendPractice() {
        cout << "\n=== Personalized Practice Recommendations ===\n";
        vector<pair<double, string>> score; 
        // higher score = weaker topic
        for (auto &entry : totalAttempts) {
            string topic = entry.first;
            int total = entry.second;
            int correct = correctAttempts[topic];
            double failureRate = 1.0 - (double)correct / total;
            double avgTime = (double)totalTime[topic] / total;
            double weaknessScore = failureRate * avgTime;
            score.push_back({weaknessScore, topic});
        }
        sort(score.rbegin(), score.rend());
        for (auto &entry : score) {
            cout << "Practice more: " << entry.second
                 << " (weakness score = "
                 << fixed << setprecision(2) << entry.first << ")\n";
        }
    }
};

int main() {
    CPAnalyzer analyzer;

    analyzer.loadData("data.csv");

    analyzer.analyzeTopics();
    analyzer.analyzeDifficulty();

    analyzer.printTopicStats();
    analyzer.printDifficultyStats();
    analyzer.recommendPractice();

    return 0;
}
