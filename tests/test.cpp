#include <gtest/gtest.h>
#include "../code_1/Circ_buff.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>


using namespace std;

class test_buff : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_buff::total_grade = 0;
double test_buff::max_grade = 100;

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_buff, InitBuff){
	Circ_buff my_buff;
	shared_ptr<buffer> buff1 = my_buff.InitBuff(5);
	//Check start size is correct
	printf("Made\n");
	ASSERT_EQ(buff1->capacity, 5);
	ASSERT_EQ(buff1->size, 0);
	//Check resizes are correct
	buff1->capacity = 12;
	ASSERT_EQ(buff1->capacity, 12);
	buff1->capacity = 8;
	ASSERT_EQ(buff1->capacity, 8);
}

TEST_F(test_buff, add_data){
	Circ_buff my_buff;
	shared_ptr<buffer> buff1 = my_buff.InitBuff(15);
	string str;
	// Fill buff
	for (int i = 0; i < buff1->capacity; i++){
		my_buff.add_data(buff1, "d");
	}
	//Check buff contents
	for (int i = 0; i < buff1->capacity; i++){
		ASSERT_EQ(buff1->buff[i], "d");
	}
	//Try overfilling buff by adding additional elements
	//This time elements start at 5 
	for (int i = 0; i < buff1->capacity; i++){
		str = to_string(i+5);
		my_buff.add_data(buff1, str);
	//While overfilling, head and tail should be incremented togother
		ASSERT_EQ(buff1->head, buff1->tail);
	}
	//Ensure all elements were updated 
	for (int i = 0; i < buff1->capacity; i++){
		str = to_string(i+5);
		ASSERT_EQ(buff1->buff[i], str);
	}
}
TEST_F(test_buff, read_data){
	Circ_buff my_buff;
	shared_ptr<buffer> buff1 = my_buff.InitBuff(3);
	my_buff.add_data(buff1, "A");
	my_buff.add_data(buff1, "B");
	my_buff.add_data(buff1, "C");
	//Confirm data read on first in first out basis
	string check = my_buff.read_data(buff1);
	ASSERT_EQ(check, "A");
	//Confirm data removed and tail incremented
	check = my_buff.read_data(buff1);
	ASSERT_EQ(check, "B");
	check = my_buff.read_data(buff1);
	ASSERT_EQ(check, "C");
	//Buffer should now be empty
	for (int i = 0; i < buff1->capacity; i++){
		ASSERT_EQ(buff1->buff[i], "");
	}
	//Overfill buffer
	my_buff.add_data(buff1, "A");
	my_buff.add_data(buff1, "B");
	my_buff.add_data(buff1, "C");
	my_buff.add_data(buff1, "D");
	my_buff.add_data(buff1, "E");
	//Confirm A abd B were over written, FIFO maintained
	// C, D, E
	check = my_buff.read_data(buff1);
	ASSERT_EQ(check, "C");
	check = my_buff.read_data(buff1);
	ASSERT_EQ(check, "D");
	check = my_buff.read_data(buff1);
	ASSERT_EQ(check, "E");
	//
}

TEST_F(test_buff, reset_buffer){
	Circ_buff my_buff;
	shared_ptr<buffer> buff1 = my_buff.InitBuff(3);
	//Fill buffer
	my_buff.add_data(buff1, "A");
	my_buff.add_data(buff1, "B");
	my_buff.add_data(buff1, "C");
	//Reset
	string check;
	my_buff.reset_buffer(buff1);
	//Confirm all values have been reset
	for (int i = 0; i < buff1->capacity; i++){
        check = buff1->buff[i];
		ASSERT_EQ(check, "");
    }
}

TEST_F(test_buff, peak_data){
	Circ_buff my_buff;
	shared_ptr<buffer> buff1 = my_buff.InitBuff(5);
	//Fill buffer
	my_buff.add_data(buff1, "A");
	my_buff.add_data(buff1, "B");
	my_buff.add_data(buff1, "C");
	my_buff.add_data(buff1, "D");
	my_buff.add_data(buff1, "E");
	string check;
	check = my_buff.peak_data(buff1);
	//Confirm peak is A
	ASSERT_EQ(check, "A");
	//Remove some values
	my_buff.read_data(buff1);
	my_buff.read_data(buff1);
	check = my_buff.peak_data(buff1);
	//Confirm that peak = data read
	string check_read = my_buff.read_data(buff1);
	ASSERT_EQ(check, check_read);
}

TEST_F(test_buff, is_full){
	Circ_buff my_buff;
	shared_ptr<buffer> buff1 = my_buff.InitBuff(5);
	//Fill buffer
	my_buff.add_data(buff1, "A");
	my_buff.add_data(buff1, "B");
	my_buff.add_data(buff1, "C");
	my_buff.add_data(buff1, "D");
	my_buff.add_data(buff1, "E");
	bool full = my_buff.is_full(buff1);
	//Buffer is full, so is_full should return true
	ASSERT_TRUE(full);
	//Remove one item
	my_buff.read_data(buff1);
	//Buff is not full, so is_full should be false
	full = my_buff.is_full(buff1);
	ASSERT_FALSE(full);
}

TEST_F(test_buff, get_size){
	Circ_buff my_buff;
	shared_ptr<buffer> buff1 = my_buff.InitBuff(3);
	//Fill buffer
	//Confirm Size changes while filling
	string str;
	for (int i = 0; i < buff1->capacity; i++){
		str = to_string(i+5);
		my_buff.add_data(buff1, str);
		ASSERT_EQ(my_buff.get_size(buff1), (i+1));
	}
	//Overfill buffer
	my_buff.add_data(buff1, "A");
	my_buff.add_data(buff1, "B");
	//Confirm size did not change 
	ASSERT_EQ(my_buff.get_size(buff1), 3);
	//Remove an item
	my_buff.read_data(buff1);
	//Confirm size updated appropraitely 
	ASSERT_EQ(my_buff.get_size(buff1), 2);
}



