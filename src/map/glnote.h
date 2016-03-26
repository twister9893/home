#ifndef _GLNOTE_H_
#define _GLNOTE_H_

#include "GL/gl.h"
#include <FTGL/ftgl.h>
#include <string>

class GlNote
{
public:
    GlNote() :  m_textR(m_defaultTextR), m_textG(m_defaultTextG), m_textB(m_defaultTextB), m_textA(m_defaultTextA),
                m_backR(m_defaultBackR), m_backG(m_defaultBackG), m_backB(m_defaultBackB), m_backA(m_defaultBackA), m_mainAlpha(m_defaultMainAlpha),
                m_windowWidth(0), m_windowHeight(0), m_layout(0), m_font(0)
    {}
    GlNote(GLfloat windowWidth, GLfloat windowHeight) :  m_textR(m_defaultTextR), m_textG(m_defaultTextG), m_textB(m_defaultTextB), m_textA(m_defaultTextA),
                m_backR(m_defaultBackR), m_backG(m_defaultBackG), m_backB(m_defaultBackB), m_backA(m_defaultBackA), m_mainAlpha(m_defaultMainAlpha),
                m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_layout(0), m_font(0)
    {}
    GlNote(GLfloat windowWidth, GLfloat windowHeight, const char *text) :  m_textR(m_defaultTextR), m_textG(m_defaultTextG), m_textB(m_defaultTextB), m_textA(m_defaultTextA),
                                m_backR(m_defaultBackR), m_backG(m_defaultBackG), m_backB(m_defaultBackB), m_backA(m_defaultBackA), m_mainAlpha(m_defaultMainAlpha),
                                m_text(text), m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_layout(0)/*, m_font(0)*/
    {}

    void setViewport(GLfloat width, GLfloat height) {m_windowWidth=width; m_windowHeight=height;}
    void setLayout(FTSimpleLayout *layout)
    {
        if(!layout)
            return;
        m_layout = layout;
        if(m_font && !m_layout->GetFont())
//            m_layout->SetFont(fontNote);
            m_layout->SetFont(m_font);

    }
    void setFont(const char *fileName, uint size)
    {
        m_font = new FTTextureFont(fileName);
        if(m_font->Error())
        {
            printf("Error open font %s\n",fileName);
            return;
        }
        if(!m_font->FaceSize(size))
        {
            puts("Error set font size\n");
            return;
        }
    }
//    void setFont(FTFont *font) {m_font = font;}

    void setText(const char *text) {m_text = text;}
    void setText(std::string text) {m_text = text;}
    void setTextColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a=255) {m_textR=r; m_textG=g; m_textB=b; m_textA=a;}
    void setBackColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a=255) {m_backR=r; m_backG=g; m_backB=b; m_backA=a;}
    void setMainAlpha(GLubyte a) {m_mainAlpha = a;}

    const char* getText() {return m_text.c_str();}

    GLubyte getTextR() {return m_textR;}
    GLubyte getTextG() {return m_textG;}
    GLubyte getTextB() {return m_textB;}
    GLubyte getTextA() {return m_textA;}

    GLubyte getBackR() {return m_backR;}
    GLubyte getBackG() {return m_backG;}
    GLubyte getBackB() {return m_backB;}
    GLubyte getBackA() {return m_backA;}

    GLubyte getMainAlpha() {return m_mainAlpha;}

    GLfloat getWidth()
    {
        if(m_text.empty())
            return 0.0;
        return m_layout->BBox(m_text.c_str()).Upper().Xf() - m_layout->BBox(m_text.c_str()).Lower().Xf() + m_margin*2;
    }

    GLfloat getHeight()
    {
        if(m_text.empty())
            return 0.0;
        return m_layout->BBox(m_text.c_str()).Upper().Yf() - m_layout->BBox(m_text.c_str()).Lower().Yf() + m_margin*2;
    }

    void draw()
    {
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//        printf("BOX SIZE: %.2f %.2f\n", getWidth(), getHeight());
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(pow((GLfloat)m_mainAlpha, 0.3)/pow(240.0, 0.3),pow((GLfloat)m_mainAlpha, 0.3)/pow(240.0, 0.3),1.0);
        glRotatef(pow((GLfloat)m_mainAlpha, 0.5)*90/pow(240.0, 0.5) -90.0, 1,1,0);

        glColor4ub(m_backR, m_backG, m_backB, (GLubyte)(m_backA*((GLfloat)m_mainAlpha/255)));
//        glColor4ub(0,0,0,150);
        glBegin(GL_QUADS);
        glVertex2f(0.0,0.0);
        glVertex2f(0.0, getHeight());
        glVertex2f(getWidth(),getHeight());
        glVertex2f(getWidth(),0.0);
//        glVertex2f(0.0, 24.0);
//        glVertex2f(150.0, 24.0);
//        glVertex2f(150.0, 0.0);
        glEnd();

        glTranslatef(m_margin, m_margin, 0.0);
//        glTranslatef(5,5,0.0);
//        printf("main alpha %d\n", (GLubyte)(m_textA*((GLfloat)m_mainAlpha/255)));
        glColor4ub(m_textR, m_textG, m_textB, (GLubyte)(m_textA*((GLfloat)m_mainAlpha/255)));
//        glColor4ub(255,255,255,100);

//        printf("font: %d\n", m_layout->GetFont());
        m_layout->Render(m_text.c_str());
//        m_layout->Render("eeetttt");
        //layoutNote.Render(m_text.c_str());
//        layoutNote.Render("eeerrr");

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

//        glDisable(GL_BLEND);
    }

private:
    FTSimpleLayout *m_layout;
    FTFont* m_font;

    GLfloat m_windowWidth, m_windowHeight;

    std::string m_text;

    GLubyte m_textR, m_textG, m_textB, m_textA;
    GLubyte m_backR, m_backG, m_backB, m_backA;
    GLubyte m_mainAlpha;

    static const GLubyte m_defaultTextR=255, m_defaultTextG=255, m_defaultTextB=255, m_defaultTextA=255;
    static const GLubyte m_defaultBackR=0, m_defaultBackG=0, m_defaultBackB=0, m_defaultBackA=150;
    static const GLubyte m_defaultMainAlpha=255;

    static const GLfloat m_margin = 5.0;
};

#endif //_GLNOTE_H_
