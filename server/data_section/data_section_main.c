# include "data_section_main.h"

EOC add_msg(const wchar_t* zFromUser, const wchar_t* zToUser, const wchar_t* zMsg, int* pMsgId)
{
    PRINTW(L"[add_msg]")
}

EOC del_msg(const int nMsgId)
{
    PRINTW(L"[del_msg]")
}

EOC get_msg(const int nMsgId)
{
    PRINTW(L"[get_msg]")
}

EOC get_msg_from(const wchar_t* zUser,const wchar_t** pzMsg, const int nMsgMaxCount, int* pMsgCount)
{
    PRINTW(L"[get_msg_from]")
}