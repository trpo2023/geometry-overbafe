#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int checkPoints(string *str)
{
  int i = 0;
  int count = 0;
  while ((*str)[i] != ')')
  {
    if ((*str)[i] == ',')
      count++;
    i++;
  }

  return count;
}

void setPoint(int *c, string *pointsArray)
{
  (*pointsArray)[(*c)] = '0';
}

int main()
{
  ifstream fin;
  fin.open("geom.txt");
  if (fin.is_open())
  {

    int itemCount = 1;
    while (!fin.eof())
    {
      int pointsCount = 0;

      string str = "";
      string *pt = &str;
      getline(fin, str);
      int c = 0;
      int bracketsStatus = 0;
      string name = "";
      while (str[c] >= 'a' && str[c] <= 'z')
      {
        name = name + str[c];
        c++;
      }
      if (name.compare("circle") == 0)
      {
        bracketsStatus = str[c] == '(' ? 1 : 0;
        //str[c] == '(' ? bracketsStatus = 1 : bracketsStatus = 0;
        c++;
      }
      else if (name.compare("triangle") == 0)
      {
        str[c] == '(' && str[c + 1] == '(' ? bracketsStatus = 2 : bracketsStatus = 0;
        c += 2;
      }
      else
      {
        cout << str << endl;

        cout << "Error at column 0: expected 'circle', 'triangle'" << endl;
        exit(0);
      }

      if (bracketsStatus == 0)
      {
        cout << str << endl;

        cout << "Error at column " << c << ": expected '('" << endl;
        exit(0);
      }
      pointsCount = checkPoints(pt);

      string *pointsArray = new string[pointsCount + 1];
      for (int i = 0; i < pointsCount + 1; i++)
      {
        string item = "";
        do
        {
          if (str[c] >= 'a' && str[c] <= 'z')
          {
            cout << str << endl;
            cout << "Error at column " << c << ": expected '<double>'" << endl;
            exit(0);
          }
          if (!(str[c] == ' ' && str[c - 1] == ','))
          {
            item = item + str[c];
          }
          c++;
        } while (str[c] != ',' && str[c] != ')');
        c++;
        pointsArray[i] = item;
      }
      c--;
      for (int i = 0; i < bracketsStatus - 1; i++)
      {
        if (str[c] != ')')
        {
          cout << str << endl;

          cout << "Error at column " << c << ": expected ) " << endl;
          exit(0);
        }
      }
      if (name.compare("triangle") == 0)
      {
        if (pointsArray[0].compare(pointsArray[pointsCount]) != 0)
        {
          cout << str << endl;
          cout << "Error at column " << c << " first and last points not same " << endl;
          exit(0);
        }
      }
      cout << itemCount << " - ";
      cout << name;
      for (int i = 0; i < bracketsStatus; i++)
      {
        cout << "(";
      }
      for (int i = 0; i < pointsCount + 1; i++)
      {
        if (i == pointsCount - 1)
        {
          cout << pointsArray[i] << ",";
        }
        else
        {
          cout << pointsArray[i];
        }
      }
      for (int i = 0; i < bracketsStatus; i++)
      {
        cout << ")";
      }
      cout << "\n";
      itemCount++;
    }
  }
  else
  {
    cout << "Error: wrong path file" << endl;
  }
  fin.close();

  return 0;
}