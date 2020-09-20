#include <iostream>
#include <vector>

#include <iomanip>
#include <chrono>
#include <string>

class timer
{
public:
	timer() = default;
	void start(const std::string& text_)
	{
		text = text_;
		begin = std::chrono::high_resolution_clock::now();
	}
	void stop()
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = end - begin;
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		std::cout << std::setw(20) << text << " timing:" << std::setw(5) << ms << "ms" << std::endl;
	}

private:
	std::string text;
	std::chrono::high_resolution_clock::time_point begin;
};

class Foo
{
public:
    Foo() = default;

	void Add(int n)
	{
		m_vec.push_back(n);
	}

	void PassByReference(std::vector<int>& vec)
	{
		vec = m_vec; // make a copy
	}
    std::vector<int>& ReturnReference()
    {
        return m_vec; // return memory address
    }
	void PassByPointer(std::vector<int>* vec)
	{
		*vec = m_vec; // make a copy
	}
	std::vector<int>* ReturnPointer()
	{
		return &m_vec; // return memory address
	}
private:
    std::vector<int> m_vec;
};

int main()
{
	const int MAX_LOOP = 100000;
	timer stopwatch;

	{
		stopwatch.start("PassByReference");
		Foo foo;
		std::vector<int> vec;
		for (int i = 0; i < MAX_LOOP; ++i)
		{
			foo.Add(i);
			foo.PassByReference(vec);
		}
		stopwatch.stop();
	}
	{
		stopwatch.start("ReturnReference");
		Foo foo;
		std::vector<int>* p = nullptr;
		for (int i = 0; i < MAX_LOOP; ++i)
		{
			foo.Add(i);
			p = &foo.ReturnReference();
		}
		stopwatch.stop();
	}
	{
		stopwatch.start("PassByPointer");
		Foo foo;
		std::vector<int> vec;
		for (int i = 0; i < MAX_LOOP; ++i)
		{
			foo.Add(i);
			foo.PassByPointer(&vec);
		}
		stopwatch.stop();
	}
	{
		stopwatch.start("ReturnPointer");
		Foo foo;
		std::vector<int>* p = nullptr;
		for (int i = 0; i < MAX_LOOP; ++i)
		{
			foo.Add(i);
			p = foo.ReturnPointer();
		}
		stopwatch.stop();
	}

    std::cout << "Done!\n";
}
