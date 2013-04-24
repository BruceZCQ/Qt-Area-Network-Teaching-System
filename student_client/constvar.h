#ifndef CONSTVAR_H
#define CONSTVAR_H
//profile
#define WINX_OFFEST 10
#define TEACHER_ITEM  8000
#define STUDENT_ITEM 9000
#define STATUS_ON 0
#define STATUS_OFFLINE 1
//port
#define TRANSFERDESKTOPCAPTURE 1030
#define TRANSFERQUESTION 1031
#define TRANSFERBROARDCAST 1032
//loginDialog
#define SYSPROMPT_SUCCESS tr("登录成功")
#define SYSPROMPT_SUCCESSMOREINFO tr("您已经成功登录到TeachingRoom")
#define SYSTEMPROMPT tr("系统提示")
#define SYSTEMPROMPTMOREINFO tr("最小化窗体，双击显示主窗体.")
#define SHOWMAINWINACTION   tr("显示/隐藏主窗口[&M]")
#define SHOWMESSAGEACTION    tr("显示消息[&I]")
#define QUITACTION  tr("退出[&Q]")
#define LOGOUTACTION    tr("注销[&L]")
//settingserverdialog
#define SETTINGSERVERPROMPT tr("系统提示")
#define SETTINGSERVERPROMPTMOREINFO tr("请先设置系统服务器地址和工作端口Port的哦")
//register prompt
#define REGISTERSUCCESSPROMPT tr("注册成功了!已为您登录到系统了")
#define REGISTERFAILURELPROMPT tr("注册失败了!请检查您的信息是否填写正确")
#define UPDATESTATUSFAILUREPROMPT tr("状态信息更新失败了，请手动登录已更新状态信息!")
#define LOGOUTUPDATESTATUSFAILUREPROMPT  tr("状态信息更新失败了，请稍后再试!")
#define INFOCANNOTOVER tr("请将您的信息填写完整!")
//login
#define LOGINFAILURE tr("登录失败了，请检查您的帐号信息是否正确!")
//window
#define     TASKBAR         "Shell_TrayWnd")   	// Taskbar class name
#define     ID_STARTBUTTON  0x130				// Start button ID
//coding
#define    CANRUN  tr("您现在可以看看效果了哦!")
#define CANCLEAR tr("清除所有")
#define CANVIEWJAVACODE tr("您现在查看查看最新的Java代码了哦!")
#define CANSEACHER  tr("您现在查找了哦!")
#define STARTSERVER tr("请先启动服务器!")
#define SHOULDSAVETOSERVERPATH tr("您不保存到Tomcat的Workhome怎么看到效果呢!")
//question
#define ANSWERQUESTIONID tr("您需要完成的问题的ID是")
//questio  exercise
#define STARTQUESTION tr("开始答题")
#define STOPQUESTION tr("结束答题")
//dashboard
#define BROADCAST tr("<font  color='red'>广播消息</font><br/>")
#define RECEIEVEQUESTION tr("<span style='color:white'>\
<font color='red'>您收到一个即时问题</font><br/>请在指定时间内完成!</span>")

//SOCKET
#define CONNECTSERVERFAILURE tr("服务器不可达!请稍候再试!")
#define HELP tr("<font color='white'><table><tr><td>Dashboard:  </td></tr>\
<tr><td>Ctrl+F 回到Dashboard </td></tr ></table></font>")
   #endif // CONSTVAR_H

