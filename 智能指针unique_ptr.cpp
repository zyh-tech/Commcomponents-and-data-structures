/*
RAII

资源获取即初始化（Resource Acquisition Is Initialization），或称 RAII，是一种 C++ 编程技术，
它将必须在使用前请求的资源（分配的堆内存、执行线程、打开的套接字、打开的文件、锁定的互斥体、磁盘空间、
数据库连接等——任何存在受限供给中的事物）的生命周期绑定与一个对象的相绑定。

*/

/*
std::unique_ptr 是通过指针占有并管理另一对象，并在 unique_ptr 离开作用域时释放该对象的智能指针。 
不允许拷贝构造和拷贝赋值
*/
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class PointerDeleter{
public:
    void operator() (const T *_ptr){
        if(_ptr){
            delete _ptr;
            _ptr = nullptr;
        }
    }
};

template<typename T, typename Delete = PointerDeleter<T>>
class UniquePtr{
private:
    T *_ptr;
public:
    // -----------------------------
    explicit UniquePtr(T *ptr = nullptr) : _ptr(ptr){}
    
    ~UniquePtr(){
        if(_ptr){
            delete _ptr;
            _ptr = nullptr;
        }
    }

    //---------------------------------------------
    // non-copyable
    UniquePtr(const UniquePtr & p) = delete ;
    UniquePtr & operator = (const UniquePtr & p) = delete ;

    // move constructor
    UniquePtr(UniquePtr && p) : _ptr(p._ptr){
        p._ptr = nullptr;
    }

    // move assignment
    UniquePtr& operator=(UniquePtr && p) noexcept {
        std::swap(this->_ptr, p._ptr);
        return *this;
    }
    
    //---------------------------------------
    
    T & operator*(){
        return *(this->_ptr);
    }
    
    T *operator->(){
        return this->_ptr;
    }
    
    operator bool (){
        return this->_ptr;
    }
    
    T *get() const {
        return this->_ptr;
    }
    
    T *release(){
        T *pointer = this->_ptr;
        this->_ptr = nullptr;
        return pointer;
    }

    void reset (T *ptr) {
        //UniquePtr<T, Delete>().swap(*this);
        this->_ptr = ptr;
    }

    void swap(UniquePtr &p) {
        std::swap(this->_ptr, p._ptr);
    }
};

int main(int argc, char *argv[]){

    unique_ptr<int> p(new int(10));
    //unique_ptr<int> p1 = p; //编译不过的
    //unique_ptr<int> p2(p); //编译不过的
    cout << *p << endl;
    
    int *p3 = p.release();
    if(!p) cout << "p is released" << endl;

    cout << *p3 << endl;
    delete p3; //手动释放

    p = unique_ptr<int>(new int(11)); //移动赋值
    unique_ptr<int> p4(new int(12));
    p4.swap(p);
    cout << *p << endl;

    p.reset(new int(13));
    cout << *p << endl;

  return 0;
}

