#ifndef BUFFERED_LINKED_LIST_H
#define BUFFERED_LINKED_LIST_H

#include <opencv2/opencv.hpp>
#include <list>
#include <mutex>
#include <condition_variable>

class BufferedLinkedList {
public:
    BufferedLinkedList(size_t maxSize);

    // Add an image to the end of the list
    bool enqueue(const cv::Mat &image);

    // Remove and return the first image from the list
    cv::Mat dequeue();

private:
    std::list<cv::Mat> buffer;
    size_t maxSize;

    std::mutex mutex;
    std::condition_variable dataAvailable;
    std::condition_variable spaceAvailable;
};

#endif  // BUFFERED_LINKED_LIST_H
