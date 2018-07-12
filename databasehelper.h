#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QList>
#include <QVariant>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlTableModel>
class databaseHelper
{

public:

    explicit databaseHelper(const QString& strDatabase = ".//autoUrineAnalysis.db");
        ~databaseHelper();

        bool createConnection(const QString& strConn);
        bool createTable();
        QSqlRecord ExecuteRecord(const QString& strQuery);
        QSqlRecord ExecuteRecord(const QString& strQuery, QList<QVariant> lstParameter);
        QSqlRecord ExecuteRecord(const QString& strQuery, QVariant Parameter);

        QSqlQuery ExecuteSqlQuery(const QString& strQuery, QList<QVariant> lstParameter);
        QSqlQuery ExecuteSqlQuery(const QString& strQuery, QVariant Parameter);
        QSqlQuery ExecuteSqlQuery(const QString& strQuery);

        int ExecuteInt(const QString& strQuery);
        int ExecuteInt(const QString& strQuery, QList<QVariant> lstParameter);
        int ExecuteInt(const QString& strQuery, QVariant Parameter);

        bool Execute(const QString& strQuery, QVariant Parameter);
        bool Execute(const QString& strQuery, QList<QVariant> lstParameter);

        QString ExecuteString(const QString& strQuery);

        void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery);
        void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery,
                               QList<QVariant> lstParameter);
        void ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery, QVariant Parameter);

        bool ExecuteTableModel(QSqlTableModel* pTableModel, QString tableName, QString tableFilter);

    private:
        QSqlDatabase m_db;
        QString m_strDatabase;
        bool bResult;

};

#endif // DATABASEHELPER_H
