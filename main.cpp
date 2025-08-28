#include <QCoreApplication>
#include "test.h"
#include <QScopedPointer>
#include <QSharedPointer>

Test* makeTree()
{
    Test* root = new Test(nullptr, "Root");

    for(int p = 0; p<5;p++)
    {
        Test* pobj = new Test(root, "Parent-" + QString::number(p));

        for (int c = 0; c< 3;c++)
        {
            Test* cobj = new Test(pobj, "Child-" + QString::number(p) +" " + QString::number(c));

            for (int s = 0; s< 3;s++)
            {
                Test* sobj = new Test(cobj, "Sub-" + QString::number(p) +" " + QString::number(c)+" " + QString::number(s));

            }

        }
    }
    return root;
}

void printTree(Test* root, int level =0)
{
    if (root ->children().length() ==0 ) return;

    QString lead = "-";
    lead.fill('-', level *5);

    foreach(QObject* obj, root->children())
    {
        Test* child = qobject_cast<Test*>(obj);
        if(!child) return;

        qInfo() << lead << child ;

        printTree(child, level +1);
    }
}

void testScPointer()
{
    QScopedPointer<Test> sp(new Test());
    sp->setObjectName("My Test");

    qInfo()<<"Scope Pointer "<< &sp;
    qInfo()<<"Pointer Data"<< sp.data();
    qInfo()<<sp->objectName();
}

QSharedPointer<Test> getObject(QString name)
{
    QSharedPointer<Test> sp(new Test());
    sp->setObjectName(name);

    return sp;
}

void doWork(QSharedPointer<Test> sp)
{
    qInfo()<<"Shared Pointer "<< &sp;
    qInfo()<<"Work"<< sp.data();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    //Test* tree = makeTree();
    //printTree(tree, 1);
    //delete tree;

    testScPointer();

    return a.exec();
}
