#include <iostream>
#include <stack>
using namespace std;
struct Leksema
{
	char type;
	double value;// значення для чисел. Для операцій говорити, що це 0 
};
bool Math_Oper(stack<Leksema>& Stack_N, stack<Leksema>& Stack_O, Leksema& item) {
	double a, b, c;
	a = Stack_N.top().value; //взяли число з самого  верху стека
	Stack_N.pop(); //видаляє верхній елемент зі стеку
	switch (Stack_O.top().type)
	{
	case '+':
		b = Stack_N.top().value;
		Stack_N.pop();
		c = a + b;
		item.type = '0';
		item.value = c;
		Stack_N.push(item);
		Stack_O.pop();
		break;
	case '-':
		b = Stack_N.top().value;
		Stack_N.pop();
		c = b - a;
		item.type = '0';
		item.value = c;
		Stack_N.push(item);
		Stack_O.pop();
		break;
	case '*':
		b = Stack_N.top().value;
		Stack_N.pop();
		c = a * b;
		item.type = '0';
		item.value = c;
		Stack_N.push(item);
		Stack_O.pop();
		break;
	case '/':
		b = Stack_N.top().value;
		if (a == 0) {
			cout << "Division on 0" << endl;
			return false;
		}
		else {
			Stack_N.pop();
			c = b / a;
			item.type = '0';
			item.value = c;
			Stack_N.push(item);
			Stack_O.pop();
			break;
		}
	default:
		cout << "Error. Not is  operation" << endl;
		return false;
		break;
	}
	return true;
}
int getRang(char Ch) { //функція повертає пріорітет оперцій, Якщо '+', '-'  - 1. Якщо '*', '/' - 2
	if (Ch == '+' || Ch == '-') return 1;
	if (Ch == '*' || Ch == '/') return 2;
	else return 0;
}
int main()
{
	cout << "This calc" << endl;
	char Ch;
	double value;
	bool flag = 1; //Дивитися чи є різниця між (-2) і 3-2
	stack <Leksema> Stack_O;
	stack <Leksema> Stack_N;
	Leksema item;
	while (1) {
		Ch = cin.peek();
		/*cout << Ch << endl;*/
		if (Ch == '\n')break;   //ігнорує символ пробіл
		if (Ch == ' ') {
			cin.ignore();
			continue;
		}
		if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) {
			cin >> value;
			item.type = '0';
			item.value = value;
			Stack_N.push(item); //Кладе число в стек з операціями
			flag = 0;
			continue;
		}
		if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/') {
			if (Stack_O.size() == 0) {
				item.type = Ch;
				item.value = 0;
				Stack_O.push(item);
				cin.ignore();
				continue;
			}
			if (Stack_O.size() != 0 && getRang(Ch) > getRang(Stack_O.top().type)) {
				item.type = Ch;
				item.value = 0;
				Stack_O.push(item);
				cin.ignore();
				continue;
			}
			if (Stack_O.size() != 0 && getRang(Ch) <= getRang(Stack_O.top().type)) {// Дивимось чи стек з операціями не пустий.Дивимось чи пріорітер, опер, який зустріли менший або ріний пріорітету оперції в стеці(найвищий його елмент) з операціями
				if (Math_Oper(Stack_N, Stack_O, item) == false) {
					system("pause");
					return 0;
				}
				continue;
			}
		}
		if (Ch == '(') { // Якщо прочитали дужку, яка відкривається
			item.type = Ch;
			item.value = 0;
			Stack_O.push(item);
			cin.ignore();
			continue;
		}
		if (Ch == ')') {
			while (Stack_O.top().type != '(') {
				if (Math_Oper(Stack_N, Stack_O, item) == false) {
					system("pause");
					return 0;
				}
				else continue;
			}
			Stack_O.pop();
			cin.ignore();
			continue;
		}
		else {
			cout << "Eroor" << endl;
			system("pause");
			return 0;
		}
	}
	while (Stack_O.size() != 0) {
		if (Math_Oper(Stack_N, Stack_O, item) == false) {
			system("pause");
			return 0;
		}
		else continue;
	}
	cout << "Answer = " << Stack_N.top().value << endl;
	return 0;
}


