#include "BufferedLinkedList.h"

BufferedLinkedList::BufferedLinkedList(size_t maxSize) : maxSize(maxSize) {}

bool BufferedLinkedList::enqueue(const cv::Mat &image) {
    std::unique_lock<std::mutex> lock(mutex);

    // Wait if the buffer is full
    spaceAvailable.wait(lock, [this]() { return buffer.size() < maxSize; });

    buffer.push_back(image);
    dataAvailable.notify_one();
    return true;
}

cv::Mat BufferedLinkedList::dequeue() {
    std::unique_lock<std::mutex> lock(mutex);

    // Wait if the buffer is empty
    dataAvailable.wait(lock, [this]() { return !buffer.empty(); });

    cv::Mat image = buffer.front();
    buffer.pop_front();
    spaceAvailable.notify_one();
    return image;
}
