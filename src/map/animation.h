#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
//#include <stdio.h>

class Animation
{
public:
//    enum Mode
//    {
//        Mode_Increase=0,
//        Mode_Decrease
//    };
    enum Function
    {
        Function_Linear=0,
        Function_Log,
        Function_Exp,
        Function_Circle,
        Function_Sin,
        Function_Bow
    };
    enum State
    {
        State_NotStarted=0,
        State_Started,
        State_Finished
    };

    Animation() : m_func(Function_Linear), m_startTime(0), m_startTimeMs(0), m_begValue(0), m_endValue(0), m_curValue(0), m_state(State_NotStarted) {}
    Animation(Function func) : m_func(func), m_startTime(0), m_startTimeMs(0), m_begValue(0), m_endValue(0), m_curValue(0), m_state(State_NotStarted) {}
    Animation(Function func, double beg, double end) : m_func(func), m_startTime(0), m_startTimeMs(0), m_begValue(beg), m_endValue(end), m_curValue(0), m_state(State_NotStarted) {}

    void setFunction(Function func) {m_func = func; reset();}
    void setBegValue(double val) {m_begValue = val;/* reset();*/}
    void setEndValue(double val) {m_endValue = val;/* reset();*/}

    double getValue()
    {
        uint timeLeft = getTimeLeft();
        if(timeLeft > m_duration)
            return m_endValue;

        double valProgress=0.0;
        double timeProgress=(double)timeLeft / (double)m_duration;
        switch(m_func)
        {
        case Function_Linear:
        {
            valProgress = timeProgress;
            break;
        }
        case Function_Log:
        {
            double maxX = 200.0;
            double curX = timeProgress*maxX + 1.0;
            valProgress = log10(pow(curX,1.0/10.0))/log10(pow(maxX+1,1.0/10.0));
            break;
        }
        case Function_Exp:
        {
            double maxX = 3.0;
            double curX = timeProgress*maxX + 1.0;
            valProgress = exp(curX)/exp(maxX+1);
            break;
        }
        case Function_Circle:
        {
            double maxX = 100.0;
            double curX = timeProgress*maxX;
            valProgress = sqrt(1-pow(curX-maxX,2)/pow(maxX,2));
            break;
        }
        case Function_Sin:
        {
            double maxX = M_PI_4;
            double curX = timeProgress*maxX;
            valProgress = sin(curX)/sin(maxX);
            break;
        }
        case Function_Bow:
        {
            double bowFactor = 0.0;
            double maxX = 1.0;
            double curX = timeProgress*maxX;
            valProgress = (-pow(curX-1,2)*(-(bowFactor+1)*(curX-1)-bowFactor)+1) / (-pow(maxX-1,2)*(-(bowFactor+1)*(maxX-1)-bowFactor)+1);
            break;
        }
        default:
            puts("animation.h getValue function ERROR: unknown animation function, use Function enum");
            break;
        }
        m_curValue = m_begValue+(m_endValue-m_begValue)*valProgress;
        return m_curValue;
    }

    void start(uint time) //msec
    {
        m_duration = time;
        timeval tv;
        gettimeofday(&tv,0);
        m_startTime = tv.tv_sec;
        m_startTimeMs = tv.tv_usec / 1000;
        m_state=State_Started;
    }

    State getState()
    {
        if(getTimeLeft() > m_duration)
            m_state=State_Finished;
        return m_state;
    }
//    Mode getMode() {return m_mode;}

private:
    void reset()
    {
        m_startTime = 0.0;
        m_startTimeMs = 0.0;
        m_curValue = m_begValue;
        m_state=State_NotStarted;
    }
    uint getTimeLeft()
    {
        if(m_state == State_Started)
        {
            timeval tv;
            gettimeofday(&tv,0);
            uint timeLeft = (tv.tv_sec - m_startTime)*1000 + (tv.tv_usec / 1000 - m_startTimeMs);
            return timeLeft;
        }
        else
            return 0;
    }

//    Mode m_mode;
    Function m_func;
    uint m_duration; //msec
    uint m_startTime; //sec
    uint m_startTimeMs; //msec

    double m_begValue;
    double m_endValue;
    double m_curValue;

    State m_state;
};

#endif //_ANIMATION_H_
