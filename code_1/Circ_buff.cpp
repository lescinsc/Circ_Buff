#include "Circ_buff.h"

Circ_buff::Circ_buff(){

}

Circ_buff::~Circ_buff(){

}

shared_ptr<buffer> Circ_buff:: InitBuff (int capacity){
    shared_ptr<buffer> ret (new buffer);
    ret->capacity = capacity;
    ret->head = 0;
    ret->tail = 0;
    ret->size = 0;
    return ret;
}

void Circ_buff:: add_data(shared_ptr<buffer> buffer, string data){
    // Ensures wrap around
    buffer->head = buffer->head%buffer->capacity;
    buffer->buff[buffer->head] = data;
    if (buffer->size == buffer->capacity){
        buffer->head++;
        buffer->tail++;
    }
    else{
        buffer->size++;
        buffer->head++;
    }
}

string Circ_buff::read_data(shared_ptr<buffer> buffer){
    buffer->tail = buffer->tail%buffer->capacity;
    string ret = buffer->buff[buffer->tail];
    buffer->buff[buffer->tail] = "";
    buffer->size--;
    buffer->tail++;
    return ret;
}

void Circ_buff::reset_buffer(shared_ptr<buffer> buffer){
    for (int i = 0; i < buffer->capacity; i++){
        buffer->buff[i] = "";
    }
    buffer->head = 0;
    buffer->tail = 0;
}

string Circ_buff::peak_data(shared_ptr<buffer> buffer){
    return buffer->buff[buffer->tail];
}

bool Circ_buff::is_full(shared_ptr<buffer> buffer){
    if (buffer->size == buffer->capacity){
        return true;
    }
    return false;
}

int Circ_buff::get_size(shared_ptr<buffer> buffer){
    return buffer->size;
}