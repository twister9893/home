#ifndef SINGLETON_H
#define SINGLETON_H

template<class T>
class Singleton {
    Singleton();
public:
    T* instance() {
		if(m_instance == 0)
			m_instance = new T;
		return m_instance;
	}

private:
    T *m_instance;
};

#endif // SINGLETON_H
