#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <vector>
#include <queue>
#include <thread>
#include <map>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include "buffer.h"
#include "joined_threads.h"
#include "job.h"

class ThreadPool
{
private:
	enum {THREADS_PER_CPU = 10,
		  MAX_RANGE = 20,};

	int threads_per_cpu = THREADS_PER_CPU;
	int max_range = MAX_RANGE;

	std::atomic_bool works_run;
	std::deque<Job> works_queue;
	std::mutex works_queue_mutex;
	std::vector<std::thread> works_threads;
	JoinedThreads works_threads_joiner;

	std::map<std::thread::id, Buffer> buffers;

	std::unique_ptr<std::thread> puller;
	JoinedThread puller_joiner;
	bool puller_run;

	/* works_threads's procedure */
	void worker_thread();

	/* puller procedure */
	void pull();
	
	/* sender procedure */
	void send(std::vector<int> &data);

	void collect_data_and_send();
	bool do_jobs();

public:
	ThreadPool();
	~ThreadPool();
	
	void start_job(int low, int high);
	
	void show();
};

#endif //__THREAD_POOL_H__
