#include <iostream>
#include <windows.h>


using namespace std;

//initialise global variables to set up the initial state.
int num = 0;
int data = 0;
int processedData = 0;

//Set up the Machine class
class Machine
{
  class State *current;
  public:
    Machine();
    void setCurrent(State *s)
    {
        current = s;
    }
    void processing();
    void sensing();
    void idle();
};

class State
{
  public:
    virtual void processing(Machine *m)
    {
        cout << "   already Pro\n";
    }
    virtual void sensing(Machine *m)
    {
        cout << "   already Sensing\n";
    }
     virtual void idle(Machine *m)
    {
        cout << "   already IDLE\n";
    }
};

void Machine::processing()
{
  current->processing(this);
}

void Machine::sensing()
{
  current->sensing(this);
}

void Machine::idle()
{
  current->idle(this);
}

class PROCESSING: public State
{
  public:

    PROCESSING()
    {
        cout << "\nCurrently in Processing state which will accumulate data from Sensing state\n";
        processedData = processedData + data;

        cout << "The result is " << processedData << "\n";
        num = 2;
    };
    ~PROCESSING()
    {
        //cout << "dtor-PRO\n";
    };
    void idle(Machine *m);

};

class IDLE: public State
{
  public:
    IDLE()
    {
        cout << "currently in Idle Mode, remain in Idle Mode for 5 seconds \n";
        Sleep(5000);
        num = 0;
    };
    ~IDLE()
    {
        //cout << "dtor-OUT\n";
    };
    void sensing(Machine *m);
};

class SENSING: public State
{
  public:

    SENSING()
    {
        cout << "Currently in Sensing state Enter Data: ";
        cin >> data;
        //cout << "Sense-ctor\n";

        num = 1;

    };
    ~SENSING()
    {
        //cout << "dtor-Sense\n";
    };


    void processing(Machine *m);

};

  void SENSING::processing(Machine *m)
    {
      cout << "Going from Sensing to Processing\n";
      m->setCurrent(new PROCESSING());
      delete this;
    }

void IDLE::sensing(Machine *m)
{
  cout << "\nGoing from Idle to Sensing\n";
  m->setCurrent(new SENSING());
  delete this;
}

void PROCESSING::idle(Machine *m)
{
  cout << "\nGoing from Processing to idle\n";
  m->setCurrent(new IDLE());
  delete this;
}

Machine::Machine()
{
  current = new SENSING();
  cout << '\n';
}

int main()
{
  void(Machine:: *ptrs[])() =
  {
    Machine::sensing, Machine::processing, Machine::idle
  };
  Machine fsm;
  while (1)
  {
    (fsm.*ptrs[num])();
  }
}
