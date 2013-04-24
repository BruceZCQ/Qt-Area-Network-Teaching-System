#ifndef CONSTVAR_H
#define CONSTVAR_H
//port
#define TRANSFERDESKTOPCAPTURE 1030
#define TRANSFERQUESTION 1031
#define TRANSFERBROARDCAST 1032
//profile
#define WINX_OFFEST 10
#define TEACHER_ITEM  8000
#define STUDENT_ITEM 9000
#define CLASS_ITEM 9500
#define CHAPTER_ITEM 10000
#define QUESTION_ITEM 10001
#define STATUS_ON 0
#define STATUS_OFFLINE 1
//loginDialog
#define SYSPROMPT_SUCCESS tr("登录成功")
#define SYSPROMPT_SUCCESSMOREINFO tr("您已经成功登录到TeachingRoom")
#define SYSTEMPROMPT tr("系统提示")
#define SYSTEMERRORPROMPT tr("操作失败")
#define SYSTEMESUCCESSPROMPT tr("操作成功")
#define SYSTEMPROMPTMOREINFO tr("最小化窗体，双击显示主窗体.")
#define SYSTEMREFRESHPROMPT tr("数据已经变动,请手动'刷新操作'以得到最新数据.")
#define SHOWMAINWINACTION tr("显示/隐藏主窗口[&M]")
#define SHOWMESSAGEACTION tr("显示消息[&I]")
#define QUITACTION tr("退出[&Q]")
#define LOGOUTACTION tr("注销[&L]")
#define PASSWORDERRORPROMPT tr("密码错误提示")
#define PASSWORDFAILUREPROMPT tr("您的密码有误，请确认您的密码!")
#define PASSWORDEMPTY tr("密码为空提示")
#define PASSWORDEMPTYPROMPT tr("密码不能为空!")
#define SYSTOOLTIP tr("欢迎使用TeachingRoom,双击显示/隐藏主窗口/查看消息")
//mainwindow
#define IAMHERE tr("[在线]")
#define IAMNOTHERE tr("[离线]")
#define BCTOOLTIP tr("<font color='blue'>一句话广播</font>")
#define MESSAGEBOXTOOLTIP tr("<font color='blue'>消息盒子</font>")
#define SEARCHTOOLTIP tr("<font color='blue'>检索</font>")
#define FUNCTIONBOXTOOLTIP tr("<font color='blue'>功能盒子</font>")
#define ABOUTPROMPT tr("关于TeachingRoom")
#define ABOUTPROMPTMOREINFO tr(" Copyright(c)2012	cqlinux. Inc\n\
** Created: cqzhu <zcq.power@gmail.com>\n\
    ** Version: 0.1\n\
    This program is free software: you can redistribute it and/or modify\
    it under the terms of the GNU General Public License as published by\
    the Free Software Foundation, either version 3 of the License, or\
    any later version.\
    This program is distributed in the hope that it will be useful,\
    but WITHOUT ANY WARRANTY; without even the implied warranty of\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\
GNU General Public License for more details.\
You should have received a copy of the GNU General Public License\
along with this program.  If not, see <http://www.gnu.org/licenses/>.\n")
    //tooltip info
    #define IDENTITY tr("身份")
    #define STUDENTIDENTITY tr("学生")
    #define STUDENTID tr("学号")
    #define TEACHERIDENTITY tr("老师")
    #define COMEFROM tr("来自")
    //userContentMenu
    #define SENDQUESTIONTOUSER tr("向学生提问")
    #define VIEWSTUDENT tr("查看学生信息 ")
    #define DELETESTUDENT tr("从该班中移除学生")
    #define SETSTUDENTZEOR tr("把学生成绩置为0")
    #define STUDENTMANAGEMENT tr("学生管理器")
    //settingserverdialog
    #define SETTINGSERVERPROMPT tr("系统提示")
    #define SETTINGSERVERPROMPTMOREINFO tr("请先设置系统服务器地址和工作端口Port")
    //changePassworddialog
    #define CHANGEPASSWORDPROMPT tr("密码修改提示")
    #define CHANGEPASSWORDSUCCESSPROMPT tr("密码修改成功!")
    #define CHANGEPASSWORDFAILUREPROMPT tr("密码修改失败")
    //sendqutiondialog
    #define QUESTIONADDR tr("当前问题来源于:<b>")
    #define QUESTIONSCORE tr("  </b>当前问题分数：<b>")
    #define QUESTIONPUBLICDATE tr(" </b>当前问题发布时间:<b>")
    #define QUESTIONPUBLICDATEEND tr("</b>")
    #define QUESTIONID tr("问题ID>>>  ")
    #define QUESTIONDEC tr("<font size='4'><b>问题概述</b></font>:")
    #define QUESTIONCONTEXT tr("<font size='4'><b>问题内容</b></font>:")
    //manage class
    #define STUDENTCOUNTUNIT tr(" （人）")
    #define DELETECLASS tr("删除")
    #define DELETECLASSPROMPT tr("删除班级会把班级下面的所有学生一并删除！确定删除 >")
    //insert new class
    #define INSERTNEWCLASSPROMPT tr("班级添加提示")
    #define INSERTNEWCLASSSUCCESS tr("班级添加成功")
    #define INSERTNEWCLASSFAILURE tr("班级添加失败")
    #define CLASSDEFAULTNAME tr("计算机学院")
    //viewstudentinfo
    #define VIEWINFO tr("信息查看 - TeachingRoom")
    #define VIEWINFO_STATUS_ON tr("当前在线")
    #define VIEWINFO_STATUS_OFF tr("当前离线")
    //chat
    #define CHAT tr("即时消息 - TeachingRoom")
    #define CHATWITH tr("发送即使消息")
    //view question
    #define VIEWQUESTION tr("查看问题信息")
    #define SUBMITEDIT tr("提交修改")
    //create question
    #define INCOMPLETION tr("请把信息填写正确！")
    #define SELECTCHAPTER tr("请选择一个章节")

    //broadcast
    #define BROADCASTCONTENTISEMPTY tr("请先写好广播内容!")
    //SOCKET
    #define CONNECTSERVERFAILURE tr("服务器不可达!服务器不可达!请稍候再试!")
    #endif // CONSTVAR_H

