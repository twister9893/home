#ifndef _GLNOTIFICATION_H_
#define _GLNOTIFICATION_H_

#include <list>
#include <stdio.h>
#include "glnote.h"
#include "animation.h"

class GlNotificationManager
{
public:
    GlNotificationManager(GLfloat windowWidth, GLfloat windowHeight)
        : m_windowWidth(windowWidth), m_windowHeight(windowHeight)
    {
        m_layout.SetLineLength(400);
        m_layout.SetLineSpacing(0.7);
    }

//    void setLayout(FTSimpleLayout *layout) {m_layout = layout;}
    void setNotePrototype(GlNote prototype) {m_notePrototype = prototype;}

    void process(uint noteTimeout)
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0,m_windowWidth,0.0,m_windowHeight,512,-512);
//        printf("Process with window %.2f x %.2f\n", m_windowWidth, m_windowHeight);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(20.0, 20.0, 0.0);

        for(std::list< std::pair<time_t,GlNote> >::iterator i=m_notes.begin(); i!=m_notes.end(); ++i)
        {
            timeval tv;
            gettimeofday(&tv,0);
            uint timeLeft = tv.tv_sec - (*i).first;

            GLfloat offset = (*i).second.getHeight()+10;
            if(timeLeft < noteTimeout)
            {
//                printf("main alpha %d\n", (*i).second.getMainAlpha());
                if((*i).second.getMainAlpha() < 240)
                    (*i).second.setMainAlpha((*i).second.getMainAlpha()+15);
                (*i).second.draw();
                glTranslatef(0.0, pow((*i).second.getMainAlpha(),0.3)*offset/pow(240.0,0.3), 0.0);
//                glTranslatef(0.0, offset, 0.0);
//                glTranslatef(0.0, m_anim.getValue(), 0.0);
            }
            else
            {
                if((*i).second.getMainAlpha() > 0)
                {
                    (*i).second.setMainAlpha((*i).second.getMainAlpha()-15);
                    (*i).second.draw();
                    glTranslatef(0.0, (*i).second.getHeight()+10, 0.0);
                }
                else
                {
                    --i;
                    m_notes.pop_back();
                }
            }
        }

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        glMatrixMode(GL_MODELVIEW);
    }

    void addNote(const char *text)
    {
        addNote(std::string(text));
    }
    void addNote(std::string text)
    {
        GlNote note = m_notePrototype;
        note.setViewport(m_windowWidth, m_windowHeight);
        note.setLayout(&m_layout);
        note.setText(text.c_str());
        note.setMainAlpha(0);
        timeval tv;
        gettimeofday(&tv,0);

//        GLfloat offset=0.0;
//        for(std::list< std::pair<time_t,GlNote> >::iterator i=m_notes.begin(); i!=m_notes.end(); --i)
//        {
//            offset += (*i).second.getHeight();
//        }
        m_notes.push_front(std::pair<time_t,GlNote>(tv.tv_sec,note));

//        m_anim.setFunction(Animation::Function_Bow);
//        m_anim.setMinValue(offset);
//        m_anim.setMaxValue(offset + note.getHeight());
//        m_anim.start(400, Animation::Mode_Increase);
    }

private:
//    Animation m_anim;
    FTSimpleLayout m_layout;

    GlNote m_notePrototype;
    std::list< std::pair<time_t,GlNote> > m_notes;
    GLfloat m_windowWidth, m_windowHeight;
};

#endif //_GLNOTIFICATION_H_
