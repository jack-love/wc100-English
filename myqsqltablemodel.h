#ifndef MYQSQLTABLEMODEL_H
#define MYQSQLTABLEMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QModelIndex>
#include <qdebug.h>
#include <qcolor.h>

class myQSqlTableModel : public QSqlTableModel
{

Q_OBJECT
public:

 myQSqlTableModel(QObject * parent = 0, QSqlDatabase db = QSqlDatabase());
 ~myQSqlTableModel();
 QVariant data(const QModelIndex & index, int role = Qt::DisplayRole)const;


};

#endif
