#include <iostream>
#include <map> //для счетчика
#include <fstream>

using namespace std;

class SBase { //родительский класс
public:
	virtual int get() = 0;// вирутальный метод для переопределения в дочерних классах, класс SBase абстрактный, для обращения к геттерам дочерних классов
};

class SFile :public SBase { // получение данных из файла
	ifstream file; //поток для чтения
public:
	SFile(string fname) {
		file.open(fname);// открытие файла
		if (!file) //если файл не открылся, выводим сообщение об ошибки и закрываем
		{
			cerr << "Файл не открылся" << endl;
		}
	}
	~SFile() { //деструктор
		file.close();// закрытие файла
	}
	int get() { //обработка по одному числу
		int i=0;
		file >> i;
		if (file.eof())
		{
			file.close();
			return -1;
		}
		else
		{
			return i;
		}
	}
	void again(string fname)
	{
		file.open(fname);
		if (!file) 
		{
			cerr << "Файл не открылся" << endl;
		}
	}

}; 

class SuppKbrd :public SBase { //ввод с клавиатуры
public:
	int get() { //обработка по одному числу
		int i=0; 
		
		if (i != -1) {
			cin >> i;
			return i;
		}
		else
		{
			return -1;
		}
	}
};

class SQueue :public SBase {
	int* q;
	int pos = -1;
public:
	SQueue(int n ) { // создаем массив заданной длины из рандомных чисел
		q = new int[n + 1];
		for (int i = 0; i < n; i++) { 
			q[i] = rand() % 15;
		}
		q[n] = -1; // последний элемент отрицательный - конец очереди 

		for (int j = 0; j < n; j++) {   //выводим массив на экран
			cout << q[j] << ' ';
		}
	}
	~SQueue() { //деструктор массива
		delete[] q;
	}
	int get() { //обработка по одному числу
		pos++;
		return q[pos];
	}
	void again()
	{
		pos = -1;
	}
};

class Freq {
	map<int, int>a;
public:
	virtual void Calc(SBase* sup) 
	{
		int b = sup->get();// b присваиваем значение очередного числа
		while (b >= 0) { // для стопа
			a[b]++;  // увеличиваем счетчик
			b = sup->get(); // b присваиваем новое значение
		}
	}
	friend ostream& operator<<(ostream& stream, Freq& obj) { //перезагрузка оператора
		for (auto it = obj.a.begin(); it != obj.a.end(); it++) { //auto- автоматическое определение типа данных
			stream << it->first << " :  " << it->second << endl; // обращаемся к ключу и значению
		}
		cout << endl;
		return stream;
	};
};

class Diap :public Freq 
{
	int sum , max , min;
public:
	void Calc(SBase* sB) {

		int b = sB->get();  // b присваиваем значение очередного числа
		sum = 0;
		max = -1;
		min = 20;
		while (b >= 0) // для стопа
		{ 
			sum =sum + b; //сумма
			if (b > max) {
				max = b; //максимальное
			}
			if (b < min) {
				min = b; //минимальное
			}
			b = sB->get();
		}
	}
	friend ostream& operator<<(ostream& stream, Diap& obj) {
		stream << "sum = " << obj.sum << " max = " << obj.max << " min = " << obj.min << ' ' << endl;
		return stream;
	}
};

int main() {

	setlocale(LC_CTYPE, "RUSSIAN");

	string fname;
	int n; // длина очереди
	fname = "input.txt"; // имя файла
	cout << "Введите количество чисел: ";
	cin >> n;
	
	//ВВОД РАНДОМНОГО МАССИВА
	cout << "Рандомный массив " << endl;
	SQueue mas1(n); 

	Freq a1;
	a1.Calc(&mas1);

	cout << endl;
	cout << a1;

	Diap d1;

	cout << endl;
	mas1.again();

	d1.Calc(&mas1);
	cout << d1;

	//ВВОД С КЛАВИАТУРЫ
	cout << "Ввод с клавиатуры " << endl;
	cout << "Введите "<< n<< " чисел, для окончания введите -1" << endl;
	SuppKbrd sk;	

	Freq a2;
	a2.Calc(&sk);

	cout << endl;
	cout << a2;
	cout << "Введите " << n << " чисел заново, для окончания введите -1" << endl;
	Diap d2;

	d2.Calc(&sk); 
	cout << d2;   

	//ВВОД С ФАЙЛА
	cout << "Ввод с файла " << endl;
	SFile M ("prob.txt");
	
	Freq a3;
	a3.Calc(&M);

	cout << endl;
	cout << a3;

	M.again("prob.txt");


	Diap d3;

	d3.Calc(&M);
	cout << d3;

	system("pause");
	return 0;
}
