#include <Grafit/System/Promise/EventLoop.hpp>

namespace gf {

EventLoop::Queue EventLoop::queue = EventLoop::Queue();

void EventLoop::enqueue(Fn&& eqf) {
    queue.push_back(std::move(eqf));
}

std::size_t EventLoop::size() {
    return queue.size();
}

void EventLoop::clear() {
    Queue empty;
    std::swap(queue, empty);
}

void EventLoop::update(float dt) {
    if (!queue.empty()) {
        const Fn& fn = queue.front();
        if (fn) { fn(); }
        queue.erase(queue.begin());
    }
}

}
