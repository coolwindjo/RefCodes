#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Command: ����� Capsulize!

class Shape
{
public:
    virtual void draw()
    {
        cout << "Shape Draw" << endl;
    }
};

class Rect : public Shape
{
public:
    void draw()
    {
        cout << "Rect draw" << endl;
    }
};

class Circle : public Shape
{
public:
    void draw()
    {
        cout << "Circle draw" << endl;
    }
};

//------------------------------------------
// ��� Command�� Objectȭ �Ѵ�.
struct ICommand
{
    virtual void execute() = 0;

    // Interface ���ο��� �⺻ ������ ������ �� �ִٸ�,
    // code�� �ߺ��� ���� �� �� �ִ�. - Java 8�� �߰��Ǿ����ϴ�.
    virtual void undo() = 0;
    virtual bool can_undo() { return false; }   // Default ���� ����

    virtual ~ICommand() {}
};

// Rect�� �߰��ϴ� ���
class AddRectCommand : public ICommand
{
public:
    AddRectCommand(vector<Shape*>& p)
        : v(p)
    {}
    ~AddRectCommand() {}

    virtual void execute() { v.push_back(new Rect); }
    virtual bool canUndo() { return true; }
    virtual void undo()
    {
        Shape* p = v.back();      // ������ ���
        v.pop_back();

        delete p;
    }

private:
    vector<Shape*>& v;

};

// Circle�� �߰��ϴ� ���
class AddCircleCommand : public ICommand
{
public:
    AddCircleCommand(vector<Shape*>& p)
        : v(p)
    {}
    ~AddCircleCommand() {}
    virtual void execute() { v.push_back(new Circle); }
    virtual bool canUndo() { return true; }
    virtual void undo()
    {
        Shape* p = v.back();      // ������ ���
        v.pop_back();

        delete p;
    }

private:
    vector<Shape*>& v;

};

class DrawCommand : public ICommand
{
    vector<Shape*>& v;
public:
    DrawCommand(vector<Shape*>& p) 
        : v(p)
    {}
    virtual void execute()
    {
        for (Shape* e : v)
            e->draw();
    }
};


const int kMaxNum = 1000;
int main()
{
    vector<Shape*> v;
    stack<ICommand*> undo;
    stack<ICommand*> redo;

    for (int i = 0;
    true
        && (i < kMaxNum); i++)
    {
        int cmd;
        cin >> cmd;

        // Command
        ICommand* pCommand = 0;

        if (cmd == 1)      { pCommand = new AddRectCommand(v); }
        else if (cmd == 2) { pCommand = new AddCircleCommand(v); }
        //else if (cmd == 9) { pCommand = new DrawCommand(v); }
        else if (cmd == 0)  {
            pCommand = undo.top();
            undo.pop();

            pCommand;
        }

        if (pCommand) {
            pCommand->execute();
            delete pCommand;
        }
    }

    system("pause");
    return 0;
}