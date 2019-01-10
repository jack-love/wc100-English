#include "myqsqltablemodel.h"
#include <QModelIndex>
#include <qcolor.h>
#include <QDebug>



myQSqlTableModel::myQSqlTableModel(QObject * parent, QSqlDatabase db) : QSqlTableModel(parent,db)
{

}

myQSqlTableModel::~myQSqlTableModel()
{

}

QVariant myQSqlTableModel::data(const QModelIndex &index, int role) const
{
    QVariant value  = QSqlTableModel::data(index,role);
   // QRgb rgb = QColor::fromRgb(255,255,0).rgba();

       if(Qt::TextAlignmentRole == role)
       {
           value   = int(Qt::AlignCenter | Qt::AlignHCenter);
           return value;
       }

//       if(Qt::ForegroundRole == role)//设置第三行字颜色
//       {
//           if(3 == index.row())
//               return QVariant(QColor(255,144,144));
//       }


       else if(role == Qt::BackgroundColorRole )//设置11行背景颜色
       {

           if(index.row()%11 == 0){
                       //return QColor(rgb);//rgbrgb颜色传递
               return QColor(Qt::gray);

           }

//           else if(index.row()%5 == 1){//设置其它行背景颜色
//                    qDebug()<<"data--2->"<<index.row();
//                       return QColor(Qt::green);
//           }
//           else if(index.row()%5 == 2)
//                       return QColor(Qt::blue);
//           else if(index.row()%5 == 3)
//                       return QColor(Qt::yellow);
//           else if(index.row()%5 == 4)
//                       return QColor(Qt::gray);
             else  return QVariant();
       }

       return value;
}
