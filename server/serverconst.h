#ifndef SERVERCONST_H
#define SERVERCONST_H

//port
#define TRANSFERDESKTOPCAPTURE 1030
#define TRANSFERQUESTION 1031
#define TRANSFERBROARDCAST 1032
//system emnu in login dialog check user info is incompletion
#define NAMEINFOINCOMPLETION 10
#define PASSWORDINFOINCOMPLETION 11
#define INFOCOMPLETION   12
//system prompt
#define SYSTEMPROMPT tr("系统提示")
//setting server host and port prompt
#define SETTINGSERVERPROMPT tr("请先设置系统服务器地址和工作端口Port")
//user info is incompletion from login dialog
#define INFOINCOMPLETIONPROMPT tr("信息填写还不完整哦!")
#define PASSWORDINCORRECT tr("密码错误!")
//dashboard
#define STUDENTCLASSINFOMAINTAIN tr("学生班级信息维护")
#define STUDENTCLASSINFOVIEW tr("学生班级信息查看")
#define STUENTCLASSINFOMANAGE tr("学生班级信息管理")
#define QUESTIONINFOMAINTAIN tr("问题信息维护")
#define QUESTIONINFOVIEW tr("问题信息查看")
#define QUESTIONANALYSIS tr("问题信息分析")
#define COURSEINFOMAINTAIN tr("课件信息维护")
#define COURSEINFOVIEW tr("课件信息查看")
#define COURSEINFOANALYSIS tr("课件信息分析")
#define DATABASEINFO tr("数据库信息")
#define SYSTEMSETTING tr("系统设置")
#define BROADCASTINFO tr("广播信息")
//treewidget item
#define STUDENT_ITEM 9000
#define CLASS_ITEM 9500
#define CHAPTER_ITEM 10000
#define QUESTION_ITEM 10001
#define CLASSCOUNTUNIT tr("人") //unused
//student class maintain
#define ALLSTUDENTS tr("ALL")//unused
#define TABLEWIDGETITEMROW 0
#define TABLEWIDGETITEMWIDTH 50
#define EDITCLASSINFOTITLE tr("<center><span style=' font-size:48pt;'>班级编辑</span></center>")
#define ADDCLASSINFOTITLE tr("<center><span style=' font-size:48pt;'>新建班级信息</span></center>")
#define NEWCLASSNAME tr("计算机学院")
#define NEWCLASSCOUNT 30
#endif // SERVERCONST_H
