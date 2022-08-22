#include <string>
#include <memory>
#include <iostream>
#include <vector>

using namespace std;

struct buffer{
    int size;
    int capacity;
    int head;
    int tail;
    string buff[15];
};

class Circ_buff{
public:
    // Constructor
    Circ_buff();
    // Destructor 
    ~Circ_buff();
    // Initialize buffer with defined capacity
    // Return pointer to buffer struct
    shared_ptr<buffer> InitBuff (int capacity);
    // Add data to buffer
    // Old data is overwritten 
    void add_data(shared_ptr<buffer> buffer, string data);
    // Read data on a first in first out basis
    string read_data(shared_ptr<buffer> buffer);
    // Reset all buffer entries 
    void reset_buffer(shared_ptr<buffer> buffer);
    //  Return next item, but don't remove
    string peak_data(shared_ptr<buffer> buffer);
    //  Return true if buffer is at capacity
    bool is_full(shared_ptr<buffer> buffer);
    //  Return size of the buffer
    int get_size(shared_ptr<buffer> buffer);


private:
    
};