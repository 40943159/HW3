//3 2.87 2 3.14 1 1.11 0
//5 1.23 8 12.3 6 123.01 3 1 2 0.2 1
#include <iostream>
using namespace std;
class Polynomial {
	class Node {
		friend Polynomial;
		friend ostream& operator<<(ostream& os, const Polynomial& p);
	private:
		float coef;
		int exp;
		Node* next;
	};

private:
	Node* root;
public:
	Polynomial();
	Polynomial(const Polynomial& p);
	~Polynomial();
	void addNode(float coef, int exp);
	friend istream& operator>>(istream& is, Polynomial& p) {
		int n, exp;
		float coef;
		is >> n;
		for (int i = 0; i < n; i++) {
			is >> coef >> exp;
			p.addNode(coef, exp);
		}
		return is;
	}
	friend ostream& operator<<(ostream& os, const Polynomial& p) {
		Node* temp = p.root;
		if (p.root == nullptr) {
			os << "Empty Polynomial" << endl;
			return os;
		}
		while (1) {
			if (temp == p.root) {
				if (temp->coef < 0) os << "- ";
			}
			else {
				if (temp->coef < 0) os << " - ";
				else os << " + ";
			}
			float a = temp->coef;
			if (a < 0) a *= -1;
			if (a != 1 || temp->exp == 0) os << a;
			if (temp->exp >= 2) os << "x^" << temp->exp;
			else if (temp->exp == 1) os << "x";
			if (temp->next == p.root) break;
			temp = temp->next;
		}
		os << endl;
		return os;
	}
	Polynomial& operator=(const Polynomial& p) {
		if (this == &p) return *this;
		if (p.root == nullptr) this->root = nullptr;
		else {
			this->root = new Node;
			Node* tempA = p.root;
			Node* tempB = this->root;
			tempB->coef = tempA->coef;
			tempB->exp = tempA->exp;
			while (1) {
				tempB->next = new Node;
				tempA = tempA->next;
				tempB = tempB->next;
				tempB->coef = tempA->coef;
				tempB->exp = tempA->exp;
				if (tempA->next == p.root) break;
			}
			tempB->next = this->root;
		}
		return *this;
	}
	Polynomial operator+(const Polynomial& p) const {
		Polynomial result;
		Node* tempA = this->root;
		Node* tempB = p.root;
		if (this->root == nullptr && p.root == nullptr) return result;
		if (tempA == nullptr) {
			while (1) {			
				result.addNode(tempB->coef, tempB->exp);
				if (tempB->next == p.root) break;
				tempB = tempB->next;
			}
			return result;
		}
		else if (tempB == nullptr) {
			while (1) {
				result.addNode(tempA->coef, tempA->exp);
				if (tempA->next == this->root) break;
				tempA = tempA->next;
			}
			return result;
		}
		while (1) {
			if (tempA->exp > tempB->exp) {
				result.addNode(tempA->coef, tempA->exp);
				tempA = tempA->next;
				if (tempA == this->root) break;
			}
			else if (tempA->exp < tempB->exp) {
				result.addNode(tempB->coef, tempB->exp);
				tempB = tempB->next;
				if (tempB == p.root) break;
			}
			else {
				result.addNode(tempA->coef + tempB->coef, tempA->exp);
				tempA = tempA->next;
				tempB = tempB->next;
				if (tempA == this->root) break;
				if (tempB == p.root) break;
			}
		}
		while (1) {
			if (tempA == this->root) {
				while (tempB != p.root) {
					result.addNode(tempB->coef, tempB->exp);
					tempB = tempB->next;
				}
				break;
			}
			if (tempB == p.root) {
				while (tempA != this->root) {
					result.addNode(tempA->coef, tempA->exp);
					tempA = tempA->next;
				}
				break;
			}
		}
		return result;
	}
	Polynomial operator-(const Polynomial& p) const {
		Polynomial result;
		Node* tempA = this->root;
		Node* tempB = p.root;
		if (this->root == nullptr && p.root == nullptr) return result;
		if (tempA == nullptr) {
			while (1) {
				result.addNode(-tempB->coef, tempB->exp);
				tempB = tempB->next;
				if (tempB == p.root)break;
			}
			return result;
		}
		if (tempB == nullptr) {
			while (1) {
				result.addNode(tempA->coef, tempA->exp);
				tempA = tempA->next;
				if (tempA == this->root)break;
			}
			return result;
		}
		while (1) {
			if (tempA->exp > tempB->exp) {
				result.addNode(tempA->coef, tempA->exp);
				tempA = tempA->next;
				if (tempA == this->root) break;
			}
			else if (tempA->exp < tempB->exp) {
				result.addNode(-tempB->coef, tempB->exp);
				tempB = tempB->next;
				if (tempB == p.root) break;
			}
			else {
				if(tempA->coef != tempB->coef)result.addNode(tempA->coef - tempB->coef, tempA->exp);
				tempA = tempA->next;
				tempB = tempB->next;
				if (tempA == this->root) break;
				if (tempB == p.root) break;
			}
		}
		while (1) {
			if (tempA == this->root) {
				while (tempB != p.root) {
					result.addNode(-tempB->coef, tempB->exp);
					tempB = tempB->next;
				}
				break;
			}
			if (tempB == p.root) {
				while (tempA != this->root) {
					result.addNode(tempA->coef, tempA->exp);
					tempA = tempA->next;
				}
				break;
			}
		}
		return result;
	}
	Polynomial operator*(const Polynomial& p) const {
		Polynomial result;
		Node* tempA = this->root;
		while (1) {
			Polynomial temp;
			Node* tempB = p.root;
			while (1) {
				float coef = tempA->coef * tempB->coef;
				int exp = tempA->exp + tempB->exp;
				temp.addNode(coef, exp);
				tempB = tempB->next;
				if (tempB == p.root) break;
			}
			result = result + temp;
			tempA = tempA->next;
			if (tempA == this->root) break;
		}
		return result;
	}
	float Evaluate(float x);
};
Polynomial::Polynomial()
{
	root = nullptr;
}
Polynomial::Polynomial(const Polynomial& p) {
	if (p.root == nullptr) this->root = nullptr;
	else {
		this->root = new Node;
		Node* tempA = p.root;
		Node* tempB = this->root;
		tempB->coef = tempA->coef;
		tempB->exp = tempA->exp;
		while (tempA->next != p.root) {
			tempB->next = new Node;
			tempA = tempA->next;
			tempB = tempB->next;
			tempB->coef = tempA->coef;
			tempB->exp = tempA->exp;
		}
		tempB->next = this->root;
	}
}
Polynomial::~Polynomial() {
	if (this->root != nullptr) {
		Node* tempA = this->root->next;
		while (tempA->next != this->root) {
			Node* tempB = tempA;
			tempA = tempA->next;
			delete tempB;
		}
		delete this->root;
		this->root = nullptr;
	}
}
void Polynomial::addNode(float coef, int exp) {
	if (root == nullptr) {
		root = new Node;
		root->coef = coef;
		root->exp = exp;
		root->next = root;
	}
	else {
		Node* temp = root;
		while (temp->next != root) {
			temp = temp->next;
		}
		temp->next = new Node;
		temp->next->coef = coef;
		temp->next->exp = exp;
		temp->next->next = root;
	}
}
float Polynomial::Evaluate(float x) {
	float result = 0;
	Node* temp = root;
	do {
		result += temp->coef * pow(x, temp->exp);
		temp = temp->next;
	} while (temp != root);
	return result;
}

int main() {
	float x;
	Polynomial A, C;
	cout << "(a)輸入多項式 A:";
	cin >> A;
	cout << "(b)輸出多項式 A:" << A;
	Polynomial B(A);
	cout << "(c)複製建構元 Polynomial B(A):" << B;
	C = A;
	cout << "(d)多載 C = A:" << C;
	A.~Polynomial();
	cout << "(e)解構 A:" << A;
	cout << "輸入多項式A:";
	cin >> A;
	cout << "A:" << A;
	cout << "B:" << B;
	cout << "(f) A + B = " << A + B;
	cout << "(g) A - B = " << A - B;
	cout << "(h) A * B = " << A * B;
	cout << "輸入x = ";
	cin >> x;
	cout << A.Evaluate(x) << endl;
	cout << B.Evaluate(x) << endl;
	cout << C.Evaluate(x) << endl;
	system("pause");
	return 0;
}