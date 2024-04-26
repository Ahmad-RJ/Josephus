#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace std;
template <class T>
class queue {
	class node {
	public:
		T data;
		node* next;
	};
public:
	node* front;
	node* rear;
	queue() {
		front = NULL;
		rear = NULL;
	}
	bool isEmpty() {
		if (front == NULL)
			return true;
		else
			return false;
	}
	void enqueue(T const& e) {
		node* temp = new node;
		if (temp != NULL) {
			node* temp = new node;
			temp->data = e;
			temp->next = NULL;
			if (rear != NULL) {
				rear->next = temp;
			}
			rear = temp;
			if (front == NULL) {
				front = temp;
			}
		}
	}
	void dequeue() {
		if (!isEmpty()) {
			node* temp = front;
			front = front->next;
			delete temp;
		}
	}
	T getFront() {
		if (!isEmpty()) {
			return front->data;
		}
	}
	void print() {
		if (!isEmpty()) {
			queue s;
			while (!isEmpty()) {
				cout << getFront() << " ";
				s.enqueue(getFront());
				dequeue();
			}
			cout << endl;
			while (!s.isEmpty()) {
				enqueue(s.getFront());
				s.dequeue();
			}
		}
	}
	int size() {
		int count = 0;
		queue s;
		while (front != NULL) {
			s.enqueue(getFront());
			dequeue();
			count++;
		}
		while (s.front != NULL) {
			enqueue(s.getFront());
			s.dequeue();
		}
		return count;
	}
	void JosephusProblem(int n, int k) {
		int s;
		cout << "Enter Starting Point: ";
		cin >> s;
		for (int i = 1; i <= n; i++) {
			enqueue(i);
		}
		rear->next = front;
		int x = 1;
		while (s != 1) {
			enqueue(getFront());
			dequeue();
			s--;
		}
		output();
		while (size() != 1) {
			if (x == k) {
				x = 1;
				dequeue();
				output();
			}
			else {
				x++;
				enqueue(getFront());
				dequeue();
			}
		}
	}
	void output() {
		sf::RenderWindow window(sf::VideoMode(1600, 900), "Josephus Problem");
		sf::Font font;
		if (!font.loadFromFile("Damonte-Regular.ttf")) {
			return;
		}
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(36);
		text.setFillColor(sf::Color::Red);
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
			window.clear();
			int n = size();
			int rad = n * 10;
			for (int i = 0; i < n; i++) {
				float angle = i * 2 * 3.14159265359 / n;
				float x = 775 + rad * std::cos(angle);
				float y = 450 + rad * std::sin(angle);
				text.setString(std::to_string(getFront()));
				enqueue(getFront());
				dequeue();
				text.setPosition(x, y);
				window.draw(text);
			}
			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
				return;
			}
		}
	}
};

int main() {
	int n, k;
	cout << "Enter Total Number of People: ";
	cin >> n;
	cout << "Enter Value of K: ";
	cin >> k;
	queue<int> q1;
	q1.JosephusProblem(n, k);
	cout << "Last Man Standing: ";
	q1.print();
	return 0;
}