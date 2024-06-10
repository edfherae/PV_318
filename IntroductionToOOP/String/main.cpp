#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "\n-----------------------------------------------\n"


class String
{
	int size; // размер строки в байтах
	char* str; // адрес строки в динамической памяти
public:
	int get_size()const
	{
		return size;
	}
	char* get_str()const
	{
		return str;
	}
	//		Constructors:
	String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "DefaultConstructor:\t" << this << endl;
	}
	String(const char arr[], int size = 80) //считается 1arg, или уже нет?
	{
		this->size = size;
		this->str = new char[size] {};
		for (int i = 0; arr[i] != '\0'; i++)
			str[i] = arr[i];
		cout << "1ArgConstructor:\t" << this << endl;
	}
	String(const char line1[], const char line2[], int size = 160)
	{
		this->size = size;
		this->str = new char[size] {};
		int index = 0;
		for (int i = 0; line1[i] != '\0'; i++, index++)
			str[i] = line1[i];
		for (int i = 0; line2[i] != '\0'; i++, index++)
			str[index] = line2[i];
		cout << "Constructor:\t" << this << endl;
	}
	String(const String& obj)
	{
		size = obj.size;
		str = new char[obj.size] {};
		for (int i = 0; obj.str[i] != '\0'; i++)
			str[i] = obj.str[i];
		cout << "CopyConstructor:\t" << this << endl;
	}
	~String()
	{
		delete[] this->str;
		cout << "Destructor:\t\t" << this << endl;
	}
	//		Methods:
	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
	String& operator=(const String& obj)
	{
		size = obj.size;
		str = new char[obj.size] {};
		for (int i = 0; obj.str[i] != '\0'; i++)
			str[i] = obj.str[i];
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
};
String operator+(const String& left, const String& right)
{
	//char* buffer = new char[left.get_size() + right.get_size()] {};
	//int index = 0;
	//for (; index < left.get_size(); index++)
	//	buffer[index] = left.get_str()[index];
	//for (; index < left.get_size() + right.get_size(); index++)
	//	buffer[index] = left.get_str()[index];
	return String
	(
		left.get_str(),
		right.get_str(),
		left.get_size() + right.get_size()
	);
}
std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << "Size:\t" << str.get_size() << endl; 
	os << "Str:\t" << str.get_str(); //почему, обращаясь к адресу начала строки в памяти, мы получаем ее всю на выводе?
	return os;
}

int main()
{
	setlocale(LC_ALL, "");

	String str1 = "Hello";
	String str2("World", 6); //на 5 элементов позволяет, на 4 Heap Corruption при вызове деструктора
							 //то есть при 5 элементах затирается лишь нуль, а на 4 уже и брейк поинт?
							 // 
							 //почему при затертом нуле выводит не 80 элементов белиберды, а лишь несколько?
							 //строка ведь полностью инициализирована нулями, при создании есть увловие остановки на нуле
	cout << str1 << endl;
	cout << str2 << endl;

	cout << delimiter << endl;

	String temp1 = str1;
	temp1.print();
	String temp2;
	temp2 = str2;
	temp2.print();

	cout << delimiter << endl;

	String str3 = str1 + str2;
	cout << str3 << endl;
}