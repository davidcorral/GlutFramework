#include <chrono>

namespace glutframework
{

class Timer
{
private:
    typedef std::chrono::high_resolution_clock clock_type;
    typedef clock_type::time_point time_point;
    //typedef std::chrono::duration_cast<std::chrono::milliseconds> duration_cast;
public:
    
    Timer(): m_stopped(true)
    {
        // m_start = 0; //TODO
    };

    void start()
    {
        m_start = clock_type::now();
        m_stopped = false;
    };
    
    int end()
    {
        time_point m_end  = clock_type::now();
        int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count();      
        m_stopped = true;
        return elapsed;
    };
    
    bool isStopped() const
    {
        return m_stopped;
    };

private:    
    time_point m_start;
    bool m_stopped;

}; // end class Timer

};