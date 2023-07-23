#include<mutex>
#include<condition_variable>
#include<queue>
/// <summary>
/// 消息队列
/// </summary>
/// <typeparam name="T">消息类型</typeparam>
template<class T> class MessageQueue {
public:
	/// <summary>
	/// 推入消息
	/// </summary>
	/// <param name="msg">消息对象</param>
	void push(const T& msg) {
		std::unique_lock<std::mutex>lck(_mtx);
		_queue.push(msg);
		_cv.notify_one();
	}
	/// <summary>
	/// 轮询消息
	/// </summary>
	/// <param name="msg">消息对象</param>
	/// <returns>是否接收到消息</returns>
	bool poll(T& msg) {
		std::unique_lock<std::mutex>lck(_mtx);
		if (_queue.size())
		{
			msg = _queue.front();
			_queue.pop();
			return true;
		}
		return false;
	}
	/// <summary>
	/// 等待消息
	/// </summary>
	/// <param name="msg">消息对象</param>
	void wait(T& msg) {
		std::unique_lock<std::mutex>lck(_mtx);
		while (!_queue.size()) _cv.wait(lck);
		msg = _queue.front();
		_queue.pop();
	}
	//队列长度
	size_t size() {
		std::unique_lock<std::mutex>lck(_mtx);
		return _queue.size();
	}
private:
	//队列
	std::queue<T> _queue;
	//互斥变量
	std::mutex _mtx;
	//条件变量
	std::condition_variable _cv;
};



#include<thread>
//自定义消息对象
class MyMessage {
public:
	int type;
	void* param1;
	void* param2;
};
int main(int argc, char* argv[])
{
	//初始化消息队列
	MessageQueue<MyMessage> mq;
	//启动线程
	std::thread t1([&]() {
		MyMessage msg;
		while (1) {
			//等待队列的消息
			mq.wait(msg);
			printf("receive message type:%d\n", msg.type);
			if (msg.type == 1001)
				break;
		}
		printf("thread exited\n");
		});
	//发送消息给线程
	MyMessage msg;
	printf("send number message to thread.1001 exit\n");
	while (1)
	{
		scanf("%d", &msg.type);
		mq.push(msg);
		if (msg.type == 1001)
			break;
	}
	t1.join();
	return 0;
}


#include<thread>
//自定义消息对象
class MyMessage {
public:
	int type;
	void* param1;
	void* param2;
};
int main(int argc, char* argv[])
{
	//初始化消息队列
	MessageQueue<MyMessage> mq;
	//启动线程
	std::thread t1([&]() {
		MyMessage msg;
		while (1) {
			//轮询队列的消息
			if (mq.poll(msg))
			{
				printf("receive message type:%d\n", msg.type);
				if (msg.type == 1001)
					break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		printf("thread exited\n");
		});
	//发送消息给线程
	MyMessage msg;
	printf("send number message to thread.1001 exit\n");
	while (1)
	{
		scanf("%d", &msg.type);
		mq.push(msg);
		if (msg.type == 1001)
			break;
	}
	t1.join();
	return 0;
}
