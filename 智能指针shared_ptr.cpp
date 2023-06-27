#include <string>
#include <iostream>
using namespace std;

//智能指针的实现
 
#include<iostream>
using namespace std;
#include<memory>
 
template<class T>
class MyShared_ptr
{
public:
 
	//构造函数
	explicit MyShared_ptr(T *p = NULL)
	{
		this->m_ptr = p;
		this->m_count = new size_t;
		if (p == NULL){
			*this->m_count = 0;
		}else{
			*this->m_count = 1;
		}
	}
 
	//析构函数
	~MyShared_ptr()
	{
		if (this->m_ptr)
		{
			if (*(--this->m_count) == 0)
			{
				delete this->m_ptr;
				delete this->m_count;
				this->m_ptr = NULL;
				this->m_count = NULL;
			}
		}
	}
 
	//拷贝构造函数
	MyShared_ptr(const MyShared_ptr& shared)
	{
		if (this != &shared)
		{
			this->m_ptr = shared.m_ptr;
			this->m_count = shared.m_count;
			(*this->m_count)++;
		}
	}
 
	//重载赋值操作符
	MyShared_ptr& operator=(const MyShared_ptr& shared)
	{
		if (this->m_ptr == shared.m_ptr)
		{
			return *this;
		}
		if (this->m_ptr)
		{
			if (*(--this->m_count) == 0)
			{
				delete this->m_ptr;
				delete this->m_count;
				this->m_ptr = NULL;
				this->m_count = NULL;
			}
		}
		this->m_ptr = shared.m_ptr;
		this->m_count = shared.m_count;
		(*this->m_count)++;
		return *this;
	}
 
    //重载->操作符
	T& operator->()
	{
		if (this->m_ptr)
		{
			return this->m_ptr;
		}
	}
 
    //重载 *
	T& operator*()
	{
		if (this->m_ptr)
		{
			return *(this->m_ptr);
		}
	}
 
    //实现 use_count函数
	size_t use_count()
	{
		return *this->m_count;
	}
 
 
 
private:
	T *m_ptr;  //内部指针，保证拷贝指向同一内存
	size_t *m_count;  //为了保证指针的引用计数，这里我是用了指针来做
};



int main(int argc, const char * argv[])
{
	MyShared_ptr<int> p1(new int(1));
	cout << "p1 cnt:" << p1.use_count() << endl;

	// 检查拷贝构造是否正常工作
	{
		MyShared_ptr<int> p2(p1);
		cout << "p2 cnt:" << p2.use_count() << endl;
		cout << "p1 cnt:" << p1.use_count() << endl;
	}
	
	// 检查引用计数是否正常工作
	cout << "p1 cnt:" << p1.use_count() << endl;

	// 检查默认初始化时计数是否正常
	MyShared_ptr<int> p4;
	cout << "p4 cnt:" << p4.use_count() << endl;

	// 检查拷贝赋值是否正常工作
	p4 = p1;
	cout << "p1 cnt:" << p1.use_count() << " p4 cnt:" << p4.use_count() << endl;

	return 0;
}
