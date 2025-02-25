#ifndef SIMPLE_FIFO_H
#define SIMPLE_FIFO_H

#include <systemc>
#include <queue>

// A First-In-First-Out (FIFO) buffer that synchronizes
// communication between producers and consumers.
// This implementation uses blocking semantics: the producer
// waits if the FIFO is full, and the consumer waits if it's empty.
class SimpleFifo : public sc_core::sc_interface
{
public:
    // Constructor to initialize FIFO with max depth (max elements to hold)
    SimpleFifo(unsigned int maxDepth) : m_maxDepth(maxDepth) {}


    // Blocking read: reads and removes oldest element
    virtual unsigned int read()
    {
        while (m_queue.empty())
        {
            wait(m_dataAvailableEvent);
        }
        // Retrieve and remove (pop) front element (oldest data)
        unsigned int value = m_queue.front();
        m_queue.pop();

        // Notify writers of available space
        m_spaceAvailableEvent.notify();
        return value;
    }

    // Blocking write
    virtual void write(unsigned int val)
    {
        // Block if FIFO is full until space is available
        while (m_queue.size() >= m_maxDepth)
        {
            wait(m_spaceAvailableEvent);
        }
        // Add the new element to the queue, notify readers of new data
        m_queue.push(val);
        m_dataAvailableEvent.notify();
    }

    // Default event: Provides access to the data available event so that
    // other modules can react when data is written.
    virtual const sc_core::sc_event& default_event() const
    {
        return m_dataAvailableEvent;
    }

private:
    // Internal FIFO storage using a standard queue
    std::queue<unsigned int> m_queue;

    unsigned int m_maxDepth;
    sc_core::sc_event m_dataAvailableEvent; // readers wait on this
    sc_core::sc_event m_spaceAvailableEvent; // writers wait on this
};

#endif // SIMPLE_FIFO_H