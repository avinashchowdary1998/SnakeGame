#include<ScoreFile.h>

#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>

std::ofstream WriteFile("./scores.txt", std::ofstream::app);
std::ifstream ReadFile;
std::string ScoreLine;

ScoreFile::ScoreFile() {
    std::cout<<"Please Type Your Name"<<std::endl;
    std::getline(std::cin, UserName);
    std::cout<<"Grey Boxes Are Obstacles"<<std::endl;
}

void ScoreFile::WriteScoreToFile(float score)
{
    ScoreFile::score = score;
    if(WriteFile.is_open()) {
        WriteFile<<UserName + "-" + std::to_string(score) + "\n";
        WriteFile.close();

    }
    else {
        std::cout<<"Error while opening the file"<<std::endl;

    }
    ReadScoreFromFile();
}

void ScoreFile::ReadScoreFromFile() {
    ReadFile.open("./scores.txt");
    if(ReadFile.is_open()) {
        while(std::getline(ReadFile, ScoreLine)) {
            int StrPos=ScoreLine.find(":");
            float ScoreOfTheUserFromFile = std::stof(ScoreLine.substr(StrPos+1, ScoreLine.size()));
            std::string NameOfTheUserFromFile = ScoreLine.substr(0, StrPos);
            ScoresSheet.emplace_back(NameOfTheUserFromFile,ScoreOfTheUserFromFile);

        }
        ArrangeScores();

    }
}

void ScoreFile::ArrangeScores() {
    std::sort(ScoresSheet.begin(), ScoresSheet.end(), [](std::pair<std::string, float> score1, std::pair<std::string, float> score2) {return score1.second > score2.second;});
}

void ScoreFile::HighestScore() {
    HighestScoredUser = ScoresSheet.front();

}

ScoreFile::~ScoreFile() {
    HighestScore();
    int NoOfUsers=0;
    if(score > GetHighestScoredUser()->second) {
        std::cout<<"Excellent, You have set a new topscore"<<std::endl;

    }
    else if(score == GetHighestScoredUser()->second) {
        std::cout<<"Good, You have got the score same as Highest score"<<std::endl;

    }
    else {
        std::cout<<"Average, Try Again"<<std::endl;

    }

    std::cout<<"Your Score is "<<score<<" "<<UserName<<std::endl;
    std::cout<<"Total Number Of Times The Snake Game Is Played "<<ScoresSheet.size()<<std::endl;
    std::cout<<"Highest Score Is "<<GetHighestScoredUser()->second<<" by "<<GetHighestScoredUser()->first<<std::endl;

    if(ScoresSheet.size()<5) {
        std::cout<<"Top "<<ScoresSheet.size()<<"scores are: "<<std::endl;
        NoOfUsers = ScoresSheet.size();
    }

    else
    {
        std::cout<<"Top 5 scores are: "<<std::endl;
        NoOfUsers=5;
    }

    for(int i=0; i < NoOfUsers; i++) {
        std::cout<<i+1<<") "<<ScoresSheet[i].first<<": "<<ScoresSheet[i].second<<std::endl;
    }

    
}

void ScoreFile::ShowComputerScore(float score)
{
    std::cout<<"Computer Score is "<<score<<std::endl;
    
}