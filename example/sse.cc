//
//  sse.cc
//
//  Copyright (c) 2020 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <httplib.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace httplib;
using namespace std;

/*
class EventDispatcher {
public:
  void add_sink(DataSink* sink) {
    unique_lock<mutex> lk(m_);
    cv_.wait(lk, []{ return !message_.empty(); });
    if (sink.is_writable()) {
      sink.write(message_.data(), message_.size());
    }
  }

  void send_event(const string& message) {
    {
      lock_guard<mutex> lk(m_);
      message_ = message;
      cv_.notify_all();
    }
    message_.clear();
  }

private:
  mutex m_;
  condition_variable cv_;
  string message_;
};
*/

int main(void) {
  // EventDispatcher evd;

  Server svr;
  svr.set_base_dir("./www");
  svr.Get("/event", [&](const Request & /*req*/, Response &res) {
    cout << "connected..." << endl;
    res.set_header("Content-Type", "text/event-stream");
    res.set_chunked_content_provider([&](uint64_t /*offset*/, DataSink &sink) {
      // evd.add_sink(&sink);
      this_thread::sleep_for(chrono::seconds(3));
      string message = "data: hello\n\n";
      sink.write(message.data(), message.size());
    });
  });

  svr.listen("localhost", 1234);
}
