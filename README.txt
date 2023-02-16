Christiana Hellenbrand

To compile proj1.cpp file, type into the terminal: g++ proj1.cpp CommandLine.cpp CommandParser.cpp -o proj1
To run: ./proj

To run this program, type any of these commands (within the quotation) along with the following information:
1.) "load_coaches <file_name>" : this will load the data from file_name into coaches section of the mini NBA database.
2.) "load_teams <file_name>" : this will load the data from file_name into the teams section of the  mini NBA database.
3.) "print_coaches" : this will print data relating to coaches from the mini NBA database.
4.) "print_teams" : this will print data relating to teams from the mini NBA database.
5.) "add_coaches <coach_ID> <season> <first_name> <last_name> <season_win> <season_loss> <playoff_win> <playoff_loss> <team>" :
        this will add a coach to the database along with its specific attributes.
6.) "add_teams <team_ID> <location> <name> <league>" : this will add a team to the database along with its specific attributes.
7.) "best_coach <year>" : this will print the coach with the most net wins based on a specific year/season.
8.) "coaches_by_name <last_name>" : this will print coaches based on a specific last name.
9.) "teams_by_city <city>" : this will print teams based on a specific city.
10.) "search_coaches <field=value>" : this will print coaches based on one/multiple fields and values.

Important to note:
- Both  data for coaches and teams must be loaded into the database before using "coaches_by_name" or "teams_by_city" command.
