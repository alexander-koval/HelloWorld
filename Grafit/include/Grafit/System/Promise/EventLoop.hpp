#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP

#include <vector>
#include <queue>
#include <functional>

namespace gf {
class EventLoop
{
using Fn = std::function<void()>;
using Queue = std::vector<std::function<void()>>;
public:
    static void enqueue(Fn&& eqf);

    static std::size_t size();

    static void clear();

    static void update(float dt);
private:
    EventLoop() = delete;

private:
    static Queue queue;
};
}
#endif
