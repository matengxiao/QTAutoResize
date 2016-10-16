#include "autoresize.h"
#include <QLabel>
#include <QMapIterator>
#include <QObject>
#include <QDebug>
#include <QComboBox>
#include <QLineEdit>

AutoResize::AutoResize(QWidget* obj,float base_width,float base_height):m_autoResizeObj(obj)
{
        m_autoResize=false;
        m_baseWidth=base_width;
        m_baseHeight=base_height;
        m_horRatio=1.0;
        m_verRatio=1.0;
        m_fontRatio=1.0;
}


AutoResize::~AutoResize(void)
{
}

void AutoResize::pushAllResizeItem()
{
        qDebug()<<"get item start";
        QWidget *item=NULL;
        AutoResizeOriginalData resizeData;
        QRect tmp;
        //add other items
        for(auto it=m_otherItem.begin();it!=m_otherItem.end();it++)
        {
                qDebug()<<*it;
                item=*it;
                tmp=item->geometry();
                tmp.setX(item->x());
                tmp.setY(item->y());
                tmp.setWidth(abs(tmp.width()));
                tmp.setHeight(abs(tmp.height()));
                resizeData.data_rect=tmp;
                resizeData.data_font=item->font();
                m_resizeMap[item]=resizeData;
        }
        if(m_autoResizeFlag&INCLUDE_LABEL)
        {
                QList<QLabel*> _labelList=m_autoResizeObj->findChildren<QLabel *>();
                for(auto it=_labelList.begin();it!=_labelList.end();it++)
                {
                        item=*it;
                        tmp=item->geometry();
                        tmp.setX(item->x());
                        tmp.setY(item->y());
                        tmp.setWidth(abs(tmp.width()));
                        tmp.setHeight(abs(tmp.height()));
                        qDebug()<<tmp;
                        resizeData.data_rect=tmp;
                        resizeData.data_font=item->font();
                        m_resizeMap[item]=resizeData;
                }
        }
        if(m_autoResizeFlag&INCLUDE_COMBOBOX)
        {
                QList<QComboBox*> _comboxList=m_autoResizeObj->findChildren<QComboBox *>();
                for(auto it=_comboxList.begin();it!=_comboxList.end();it++)
                {
                        item=*it;
                        tmp=item->geometry();
                        tmp.setX(item->x());
                        tmp.setY(item->y());
                        tmp.setWidth(abs(tmp.width()));
                        tmp.setHeight(abs(tmp.height()));
                        resizeData.data_rect=tmp;
                        resizeData.data_font=item->font();
                        m_resizeMap[item]=resizeData;
                }
        }
        if(m_autoResizeFlag&INCLUDE_BUTTON)
        {
                qDebug()<<"button added";
                QList<QAbstractButton*> _buttonList=m_autoResizeObj->findChildren<QAbstractButton*>();
                for(auto it=_buttonList.begin();it!=_buttonList.end();it++)
                {
                        qDebug()<<*it;
                        item=*it;
                        tmp=item->geometry();
                        tmp.setX(item->x());
                        tmp.setY(item->y());
                        tmp.setWidth(abs(tmp.width()));
                        tmp.setHeight(abs(tmp.height()));
                        qDebug()<<tmp;
                        resizeData.data_rect=tmp;
                        resizeData.data_font=item->font();
                        m_resizeMap[item]=resizeData;
                }
        }
        if(m_autoResizeFlag&INCLUDE_EDITOR)
        {
                qDebug()<<"editor";
                QList<QLineEdit*> _editorList=m_autoResizeObj->findChildren<QLineEdit*>();
                for(auto it=_editorList.begin();it!=_editorList.end();it++)
                {
                        item=*it;
                        tmp=item->geometry();
                        tmp.setX(item->x());
                        tmp.setY(item->y());
                        tmp.setWidth(abs(tmp.width()));
                        tmp.setHeight(abs(tmp.height()));
                        resizeData.data_rect=tmp;
                        resizeData.data_font=item->font();
                        m_resizeMap[item]=resizeData;
                }
        }
        for(auto it=m_ignoreItem.begin();it!=m_ignoreItem.end();it++)
        {
                if(m_resizeMap.contains(*it))
                        m_resizeMap.remove(*it);
        }
        m_autoResize=true;
}

void AutoResize::calculateResizeRatio()
{
        m_horRatio=m_autoResizeObj->width()/m_baseWidth;
        m_verRatio=m_autoResizeObj->height()/m_baseHeight;\
        m_fontRatio=m_horRatio>m_verRatio?m_horRatio:m_verRatio;
        qDebug()<<m_horRatio;
        qDebug()<<m_verRatio;
}

void AutoResize::addOtherItem(QWidget *other)
{
        m_otherItem.push_back(other);
}

void AutoResize::addIgnoreItem(QWidget *ignore)
{
        m_ignoreItem.push_back(ignore);
}

void AutoResize::setAutoResizeFlag(int flag)
{
        m_autoResizeFlag=flag;
}

void AutoResize::doAutoResize()
{
        calculateResizeRatio();
        if(m_autoResize)
        {
                qDebug()<<"resizevent";
                QMapIterator<QWidget*, AutoResizeOriginalData> _itarator(m_resizeMap);
                QFont changedFont;
                while(_itarator.hasNext())
                {
                        _itarator.next();
                        QWidget* _item=_itarator.key();
                        QRect tmp=_itarator.value().data_rect;
                        tmp.setWidth(tmp.width()*m_horRatio);
                        tmp.setHeight(tmp.height()*m_verRatio);
                        QRect after=QRect(tmp.x()*m_horRatio,tmp.y()*m_verRatio,tmp.width(),tmp.height());
                        //changed font
                        changedFont=_itarator.value().data_font;
                        qDebug()<<changedFont;
                        changedFont.setPointSize(changedFont.pointSize()*m_fontRatio);
                        qDebug()<<"changed"<<changedFont;
                        _item->setFont(changedFont);
                         qDebug()<<_item->font();
                        _item->setGeometry(after);
                }
        }
}
