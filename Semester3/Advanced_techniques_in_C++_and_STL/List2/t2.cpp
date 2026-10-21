#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

using namespace std;

class line_writer {
private:
    ofstream file;
public:
    line_writer(const string &filename) : file(filename)
    {
        if (!file.is_open())
            cerr << "Cannot open the file!" << '\n';
    }
    ~line_writer()
    {
        file.close();
    }
    void write_line(const string &text)
    {
        file << text << '\n';
    }
};

int main()
{
    // shared_ptr<line_writer> ptr1 { new line_writer("file.txt") };
    auto ptr1 = make_shared<line_writer>("file.txt");
    shared_ptr<line_writer> ptr2 = ptr1;
    shared_ptr<line_writer> ptr3 = ptr1;
    shared_ptr<line_writer> ptr4 = ptr1;

    ptr1->write_line("Line1");
    ptr2->write_line("Line2");
    ptr3->write_line("Line3");
    ptr4->write_line("Line4");
    return 0;
}