#include <QDebug>

void Parsing(QString message){
    QList<QString> parts = message.split('&');
    qDebug() << parts[0];
    if(parts[0] == "sort"){
        if (parts.length() != 3) {
            qDebug() << "error";
        } else {
            int step = parts[1].toInt();
            QString mas = parts[2];

        }
    }
}



