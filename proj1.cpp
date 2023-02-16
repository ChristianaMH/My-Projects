
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <string>
#include <bits/stdc++.h> //replace function
#include "CommandLine.h"
#include "CommandParser.h"

using namespace std;
struct Coach{
    string coach_ID;
    int season;
    string first_name;
    string last_name;
    int season_win;
    int season_loss;
    int playoff_win;
    int playoff_loss;
    string team;
    int win_streak;
};
struct Team{
    string team_ID;
    string location;
    string name;
    string league;
};

vector<Coach> vec_coach;
vector<Team> vec_team;

int add_coach(vector<Coach>& vec_coach, string ID, int season, string first_name, string last_name, int season_win, int season_loss, int playoff_win, int playoff_loss, string team){
    if(season < 0 || season_win < 0 || season_loss < 0 || playoff_win < 0 || playoff_loss < 0){
        cout << "You entered a negative number. Please try again." << endl;
        return 0;
    }
    
    
    vec_coach.push_back(Coach());
    int size = vec_coach.size()-1;
    vec_coach[size].coach_ID = ID;
    vec_coach[size].season = season;
    replace(first_name.begin(), first_name.end(), '+', ' '); // replace all '+' to ' '
    vec_coach[size].first_name = first_name;
    replace(last_name.begin(), last_name.end(), '+', ' '); // replace all '+' to ' '
    vec_coach[size].last_name = last_name;
    vec_coach[size].season_win = season_win;
    vec_coach[size].season_loss = season_loss;
    vec_coach[size].playoff_win = playoff_win;
    vec_coach[size].playoff_loss = playoff_loss;
    vec_coach[size].team = team;
    vec_coach[size].win_streak = (vec_coach[size].season_win - vec_coach[size].season_loss) + (vec_coach[size].playoff_win - vec_coach[size].playoff_loss);

    return 0;
}
int add_team(vector<Team>& vec_team, string ID,string location, string name,string league){
    vec_team.push_back(Team());
    int size = vec_team.size()-1;
    vec_team[size].team_ID = ID;
    replace(location.begin(), location.end(), '+', ' '); // replace all '+' to ' '
    vec_team[size].location = location;
    vec_team[size].name = name;
    vec_team[size].league = league;

    return 0;
}
int load_coaches(vector<Coach>& vec_coach, string file_name){
    ifstream fcoaches;
    int i = 0, j, k, num;
    int flag = 0;
    string line;
    string word;
    bool firstline = true;
    
    fcoaches.open(file_name);

    if(!fcoaches.is_open()){
        printf("error in opening file. Please try again.\n");
        return 1;
    }
    
    while(getline(fcoaches,line)) {
        vec_coach.push_back(Coach());
        if(firstline){
            firstline = false;
            continue;
        }
	    istringstream iss(line);
        
        while(getline(iss,word,',')){
            word = regex_replace(word, regex("^ +| +$|( ) +"), "$1"); //removes leading & trailing whitespaces
            if(flag == 0) vec_coach[j].coach_ID = word;
            else if(flag == 1){
                istringstream(word) >> num;
                vec_coach[j].season = num;
            }
            else if(flag == 2){
                flag++;
                continue;
            }
            else if(flag == 3) vec_coach[j].first_name = word;
            else if(flag == 4) vec_coach[j].last_name = word;
            else if(flag == 5){
                istringstream(word) >> num;
                vec_coach[j].season_win = num;
            }
            else if(flag == 6){
                istringstream(word) >> num;
                vec_coach[j].season_loss = num;
            }
            else if(flag == 7){
                istringstream(word) >> num;
                vec_coach[j].playoff_win = num;
            }
            else if(flag == 8){
                istringstream(word) >> num;
                vec_coach[j].playoff_loss = num;
            }
            else vec_coach[j].team = word;
            vec_coach[j].win_streak = (vec_coach[j].season_win - vec_coach[j].season_loss) + (vec_coach[j].playoff_win - vec_coach[j].playoff_loss);
            flag++;
        }
        flag = 0;
        j++;

    }

    vec_coach.pop_back();

    fcoaches.close();

    return 0;
}
int load_teams(vector<Team>& vec_team, string file_name){
    ifstream fteam;
    int i = 0, j = 0, flag = 0;
    string line;
    string word;
    bool firstline = true;

    fteam.open(file_name);

    if(!fteam.is_open()){
        printf("error in opening file. Please try again.\n");
        return 1;
    }

    while(getline(fteam,line)) {
        vec_team.push_back(Team());
        if(firstline){
            firstline = false;
            continue;
        }
	    istringstream iss(line);
        while(getline(iss,word,',')){
            word = regex_replace(word, regex("^ +| +$|( ) +"), "$1"); //removes leading & trailing whitespace
            if(flag == 0) vec_team[j].team_ID = word;
            else if(flag == 1) vec_team[j].location = word;
            else if(flag == 2) vec_team[j].name = word;
            else vec_team[j].league = word;
            flag++;
        }
        flag = 0;
        j++;
    }

    vec_team.pop_back(); 

    fteam.close();

    return 0;
}
int print_coaches(vector<Coach>& vec_coach){
    for(int i = 0; i < vec_coach.size(); i++ ){ 
        cout << vec_coach[i].coach_ID << " " << vec_coach[i].season << " " << vec_coach[i].first_name << " " << 
        vec_coach[i].last_name << " " << vec_coach[i].season_win << " " << vec_coach[i].season_loss << " " << 
        vec_coach[i].playoff_win << " " << vec_coach[i].playoff_loss << " " << vec_coach[i].team << endl; 
        
    }
    
    return 0;
}
int print_teams(vector<Team>& vec_team){
  
    for(int i = 0; i < vec_team.size(); i++ ){ 
        cout << vec_team[i].team_ID << " " << vec_team[i].location << " " << vec_team[i].name 
        << " " << vec_team[i].league << endl; 
    }

    return 0;
}
int coaches_by_name(vector<Coach>& vec_coach, vector<Team>& vec_team, string last_name){
    if(vec_team.size()==0){
        cout << "No teams found in database. Please try again." << endl;
        return 0;
    }
    replace(last_name.begin(), last_name.end(), '+', ' '); // replace all '+' to ' '
    int flag = 0;
    for(int i = 0; i < vec_coach.size(); i++){
        if(vec_coach[i].last_name == last_name){
            for(int j = 0; j < vec_team.size(); j++){
                if(vec_team[j].team_ID == vec_coach[i].team){
                    cout << vec_coach[i].coach_ID << " " << vec_coach[i].season << " " << vec_coach[i].first_name << " " << 
                    vec_coach[i].last_name << " " << vec_coach[i].season_win << " " << vec_coach[i].season_loss << " " << 
                    vec_coach[i].playoff_win << " " << vec_coach[i].playoff_loss << " " << vec_coach[i].team << " " <<
                    vec_team[j].location <<" "<< vec_team[j].name << endl;
                    flag = 1;
                }
            }

        }
    }
    if(flag == 0) cout << "No coach found. Please try again." << endl;
    return 0;
}
int teams_by_city(vector<Coach>& vec_coach, vector<Team>& vec_team, string city){
    if(vec_coach.size()==0){
        cout << "No coaches found in database. Please try again." << endl;
        return 0;
    }
    replace(city.begin(), city.end(), '+', ' '); // replace all '+' to ' '
    int flag = 0;
    for(int i = 0; i < vec_team.size(); i++){
        if(vec_team[i].location == city){
            for(int j = 0; j < vec_coach.size(); j++){
                if(vec_coach[j].team == vec_team[i].team_ID){
                    cout << vec_team[i].team_ID << " " << vec_team[i].location << " " << 
                    vec_team[i].name << " " << vec_team[i].league << " " << vec_coach[j].last_name 
                    << endl;
                    flag = 1;
                }
            }
        }
    }
    if(flag == 0) cout << "No team found. Please try again." << endl;
    return 0;
}
int best_coach(vector<Coach>& vec_coach, int year){
    int largest = 0;
    int coach_index = 0;
    for(int i = 0; i < vec_coach.size(); i++){
        if((vec_coach[i].season == year) && (vec_coach[i].win_streak > largest)){
            largest = vec_coach[i].win_streak;
            coach_index = i;
        }
    }
    cout << vec_coach[coach_index].first_name << " " << vec_coach[coach_index].last_name << endl;
    return 0;
}
int search_coaches(vector<Coach>& vec_coach, vector<string>& field_line){
    vector<string> field;
    vector<string> value;
    vector<Coach> coach;
    vector<int> position;
    string word;

    int i, j, field_amount = 0;
    for(i = 0, j = 0; i < field_line.size(); i++){
        istringstream iss2(field_line.at(i));
        while(getline(iss2, word, ' ')){
            if(j%2==0){
                field.push_back(word); 
                field_amount++;
            }
            else{
                replace(word.begin(), word.end(), '+', ' ');
                value.push_back(word);
            }
            j++;
        }
    }
    vector<int> pos;
    pos.push_back(-1);
    int s = 0;
    int t = 0;
    int value_int = 0;
    if(field.at(s) == "last_name"){
            for(t = 0; t < vec_coach.size(); t++){
                if(vec_coach[t].last_name == value.at(s)){
                    add_coach(coach,vec_coach[t].coach_ID, vec_coach[t].season, vec_coach[t].first_name,
                    vec_coach[t].last_name, vec_coach[t].season_win, vec_coach[t].season_loss,
                    vec_coach[t].playoff_win, vec_coach[t].playoff_loss, vec_coach[t].team);
                    pos.push_back(t);
                }
            }
    }
    else if(field.at(s) == "first_name"){
            for(t = 0; t < vec_coach.size(); t++){
                if(vec_coach[t].first_name == value.at(s)){
                    add_coach(coach,vec_coach[t].coach_ID, vec_coach[t].season, vec_coach[t].first_name,
                    vec_coach[t].last_name, vec_coach[t].season_win, vec_coach[t].season_loss,
                    vec_coach[t].playoff_win, vec_coach[t].playoff_loss, vec_coach[t].team);
                    pos.push_back(t);
                }
            }
        }
    else if(field.at(s) =="coach"){
            for(t = 0; t < vec_coach.size(); t++){
                if(vec_coach[t].coach_ID == value.at(s)){
                    add_coach(coach,vec_coach[t].coach_ID, vec_coach[t].season, vec_coach[t].first_name,
                    vec_coach[t].last_name, vec_coach[t].season_win, vec_coach[t].season_loss,
                    vec_coach[t].playoff_win, vec_coach[t].playoff_loss, vec_coach[t].team);
                    pos.push_back(t);
                }
            }
        }
    else if(field.at(s) == "season_win"){
            istringstream(value.at(s)) >> value_int;
            for(t = 0; t < vec_coach.size(); t++){
                if(vec_coach[t].season_win == value_int){
                    add_coach(coach,vec_coach[t].coach_ID, vec_coach[t].season, vec_coach[t].first_name,
                    vec_coach[t].last_name, vec_coach[t].season_win, vec_coach[t].season_loss,
                    vec_coach[t].playoff_win, vec_coach[t].playoff_loss, vec_coach[t].team);
                    pos.push_back(t);
                }
            }
        }
    else if(field.at(s) == "season_loss"){
            istringstream(value.at(s)) >> value_int;
            for(t = 0; t < vec_coach.size(); t++){
                if(vec_coach[t].season_loss == value_int){
                    add_coach(coach,vec_coach[t].coach_ID, vec_coach[t].season, vec_coach[t].first_name,
                    vec_coach[t].last_name, vec_coach[t].season_win, vec_coach[t].season_loss,
                    vec_coach[t].playoff_win, vec_coach[t].playoff_loss, vec_coach[t].team);
                    pos.push_back(t);
                }
            }
        }
    else if(field.at(s) == "playoff_win"){
            istringstream(value.at(s)) >> value_int;
            for(t = 0; t < vec_coach.size(); t++){
                if(vec_coach[t].playoff_win == value_int){
                    add_coach(coach,vec_coach[t].coach_ID, vec_coach[t].season, vec_coach[t].first_name,
                    vec_coach[t].last_name, vec_coach[t].season_win, vec_coach[t].season_loss,
                    vec_coach[t].playoff_win, vec_coach[t].playoff_loss, vec_coach[t].team);
                    pos.push_back(t);
                }
            }
        }
    else if(field.at(s) == "playoff_loss"){
            istringstream(value.at(s)) >> value_int;
            for(t = 0; t < vec_coach.size(); t++){
                if(vec_coach[t].playoff_loss == value_int){
                    add_coach(coach,vec_coach[t].coach_ID, vec_coach[t].season, vec_coach[t].first_name,
                    vec_coach[t].last_name, vec_coach[t].season_win, vec_coach[t].season_loss,
                    vec_coach[t].playoff_win, vec_coach[t].playoff_loss, vec_coach[t].team);
                    pos.push_back(t);
                }
            }
        }
    else if(field.at(s) == "team"){
            for(t = 0; t < vec_coach.size(); t++){
                if(vec_coach[t].team == value.at(s)){
                    add_coach(coach,vec_coach[t].coach_ID, vec_coach[t].season, vec_coach[t].first_name,
                    vec_coach[t].last_name, vec_coach[t].season_win, vec_coach[t].season_loss,
                    vec_coach[t].playoff_win, vec_coach[t].playoff_loss, vec_coach[t].team);
                    pos.push_back(t);
                }
            }
        }
    else if(field.at(s) == "season"){
            istringstream(value.at(s)) >> value_int;
            for(t = 0; t < vec_coach.size(); t++){
                if(vec_coach[t].season == value_int){
                    add_coach(coach, vec_coach[t].coach_ID, vec_coach[t].season, vec_coach[t].first_name,
                    vec_coach[t].last_name, vec_coach[t].season_win, vec_coach[t].season_loss,
                    vec_coach[t].playoff_win, vec_coach[t].playoff_loss, vec_coach[t].team);
                    pos.push_back(t);
                }
            }
        }
    else{ 
            return 1;
        } 
    
    field_amount--;

    while(field_amount > 0){
        int number = 0;
        for(int y = 1; y < field.size(); y++){
            if(field.at(y) == "last_name"){
                for(int x = 0; x < coach.size(); x++){
                    if(coach[x].last_name != value.at(y)) pos.erase(pos.begin()+x);
                }
            }
            else if(field.at(y) == "first_name"){
                for(int x = 0; x < coach.size(); x++){
                    if(coach[x].first_name != value[y]) pos.erase(pos.begin()+x);
                }
            }
            else if(field.at(y) == "season"){
                for(int x = 0; x < coach.size(); x++){
                    istringstream(value[y]) >> number;
                    if(coach[x].season != number) pos.erase(pos.begin()+x);
                }
            }
            else if(field.at(y) == "season_win"){
                for(int x = 0; x < coach.size(); x++){
                    istringstream(value[y]) >> number;
                    if(coach[x].season_win != number) pos.erase(pos.begin()+x);
                }
            }
            else if( "season_loss"){
                for(int x = 0; x < coach.size(); x++){
                    istringstream(value[y]) >> number;
                    if(coach[x].season_loss != number) pos.erase(pos.begin()+x);
                }
            }
            else if( "playoff_win"){
                for(int x = 0; x < coach.size(); x++){
                    istringstream(value[y]) >> number;
                    if(coach[x].playoff_win != number) pos.erase(pos.begin()+x);
                }
            }
            else if( "playoff_loss"){
                for(int x = 0; x < coach.size(); x++){
                    istringstream(value[y]) >> number;
                    if(coach[x].playoff_loss != number) pos.erase(pos.begin()+x);
                }
            }
            else if( "coach"){
                for(int x = 0; x < coach.size(); x++){
                    if(coach[x].coach_ID != value[y]) pos.erase(pos.begin()+x);
                }
            }
            else if( "team"){
                for(int x = 0; x < coach.size(); x++){
                    if(coach[x].team != value[y]) pos.erase(pos.begin()+x);
                }
            }
            else{
                return 1;
            }
        }
        field_amount--;    
    }

    if(pos.size() == 1){
        cout << "No match. Please try again." << endl;
        return 0;
    }
    int q;
    for(int g = 1; g < pos.size(); g++){
        q = pos.at(g);
        cout << vec_coach[q].coach_ID << " " << vec_coach[q].season << " " << vec_coach[q].first_name 
        << " " << vec_coach[q].last_name << " " << vec_coach[q].season_win << " " << vec_coach[q].season_loss 
        << " " << vec_coach[q].playoff_win << " " << vec_coach[q].playoff_loss
        << " " << vec_coach[q].team << endl;
    }
    return 0;
}
bool doHelp(){
    cout << "add_coach ID SEASON FIRST_NAME LAST_NAME SEASON_WIN " << endl;
    cout << "          EASON_LOSS PLAYOFF_WIN PLAYOFF_LOSS TEAM - add new coach data" << endl;
    cout << "add_team ID LOCATION NAME LEAGUE - add a new team" << endl;
    cout << "print_coaches - print a listing of all coaches" << endl;
    cout << "print_teams - print a listing of all teams" << endl;
    cout << "coaches_by_name NAME - list info of coaches with the specified name" << endl;
    cout << "teams_by_city CITY - list the teams in the specified city" << endl;
    cout << "load_coaches FILENAME - bulk load of coach info from a file" << endl;
    cout << "load_teames FILENAME - bulk load of team info from a file" << endl;
    cout << "best_coach SEASON - print the name of the coach with the most netwins in a specified season" << endl;
    cout << "search_coaches field=VALUE - print the name of the coach satisfying the specified conditions" << endl;
    cout << "exit - quit the program" << endl;
    return true;
}
void run(){
    cout << "The mini-DB of NBA coaches and teams" << endl;
    cout << "Please enter a command. Enter 'help' for a list of commands." << endl;
    cout << endl << "Enter here: ";

    CommandParser parser;
    CommandLine* in_command = nullptr;
    while((in_command = parser.fetchCommand()) != nullptr){

        if(in_command->getCommand() == "help"){
            doHelp();
        }

        else if(in_command->getCommand() == "add_coach"){
            if(in_command->getParams().size() < 9){
                cout << "9 arguments needed. Please try again." << endl;
                cout << "Enter here: ";
                continue;
            }

            int season, seasonloss, seasonwin, playoffwin, playoffloss;
            string coach = in_command->getParams().at(0);
            string season_yr = in_command->getParams().at(1);
            istringstream(season_yr) >> season;
            string first = in_command->getParams().at(2);
            string last = in_command->getParams().at(3);
            string s_win = in_command->getParams().at(4);
            istringstream(s_win) >> seasonwin;
            string s_loss = in_command->getParams().at(5);
            istringstream(s_loss) >> seasonloss;
            string p_win = in_command->getParams().at(6);
            istringstream(p_win) >> playoffwin;
            string p_loss = in_command->getParams().at(7);
            istringstream(p_loss) >> playoffloss;
            string team = in_command->getParams().at(8);

            add_coach(vec_coach, coach, season, first, last, seasonwin, seasonloss, playoffwin, playoffloss, team);
            cout << endl << "Coach has been successfully added."<< endl;
	    }

        else if(in_command->getCommand() == "add_team"){
            if(in_command->getParams().size() < 4){
                cout << "4 arguments needed. Please try again.";
                cout << "Enter here: ";
                continue;
            }

            string team = in_command->getParams().at(0);
            string location = in_command->getParams().at(1);
            string name = in_command->getParams().at(2);
            string league = in_command->getParams().at(3);

            add_team(vec_team, team, location, name, league);
            cout << endl << "Team has been successfully added." << endl;
		}

        else if(in_command->getCommand() == "print_coaches"){
            print_coaches(vec_coach);
            cout << endl << "Done.";
	    }

        else if(in_command->getCommand() == "print_teams"){
            print_teams(vec_team);
            cout << endl << "Done.";
		}
    
        else if(in_command->getCommand() == "coaches_by_name"){
            if(in_command->getParams().size() < 1){
                cout << "No last name found. Please try again." << endl;
                cout << "Enter here: ";
                continue;
            }

            string last_name = in_command->getParams().at(0);

            coaches_by_name(vec_coach, vec_team, last_name);
	    }

        else if(in_command->getCommand() == "teams_by_city"){
            if(in_command->getParams().size() < 1){
                cout << "No city found. Please try again." << endl;
                cout << "Enter here: ";
                continue;
            }
            string city = in_command->getParams().at(0);

            teams_by_city(vec_coach, vec_team, city);
	    }

        else if(in_command->getCommand() == "load_coaches"){
            if(in_command->getParams().size() < 1){
                cout << "No file name specified. Please try again." << endl;
                cout << "Enter here: ";
                continue;
            }
            string fileName = in_command->getParams().at(0);

            int load = load_coaches(vec_coach, fileName);
            if(load == 0) cout << endl << "Coaches have been loaded successfully into database." << endl;
        }
    
        else if(in_command->getCommand() == "load_teams"){
		    if(in_command->getParams().size() < 1){
                cout << "No file name specified. Please try again." << endl;
                cout << "Enter here: ";
                continue;
            }
            string fileName = in_command->getParams().at(0);

            int load2 = load_teams(vec_team, fileName);
            if(load2 == 0) cout << endl << "Teams have been loaded successfully into database." << endl;
	    }

        else if(in_command->getCommand() == "best_coach"){
      	    if(in_command->getParams().size() < 1){
                cout << "No year specified. Please try again." << endl;
                cout << "Enter here: ";
                continue;
            }
            int year = 0;
            string word = in_command->getParams().at(0);
            istringstream(word) >> year;

            best_coach(vec_coach, year);
	    }
    
        else if(in_command->getCommand() == "search_coaches"){
            if(in_command->getParams().size() < 1){
                cout << "No field specified. Please try again." << endl;
                cout << "Enter here: ";
                continue;
            }
            string field_line;
            vector<string> field;

            for(int i = 0; i < in_command->getParams().size(); i++){
                field_line = in_command->getParams().at(i);
                replace(field_line.begin(), field_line.end(), '=', ' '); // replace all '+' to ' '
                field.push_back(field_line); 
            }

            int ans = search_coaches(vec_coach, field);
            if(ans == 1) cout << "Field cannot be found in database. Please try again." << endl;
	    }

        else if(in_command->getCommand() == "exit"){
			cout << endl << "Exiting database..."<< endl;
            cout << "Done." << endl;
			break;
		}

        else if(in_command->getCommand() == ""){
            continue;
		}

        else{
			cout << "Invalid Command. Please try again." << endl;
        } 

        cout << endl << "Enter here: ";
    }
  return;
}
int main(){
    run();
    return 0;
}
