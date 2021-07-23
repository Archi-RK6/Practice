#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <mutex>

using namespace std;

int R1=9, G1=5, N1=24; //начальные данные 
                                               
double random(double min, double max)
{
    return (1000000000./RAND_MAX)*(max - min) + min;  //случайное вещ. число
}

mutex mtx;

class Cash 
{
  private:
    double x;
    double y; 
  public:
    Cash(double a, double b) {x = a; y = b;};
    void service(); 
    void vhod(double);
    void vihod(double, ofstream&);

    vector<int> line; 
    vector<double> Smoment; 
    vector<int> gate;
    vector<double> Emoment;        
};


void Cash::service() //Вычисление времени, в которое транзакт закончит обслуживаться
{
  double time = random (x, y);

  Smoment.push_back(Emoment.back() + time); 
}


 void Cash::vihod(double entry_time, ofstream& f) //удаление транзактов, обслуживание которых закончилось, из очереди на обслуживание 
{
    mtx.lock();
  if (Smoment.empty()==false) 
  {
    for (int i = 0; i < Smoment.size();)
    {
      if (entry_time > Smoment[i]) 
      {
        f << "В момент времени " << Smoment.front() << " транзакт с идентификатором " << line.front() << " вышел из модели.\n";
        Smoment.erase(Smoment.begin()+i); 
        line.erase(line.begin()+i);
      }
      else 
      {
        ++i;
      }
    }
  }
      mtx.unlock();
}


 void Cash::vhod(double entry_time) // удаление транзактов , обслуживание которых началось, из очереди на вход 
{
   mtx.lock(); 
  if (Emoment.empty()==false) 
  {        
    for (int i = 0; i < Emoment.size();) 
    {
      if (entry_time > Emoment[i] )
      {
        Emoment.erase(Emoment.begin()+i); 
        gate.erase(gate.begin()+i);   
      }
      else 
      {
        ++i;
      }      
    }
  }
    mtx.unlock();
}


int main () 
{
  srand((unsigned int)time(0));


  ofstream fout;
  fout.open("result.txt", ios::trunc);


  int number = 0;
  double entry_time = 0;

  Cash q1 (R1, N1); // первая касса 
  Cash q2 (G1, N1); // вторая касса

  while ((entry_time += random(0, N1))<90) 
  {

    number++;

    thread th1 ([&]()
              {
                q1.vhod(entry_time);
              });

    thread th2 ([&]()
              {
                q2.vhod(entry_time);
              });

    thread th3 ([&]()
              {
                q1.vihod(entry_time, fout);
              });

        thread th4 ([&]()
              {
                q2.vihod(entry_time, fout); 
              });

    th1.join();
    th2.join();
    th3.join();
    th4.join();

    if (q2.line.size() < q1.line.size()) 
    {
      fout << "В момент времени " << entry_time << " транзакт с идентификатором " << number << " вошёл в модель.\n";
      fout << "В момент времени " << entry_time << " транзакт с идентификатором " << number << " встал в очередь 2.\n";

      q2.line.push_back(number);//запись номера текущего транзакта 

      if (q2.Emoment.empty()==false) 
      { 
        q2.Emoment.push_back(q2.Smoment.back()); 
        q2.gate.push_back(number);
      }
      else 
      {
        q2.Emoment.push_back(entry_time);
        q2.gate.push_back(number);
      }
      q2.service();
    }
    else 
      {
        fout << "В момент времени " << entry_time << " транзакт с идентификатором " << number << " вошёл в модель.\n";
        fout << "В момент времени " << entry_time << " транзакт с идентификатором " << number << " встал в очередь 1.\n";

        q1.line.push_back(number);//запись номера текущего транзакта

        if (q1.Emoment.empty()==false) 
        {
          q1.Emoment.push_back(q1.Smoment.back());
          q1.gate.push_back(number);
        }
        else 
        {
          q1.Emoment.push_back(entry_time);
          q1.gate.push_back(number);
        } 
        q1.service();
      }
  }
  fout<<"ВРЕМЯ РАБОТЫ МОДЕЛИ ЗАКОНЧЕНО!"<<endl;
  fout.close();
  return 0;
}
