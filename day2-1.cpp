#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void split(string str, string delimiter, vector<string> &result)
{
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  string token;

  while ((pos_end = str.find(delimiter, pos_start)) != string::npos)
  {
    token = str.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    result.push_back(token);
  }

  result.push_back(str.substr(pos_start));
}

int stringToInt(string str)
{
  int num = 0;
  for (int i = 0; i < str.length(); i++)
  {
    char ch = str[i];
    num = (num * 10) + (ch - 48);
  }
  return num;
}

bool isPossible(string draw_res)
{
  vector<string> games;
  split(draw_res, ";", games);

  string num;
  char ch;

  bool isPossible = true;
  for (int i = 0; i < games.size(); i++)
  {
    int draw_qty[] = {0, 0, 0}; // r,b,g

    for (int j = 0; j < games[i].length(); j++)
    {
      ch = games[i][j];
      if (ch >= 47 && ch <= 57)
      {
        num += ch;
      }

      else if (ch == ' ')
      {
        ch = games[i][j + 1];
        if (ch == 'r')
        {
          draw_qty[0] += stringToInt(num);
        }

        else if (ch == 'g')
        {
          draw_qty[1] += stringToInt(num);
        }

        else if (ch == 'b')
        {
          draw_qty[2] += stringToInt(num);
        }

        num = "";
      }
    }
    // 12 red cubes, 13 green cubes, and 14 blue cubes
    if (draw_qty[0] > 12 || draw_qty[1] > 13 || draw_qty[2] > 14)
    {
      isPossible = false;
      break;
    }

  return isPossible;
}

int main()
{
  // get game code -done
  // use brute force technique
  // use semi colon to split game
  // use r g b regex to identify color

  fstream myFile;
  myFile.open("day2.txt", ios::in);

  vector<string> str_arr;
  string cur_str = "";

  while (!myFile.eof())
  {
    getline(myFile, cur_str);
    if (cur_str.length() > 0)
    {
      str_arr.push_back(cur_str);
    }
  }

  int sumPossibleGameID = 0;

  for (int i = 0; i < str_arr.size(); i++)
  {

    vector<string> game;
    split(str_arr[i], ":", game); // game[0]= gameID, game[1]= draws
    int gameID = stringToInt(game[0].substr(5, game[0].length() - 2));

    if (isPossible(game[1]))
    {
      sumPossibleGameID += gameID;
      cout << gameID << endl;
    }
  }

  cout << sumPossibleGameID;
}
