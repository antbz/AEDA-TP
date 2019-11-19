# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
private:
    stack<T> values;
    stack<T> min_values;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
	return values.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    return values.top();
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{
    if (values.top() == min_values.top()) {
        min_values.pop();
    }
    values.pop();
}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
    values.push(val);
    if (min_values.empty() || val <= min_values.top()) {
        min_values.push(val);
    }
}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    return min_values.top();
}

