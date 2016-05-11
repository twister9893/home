#ifndef _ABSTRACTPRIMARY_H_
#define _ABSTRACTPRIMARY_H_

class AbstractPrimary {
public:
    void setSize(uint pelengCount, uint discretCount);

    unsigned char** getData() {
        return m_data;
    }

    int update() {
        unsigned char *discrets = (unsigned char*)malloc(m_discretCount);
        int peleng = listen(m_port, discrets);
        if(peleng>=0)
            memcpy(m_data[peleng], discrets, m_discretCount);
        free(discrets);
        return peleng;
    }

protected:
    virtual int listen(int port, unsigned char *discrets)=0;

private:
    int m_port;
    uint m_pelengCount;
    uint m_discretCount;
    unsigned char *m_data[];
};


class PrimaryManager {
public:
    void process();
};

#endif //_ABSTRACTPRIMARY_H_
